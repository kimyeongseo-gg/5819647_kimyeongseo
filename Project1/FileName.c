#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENT 200 // 최대 힙의 크기

// 힙의 각 요소를 표현하는 구조체
typedef struct {
    int key; // 힙의 키 값
} element;

// 힙을 표현하는 구조체
typedef struct {
    element heap[MAX_ELEMENT]; // 힙 배열
    int heap_size; // 힙의 현재 크기
} HeapType;

// 힙을 생성하는 함수
HeapType* create() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType)); // 힙 메모리 할당
    if (h == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1); // 메모리 할당 실패 시 프로그램 종료
    }
    h->heap_size = 0; // 초기 힙 크기 0으로 설정
    return h;
}

// 힙의 현재 상태를 출력하는 함수
void printHeap(HeapType* h) {
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key); // 힙의 각 요소 출력
    }
    printf("\n");
}

// 최대 힙에 새로운 요소를 추가하는 함수
void insert_max_heap(HeapType* h, element item, bool show) {
    if (h->heap_size >= MAX_ELEMENT - 1) {
        printf("힙이 가득 찼습니다.\n");
        return; // 배열 범위 초과 방지
    }

    int i = ++(h->heap_size); // 힙의 크기를 증가시키고 새 위치 설정
    h->heap[i] = item; // 새로운 노드를 마지막 위치에 삽입

    // 새로운 노드가 삽입된 직후의 상태 출력
    if (show) {

        printHeap(h); // 현재 상태 출력
    }

    int move_count = 0; // 이동 횟수 초기화

    // 부모 노드와 비교하여 위치를 조정하는 과정
    while (i != 1 && h->heap[i].key > h->heap[i / 2].key) {
        // 부모 노드와 현재 노드의 값을 교환
        element temp = h->heap[i];
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = temp;

        i /= 2; // 부모 노드로 이동
        move_count++; // 이동 횟수 증가

        if (show) {
            printHeap(h); // 현재 상태 출력 (중간 과정 출력)
        }
    }

    if (show) {
        printf("노드가 이동된 횟수: %d\n", move_count); // 이동 횟수 출력
    }
}


// 최대 힙에서 루트 노드를 삭제하는 함수
element delete_max_heap(HeapType* h) {
    if (h->heap_size == 0) {
        printf("힙이 비어 있습니다.\n");
        element empty = { -1 }; // 빈 값 반환
        return empty;
    }

    int parent, child; // 부모, 자식 노드 인덱스
    element item, temp; // 삭제할 아이템과 마지막 노드 저장

    item = h->heap[1]; // 루트 노드 저장
    temp = h->heap[h->heap_size--]; // 마지막 노드를 루트로 이동
    parent = 1; // 루트 노드로 초기화
    child = 2; // 자식 노드 초기화
    int move_count = 0; // 이동 횟수 초기화

    h->heap[1] = h->heap[h->heap_size + 1];

    printHeap(h);
    // 힙의 성질을 만족하도록 노드 위치 조정
    while (child <= h->heap_size) {
        // 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++; // 더 큰 자식으로 이동
        }
        if (temp.key >= h->heap[child].key)
            break; // 현재 노드가 더 크면 종료
        // 한 단계 아래로 이동
        element swap = h->heap[parent];
        h->heap[parent] = h->heap[child];
        h->heap[child] = swap;
        parent = child; // 부모 노드 인덱스 갱신
        child *= 2; // 자식 노드 인덱스 갱신
        move_count++; // 이동 횟수 증가
        printHeap(h); // 현재 상태 출력 (중간 과정 출력)
    }
    h->heap[parent] = temp; // 마지막 노드를 새 위치에 삽입
    move_count++;
    printf("노드가 이동된 횟수: %d\n", move_count); // 이동 횟수 출력
    return item; // 삭제한 루트 노드 반환
}




// 힙을 레벨별로 출력하는 함수
void printHeapByLevel(HeapType* h) {
    if (h->heap_size == 0) {
        printf("힙이 비어 있습니다.\n");
        return;
    }
    int level = 1; // 현재 레벨
    int nodesAtCurrentLevel = 1; // 현재 레벨에서 출력할 노드 수
    int currentNodeIndex = 1; // 현재 노드 인덱스

    // 각 레벨에 대해 반복
    while (currentNodeIndex <= h->heap_size) {
        printf("레벨 %d: ", level); // 현재 레벨 출력
        for (int i = 0; i < nodesAtCurrentLevel && currentNodeIndex <= h->heap_size; i++) {
            printf("[%d] ", h->heap[currentNodeIndex].key); // 현재 노드 출력
            currentNodeIndex++; // 다음 노드로 이동
        }
        printf("\n"); // 줄바꿈
        level++; // 레벨 증가
        nodesAtCurrentLevel *= 2; // 다음 레벨의 노드 수
    }
}

// 사용자 인터페이스를 실행하는 함수
void runUserInterface(HeapType* heap) {
    char command; // 사용자 명령 저장
    element item; // 입력할 요소

    for (true;;) {
        printf("\n"); // 줄바꿈
        printf("\n"); // 줄바꿈

        printf("*-*=======================*-*\n");
        printf("|    i : 노드 추가          |\n");
        printf("|    d : 노드 삭제          |\n");
        printf("|    p : 레벨별 출력        |\n");
        printf("|    c : 종료               |\n");
        printf("*-*========================*-*\n");

        printf("\n"); // 줄바꿈

        printf("\n메뉴 입력 (i: 추가, d: 삭제, p: 출력, c: 종료): ");
        scanf_s(" %c", &command); // 사용자 입력 받기

        switch (command) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf_s("%d", &item.key); // 추가할 값 입력
            insert_max_heap(heap, item, true); // 힙에 추가
            break;

        case 'd':
            if (heap->heap_size == 0) {
                printf("삭제할 노드가 없습니다.\n"); // 힙이 비어있을 경우
            }
            else {
                delete_max_heap(heap); // 루트 노드 삭제
            }
            break;

        case 'p':
            printf("트리 레벨별 출력:\n");
            printHeapByLevel(heap); // 레벨별로 힙 출력
            break;

        case 'c':
            printf("프로그램이 종료 되었습니다.\n");
            return; // 프로그램 종료

        default:
            printf("잘못된 입력입니다.\n");
            break;
        }
    }
}

// 주어진 배열을 사용하여 최대 힙을 생성하는 함수
HeapType* generateMaxHeapTree(int inputData[], int size) {
    HeapType* heap = create(); // 힙 생성
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i]; // 입력 데이터로 요소 초기화
        insert_max_heap(heap, item, false); // 힙에 요소 추가
    }
    return heap;
}


int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // 초기 데이터
    int size = sizeof(inputData) / sizeof(inputData[0]); // 데이터 크기 계산


    HeapType* heap = generateMaxHeapTree(inputData, size);


    runUserInterface(heap);

    free(heap);
    return 0;
}