#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 비교 및 이동 횟수 글로벌 변수
int comparisonCount = 0;
int moveCount = 0;
int isFirst = 0;
int rounds = 0;
double totalComparisons = 0;
double totalMoveCount = 0;

// 랜덤 배열 생성 함수
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;  // 0-999 사이 랜덤 숫자
    }
}

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 파티션 함수
int partition(int list[], int left, int right) {
    int pivot = list[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        comparisonCount++; // 비교 횟수 증가

        if (list[j] <= pivot) {
            i++;

            // 이동 횟수 증가
            moveCount += 3;

            // 요소 교환
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }

    // 마지막 스왑
    moveCount += 3;
    int temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;

    return i + 1;
}

// 퀵 정렬 재귀 함수
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        // 출력 부분: 40~60 사이의 값 출력
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", list[i]);
            printf("\n\n");
        }
        rounds++;

        int pivotIndex = partition(list, left, right);

        // 재귀 호출
        doQuickSort(list, left, pivotIndex - 1);
        doQuickSort(list, pivotIndex + 1, right);
    }
}

// 메인 함수 
int main(int argc, char* argv[]) {
    srand(time(NULL)); 
    int array[SIZE];


    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); //새로운 랜덤 데이터 생성
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); //퀵 정렬 시행

            printf("Result\n");
            printArray(array, SIZE); // 정렬된 배열 출력
            isFirst++; // 첫 번째 반복
        }
        else {
            doQuickSort(array, 0, SIZE - 1); // 다른 반복에서는 퀵 정렬만 시행
        }
        // 값 누적
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}