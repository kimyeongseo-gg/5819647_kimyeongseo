#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

void generateRandomData(int list[]) {
    int n = SIZE;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;  // 0-999 ������ ���� ������ ����
    }
}

void doSelectionSort(int list[]) {
    int n = SIZE;
    int i, j, least, temp;
    printf("���� ����");

    printf("\n");
    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) { // �ּڰ� Ž��
            if (list[j] < list[least]) least = j;
        }
        SWAP(list[i], list[least], temp);

        // 10, 30, 50, ..., n-1 �ܰ迡�� ���
        if ((i + 1) % 20 == 10 || i == n - 2) {
            printf("step %d: ", (i + 1));
            for (int k = 0; k < n; k++) {
                printf("%d ", list[k]);
            }
            printf("\n");
        }
    }
    
}

void doInsertionSort(int randomData[]) {
    int n = SIZE;
    int totalComparisons = 0;  // �� �� Ƚ�� ����

    // 20ȸ ���� ���� �õ�
    for (int trial = 0; trial < 20; trial++) {
        int insertionData[SIZE];

        // ���� �����͸� �����Ͽ� ���� ���Ŀ� ���
        generateRandomData(insertionData, SIZE);  // ���ο� ���� ������ ����

        int comparisons = 0;  // ���� �õ��� �� Ƚ�� �ʱ�ȭ

        // ���� ���� ����
        for (int i = 1; i < n; i++) {
            int key = insertionData[i];
            int j = i - 1;
            while (j >= 0 && insertionData[j] > key) {
                insertionData[j + 1] = insertionData[j]; // ���ڵ��� ������ �̵�
                j--;
                comparisons++;  // �� Ƚ�� ����
            }
            insertionData[j + 1] = key;
            comparisons++;  // ������ �� Ƚ�� ����
        }

        totalComparisons += comparisons;  // �õ������� �� Ƚ�� ����


    }
    printf("\n");
    // ��� �� Ƚ�� ���
    printf("���� ���� ��� �� Ƚ��: %d\n", totalComparisons / 20);

    printf("\n");
    // ���� ����� ���
    printf("���� ���� ���: ");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", randomData[k]);
    }
    printf("\n");

   
}


void doBubbleSort(int randomData[]) {
    int n = SIZE;
    int totalMoves = 0;  // ��ü �̵� Ƚ�� �ʱ�ȭ

    // 20ȸ ���� ���� �õ�
    for (int trial = 0; trial < 20; trial++) {
        int bubbleData[SIZE];

        // ���� �����͸� �����Ͽ� ���� ���Ŀ� ���
        generateRandomData(bubbleData, SIZE);  // ���ο� ���� ������ ����

        int moves;  // ���� �õ��� �̵� Ƚ�� �ʱ�ȭ
        for (int i = n - 1; i > 0; i--) {
            moves = 0; // �� �ݺ����� �̵� Ƚ�� �ʱ�ȭ
            for (int j = 0; j < i; j++) { // �յ��� ���ڵ带 ���� �� ��ü
                if (bubbleData[j] > bubbleData[j + 1]) {
                    // ����
                    int temp = bubbleData[j];
                    bubbleData[j] = bubbleData[j + 1];
                    bubbleData[j + 1] = temp;
                    moves += 3; // ���� �� 3ȸ �̵����� ���
                }
            }
            totalMoves += moves; // ��ü �̵� Ƚ���� �߰�
        }


    }

     printf("\n");
    // ��� �̵� Ƚ�� ���
    printf("���� ���� ��� �̵� Ƚ��: %d\n", totalMoves / 20);
    printf("\n");


    // ���� ��� ���
    printf("���� ���� ���:");
    for (int k = 0; k < SIZE; k++) {
        printf("%d ", randomData[k]);
    }

   
}

int main() {
    int randomData[SIZE];
    generateRandomData(randomData);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}
