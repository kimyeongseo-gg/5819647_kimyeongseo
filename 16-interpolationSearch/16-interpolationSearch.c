#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

// 랜덤 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000;
    }
}

// 퀵소트를 위한 partition 함수
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];

    do {
        do
            low++;
        while (low <= right && list[low] < pivot);
        do
            high--;
        while (high >= left && list[high] > pivot);
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);

    SWAP(list[left], list[high], temp);
    return high;
}

// 퀵소트 함수
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);
        QuickSort(list, left, q - 1);
        QuickSort(list, q + 1, right);
    }
}

// 배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%4d ", array[i]);
    printf("\n\n");
}

// 이진 탐색 함수
int binarySearch(int* array, int key, int* compareCount) {
    int low = 0;
    int high = SIZE - 1;
    *compareCount = 0;

    while (low <= high) {
        (*compareCount)++;
        int middle = (low + high) / 2;
        if (key == array[middle]) return middle;
        else if (key > array[middle]) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

// 보간 탐색 함수 수정
int interpolationSearch(int* array, int key, int* compareCount) {
    int low = 0;
    int high = SIZE - 1;
    *compareCount = 0;

    while (1) {
        // 범위 체크 및 비교 횟수 증가
        (*compareCount)++;
        if (array[high] < key || key <= array[low])
            break;

        // 보간 위치 계산
        int j = ((float)(key - array[low]) / (array[high] - array[low])
            * (high - low)) + low;

        (*compareCount)++; // 현재 위치의 값과 키 값 비교
        if (key > array[j]) {
            low = j + 1;
        }
        else if (key < array[j]) {
            high = j - 1;
        }
        else {
            return j; // 키를 찾은 경우
        }
    }

    // 마지막 위치 확인
    (*compareCount)++;
    if (array[low] == key) return low;
    return -1;
}


// 평균 이진 탐색 비교 횟수 계산
float getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    int compareCount;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        binarySearch(array, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return (float)totalCompareCount / 1000;
}

// 평균 보간 탐색 비교 횟수 계산
float getAverageInterpolationSearchComparecount(int* array) {
    int totalCompareCount = 0;
    int compareCount;

    for (int i = 0; i < 1000; i++) {
        int target = array[rand() % SIZE];
        interpolationSearch(array, target, &compareCount);
        totalCompareCount += compareCount;
    }
    return (float)totalCompareCount / 1000;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);
    QuickSort(array, 0, SIZE - 1);
    printArray(array);

    printf("Average Compare Count of Binary Search: %.2f\n",
        getAverageBinarySearchCompareCount(array));
    printf("Average Compare Count of Interpolation Search: %.2f\n",
        getAverageInterpolationSearchComparecount(array));

    return 0;
}
