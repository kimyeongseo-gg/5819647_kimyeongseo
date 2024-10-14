#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    if (h == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(1); // �޸� �Ҵ� ���� �� ���α׷� ����
    }
    h->heap_size = 0; // �ʱ� �� ũ�� 0���� ����
    return h;
}

// ���� ���� ���¸� ����ϴ� �Լ�
void printHeap(HeapType* h) {
    for (int j = 1; j <= h->heap_size; j++) {
        printf("%d ", h->heap[j].key); // ���� �� ��� ���
    }
    printf("\n");
}

// �ִ� ���� ���ο� ��Ҹ� �߰��ϴ� �Լ�
void insert_max_heap(HeapType* h, element item, bool show) {
    if (h->heap_size >= MAX_ELEMENT - 1) {
        printf("���� ���� á���ϴ�.\n");
        return; // �迭 ���� �ʰ� ����
    }

    int i = ++(h->heap_size); // ���� ũ�⸦ ������Ű�� �� ��ġ ����
    h->heap[i] = item; // ���ο� ��带 ������ ��ġ�� ����

    // ���ο� ��尡 ���Ե� ������ ���� ���
    if (show) {

        printHeap(h); // ���� ���� ���
    }

    int move_count = 0; // �̵� Ƚ�� �ʱ�ȭ

    // �θ� ���� ���Ͽ� ��ġ�� �����ϴ� ����
    while (i != 1 && h->heap[i].key > h->heap[i / 2].key) {
        // �θ� ���� ���� ����� ���� ��ȯ
        element temp = h->heap[i];
        h->heap[i] = h->heap[i / 2];
        h->heap[i / 2] = temp;

        i /= 2; // �θ� ���� �̵�
        move_count++; // �̵� Ƚ�� ����

        if (show) {
            printHeap(h); // ���� ���� ��� (�߰� ���� ���)
        }
    }

    if (show) {
        printf("��尡 �̵��� Ƚ��: %d\n", move_count); // �̵� Ƚ�� ���
    }
}


// �ִ� ������ ��Ʈ ��带 �����ϴ� �Լ�
element delete_max_heap(HeapType* h) {
    if (h->heap_size == 0) {
        printf("���� ��� �ֽ��ϴ�.\n");
        element empty = { -1 }; // �� �� ��ȯ
        return empty;
    }

    int parent, child; // �θ�, �ڽ� ��� �ε���
    element item, temp; // ������ �����۰� ������ ��� ����

    item = h->heap[1]; // ��Ʈ ��� ����
    temp = h->heap[h->heap_size--]; // ������ ��带 ��Ʈ�� �̵�
    parent = 1; // ��Ʈ ���� �ʱ�ȭ
    child = 2; // �ڽ� ��� �ʱ�ȭ
    int move_count = 0; // �̵� Ƚ�� �ʱ�ȭ

    h->heap[1] = h->heap[h->heap_size + 1];

    printHeap(h);
    // ���� ������ �����ϵ��� ��� ��ġ ����
    while (child <= h->heap_size) {
        // ���� ����� �ڽ� ��� �� �� ū �ڽ� ��带 ã�´�.
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++; // �� ū �ڽ����� �̵�
        }
        if (temp.key >= h->heap[child].key)
            break; // ���� ��尡 �� ũ�� ����
        // �� �ܰ� �Ʒ��� �̵�
        element swap = h->heap[parent];
        h->heap[parent] = h->heap[child];
        h->heap[child] = swap;
        parent = child; // �θ� ��� �ε��� ����
        child *= 2; // �ڽ� ��� �ε��� ����
        move_count++; // �̵� Ƚ�� ����
        printHeap(h); // ���� ���� ��� (�߰� ���� ���)
    }
    h->heap[parent] = temp; // ������ ��带 �� ��ġ�� ����
    move_count++;
    printf("��尡 �̵��� Ƚ��: %d\n", move_count); // �̵� Ƚ�� ���
    return item; // ������ ��Ʈ ��� ��ȯ
}




// ���� �������� ����ϴ� �Լ�
void printHeapByLevel(HeapType* h) {
    if (h->heap_size == 0) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }
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

    for (true;;) {
        printf("\n"); // �ٹٲ�
        printf("\n"); // �ٹٲ�

        printf("*-*=======================*-*\n");
        printf("|    i : ��� �߰�          |\n");
        printf("|    d : ��� ����          |\n");
        printf("|    p : ������ ���        |\n");
        printf("|    c : ����               |\n");
        printf("*-*========================*-*\n");

        printf("\n"); // �ٹٲ�

        printf("\n�޴� �Է� (i: �߰�, d: ����, p: ���, c: ����): ");
        scanf_s(" %c", &command); // ����� �Է� �ޱ�

        switch (command) {
        case 'i':
            printf("�߰��� �� �Է�: ");
            scanf_s("%d", &item.key); // �߰��� �� �Է�
            insert_max_heap(heap, item, true); // ���� �߰�
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
            printf("�߸��� �Է��Դϴ�.\n");
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
        insert_max_heap(heap, item, false); // ���� ��� �߰�
    }
    return heap;
}


int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 }; // �ʱ� ������
    int size = sizeof(inputData) / sizeof(inputData[0]); // ������ ũ�� ���


    HeapType* heap = generateMaxHeapTree(inputData, size);


    runUserInterface(heap);

    free(heap);
    return 0;
}