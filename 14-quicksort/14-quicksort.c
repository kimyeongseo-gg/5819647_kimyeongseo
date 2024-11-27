#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// �� �� �̵� Ƚ�� �۷ι� ����
int comparisonCount = 0;
int moveCount = 0;
int isFirst = 0;
int rounds = 0;
double totalComparisons = 0;
double totalMoveCount = 0;

// ���� �迭 ���� �Լ�
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;  // 0-999 ���� ���� ����
    }
}

// �迭 ��� �Լ�
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ��Ƽ�� �Լ�
int partition(int list[], int left, int right) {
    int pivot = list[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        comparisonCount++; // �� Ƚ�� ����

        if (list[j] <= pivot) {
            i++;

            // �̵� Ƚ�� ����
            moveCount += 3;

            // ��� ��ȯ
            int temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }

    // ������ ����
    moveCount += 3;
    int temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;

    return i + 1;
}

// �� ���� ��� �Լ�
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        // ��� �κ�: 40~60 ������ �� ���
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", list[i]);
            printf("\n\n");
        }
        rounds++;

        int pivotIndex = partition(list, left, right);

        // ��� ȣ��
        doQuickSort(list, left, pivotIndex - 1);
        doQuickSort(list, pivotIndex + 1, right);
    }
}

// ���� �Լ� 
int main(int argc, char* argv[]) {
    srand(time(NULL)); 
    int array[SIZE];


    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); //���ο� ���� ������ ����
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); //�� ���� ����

            printf("Result\n");
            printArray(array, SIZE); // ���ĵ� �迭 ���
            isFirst++; // ù ��° �ݺ�
        }
        else {
            doQuickSort(array, 0, SIZE - 1); // �ٸ� �ݺ������� �� ���ĸ� ����
        }
        // �� ����
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}