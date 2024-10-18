#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // 최대 정점 수 정의

// 그래프 구조체 정의
typedef struct Graph {
    int n; 
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; 
} Graph;

// 그래프 생성 함수
Graph* create_mat_graph() {
    return (Graph*)malloc(sizeof(Graph)); 
}

// 그래프 소멸 함수
void destroy_mat_graph(Graph* g) {
    free(g); 
}

// 그래프 초기화 함수
void init_mat_graph(Graph* g) {
    g->n = 0; 
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0; 
        }
    }
}

// 정점 추가 함수
void insert_vertex_mat_graph(Graph* g, int v) {
    if ((g->n) >= (MAX_VERTICES - 1)) { // 정점 수가 최대를 초과하는지 확인
        fprintf(stderr, "Over number of vertex\n"); 
        return;
    }
    (g->n)++;
}

// 간선 추가 함수
void insert_edge(Graph* g, int s, int e) {
    if (g->n <= s || g->n <= e) { // 정점 번호가 유효한지 확인
        fprintf(stderr, "Vertex number error\n"); 
        return;
    }
    g->adj_mat[s][e] = 1; 
    g->adj_mat[e][s] = 1; 
}

// 인접 행렬 출력 함수
void print_adj_mat(Graph* g) {
    printf("      "); // 인접 행렬 헤더 출력
    for (int i = 0; i < g->n; i++) {
        printf("%02d ", i); 
    }
    printf("\n");

    for (int i = 0; i < g->n; i++) {
        printf(" [%02d] ", i); // 각 행의 정점 번호 출력
        for (int j = 0; j < g->n; j++) {
            printf("%02d ", g->adj_mat[i][j]); // 인접 행렬의 값 출력
        }
        printf("\n");
    }
}

// 깊이 우선 탐색 (DFS) 함수
void iterativeDFS(Graph* g, int start, int target) {
    int stack[MAX_VERTICES], top = -1; // 스택과 top 인덱스 초기화
    int visited[MAX_VERTICES] = { 0 }; // 방문 여부 배열 초기화
    int found = 0; 
    int visitedCount = 0; // 방문한 노드 수

    printf("스택 추가: %d ", start); 
    stack[++top] = start; 

    while (top != -1) { // 스택이 비어있지 않을 때까지 반복
        int v = stack[top]; 

        if (!visited[v]) { // 방문하지 않은 노드일 경우
            visited[v] = 1; 

            if (v == target) { // 현재 노드가 타겟 노드라면
                found = 1; 
                break; 
            }
        }

        int pushed = 0; // 인접 노드가 스택에 추가되었는지 여부
       
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1 && !visited[i]) { // 인접 노드이면서 방문하지 않은 경우
                printf("%d ", i); 
                stack[++top] = i; // 스택에 추가
                pushed = 1; 
                visitedCount++; // 방문한 노드 수 증가
                break; // 한 번에 하나의 인접 노드만 추가
            }
        }

        if (!pushed) { // 추가된 인접 노드가 없는 경우
            printf("%d ", stack[top - 1]); // 백트래킹 시 노드 출력
            visitedCount++; 
            top--; // 스택에서 노드 제거
        }
    }

    // 탐색 결과 출력
    if (found) {
        printf("\n탐색 성공: %d\n", target); 
    }
    else {
        printf("\n탐색 실패: %d\n", target); 
    }
    printf("방문한 노드의 수: %d\n", visitedCount);
}

// 너비 우선 탐색 (BFS) 함수
void iterativeBFS(Graph* g, int start, int target) {
    int queue[MAX_VERTICES], front = 0, rear = -1; // 큐와 포인터 초기화
    int visitedCount = 0; 
    int found = 0; 
    int visited[MAX_VERTICES] = { 0 }; 

    queue[++rear] = start; // 시작 노드를 큐에 추가
    visited[start] = 1; 

    while (front <= rear) { 
        int v = queue[front++]; // 큐에서 노드 꺼내기
        printf("%d ", v); // 현재 노드 출력

        if (v == target) { // 현재 노드가 타겟 노드라면
            found = 1; 
            break; 
        }

        // 인접 노드 탐색
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1 && !visited[i]) { 
                queue[++rear] = i; // 큐에 추가
                visited[i] = 1; // 방문 처리
                visitedCount++; // 방문한 노드 수 증가
            }
        }
    }

    // 탐색 결과 출력
    if (found) {
        printf("\n탐색 성공: %d\n", target); 
    }
    else {
        printf("\n탐색 실패: %d\n", target); 
    }
    printf("방문한 노드의 수: %d\n", visitedCount); // 총 방문한 노드 수 출력
}

// 메인 함수
int main() {
    Graph* g = create_mat_graph(); // 그래프 생성
    init_mat_graph(g);

    // 그래프에 정점 추가
    for (int i = 0; i <= 10; i++) {
        insert_vertex_mat_graph(g, i);
    }

    // 그래프에 간선 삽입
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

    // 사용자 입력을 통한 탐색 선택
    while (1) {
        int choice;
        printf("\n1: 깊이우선탐색\n");
        printf("2: 너비우선탐색\n");
        printf("3: 종료\n");
        printf("메뉴입력: ");
        scanf_s("%d", &choice); // 사용자
        if (choice == 3) {
            break;
        }

        int start, target;
        printf("시작 번호와 탐색할 값 입력: ");
        scanf_s("%d %d", &start, &target);

        if (choice == 1) {
            iterativeDFS(g, start, target);
        }
        else if (choice == 2) {
            iterativeBFS(g, start, target);
        }
        else {
            printf("잘못된 선택입니다.\n");
        }
    }

    // 메모리 해제
    destroy_mat_graph(g);
    return 0;
}
