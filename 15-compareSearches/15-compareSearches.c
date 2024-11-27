#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0;

// ������ ���� ����
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// ���� Ž��
int seq_search(int* array, int key, int low, int high) {
    for (int i = low; i <= high; i++) {
        compareCount++;
        if (array[i] == key)
            return i; // Ž�� ����
    }
    return -1; // Ž�� ����
}

// �迭�� �����ϴ� �Լ�
int partition(int* list, int left, int right) {
    // ���� �ǹ� ����
    int pivotIndex = left + rand() % (right - left + 1);
    int pivot = list[pivotIndex];

    // �ǹ��� ������ ��ҷ� �̵�
    int temp = list[pivotIndex];
    list[pivotIndex] = list[right];
    list[right] = temp;

    int i = left - 1; // ���� ����� �ε���

    for (int j = left; j < right; j++) {
        compareCount++; // �� Ƚ�� ����
        if (list[j] <= pivot) {
            i++;
            // ��Ҹ� ��ȯ
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }

    // �ǹ� ��ġ�� ��Ҹ� ��ȯ
    temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;

    return i + 1; // �ǹ��� ���� ��ġ ��ȯ
}

// �� ����
void quick_sort(int* list, int left, int right) {
    while (left < right) {
        int q = partition(list, left, right);
        // ���� �κ��� ��������� ����
        if (q - left < right - q) {
            quick_sort(list, left, q - 1);
            left = q + 1; // ū �κ��� �ݺ������� ó��
        }
        else {
            quick_sort(list, q + 1, right);
            right = q - 1; // ���� �κ��� �ݺ������� ó��
        }
    }
}

// ���� Ž��
int search_binary(int* list, int key, int low, int high) {
    int middle;
    while (low <= high) {
        middle = (low + high) / 2;
        compareCount++;
        if (key == list[middle]) return middle; // Ž�� ����
        else if (key > list[middle]) low = middle + 1; // ���� �κи���Ʈ Ž��
        else high = middle - 1; // ������ �κи���Ʈ Ž��
    }
    return -1; 
}

// �迭 ���
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)
        printf("%3d ", array[i]);
    printf("\n");
}

// ��� �� Ƚ�� ���
double getAverageLinearSearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = array[rand() % SIZE]; // ���� �ε������� ���� ������
        compareCount = 0; 
        seq_search(array, key, 0, SIZE - 1);
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100;
}

// �� ���� �� Ƚ�� ���
void getQuickSortCompareCount(int* array) {
    compareCount = 0; 
    quick_sort(array, 0, SIZE - 1);
}

// ��� ���� Ž�� �� Ƚ�� ���
double getAverageBinarySearchCompareCount(int* array) {
    double totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % SIZE; // ���� �ε��� ����
        int target = array[key]; // �ش� �ε����� �� ������
        compareCount = 0; 
        search_binary(array, target, 0, SIZE - 1); // target���� Ž��
        totalCompareCount += compareCount;
    }
    return totalCompareCount / 100;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    // ��� ���� Ž�� �� Ƚ�� ���
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // �� ���� �� �� Ƚ�� ���
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // ��� ���� Ž�� �� Ƚ�� ���
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    // �迭 ���
    printArray(array);

    return 0;
}
