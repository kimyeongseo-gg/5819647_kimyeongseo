#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // �θ� ���

// �θ� �迭 �ʱ�ȭ
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr; // ��Ʈ 
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b) {
    int root1 = set_find(a); // ��� a�� ��Ʈ�� ã�´�. 
    int root2 = set_find(b); // ��� b�� ��Ʈ�� ã�´�. 
    if (root1 != root2) // ��ģ��.
        parent[root1] = root2;
}

// ������ ��Ÿ���� ����ü
struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n; // ������ ����
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n >= 2 * MAX_VERTICES) {
        printf("���� ���� �ִ븦 �ʰ��߽��ϴ�.\n");
        return; // ���� ó��
    }
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

// ũ�罺Į�� �ּ� ��� ���� Ʈ�� ���α׷�
void QuickKruskal(GraphType* g) {
    if (g->n == 0) {
        printf("�׷����� ������ �����ϴ�.\n");
        return;
    }

    int edge_accepted = 0; // ������� ���õ� ������ ��    
    int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
    struct Edge e;

    set_init(MAX_VERTICES); // ���� �ʱ�ȭ
    qsort(g->edges, g->n, sizeof(struct Edge), compare);

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->n - 1) && i < g->n) { // ������ �� < (n-1)
        e = g->edges[i];
        uset = set_find(e.start); // ���� u�� ���� ��ȣ 
        vset = set_find(e.end); // ���� v�� ���� ��ȣ
        if (uset != vset) { // ���� ���� ������ �ٸ���
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset); // �ΰ��� ������ ��ģ��.
        }
        i++;
    }
}

// �׷����� �����ϴ� �Լ�
void GenerateGraph(GraphType* g) {
    // ���� ���� �߰� (start, end, weight)
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
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

// ���� �Լ�
int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    if (g == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return -1; // ���� ó��
    }

    graph_init(g);
    GenerateGraph(g);

    QuickKruskal(g); // Qsort ��� ũ�罺Į
    // MinHeapKruskal(g); // MinHeap ��� ũ�罺Į (�ʿ� �� ����)
    free(g);
    return 0;
}