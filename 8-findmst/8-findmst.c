#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모 노드를 저장하는 배열

// 부모 배열 초기화 함수
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr가 속하는 집합을 반환하는 함수
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

// 두 개의 원소가 속한 집합을 합치는 함수
void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// 간선을 나타내는 구조체
struct Edge {
    int start, end, weight; // 시작 노드, 끝 노드, 가중치
};

typedef struct GraphType {
    int n; // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES]; // 간선 배열
} GraphType;

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0; // 간선 수 초기화
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
    if (g == NULL) {
        printf("메모리 할당 실패\n");
        return -1;
    }
}

// 간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n >= 2 * MAX_VERTICES) {
        printf("간선 수가 최대를 초과했습니다.\n"); // 간선 수 초과 시 오류 메시지
        return; // 오류 처리
    }
    // 간선 정보를 배열에 삽입
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++; // 간선 수 증가
}

// qsort()에 사용되는 비교 함수
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight); // 가중치를 기준으로 정렬
}

// Qsort 기반 크루스칼 알고리즘
void QuickKruskal(GraphType* g) {
    if (g->n == 0) {
        printf("그래프에 간선이 없습니다.\n"); // 간선이 없을 경우 메시지 출력
        return;
    }

    int edge_accepted = 0; // 현재까지 선택된 간선의 수    
    int uset, vset;
    struct Edge e;

    set_init(MAX_VERTICES); // 집합 초기화
    qsort(g->edges, g->n, sizeof(struct Edge), compare); // 간선을 가중치 기준으로 정렬

    printf("Quick Based Kruskal\n");
    int i = 0;

    // 선택된 간선 수가 (n-1)보다 작고, 간선 인덱스가 n보다 작을 동안 반복
    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) { // 서로 다른 집합일 경우
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++; // 다음 간선으로 이동
    }
}

// MinHeap 구조체 정의
typedef struct MinHeap {
    struct Edge* edges; // 간선 배열
    int size; // 현재 힙의 크기
    int capacity; // 힙의 최대 용량
} MinHeap;

// MinHeap 생성 함수
MinHeap* create_min_heap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->edges = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// 두 Edge를 교환하는 함수
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

// MinHeap 구조 조정 함수
void min_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx; // 가장 작은 요소의 인덱스
    int left = 2 * idx + 1; // 왼쪽 자식 인덱스
    int right = 2 * idx + 2; // 오른쪽 자식 인덱스

    // 가장 작은 값의 인덱스를 찾음
    if (left < minHeap->size && minHeap->edges[left].weight < minHeap->edges[smallest].weight)
        smallest = left;

    if (right < minHeap->size && minHeap->edges[right].weight < minHeap->edges[smallest].weight)
        smallest = right;

    // 교환이 필요할 경우
    if (smallest != idx) {
        swap(&minHeap->edges[idx], &minHeap->edges[smallest]); // 교환
        min_heapify(minHeap, smallest);
    }
}

// 최소값을 추출하는 함수
struct Edge extract_min(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        struct Edge infEdge = { 0, 0, INF }; // 가상의 간선 반환
        return infEdge;
    }

    struct Edge root = minHeap->edges[0]; // 루트 요소 저장
    minHeap->edges[0] = minHeap->edges[minHeap->size - 1]; // 마지막 요소로 대체
    minHeap->size--; // 크기 감소
    min_heapify(minHeap, 0); // 힙 구조 조정
    return root; // 최소값 반환
}

// MinHeap에 요소를 삽입하는 함수
void insert_min_heap(MinHeap* minHeap, struct Edge edge) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    minHeap->edges[minHeap->size] = edge; // 새로운 간선 추가
    int i = minHeap->size;
    minHeap->size++;

    // 부모와 비교하며 위로 올라가며 위치 조정
    while (i != 0 && minHeap->edges[(i - 1) / 2].weight > minHeap->edges[i].weight) {
        swap(&minHeap->edges[i], &minHeap->edges[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// MinHeap 기반 Kruskal 알고리즘
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

// 그래프를 생성하는 함수
void GenerateGraph(GraphType* g) {
    // 예시 간선 추가 (start, end, weight)
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



// 메인 함수
int main(void) {

    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    //그래프를 생성하는 함수
    GenerateGraph(g);

    QuickKruskal(g); // quick 기반
    MinHeapKruskal(g); // minheap 기반

    free(g);
    return 0;
}