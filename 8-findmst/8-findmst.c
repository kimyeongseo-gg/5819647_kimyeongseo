#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // �θ� ��带 �����ϴ� �迭

// �θ� �迭 �ʱ�ȭ �Լ�
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr�� ���ϴ� ������ ��ȯ�ϴ� �Լ�
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// �� ���� ���Ұ� ���� ������ ��ġ�� �Լ�
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// ������ ��Ÿ���� ����ü
struct Edge {
    int start, end, weight; // ���� ���, �� ���, ����ġ
};

typedef struct GraphType {
    int n; // ������ ����
    struct Edge edges[2 * MAX_VERTICES]; // ���� �迭
} GraphType;

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = 0; // ���� �� �ʱ�ȭ
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
    if (g == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return -1;
    }
}

// ���� ���� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n >= 2 * MAX_VERTICES) {
        printf("���� ���� �ִ븦 �ʰ��߽��ϴ�.\n"); // ���� �� �ʰ� �� ���� �޽���
        return; // ���� ó��
    }
    // ���� ������ �迭�� ����
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++; // ���� �� ����
}

// qsort()�� ���Ǵ� �� �Լ�
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); // ����ġ�� �������� ����
}

// Qsort ��� ũ�罺Į �˰���
void QuickKruskal(GraphType* g) {
    if (g->n == 0) {
        printf("�׷����� ������ �����ϴ�.\n"); // ������ ���� ��� �޽��� ���
        return;
    }

    int edge_accepted = 0; // ������� ���õ� ������ ��    
    int uset, vset;
    struct Edge e;

    set_init(MAX_VERTICES); // ���� �ʱ�ȭ
    qsort(g->edges, g->n, sizeof(struct Edge), compare); // ������ ����ġ �������� ����

    printf("Quick Based Kruskal\n");
    int i = 0;

    // ���õ� ���� ���� (n-1)���� �۰�, ���� �ε����� n���� ���� ���� �ݺ�
    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) { // ���� �ٸ� ������ ���
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++; // ���� �������� �̵�
    }
}

// MinHeap ����ü ����
typedef struct MinHeap {
    struct Edge* edges; // ���� �迭
    int size; // ���� ���� ũ��
    int capacity; // ���� �ִ� �뷮
} MinHeap;

// MinHeap ���� �Լ�
MinHeap* create_min_heap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->edges = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// �� Edge�� ��ȯ�ϴ� �Լ�
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

// MinHeap ���� ���� �Լ�
void min_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx; // ���� ���� ����� �ε���
    int left = 2 * idx + 1; // ���� �ڽ� �ε���
    int right = 2 * idx + 2; // ������ �ڽ� �ε���

    // ���� ���� ���� �ε����� ã��
    if (left < minHeap->size && minHeap->edges[left].weight < minHeap->edges[smallest].weight)
        smallest = left;

    if (right < minHeap->size && minHeap->edges[right].weight < minHeap->edges[smallest].weight)
        smallest = right;

    // ��ȯ�� �ʿ��� ���
    if (smallest != idx) {
        swap(&minHeap->edges[idx], &minHeap->edges[smallest]); // ��ȯ
        min_heapify(minHeap, smallest);
    }
}

// �ּҰ��� �����ϴ� �Լ�
struct Edge extract_min(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        struct Edge infEdge = { 0, 0, INF }; // ������ ���� ��ȯ
        return infEdge;
    }

    struct Edge root = minHeap->edges[0]; // ��Ʈ ��� ����
    minHeap->edges[0] = minHeap->edges[minHeap->size - 1]; // ������ ��ҷ� ��ü
    minHeap->size--; // ũ�� ����
    min_heapify(minHeap, 0); // �� ���� ����
    return root; // �ּҰ� ��ȯ
}

// MinHeap�� ��Ҹ� �����ϴ� �Լ�
void insert_min_heap(MinHeap* minHeap, struct Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    minHeap->edges[minHeap->size] = edge; // ���ο� ���� �߰�
    int i = minHeap->size;
    minHeap->size++;

    // �θ�� ���ϸ� ���� �ö󰡸� ��ġ ����
    while (i != 0 && minHeap->edges[(i - 1) / 2].weight > minHeap->edges[i].weight) {
        swap(&minHeap->edges[i], &minHeap->edges[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// MinHeap ��� Kruskal �˰���
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;


    set_init(g->n);
    MinHeap* minHeap = create_min_heap(g->n);

    for (int i = 0; i < g->n; i++) {
        insert_min_heap(minHeap, g->edges[i]);
    }

    printf("\n");
    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (g->n - 1)) {
        e = extract_min(minHeap);
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }
    free(minHeap->edges);
    free(minHeap);
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

    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    //�׷����� �����ϴ� �Լ�
    GenerateGraph(g);

    QuickKruskal(g); // quick ���
    MinHeapKruskal(g); // minheap ���

    free(g);
    return 0;
}