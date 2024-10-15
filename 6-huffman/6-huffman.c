#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

// 트리 노드 구조체
typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 힙의 노드 구조체
typedef struct {
    TreeNode* ptree;
    char ch;
    int key;
} element;

// 힙 구조체
typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 힙 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;
}

// 힙에 노드를 삽입하는 함수
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);
    while (i != 1 && item.key < h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}

// 힙에서 최소 노드를 삭제하는 함수
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

// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    node->weight = left->weight + right->weight; // 부모 노드의 가중치
    node->ch = '\0'; // 부모 노드는 문자 없음
    return node;
}

// 트리 노드가 리프 노드인지 확인하는 함수
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 허프만 코드 출력 함수
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 코드 생성 및 출력 함수
void print_codes(TreeNode* root, int codes[], int top) {
    if (root->left) {
        codes[top] = 1; // 왼쪽 자식은 1
        print_codes(root->left, codes, top + 1);
    }
    if (root->right) {
        codes[top] = 0; // 오른쪽 자식은 0
        print_codes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) {
        printf("%c: ", root->ch);
        print_array(codes, top);
    }
}

// 허프만 트리 생성 함수
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

        // 힙에 추가된 후의 상태 출력

        for (int j = 1; j <= heap->heap_size; j++) {
            printf("%d ", heap->heap[j].key);
        }
        printf("\n");
    }

    // 병합 및 힙 변화 과정 출력
    for (i = 1; i < size; i++) {
        // 최소값을 가지는 두 개의 노드를 삭제
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);

        // 두 개의 노드를 합친다.
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x->weight;
        e.ptree = x;

        printf("/// %d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);

        // 힙 변화 과정 출력

        for (int j = 1; j <= heap->heap_size; j++) {
            printf("%d ", heap->heap[j].key);
        }
        printf("\n");
    }

    e = delete_min_heap(heap); // 최종 트리
    free(heap);
    return e.ptree; // 최종 트리의 루트 반환
}

// 허프만 코드 생성 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);
    int* arr = (int*)malloc(size * sizeof(int)); // 동적 메모리 할당
    int top = 0;
    print_codes(root, arr, top);
    free(arr); // 동적 메모리 해제
}

// 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
