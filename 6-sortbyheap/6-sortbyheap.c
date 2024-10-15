#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i; // 루트
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 루트보다 큰 경우
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 오른쪽 자식이 현재 가장 큰 값보다 큰 경우
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 루트가 가장 큰 값이 아닌 경우
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void BuildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

void resortHeap(int arr[], int n, int i) {
    maxHeapify(arr, n, i);
}

//현재 상태 출력 함수
void printCurrentState(int arr[], int n) {
    for (int j = 0; j < n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

void insertAndHeapify(int inputData[], int* n, int newElement) {
    // 배열에 새로운 요소 추가
    inputData[*n] = newElement;
    (*n)++;

    // 힙을 재구성
    BuildMaxHeap(inputData, *n);

    // 현재 상태 출력
    printCurrentState(inputData, *n);
}


void insertElementsAndPrintHeap(int inputData[], int newElements[], int newSize, int* size) {
    // 배열에 하나씩 요소 삽입하며 상태 출력
    for (int i = 0; i < newSize; i++) {
        insertAndHeapify(inputData, size, newElements[i]);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n) {
    int size = 0; // 현재 배열 크기

    // 삽입할 요소
    int newElements[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int newSize = sizeof(newElements) / sizeof(newElements[0]);

    // 요소 삽입하고 상태 출력하기
    insertElementsAndPrintHeap(inputData, newElements, newSize, &size);

    // 최대 힙 생성
    BuildMaxHeap(inputData, n);

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--) {

        // 현재 루트(최대값)를 배열의 마지막 요소와 교환
        swap(&inputData[0], &inputData[i]);

        // 힙 크기를 줄이고 힙 재정렬
        resortHeap(inputData, i, 0);

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);


    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);


    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
