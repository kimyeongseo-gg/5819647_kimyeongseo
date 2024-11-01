#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */

typedef struct Node {
    int vertex;       // ���� ��ȣ
    int weight;      // ����ġ
    struct Node* next; // ���� ���
} Node;

typedef struct GraphType {
    int n;           // ������ ����
    Node* adjList[MAX_VERTICES]; // ���� ����Ʈ
} GraphType;

int distance[MAX_VERTICES]; /* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES];     /* �湮�� ���� ǥ�� */
int foundOrder[MAX_VERTICES]; // �湮�� ���� ���� ����
int orderIndex = 0; // �湮 ���� �ε���

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void insert_edge(GraphType* g, int u, int v, int w) {
    Node* newNode = createNode(v, w);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;

    newNode = createNode(u, w); // ���� �׷����̹Ƿ� ���ʿ� �߰�
    newNode->next = g->adjList[v];
    g->adjList[v] = newNode;
}

int choose(int distance[], int n, int found[]) {
    int i, min = INT_MAX, minpos = -1;
    for (i = 1; i <= n; i++) { // 1���� n����
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) { // 1���� n����
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 1; i <= g->n; i++) { // 1���� n����
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;
    for (i = 1; i <= g->n; i++) { /* �ʱ�ȭ */
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    foundOrder[orderIndex++] = start; // �湮 ���� ���

    for (i = 1; i <= g->n; i++) {
        u = choose(distance, g->n, found);
        if (u == -1) break; // �� �̻� �湮�� ������ ������ ����
        found[u] = TRUE; // ������ ���� �湮 ǥ��

        // �湮 ���� ��� (�̹� �湮�� ������ ������� ����)
        if (orderIndex == 0 || foundOrder[orderIndex - 1] != u) {
            foundOrder[orderIndex++] = u; // �湮 ���� ���
        }

        print_status(g); // ���� ���� ���

        Node* p = g->adjList[u]; // ���� ���� u�� ���� ����Ʈ�� ��ȸ
        while (p != NULL) {
            w = p->vertex; // ����� ����
            // �Ÿ� ������Ʈ ����
            if (!found[w] && distance[u] + p->weight < distance[w]) {
                distance[w] = distance[u] + p->weight;
            }
            p = p->next; // ���� ���
        }
    }


    // ������ ���� ���
    print_status(g);


    // �湮�� ���� ���� ���
    printf("Found Order: ");
    for (i = 0; i < orderIndex; i++) {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

int main(void) {
    GraphType g;
    g.n = 10; // ���� ���� (1���� 10����)

    // ���� ����Ʈ �ʱ�ȭ
    for (int i = 1; i <= g.n; i++) {
        g.adjList[i] = NULL;
    }

    // ���� �߰� (1���� ����)
    insert_edge(&g, 1, 2, 3);
    insert_edge(&g, 1, 6, 11);
    insert_edge(&g, 1, 7, 12);
    insert_edge(&g, 2, 3, 5);
    insert_edge(&g, 2, 4, 4);
    insert_edge(&g, 2, 5, 1);
    insert_edge(&g, 2, 6, 7);
    insert_edge(&g, 2, 7, 8);
    insert_edge(&g, 5, 4, 13);
    insert_edge(&g, 5, 9, 18);
    insert_edge(&g, 5, 10, 17);
    insert_edge(&g, 4, 3, 2);
    insert_edge(&g, 4, 8, 14);
    insert_edge(&g, 4, 10, 16);
    insert_edge(&g, 3, 7, 6);
    insert_edge(&g, 3, 8, 5);
    insert_edge(&g, 5, 6, 9);
    insert_edge(&g, 7, 8, 13);
    insert_edge(&g, 8, 10, 15);
    insert_edge(&g, 10, 9, 10);

    shortest_path(&g, 1); // ���� ���� 1���� �ִ� ��� ã��

    return 0;
}
