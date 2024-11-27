#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0;

// 임의의 숫자 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 순차 탐색
int seq_search(int* array, int key, int low, int high) {
    for (int i = low; i <= high; i++) {
        compareCount++;
        if (array[i] == key)
            return i; // 탐색 성공
    }
    return -1; // 탐색 실패
}

// 배열을 분할하는 함수
int partition(int* list, int left, int right) {
    // 랜덤 피벗 선택
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = list[pivotIndex];

    // 피벗을 마지막 요소로 이동
    int temp = list[pivotIndex];
    list[pivotIndex] = list[right];
    list[right] = temp;

    int i = left - 1; // 작은 요소의 인덱스

    for (int j = left; j < right; j++) {
        compareCount++; // 비교 횟수 증가
        if (list[j] <= pivot) {
            i++;
            // 요소를 교환
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }

    // 피벗 위치로 요소를 교환
    temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;

    return i + 1; // 피벗의 최종 위치 반환
}

// 퀵 정렬
void quick_sort(int* list, int left, int right) {
    while (left < right) {
        int q = partition(list, left, right);
        // 작은 부분을 재귀적으로 정렬
        if (q - left < right - q) {
            quick_sort(list, left, q - 1);
            left = q + 1; // 큰 부분은 반복적으로 처리
        }
        else {
            quick_sort(list, q + 1, right);
            right = q - 1; // 작은 부분은 반복적으로 처리
        }
    }
}

// 이진 탐색
int search_binary(int* list, int key, int low, int high) {
    int middle;
    while (low <= high) {
        middle = (low + high) / 2;
        compareCount++;
        if (key == list[middle]) return middle; // 탐색 성공
        else if (key > list[middle]) low = middle + 1; // 왼쪽 부분리스트 탐색
        else high = middle - 1; // 오른쪽 부분리스트 탐색
    }
    return -1; 
}

// 배열 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// 평균 비교 횟수 계산
double getAverageLinearSearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = array[rand() % SIZE]; // 랜덤 인덱스에서 값을 가져옴
        compareCount = 0; 
        seq_search(array, key, 0, SIZE - 1);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100;
}

// 퀵 정렬 비교 횟수 계산
void getQuickSortCompareCount(int* array) {
    compareCount = 0; 
    quick_sort(array, 0, SIZE - 1);
}

// 평균 이진 탐색 비교 횟수 계산
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % SIZE; // 랜덤 인덱스 생성
        int target = array[key]; // 해당 인덱스의 값 가져옴
        compareCount = 0; 
        search_binary(array, target, 0, SIZE - 1); // target으로 탐색
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    // 평균 순차 탐색 비교 횟수 출력
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // 퀵 정렬 및 비교 횟수 출력
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 평균 이진 탐색 비교 횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // 배열 출력
    printArray(array);

    return 0;
}
