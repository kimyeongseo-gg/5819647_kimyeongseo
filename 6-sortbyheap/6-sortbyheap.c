#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i; // ��Ʈ
    int left = 2 * i + 1; // ���� �ڽ�
    int right = 2 * i + 2; // ������ �ڽ�

    // ���� �ڽ��� ��Ʈ���� ū ���
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // ������ �ڽ��� ���� ���� ū ������ ū ���
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // ��Ʈ�� ���� ū ���� �ƴ� ���
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

//���� ���� ��� �Լ�
void printCurrentState(int arr[], int n) {
    for (int j = 0; j < n; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

void insertAndHeapify(int inputData[], int* n, int newElement) {
    // �迭�� ���ο� ��� �߰�
    inputData[*n] = newElement;
    (*n)++;

    // ���� �籸��
    BuildMaxHeap(inputData, *n);

    // ���� ���� ���
    printCurrentState(inputData, *n);
}


void insertElementsAndPrintHeap(int inputData[], int newElements[], int newSize, int* size) {
    // �迭�� �ϳ��� ��� �����ϸ� ���� ���
    for (int i = 0; i < newSize; i++) {
        insertAndHeapify(inputData, size, newElements[i]);
    }
}

void BuildMaxHeapAndSort(int inputData[], int n) {
    int size = 0; // ���� �迭 ũ��

    // ������ ���
    int newElements[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int newSize = sizeof(newElements) / sizeof(newElements[0]);

    // ��� �����ϰ� ���� ����ϱ�
    insertElementsAndPrintHeap(inputData, newElements, newSize, &size);

    // �ִ� �� ����
    BuildMaxHeap(inputData, n);

    // �ϳ��� ������ ��Ʈ(�ִ밪)�� �����ϰ� ����
    for (int i = n - 1; i > 0; i--) {

        // ���� ��Ʈ(�ִ밪)�� �迭�� ������ ��ҿ� ��ȯ
        swap(&inputData[0], &inputData[i]);

        // �� ũ�⸦ ���̰� �� ������
        resortHeap(inputData, i, 0);

        // �� ������ �� ���� ���
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
