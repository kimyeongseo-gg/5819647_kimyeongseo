#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 배열 트리 생성 함수
void GenerateArrayTree(int* tree) {
    // 링크드 트리와 동일한 구조로 트리 순서에 맞는 수 입력
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    // 배열 출력
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// 배열 전위 순회
void ArrayPreOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        printf("%d ", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1, size); // 왼쪽 자식
        ArrayPreOrder(tree, 2 * index + 2, size); // 오른쪽 자식
    }
}

// 배열 중위 순회
void ArrayInOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        ArrayInOrder(tree, 2 * index + 1, size); // 왼쪽 자식
        printf("%d ", tree[index]);
        ArrayInOrder(tree, 2 * index + 2, size); // 오른쪽 자식
    }
}

// 배열 후위 순회
void ArrayPostOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        ArrayPostOrder(tree, 2 * index + 1, size); // 왼쪽 자식
        ArrayPostOrder(tree, 2 * index + 2, size); // 오른쪽 자식
        printf("%d ", tree[index]);
    }
}

// 배열 순회 함수 호출
void ArrayOrders(int* tree, int size) {
    printf("Array PreOrder: ");
    ArrayPreOrder(tree, 0, size);
    printf("\n");

    printf("Array InOrder: ");
    ArrayInOrder(tree, 0, size);
    printf("\n");

    printf("Array PostOrder: ");
    ArrayPostOrder(tree, 0, size);
    printf("\n");
}


void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}


void GenerateLinkTree(TreeNode** root) {
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->data = 1; // 루트 노드
    (*root)->left = NULL;
    (*root)->right = NULL;

    // 링크드 트리 구성 (배열과 동일한 구조)
    PlaceNode(*root, 0, 2);   // 2
    PlaceNode(*root, 1, 9);   // 9
    PlaceNode((*root)->left, 0, 3);   // 3
    PlaceNode((*root)->left, 1, 5);   // 5
    PlaceNode((*root)->right, 0, 10); // 10
    PlaceNode((*root)->right, 1, 13); // 13
    PlaceNode((*root)->left->left, 0, 4); // 4
    PlaceNode((*root)->left->left, 1, 6); // 6
    PlaceNode((*root)->left->right, 0, 7); // 7
    PlaceNode((*root)->left->right, 1, 8); // 8
    PlaceNode((*root)->right->left, 0, 11); // 11
    PlaceNode((*root)->right->left, 1, 12); // 12
    PlaceNode((*root)->right->right, 0, 14); // 14
    PlaceNode((*root)->right->right, 1, 15); // 15
}


// 링크드 트리 전위 순회
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return; {
        printf("%d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

// 링크드 트리 중위 순회
void LinkInOrder(TreeNode* root) {
    if (root) {
        LinkInOrder(root->left);
        printf("%d ", root->data);
        LinkInOrder(root->right);
    }
}

// 링크드 트리 후위 순회
void LinkPostOrder(TreeNode* root) {
    if (root) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%d ", root->data);
    }
}

// 링크드 트리 순회 함수 호출
void LinkOrders(TreeNode* root) {
    printf("Link PreOrder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Link InOrder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Link PostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15] = { 0 }; // 배열 초기화
    TreeNode* root = NULL;


    GenerateArrayTree(arr);
    ArrayOrders(arr, 15);

    GenerateLinkTree(&root);
    LinkOrders(root);

    return 0;
}
