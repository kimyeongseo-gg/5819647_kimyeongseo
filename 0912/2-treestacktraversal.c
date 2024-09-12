#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ����ü
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ������ ���� ����ü
typedef struct Stack {
    TreeNode* nodes[100];
    int top;
} Stack;

// ���� �ʱ�ȭ
void init(Stack* s) {
    s->top = -1;
}

// ������ ����ִ��� Ȯ��
int isEmpty(Stack* s) {
    return s->top == -1;
}

// ���ÿ� push
void push(Stack* s, TreeNode* node) {
    if (node != NULL) {
        s->nodes[++(s->top)] = node;
        printf("push(%d) ", node->data);
    }
}

// ���ÿ��� pop
TreeNode* pop(Stack* s) {
    if (!isEmpty(s)) {
        printf("pop(%d) ", s->nodes[s->top]->data);
        return s->nodes[(s->top)--];
    }
    return NULL;
}

// ��� ���� �� ���⿡ ���� ��ġ
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) { // ����
        node->left = newNode;
    }
    else { // ������
        node->right = newNode;
    }
}

// Ʈ�� ����
void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);   // 2
    PlaceNode(root, 1, 9);   // 9
    PlaceNode((root)->left, 0, 3);   // 3
    PlaceNode((root)->left, 1, 5);   // 5
    PlaceNode((root)->right, 0, 10); // 10
    PlaceNode((root)->right, 1, 13); // 13
    PlaceNode((root)->left->left, 0, 4); // 4
    PlaceNode((root)->left->left, 1, 6); // 6
    PlaceNode((root)->left->right, 0, 7); // 7
    PlaceNode((root)->left->right, 1, 8); // 8
    PlaceNode((root)->right->left, 0, 11); // 11
    PlaceNode((root)->right->left, 1, 12); // 12
    PlaceNode((root)->right->right, 0, 14); // 14
    PlaceNode((root)->right->right, 1, 15); // 15
}


// ���� ��ȸ (PreOrder)
void LinkPreOrder(TreeNode* root) {
    Stack s;
    init(&s);
    printf("\nLinkedPreOrder: ");
    TreeNode* curr = root;

    while (curr != NULL || !isEmpty(&s)) {
        while (curr != NULL) {
          
            push(&s, curr);
            printf("visit(%d) ", curr->data); // visit ���
            curr = curr->left;
        }
        curr = pop(&s);
        curr = curr->right;
    }
}


// ���� ��ȸ (InOrder)
void LinkInOrder(TreeNode* root) {
    Stack s;
    init(&s);
    TreeNode* curr = root;
    printf("\nLinkedInOrder: ");

    while (curr != NULL || !isEmpty(&s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("visit(%d) ", curr->data);
        curr = curr->right;
    }
}


// ���� ��ȸ (PostOrder)
void LinkPostOrder(TreeNode* root) {
    Stack s;
    init(&s);
    printf("\nLinkedPostOrder: ");

    TreeNode* curr = root;
    TreeNode* lastVisited = NULL;

    while (curr != NULL || !isEmpty(&s)) {
        // ���� �ڽĵ��� ��� ���ÿ� �״´�.
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }

        // ������ top�� �ִ� ��带 �����´�.
        TreeNode* node = s.nodes[s.top];

        // ������ �ڽ��� ���ų� �̹� �湮�� ���, �湮�Ѵ�.
        if (node->right == NULL || node->right == lastVisited) {
            printf("visit(%d) ", node->data);
            pop(&s);  // �湮�����Ƿ� ���ÿ��� ����
            lastVisited = node;  // ���������� �湮�� ��� ����
        }
        else {
            // ������ �ڽ��� �湮�ؾ� �ϹǷ�, ������ �ڽ��� Ž���Ѵ�.
            curr = node->right;
        }
    }
}



// �� ���� ��ȸ ��� ����
void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    // Ʈ�� ����
    GenerateLinkTree(root);

    // ����, ����, ���� ��ȸ
    LinkOrders(root);

    return 0;
}
