#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리의 노드 구조체
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 스레드 이진 트리의 노드 구조체
typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int isThreaded; // 1이면 스레드임
} ThreadNode;

// 이진 탐색 트리 생성 함수
TreeNode* InsertBinaryTree(TreeNode* root, int data) {
    if (root == NULL) {
        root = (TreeNode*)malloc(sizeof(TreeNode));
        root->data = data;
        root->left = root->right = NULL;
    }
    else if (data < root->data) {
        root->left = InsertBinaryTree(root->left, data);
    }
    else {
        root->right = InsertBinaryTree(root->right, data);
    }
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertBinaryTree(root, inputData[i]);
    }
    return root;
}

// 이진 탐색 트리 중위 순회 함수
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// 스레드 이진 트리 생성 함수
ThreadNode* InsertThreadTree(ThreadNode* root, int data) {
    if (root == NULL) {
        root = (ThreadNode*)malloc(sizeof(ThreadNode));
        root->data = data;
        root->left = root->right = NULL;
        root->isThreaded = 0;
    }
    else if (data < root->data) {
        root->left = InsertThreadTree(root->left, data);
    }
    else {
        root->right = InsertThreadTree(root->right, data);
    }
    return root;
}

// 스레드 이진 트리에서 중위 순회를 위한 스레드 설정
void SetThreadedInOrder(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL)
        return;

    // 왼쪽 서브트리로 재귀
    SetThreadedInOrder(root->left, prev);

    // 스레드 설정: 이전 노드가 존재하고, 이전 노드의 오른쪽이 비어 있으면
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1; // 스레드로 연결되었음을 표시
    }

    // 이전 노드를 현재 노드로 갱신
    *prev = root;

    // 오른쪽 서브트리로 재귀
    if (root->isThreaded == 0) {
        SetThreadedInOrder(root->right, prev);
    }
}

// 스레드 이진 트리 생성 후 스레드 설정
ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertThreadTree(root, inputData[i]);
    }

    // 스레드 설정
    ThreadNode* prev = NULL;
    SetThreadedInOrder(root, &prev);

    return root;
}

// 스레드 이진 트리의 중위 순회 함수
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    // 가장 왼쪽 노드 찾기
    while (current->left != NULL) {
        current = current->left;
    }

    // 중위 순회 시작
    while (current != NULL) {
        printf("%d ", current->data);

        // 스레드가 있으면 다음 노드로 이동
        if (current->isThreaded) {
            current = current->right;
        }
        else {
            // 오른쪽 서브트리에서 가장 왼쪽 노드로 이동
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}

// 메인 함수
int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 이진 탐색 트리 생성 및 중위 순회
    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // 스레드 이진 트리 생성 및 중위 순회
    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    // 메모리 해제
    free(root);
    free(troot);

    return 0;
}
