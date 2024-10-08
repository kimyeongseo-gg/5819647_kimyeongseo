#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;


typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int isThreaded; 
} ThreadNode;


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


void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}


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

void SetThreadedInOrder(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL)
        return;

    
    SetThreadedInOrder(root->left, prev);

    
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1; 
    }

    
    *prev = root;

    
    if (root->isThreaded == 0) {
        SetThreadedInOrder(root->right, prev);
    }
}


ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertThreadTree(root, inputData[i]);
    }

    
    ThreadNode* prev = NULL;
    SetThreadedInOrder(root, &prev);

    return root;
}


void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    
    while (current->left != NULL) {
        current = current->left;
    }

    
    while (current != NULL) {
        printf("%d ", current->data);

        
        if (current->isThreaded) {
            current = current->right;
        }
        else {
            
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}


int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
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

    
    free(root);
    free(troot);

    return 0;
}
