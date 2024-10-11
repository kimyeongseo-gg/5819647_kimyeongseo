#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 200 // �ִ� ���� ũ��

// ���� �� ��Ҹ� ǥ���ϴ� ����ü
typedef struct {
    int key; // ���� Ű ��
} element;

// ���� ǥ���ϴ� ����ü
typedef struct {
    element heap[MAX_ELEMENT]; // �� �迭
    int heap_size; // ���� ���� ũ��
} HeapType;

// ���� �����ϴ� �Լ�
HeapType* create() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType)); // �� �޸� �Ҵ�
    h->heap_size = 0; // �ʱ� �� ũ�� 0���� ����
    return h;
}



// �ִ� ���� ���ο� ��Ҹ� �߰��ϴ� �Լ�
void insert_max_heap(HeapType* h, element item) {
    int i = ++(h->heap_size); // ���� ũ�⸦ ������Ű�� �� ��ġ ����
    int move_count = 0; // �̵� Ƚ�� �ʱ�ȭ

    // �θ� ���� ���Ͽ� ��ġ�� �����ϴ� ����
    while (i != 1 && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2]; // �θ� ��带 ��������
        i /= 2; // �θ� ���� �̵�
        move_count++; // �̵� Ƚ�� ����
        printHeap(h); // ���� ���� ���
    }
    h->heap[i] = item; // ���ο� ��带 ����
    printHeap(h); // ���� ���� ���
    printf("��尡 �̵��� Ƚ��: %d\n", move_count); // �̵� Ƚ�� ���
}

// �ִ� ������ ��Ʈ ��带 �����ϴ� �Լ�
element delete_max_heap(HeapType* h) {
    int parent, child; // �θ�, �ڽ� ��� �ε���
    element item, temp; // ������ �����۰� ������ ��� ����

    item = h->heap[1]; // ��Ʈ ��� ����
    temp = h->heap[(h->heap_size)--]; // ������ ��带 ��Ʈ�� �̵�
    parent = 1; // ��Ʈ ���� �ʱ�ȭ
    child = 2; // �ڽ� ��� �ʱ�ȭ
    int move_count = 0; // �̵� Ƚ�� �ʱ�ȭ

    // ���� ������ �����ϵ��� ��� ��ġ ����
    while (child <= h->heap_size) {
        // ���� ����� �ڽ� ��� �� �� ū �ڽ� ��带 ã�´�.
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++; // �� ū �ڽ����� �̵�
        }
        if (temp.key >= h->heap[child].key) break; // ���� ��尡 �� ũ�� ����
        // �� �ܰ� �Ʒ��� �̵�
        h->heap[parent] = h->heap[child];
        parent = child; // �θ� ��� �ε��� ����
        child *= 2; // �ڽ� ��� �ε��� ����
        move_count++; // �̵� Ƚ�� ����
        printHeap(h); // ���� ���� ���
    }
    h->heap[parent] = temp; // ������ ��带 �� ��ġ�� ����
    printf("������ ���: %d\n", item.key); // ������ ��� ���
    printHeap(h); // ���� ���� ���
    printf("��尡 �̵��� Ƚ��: %d\n", move_count); // �̵� Ƚ�� ���
    return item; // ������ ��Ʈ ��� ��ȯ
}

// ���� �������� ����ϴ� �Լ�
void printHeapByLevel(HeapType* h) {
    int level = 1; // ���� ����
    int nodesAtCurrentLevel = 1; // ���� �������� ����� ��� ��
    int currentNodeIndex = 1; // ���� ��� �ε���

    // �� ������ ���� �ݺ�
    while (currentNodeIndex <= h->heap_size) {
        printf("���� %d: ", level); // ���� ���� ���
        for (int i = 0; i < nodesAtCurrentLevel && currentNodeIndex <= h->heap_size; i++) {
            printf("[%d] ", h->heap[currentNodeIndex].key); // ���� ��� ���
            currentNodeIndex++; // ���� ���� �̵�
        }
        printf("\n"); // �ٹٲ�
        level++; // ���� ����
        nodesAtCurrentLevel *= 2; // ���� ������ ��� ��
    }
}

// ����� �������̽��� �����ϴ� �Լ�
void runUserInterface(HeapType* heap) {
    char command; // ����� ��� ����
    element item; // �Է��� ���

    while (1) {
        printf("\n�޴� �Է� (i: �߰�, d: ����, p: ���, c: ����): ");
        scanf_s(" %c", &command); // ����� �Է� �ޱ�

        switch (command) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf_s("%d", &item.key); // �߰��� �� �Է�
            insert_max_heap(heap, item); // ���� �߰�
            break;

        case 'd':
            if (heap->heap_size == 0) {
                printf("������ ��尡 �����ϴ�.\n"); // ���� ������� ���
            }
            else {
                delete_max_heap(heap); // ��Ʈ ��� ����
            }
            break;

        case 'p':
            printf("Ʈ�� ������ ���:\n");
            printHeapByLevel(heap); // �������� �� ���
            break;

        case 'c':
            printf("���α׷��� ���� �Ǿ����ϴ�.\n");
            return; // ���α׷� ����

        default:
            printf("�߸��� �Է��Դϴ�.\n"); // �߸��� �Է� ó��
            break;
        }
    }
}

// �־��� �迭�� ����Ͽ� �ִ� ���� �����ϴ� �Լ�
HeapType* generateMaxHeapTree(int inputData[], int size) {
    HeapType* heap = create(); // �� ����
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i]; // �Է� �����ͷ� ��� �ʱ�ȭ
        insert_max_heap(heap, item); // ���� ��� �߰�
    }
    return heap; // ������ �� ��ȯ
}

// ���α׷��� ������
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // �ʱ� ������
    int size = sizeof(inputData) / sizeof(inputData[0]); // ������ ũ�� ���

    // ���� ����
    HeapType* heap = generateMaxHeapTree(inputData, size);

    // ����� �������̽� ����
    runUserInterface(heap);

    // �޸� ����
    free(heap);
    return 0;
}
