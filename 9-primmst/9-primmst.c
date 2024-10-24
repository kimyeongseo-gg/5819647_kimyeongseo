#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; // ���� ���
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n) {
    int v = -1; // �ʱⰪ ����
    for (int i = 1; i <= n; i++) { // 1���� n����
        if (!selected[i]) {
            if (v == -1 || distance[i] < distance[v]) {
                v = i;
            }
        }
    }
    return v;
}

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->weight[i][j] = INF;
}

// ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start][end] = weight;
    g->weight[end][start] = weight; // ���� �׷���
    if (start > g->n) g->n = start;
    if (end > g->n) g->n = end;
}

// ���� �˰���
void FindPrimMST(GraphType* g) {
    int s = 1; // ���� ���� 1�� �ϵ��ڵ�
    int u;

    // distance �迭 �ʱ�ȭ
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        selected[i] = FALSE; // selected �迭�� �ʱ�ȭ
    }
    distance[s] = 0;

    printf("Prim MST Algorithm\n");

    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;

        if (distance[u] == INF) return; // ����� ������ ������ ����

        printf("���� %d �߰�\n", u); // 1-based index�� ���

        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF) {
                if (!selected[v] && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];
                }
            }
        }
    }
}


void GenerateGraph(GraphType* g) {

    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 3, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    FindPrimMST(g); // ���� ���� 1�� ���ο��� ���
    free(g);
    return 0;
}
