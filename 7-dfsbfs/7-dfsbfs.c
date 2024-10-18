#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // �ִ� ���� �� ����

// �׷��� ����ü ����
typedef struct Graph {
    int n; 
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; 
} Graph;

// �׷��� ���� �Լ�
Graph* create_mat_graph() {
    return (Graph*)malloc(sizeof(Graph)); 
}

// �׷��� �Ҹ� �Լ�
void destroy_mat_graph(Graph* g) {
    free(g); 
}

// �׷��� �ʱ�ȭ �Լ�
void init_mat_graph(Graph* g) {
    g->n = 0; 
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0; 
        }
    }
}

// ���� �߰� �Լ�
void insert_vertex_mat_graph(Graph* g, int v) {
    if ((g->n) >= (MAX_VERTICES - 1)) { // ���� ���� �ִ븦 �ʰ��ϴ��� Ȯ��
        fprintf(stderr, "Over number of vertex\n"); 
        return;
    }
    (g->n)++;
}

// ���� �߰� �Լ�
void insert_edge(Graph* g, int s, int e) {
    if (g->n <= s || g->n <= e) { // ���� ��ȣ�� ��ȿ���� Ȯ��
        fprintf(stderr, "Vertex number error\n"); 
        return;
    }
    g->adj_mat[s][e] = 1; 
    g->adj_mat[e][s] = 1; 
}

// ���� ��� ��� �Լ�
void print_adj_mat(Graph* g) {
    printf("      "); // ���� ��� ��� ���
    for (int i = 0; i < g->n; i++) {
        printf("%02d ", i); 
    }
    printf("\n");

    for (int i = 0; i < g->n; i++) {
        printf(" [%02d] ", i); // �� ���� ���� ��ȣ ���
        for (int j = 0; j < g->n; j++) {
            printf("%02d ", g->adj_mat[i][j]); // ���� ����� �� ���
        }
        printf("\n");
    }
}

// ���� �켱 Ž�� (DFS) �Լ�
void iterativeDFS(Graph* g, int start, int target) {
    int stack[MAX_VERTICES], top = -1; // ���ð� top �ε��� �ʱ�ȭ
    int visited[MAX_VERTICES] = { 0 }; // �湮 ���� �迭 �ʱ�ȭ
    int found = 0; 
    int visitedCount = 0; // �湮�� ��� ��

    printf("���� �߰�: %d ", start); 
    stack[++top] = start; 

    while (top != -1) { // ������ ������� ���� ������ �ݺ�
        int v = stack[top]; 

        if (!visited[v]) { // �湮���� ���� ����� ���
            visited[v] = 1; 

            if (v == target) { // ���� ��尡 Ÿ�� �����
                found = 1; 
                break; 
            }
        }

        int pushed = 0; // ���� ��尡 ���ÿ� �߰��Ǿ����� ����
       
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1 && !visited[i]) { // ���� ����̸鼭 �湮���� ���� ���
                printf("%d ", i); 
                stack[++top] = i; // ���ÿ� �߰�
                pushed = 1; 
                visitedCount++; // �湮�� ��� �� ����
                break; // �� ���� �ϳ��� ���� ��常 �߰�
            }
        }

        if (!pushed) { // �߰��� ���� ��尡 ���� ���
            printf("%d ", stack[top - 1]); // ��Ʈ��ŷ �� ��� ���
            visitedCount++; 
            top--; // ���ÿ��� ��� ����
        }
    }

    // Ž�� ��� ���
    if (found) {
        printf("\nŽ�� ����: %d\n", target); 
    }
    else {
        printf("\nŽ�� ����: %d\n", target); 
    }
    printf("�湮�� ����� ��: %d\n", visitedCount);
}

// �ʺ� �켱 Ž�� (BFS) �Լ�
void iterativeBFS(Graph* g, int start, int target) {
    int queue[MAX_VERTICES], front = 0, rear = -1; // ť�� ������ �ʱ�ȭ
    int visitedCount = 0; 
    int found = 0; 
    int visited[MAX_VERTICES] = { 0 }; 

    queue[++rear] = start; // ���� ��带 ť�� �߰�
    visited[start] = 1; 

    while (front <= rear) { 
        int v = queue[front++]; // ť���� ��� ������
        printf("%d ", v); // ���� ��� ���

        if (v == target) { // ���� ��尡 Ÿ�� �����
            found = 1; 
            break; 
        }

        // ���� ��� Ž��
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1 && !visited[i]) { 
                queue[++rear] = i; // ť�� �߰�
                visited[i] = 1; // �湮 ó��
                visitedCount++; // �湮�� ��� �� ����
            }
        }
    }

    // Ž�� ��� ���
    if (found) {
        printf("\nŽ�� ����: %d\n", target); 
    }
    else {
        printf("\nŽ�� ����: %d\n", target); 
    }
    printf("�湮�� ����� ��: %d\n", visitedCount); // �� �湮�� ��� �� ���
}

// ���� �Լ�
int main() {
    Graph* g = create_mat_graph(); // �׷��� ����
    init_mat_graph(g);

    // �׷����� ���� �߰�
    for (int i = 0; i <= 10; i++) {
        insert_vertex_mat_graph(g, i);
    }

    // �׷����� ���� ����
    insert_edge(g, 1, 4);
    insert_edge(g, 1, 5);
    insert_edge(g, 1, 7);
    insert_edge(g, 1, 10);
    insert_edge(g, 4, 0);
    insert_edge(g, 4, 2);
    insert_edge(g, 4, 3);
    insert_edge(g, 4, 5);
    insert_edge(g, 4, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 5);
    insert_edge(g, 0, 6);
    insert_edge(g, 0, 9);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 5);
    insert_edge(g, 6, 7);
    insert_edge(g, 6, 8);
    insert_edge(g, 7, 10);
    insert_edge(g, 10, 8);
    insert_edge(g, 8, 9);

    // ����� �Է��� ���� Ž�� ����
    while (1) {
        int choice;
        printf("\n1: ���̿켱Ž��\n");
        printf("2: �ʺ�켱Ž��\n");
        printf("3: ����\n");
        printf("�޴��Է�: ");
        scanf_s("%d", &choice); // �����
        if (choice == 3) {
            break;
        }

        int start, target;
        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1) {
            iterativeDFS(g, start, target);
        }
        else if (choice == 2) {
            iterativeBFS(g, start, target);
        }
        else {
            printf("�߸��� �����Դϴ�.\n");
        }
    }

    // �޸� ����
    destroy_mat_graph(g);
    return 0;
}
