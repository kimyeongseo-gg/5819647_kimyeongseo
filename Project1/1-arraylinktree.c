#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// �迭 Ʈ�� ���� �Լ�
void GenerateArrayTree(int* tree) {
    // ��ũ�� Ʈ���� ������ ������ Ʈ�� ������ �´� �� �Է�
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    // �迭 ���
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// �迭 ���� ��ȸ
void ArrayPreOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        printf("%d ", tree[index]);
        ArrayPreOrder(tree, 2 * index + 1, size); // ���� �ڽ�
        ArrayPreOrder(tree, 2 * index + 2, size); // ������ �ڽ�
    }
}

// �迭 ���� ��ȸ
void ArrayInOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        ArrayInOrder(tree, 2 * index + 1, size); // ���� �ڽ�
        printf("%d ", tree[index]);
        ArrayInOrder(tree, 2 * index + 2, size); // ������ �ڽ�
    }
}

// �迭 ���� ��ȸ
void ArrayPostOrder(int* tree, int index, int size) {
    if (index < size && tree[index] != 0) {
        ArrayPostOrder(tree, 2 * index + 1, size); // ���� �ڽ�
        ArrayPostOrder(tree, 2 * index + 2, size); // ������ �ڽ�
        printf("%d ", tree[index]);
    }
}

// �迭 ��ȸ �Լ� ȣ��
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
    (*root)->data = 1; // ��Ʈ ���
    (*root)->left = NULL;
    (*root)->right = NULL;

    // ��ũ�� Ʈ�� ���� (�迭�� ������ ����)
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


// ��ũ�� Ʈ�� ���� ��ȸ
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return; {
        printf("%d ", root->data);
        LinkPreOrder(root->left);
        LinkPreOrder(root->right);
    }
}

// ��ũ�� Ʈ�� ���� ��ȸ
void LinkInOrder(TreeNode* root) {
    if (root) {
        LinkInOrder(root->left);
        printf("%d ", root->data);
        LinkInOrder(root->right);
    }
}

// ��ũ�� Ʈ�� ���� ��ȸ
void LinkPostOrder(TreeNode* root) {
    if (root) {
        LinkPostOrder(root->left);
        LinkPostOrder(root->right);
        printf("%d ", root->data);
    }
}

// ��ũ�� Ʈ�� ��ȸ �Լ� ȣ��
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
    int arr[15] = { 0 }; // �迭 �ʱ�ȭ
    TreeNode* root = NULL;


    GenerateArrayTree(arr);
    ArrayOrders(arr, 15);

    GenerateLinkTree(&root);
    LinkOrders(root);

    return 0;
}
