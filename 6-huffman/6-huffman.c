#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

// Ʈ�� ��� ����ü
typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���� ��� ����ü
typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

// �� ����ü
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// �� ���� �Լ�
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// �� �ʱ�ȭ �Լ�
void init(HeapType* h) {
    h->heap_size = 0;
}

// ���� ��带 �����ϴ� �Լ�
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // ���ο� ��带 ����
}

// ������ �ּ� ��带 �����ϴ� �Լ�
element delete_min_heap(HeapType* h) {
    element item = h->heap[1];
    element temp = h->heap[(h->heap_size)--];
    int parent = 1, child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) {
            child++;
        }
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// ���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    node->weight = left->weight + right->weight; // �θ� ����� ����ġ
    node->ch = '\0'; // �θ� ���� ���� ����
    return node;
}

// Ʈ�� ��尡 ���� ������� Ȯ���ϴ� �Լ�
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// ������ �ڵ� ��� �Լ�
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// ������ �ڵ� ���� �� ��� �Լ�
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; // ���� �ڽ��� 1
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0; // ������ �ڽ��� 0
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// ������ Ʈ�� ���� �Լ�
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    int i;
    TreeNode* node, * x;
    HeapType* heap = create();
    element e, e1, e2;

    init(heap);
    for (i = 0; i < size; i++) {
        node = (TreeNode*)malloc(sizeof(TreeNode));
        node->ch = characters[i];
        node->weight = frequencies[i];
        node->left = node->right = NULL;
        e.ch = node->ch;
        e.key = node->weight;
        e.ptree = node;
        insert_min_heap(heap, e);

        // ���� �߰��� ���� ���� ���

        for (int j = 1; j <= heap->heap_size; j++) {
            printf("%d ", heap->heap[j].key);
        }
        printf("\n");
    }

    // ���� �� �� ��ȭ ���� ���
    for (i = 1; i < size; i++) {
        // �ּҰ��� ������ �� ���� ��带 ����
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);

        // �� ���� ��带 ��ģ��.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight;
        e.ptree = x;

        printf("/// %d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);

        // �� ��ȭ ���� ���

        for (int j = 1; j <= heap->heap_size; j++) {
            printf("%d ", heap->heap[j].key);
        }
        printf("\n");
    }

    e = delete_min_heap(heap); // ���� Ʈ��
    free(heap);
    return e.ptree; // ���� Ʈ���� ��Ʈ ��ȯ
}

// ������ �ڵ� ���� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int)); // ���� �޸� �Ҵ�
    int top = 0;
    print_codes(root, arr, top);
    free(arr); // ���� �޸� ����
}

// ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
