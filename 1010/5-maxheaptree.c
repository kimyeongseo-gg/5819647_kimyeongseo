#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
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
    h->heap_size = 0; // 초기 힙 크기 0으로 설정
    return h;
}



// 최대 힙에 새로운 요소를 추가하는 함수
void insert_max_heap(HeapType* h, element item) {
    int i = ++(h->heap_size); // 힙의 크기를 증가시키고 새 위치 설정
    int move_count = 0; // 이동 횟수 초기화

    // 부모 노드와 비교하여 위치를 조정하는 과정
    while (i != 1 && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2]; // 부모 노드를 내려보냄
        i /= 2; // 부모 노드로 이동
        move_count++; // 이동 횟수 증가
        printHeap(h); // 현재 상태 출력
    }
    h->heap[i] = item; // 새로운 노드를 삽입
    printHeap(h); // 최종 상태 출력
    printf("노드가 이동된 횟수: %d\n", move_count); // 이동 횟수 출력
}

// 최대 힙에서 루트 노드를 삭제하는 함수
element delete_max_heap(HeapType* h) {
    int parent, child; // 부모, 자식 노드 인덱스
    element item, temp; // 삭제할 아이템과 마지막 노드 저장

    item = h->heap[1]; // 루트 노드 저장
    temp = h->heap[(h->heap_size)--]; // 마지막 노드를 루트로 이동
    parent = 1; // 루트 노드로 초기화
    child = 2; // 자식 노드 초기화
    int move_count = 0; // 이동 횟수 초기화

    // 힙의 성질을 만족하도록 노드 위치 조정
    while (child <= h->heap_size) {
        // 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++; // 더 큰 자식으로 이동
        }
        if (temp.key >= h->heap[child].key) break; // 현재 노드가 더 크면 종료
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child; // 부모 노드 인덱스 갱신
        child *= 2; // 자식 노드 인덱스 갱신
        move_count++; // 이동 횟수 증가
        printHeap(h); // 현재 상태 출력
    }
    h->heap[parent] = temp; // 마지막 노드를 새 위치에 삽입
    printf("삭제된 노드: %d\n", item.key); // 삭제된 노드 출력
    printHeap(h); // 최종 상태 출력
    printf("노드가 이동된 횟수: %d\n", move_count); // 이동 횟수 출력
    return item; // 삭제한 루트 노드 반환
}

// 힙을 레벨별로 출력하는 함수
void printHeapByLevel(HeapType* h) {
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

    while (1) {
        printf("\n메뉴 입력 (i: 추가, d: 삭제, p: 출력, c: 종료): ");
        scanf_s(" %c", &command); // 사용자 입력 받기

        switch (command) {
        case 'i':
            printf("추가할 값 입력: ");
            scanf_s("%d", &item.key); // 추가할 값 입력
            insert_max_heap(heap, item); // 힙에 추가
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
            printf("잘못된 입력입니다.\n"); // 잘못된 입력 처리
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
        insert_max_heap(heap, item); // 힙에 요소 추가
    }
    return heap; // 생성된 힙 반환
}

// 프로그램의 진입점
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // 초기 데이터
    int size = sizeof(inputData) / sizeof(inputData[0]); // 데이터 크기 계산

    // 히프 생성
    HeapType* heap = generateMaxHeapTree(inputData, size);

    // 사용자 인터페이스 실행
    runUserInterface(heap);

    // 메모리 해제
    free(heap);
    return 0;
}
