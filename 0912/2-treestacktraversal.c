#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 스택을 위한 구조체
typedef struct Stack {
    TreeNode* nodes[100];
    int top;
} Stack;

// 스택 초기화
void init(Stack* s) {
    s->top = -1;
}

// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 스택에 push
void push(Stack* s, TreeNode* node) {
    if (node != NULL) {
        s->nodes[++(s->top)] = node;
        printf("push(%d) ", node->data);
    }
}

// 스택에서 pop
TreeNode* pop(Stack* s) {
    if (!isEmpty(s)) {
        printf("pop(%d) ", s->nodes[s->top]->data);
        return s->nodes[(s->top)--];
    }
    return NULL;
}

// 노드 생성 및 방향에 따라 배치
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) { // 왼쪽
        node->left = newNode;
    }
    else { // 오른쪽
        node->right = newNode;
    }
}

// 트리 생성
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


// 전위 순회 (PreOrder)
void LinkPreOrder(TreeNode* root) {
    Stack s;
    init(&s);
    printf("\nLinkedPreOrder: ");
    TreeNode* curr = root;

    while (curr != NULL || !isEmpty(&s)) {
        while (curr != NULL) {
          
            push(&s, curr);
            printf("visit(%d) ", curr->data); // visit 출력
            curr = curr->left;
        }
        curr = pop(&s);
        curr = curr->right;
    }
}


// 중위 순회 (InOrder)
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


// 후위 순회 (PostOrder)
void LinkPostOrder(TreeNode* root) {
    Stack s;
    init(&s);
    printf("\nLinkedPostOrder: ");

    TreeNode* curr = root;
    TreeNode* lastVisited = NULL;

    while (curr != NULL || !isEmpty(&s)) {
        // 왼쪽 자식들을 계속 스택에 쌓는다.
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->left;
        }

        // 스택의 top에 있는 노드를 가져온다.
        TreeNode* node = s.nodes[s.top];

        // 오른쪽 자식이 없거나 이미 방문한 경우, 방문한다.
        if (node->right == NULL || node->right == lastVisited) {
            printf("visit(%d) ", node->data);
            pop(&s);  // 방문했으므로 스택에서 제거
            lastVisited = node;  // 마지막으로 방문한 노드 갱신
        }
        else {
            // 오른쪽 자식을 방문해야 하므로, 오른쪽 자식을 탐색한다.
            curr = node->right;
        }
    }
}



// 세 가지 순회 방식 실행
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

    // 트리 생성
    GenerateLinkTree(root);

    // 전위, 중위, 후위 순회
    LinkOrders(root);

    return 0;
}
