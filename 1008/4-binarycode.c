#include <stdio.h>
#include <stdlib.h>

// ���� Ž�� Ʈ���� ��� ����ü
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// ������ ���� Ʈ���� ��� ����ü
typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int isThreaded; // 1�̸� ��������
} ThreadNode;

// ���� Ž�� Ʈ�� ���� �Լ�
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

// ���� Ž�� Ʈ�� ���� ��ȸ �Լ�
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// ������ ���� Ʈ�� ���� �Լ�
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

// ������ ���� Ʈ������ ���� ��ȸ�� ���� ������ ����
void SetThreadedInOrder(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL)
        return;

    // ���� ����Ʈ���� ���
    SetThreadedInOrder(root->left, prev);

    // ������ ����: ���� ��尡 �����ϰ�, ���� ����� �������� ��� ������
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->isThreaded = 1; // ������� ����Ǿ����� ǥ��
    }

    // ���� ��带 ���� ���� ����
    *prev = root;

    // ������ ����Ʈ���� ���
    if (root->isThreaded == 0) {
        SetThreadedInOrder(root->right, prev);
    }
}

// ������ ���� Ʈ�� ���� �� ������ ����
ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = InsertThreadTree(root, inputData[i]);
    }

    // ������ ����
    ThreadNode* prev = NULL;
    SetThreadedInOrder(root, &prev);

    return root;
}

// ������ ���� Ʈ���� ���� ��ȸ �Լ�
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    // ���� ���� ��� ã��
    while (current->left != NULL) {
        current = current->left;
    }

    // ���� ��ȸ ����
    while (current != NULL) {
        printf("%d ", current->data);

        // �����尡 ������ ���� ���� �̵�
        if (current->isThreaded) {
            current = current->right;
        }
        else {
            // ������ ����Ʈ������ ���� ���� ���� �̵�
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}

// ���� �Լ�
int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // ���� Ž�� Ʈ�� ���� �� ���� ��ȸ
    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    // ������ ���� Ʈ�� ���� �� ���� ��ȸ
    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    // �޸� ����
    free(root);
    free(troot);

    return 0;
}
