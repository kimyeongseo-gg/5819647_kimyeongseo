#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n) {
    int v = -1; // 초기값 설정
    for (int i = 1; i <= n; i++) { // 1부터 n까지
        if (!selected[i]) {
            if (v == -1 || distance[i] < distance[v]) {
                v = i;
            }
        }
    }
    return v;
}

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            g->weight[i][j] = INF;
}

// 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->weight[start][end] = weight;
    g->weight[end][start] = weight; // 무향 그래프
    if (start > g->n) g->n = start;
    if (end > g->n) g->n = end;
}

// 프림 알고리즘
void FindPrimMST(GraphType* g) {
    int s = 1; // 시작 정점 1로 하드코딩
    int u;

    // distance 배열 초기화
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        selected[i] = FALSE; // selected 배열도 초기화
    }
    distance[s] = 0;

    printf("Prim MST Algorithm\n");

    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);
        selected[u] = TRUE;

        if (distance[u] == INF) return; // 연결된 정점이 없으면 종료

        printf("정점 %d 추가\n", u); // 1-based index로 출력

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

    FindPrimMST(g); // 시작 정점 1을 내부에서 사용
    free(g);
    return 0;
}
