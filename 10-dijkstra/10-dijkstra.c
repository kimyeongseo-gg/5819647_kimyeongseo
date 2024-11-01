#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct Node {
    int vertex;       // 정점 번호
    int weight;      // 가중치
    struct Node* next; // 다음 노드
} Node;

typedef struct GraphType {
    int n;           // 정점의 개수
    Node* adjList[MAX_VERTICES]; // 인접 리스트
} GraphType;

int distance[MAX_VERTICES]; /* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];     /* 방문한 정점 표시 */
int foundOrder[MAX_VERTICES]; // 방문한 정점 순서 저장
int orderIndex = 0; // 방문 순서 인덱스

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

    newNode = createNode(u, w); // 무향 그래프이므로 양쪽에 추가
    newNode->next = g->adjList[v];
    g->adjList[v] = newNode;
}

int choose(int distance[], int n, int found[]) {
    int i, min = INT_MAX, minpos = -1;
    for (i = 1; i <= n; i++) { // 1부터 n까지
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) { // 1부터 n까지
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 1; i <= g->n; i++) { // 1부터 n까지
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;
    for (i = 1; i <= g->n; i++) { /* 초기화 */
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    foundOrder[orderIndex++] = start; // 방문 순서 기록

    for (i = 1; i <= g->n; i++) {
        u = choose(distance, g->n, found);
        if (u == -1) break; // 더 이상 방문할 정점이 없으면 종료
        found[u] = TRUE; // 선택한 정점 방문 표시

        // 방문 순서 기록 (이미 방문한 정점은 기록하지 않음)
        if (orderIndex == 0 || foundOrder[orderIndex - 1] != u) {
            foundOrder[orderIndex++] = u; // 방문 순서 기록
        }

        print_status(g); // 현재 상태 출력

        Node* p = g->adjList[u]; // 현재 정점 u의 인접 리스트를 순회
        while (p != NULL) {
            w = p->vertex; // 연결된 정점
            // 거리 업데이트 조건
            if (!found[w] && distance[u] + p->weight < distance[w]) {
                distance[w] = distance[u] + p->weight;
            }
            p = p->next; // 다음 노드
        }
    }


    // 마지막 상태 출력
    print_status(g);


    // 방문한 정점 순서 출력
    printf("Found Order: ");
    for (i = 0; i < orderIndex; i++) {
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
