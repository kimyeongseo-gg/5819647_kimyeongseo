#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100 // 배열의 크기 정의

// 랜덤 숫자를 생성하여 주어진 배열에 저장하는 함수
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0-999 사이의 랜덤 숫자 생성
    }
}

// 간접 삽입 정렬을 수행하는 함수
void inc_insertion_sort(int list[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;
    for (i = first + gap; i <= last; i += gap) {
        key = list[i]; // 현재 키 값 저장
        (*moveCount)++; // 이동 횟수 증가
        for (j = i - gap; j >= first && key < list[j]; j -= gap) {
            list[j + gap] = list[j]; // 요소 이동
            (*moveCount)++; // 이동 횟수 증가
            (*comparisonCount)++; // 비교 횟수 증가
        }
        list[j + gap] = key; // 키 값을 올바른 위치에 삽입
        (*moveCount)++;
        if (j >= first) (*comparisonCount)++; // 마지막 비교 횟수 증가
    }
}

// 셸 정렬을 수행하는 함수
void doShellSort(int originalArray[], int method, int* comparisonCount, int* moveCount) {
    *comparisonCount = 0; // 비교 횟수 초기화
    *moveCount = 0; // 이동 횟수 초기화

    // 원본 데이터를 복사하여 정렬에 사용
    int list[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list[i] = originalArray[i];
    }

    int gap;
    if (method == 2) {
        // n/2 방식으로 간격 설정
        for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
            printf("Sorting with gap = %d;\n", gap);
            for (int i = 0; i < gap; i++) {
                inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount); // 간접 삽입 정렬 호출
            }
            // 배열의 처음 20개 요소 출력
            for (int k = 0; k < 20 && k < ARRAY_SIZE; k++) {
                printf("%d ", list[k]);
            }
            printf(". . .\n");
        }
    }
    else if (method == 3) {
        // n/3 방식으로 간격 설정
        for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
            printf("Sorting with gap = %d;\n", gap);
            for (int i = 0; i < gap; i++) {
                inc_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount); // 간접 삽입 정렬 호출
            }
            // 배열의 처음 20개 요소 출력
            for (int k = 0; k < 20 && k < ARRAY_SIZE; k++) {
                printf("%d ", list[k]);
            }
            printf(". . .\n");
        }
    }

    // 정렬된 배열 출력
    printf("Sorted shellArray (gap = %d) :\n", method);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 기본 삽입 정렬을 수행하는 함수
void doInsertionSort(int originalArray[], int* comparisonCount, int* moveCount) {
    *comparisonCount = 0; // 비교 횟수 초기화
    *moveCount = 0; // 이동 횟수 초기화

    // 원본 데이터를 복사하여 정렬에 사용
    int list[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list[i] = originalArray[i];
    }

    // 삽입 정렬
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int key = list[i]; // 현재 키 값 저장
        (*moveCount)++;
        int j = i - 1;
        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j]; // 요소 이동
            (*moveCount)++;
            (*comparisonCount)++; // 비교 횟수 증가
            j--;
        }
        list[j + 1] = key; // 키 값을 올바른 위치에 삽입
        (*moveCount)++;
        if (j >= 0) (*comparisonCount)++; // 마지막 비교 횟수 증가
    }

    // 정렬된 배열 출력
    printf("Sorted insertionArray:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 메인 함수
int main() {
    srand(time(NULL)); // 랜덤 시드 초기화
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

 
    generateRandomNumbers(array);


    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);


    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // 삽입 정렬 수행
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0; 
}
