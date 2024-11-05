#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

// 노드 구조체 정의
typedef struct Node {
    int vertex;       
    int weight;      
    struct Node* next; 
} Node;

// 그래프 구조체 정의
typedef struct GraphType {
    int n;                       
    Node* adjList[MAX_VERTICES]; 
} GraphType;

// 최소힙 노드 구조체 정의
typedef struct MinHeapNode {
    int vertex;   
    int distance;  
} MinHeapNode;

// 최소힙 구조체 정의
typedef struct MinHeap {
    MinHeapNode* array; 
    int size;           
    int capacity;       
} MinHeap;

// 최소힙 생성 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    return minHeap;
}

// 두 노드를 교환하는 함수
void swap(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// 최소힙을 정렬하는 함수
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;  
    int right = 2 * idx + 2; 

    // 왼쪽 자식과 비교
    if (left < minHeap->size && minHeap->array[left].distance < minHeap->array[smallest].distance)
        smallest = left;

    // 오른쪽 자식과 비교
    if (right < minHeap->size && minHeap->array[right].distance < minHeap->array[smallest].distance)
        smallest = right;

    // 제일 작은 노드가 현재 노드가 아니면 교환
    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest); 
    }
}

// 최소힙이 비었는지 확인하는 함수
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// 최소힙에서 최솟값을 추출하는 함수
MinHeapNode extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return (MinHeapNode) { -1, -1 }; 

    MinHeapNode root = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
    minHeap->size--;
    minHeapify(minHeap, 0); 
    return root;
}

// 최소힙에서 키를 감소시키는 함수
void decreaseKey(MinHeap* minHeap, int vertex, int distance) {
    int i;
    for (i = 0; i < minHeap->size; i++) {
        if (minHeap->array[i].vertex == vertex) {
            break; // 정점을 찾으면 종료
        }
    }
    minHeap->array[i].distance = distance; 
    // 부모 노드와 비교하여 위치 조정
    while (i != 0 && minHeap->array[i].distance < minHeap->array[(i - 1) / 2].distance) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2; 
    }
}

// 최소힙에 새로운 노드를 삽입하는 함수
void insertMinHeap(MinHeap* minHeap, int vertex, int distance) {
    minHeap->size++; // 크기 증가
    minHeap->array[minHeap->size - 1].vertex = vertex;
    minHeap->array[minHeap->size - 1].distance = distance;

    decreaseKey(minHeap, vertex, distance);
}

// 인접 리스트의 노드를 생성하는 함수
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 그래프에 엣지를 추가하는 함수
void insert_edge(GraphType* g, int u, int v, int w) {
    Node* newNode = createNode(v, w); 
    newNode->next = g->adjList[u]; 
    g->adjList[u] = newNode;

    newNode = createNode(u, w); 
    newNode->next = g->adjList[v]; 
    g->adjList[v] = newNode;
}

// 최단 거리 정점을 선택하는 함수
int choose(int distance[], int n, int found[]) {
    int min = INF; // 최소 거리
    int minIndex = -1;

    for (int i = 1; i <= n; i++) {
        if (!found[i] && distance[i] < min) {
            min = distance[i];
            minIndex = i; 
        }
    }

    return minIndex; 
}

void print_status(GraphType* g, int distance[], int found[]) {
    // 거리 출력
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) { 
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\n");

    // 방문 상태 출력
    printf("Found: ");
    for (int i = 1; i <= g->n; i++) { 
        printf("%d ", found[i]);
    }
    printf("\n\n");
}


void shortest_path(GraphType* g, int start) {
    int distance[MAX_VERTICES];
    int found[MAX_VERTICES] = { FALSE };
    int foundOrder[MAX_VERTICES]; // 방문 순서를 저장할 배열
    int orderIndex = 0;

    // 거리와 방문 상태 초기화
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    foundOrder[orderIndex++] = start; // 시작 정점 방문 순서 기록

    for (int i = 1; i <= g->n; i++) {
        int u = choose(distance, g->n, found); 
        if (u == -1) break; 
        found[u] = TRUE;

        // 방문 순서 기록
        foundOrder[orderIndex++] = u; // 방문 순서 기록

        // 현재 상태 출력
        print_status(g, distance, found);

        Node* p = g->adjList[u]; // 현재 정점 u의 인접 리스트를 순회
        while (p != NULL) {
            int w = p->vertex; // 연결된 정점
            // 거리 업데이트 조건
            if (!found[w] && distance[u] + p->weight < distance[w]) {
                distance[w] = distance[u] + p->weight;
            }
            p = p->next; // 다음 노드
        }
    }


    // 탐색 순서 출력
    printf("Found Order: ");
    for (int i = 1; i < orderIndex; i++) {
        printf("%d ", foundOrder[i]);
    }
    printf("\n");
}

int main(void) {
    GraphType g;
    g.n = 10; // 정점 개수 (1부터 10까지)

    // 인접 리스트 초기화
    for (int i = 1; i <= g.n; i++) {
        g.adjList[i] = NULL;
    }

    // 엣지 추가 (1부터 시작)
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

    shortest_path(&g, 1); // 시작 정점 1에서 최단 경로 찾기

    return 0;
}
