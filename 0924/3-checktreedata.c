#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = createNode(data);
  
    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);   // 2
    PlaceNode(root, 1, 9);   // 9
    PlaceNode(root->left, 0, 3);   // 3
    PlaceNode(root->left, 1, 5);   // 5
    PlaceNode(root->right, 0, 10); // 10
    PlaceNode(root->right, 1, 13); // 13
    PlaceNode(root->left->left, 0, 4); // 4
    PlaceNode(root->left->left, 1, 6); // 6
    PlaceNode(root->left->right, 0, 7); // 7
    PlaceNode(root->left->right, 1, 8); // 8
    PlaceNode(root->right->left, 0, 11); // 11
    PlaceNode(root->right->left, 1, 12); // 12
    PlaceNode(root->right->right, 0, 14); // 14
    PlaceNode(root->right->right, 1, 15); // 15
}

int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    TreeNode* stack[100]; // 스택을 사용하여 반복적으로 탐색
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        TreeNode* node = stack[top--];
        sum += node->data;

        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
   
    printf("Sum of nodes: %d\n", sum);
    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        TreeNode* node = stack[top--];
        count++;

        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
    printf("Number of nodes: %d\n", count);
    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    int height = 0;
    TreeNode* stack[100];
    int top = -1;
    int level[100];

    stack[++top] = root;
    level[top] = 1; // root의 높이

    while (top != -1) {
        TreeNode* node = stack[top--];
        int currentLevel = level[top + 1];

        if (node->left == NULL && node->right == NULL) {
            if (currentLevel > height) {
                height = currentLevel;
            }
        }

        if (node->right != NULL) {
            stack[++top] = node->right;
            level[top] = currentLevel + 1;
        }
        if (node->left != NULL) {
            stack[++top] = node->left;
            level[top] = currentLevel + 1;
        }
    }
    printf("Height of Tree: %d\n", height);
    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        TreeNode* node = stack[top--];

        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }

        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
    printf("Number of leaf nodes: %d\n", leafCount);
    return leafCount;
}

int main() {
    TreeNode* root = createNode(1);
    root->data = 1;

    //트리생성, 출력은 없는 함수.
    GenerateLinkTree(root);

    GetSumOfNodes(root);
    GetNumberOfNodes(root);
    GetHeightOfTree(root);
    GetNumberOfLeafNodes(root);

    return 0;
}
