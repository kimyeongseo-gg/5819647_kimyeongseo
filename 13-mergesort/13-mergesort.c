#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define MAX_SIZE 1000 // 0-999 사이의 랜덤 데이터 범위

int sorted[MAX_SIZE]; // 추가 공간을 위한 배열
int comparisonCount = 0; // 비교 횟수
int moveCount = 0; // 이동 횟수
int totalComparisons = 0;
int totalMoves = 0;
int isFirst = 0;

void generateRandomArray(int array[]) {
    int count = 0;
    while (count < SIZE) {
        int num = rand() % 1000; // 0-999 사이의 랜덤 데이터
        int isDuplicate = 0;

        // 중복 체크
        for (int i = 0; i < count; i++) {
            if (array[i] == num) {
                isDuplicate = 1;
                break;
            }
        }

        // 중복이 아닐 경우 배열에 추가
        if (!isDuplicate) {
            array[count++] = num;
        }
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

void merge(int list[], int left, int mid, int right, int rounds) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        comparisonCount++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++; // 요소가 sorted 배열로 이동
    }

    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++; // 요소가 sorted 배열로 이동
    }

    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++; // 요소가 sorted 배열로 이동
    }

    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++; // 요소가 list 배열로 이동
    }

    if (rounds % 10 == 0 && isFirst == 0) { //10 번에 한번만 출력
        for (int i = 0; i < 10; i++) //0 ~ 9 값
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

void iterativeMergeSort(int list[], int n) {
    int rounds = 0;
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right) {
                rounds++;
                merge(list, left, mid, right, rounds);
            }
        }
    }
}

int main() {
    int array[SIZE];

    srand(time(NULL)); // 랜덤 시드 초기화

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array, SIZE);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            iterativeMergeSort(array, SIZE);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}