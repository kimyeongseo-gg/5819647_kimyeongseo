#include <stdio.h>
#include <stdlib.h>

// ���� Ʈ�� ��� ����ü
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ������ ���� Ʈ�� ��� ����ü
typedef struct ThreadNode {
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int isThreaded; // ������ �ڽ��� ���������� ����
} ThreadNode;

// ���� Ž�� Ʈ�� ����
TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;

    for (int i = 0; i < 15; i++) { // 15�� inputData�� ũ��
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = inputData[i];
        newNode->left = newNode->right = NULL;

        if (root == NULL) {
            root = newNode;
        }
        else {
            TreeNode* current = root;
            TreeNode* parent = NULL;

            while (1) {
                parent = current;
                if (inputData[i] < current->data) {
                    current = current->left;
                    if (current == NULL) {
                        parent->left = newNode;
                        break;
                    }
                }
                else {
                    current = current->right;
                    if (current == NULL) {
                        parent->right = newNode;
                        break;
                    }
                }
            }
        }
    }
    return root;
}

// ������ ���� Ʈ�� ����
void CreateThreaded(TreeNode* root, ThreadNode** threadRoot, ThreadNode** prev) {
    if (root == NULL) return;

    CreateThreaded(root->left, threadRoot, prev);

    ThreadNode* newThreadNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newThreadNode->data = root->data;
    newThreadNode->left = NULL;
    newThreadNode->right = NULL;
    newThreadNode->isThreaded = 0;

    if (*threadRoot == NULL) {
        *threadRoot = newThreadNode;
    }
    else {
        if ((*prev)->right == NULL) {
            (*prev)->right = newThreadNode;
            (*prev)->isThreaded = 1; // ������ �ڽ��� ������
        }
        else {
            (*prev)->right = newThreadNode;
        }
    }
    *prev = newThreadNode;

    CreateThreaded(root->right, threadRoot, prev);
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* threadRoot = NULL;
    ThreadNode* prev = NULL;
    CreateThreaded(root, &threadRoot, &prev);
    return threadRoot;
}

// ���� Ʈ�� ���� ��ȸ
void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

// ������ ���� Ʈ�� ���� ��ȸ
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current) {
        while (current->left) {
            current = current->left;
        }
        printf("%d ", current->data);
        if (current->isThreaded) {
            current = current->right; // ������� �̵�
        }
        else {
            current = current->right; // �Ϲ� ������ �ڽ����� �̵�
        }
    }
}

// ���� �Լ�
int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    // Ʈ�� ����, *root�� Ʈ���� ������ ��ȯ
    TreeNode* root = GenerateBinaryTree(inputData);

    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    // �޸� ���� (����)
    return 0;
}
