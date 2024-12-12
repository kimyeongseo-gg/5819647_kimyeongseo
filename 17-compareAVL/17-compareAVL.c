#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;
} Node;

int compareCount = 0;
int searchCount = 0;

// ��� ���� �Լ�
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return (nptr);
}

// AVL Ʈ���� ���̸� ��ȯ�ϴ� �Լ�
int getHeight(Node* nptr) {
    return (nptr == (Node*)NULL) ? 0 : nptr->height;
}

// AVL Ʈ���� ������ ����ϴ� �Լ�
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

// AVL Ʈ������ ������ ȸ���� �����ϴ� �Լ�
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T3 = x->right;


    x->right = y;
    y->left = T3;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// AVL Ʈ������ ���� ȸ���� �����ϴ� �Լ�
Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;


    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// AVL Ʈ������ ����-������ ȸ���� �����ϴ� �Լ�
Node* rotateLeftRight(Node* z) {
    z->left = rotateLeft(z->left); // ���� ȸ��
    return rotateRight(z); // ������ ȸ��
}

// AVL Ʈ������ ������-���� ȸ���� �����ϴ� �Լ�
Node* rotateRightLeft(Node* z) {
    z->right = rotateRight(z->right); // ������ ȸ��
    return rotateLeft(z); // ���� ȸ��
}

// AVL Ʈ���� ���ο� Ű�� �����ϴ� �Լ�
Node* insertAVL(Node* root, int key) {
    if (root == (Node*)NULL) return createNode(key);


    if (root->key > key)
        root->left = insertAVL(root->left, key);
    else if (root->key < key)
        root->right = insertAVL(root->right, key);
    else
        return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    // AVL Ʈ�� ���� ����
    if (balance >= 2) {
        if (getBalance(root->left) >= 0) return rotateRight(root); // LL
        else return rotateLeftRight(root); // LR
    }
    else if (balance <= -2) {
        if (getBalance(root->right) <= 0) return rotateLeft(root); // RR
        else return rotateRightLeft(root); // RL
    }
    return root;
}

// AVL Ʈ������ �ּҰ� ��带 ã�� �Լ�
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

// AVL Ʈ������ Ư�� Ű�� �����ϴ� �Լ�
Node* deleteAVL(Node* root, int key) {
    if (root == NULL) return root;


    if (key < root->key) {
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteAVL(root->right, key);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    // AVL Ʈ�� ���� ����
    if (balance >= 2) {
        if (getBalance(root->left) >= 0) return rotateRight(root); // LL
        else return rotateLeftRight(root); // LR
    }
    else if (balance <= -2) {
        if (getBalance(root->right) <= 0) return rotateLeft(root); // RR
        else return rotateRightLeft(root); // RL
    }
    return root;
}

// ���� Ž�� Ʈ���� ���ο� Ű�� �����ϴ� �Լ�
Node* insertBST(Node* root, int key) {
    if (root == NULL) return createNode(key);

    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);
    // �ߺ��� Ű�� �������� ����
    return root;
}

// ���� Ž�� Ʈ������ Ư�� Ű�� �����ϴ� �Լ�
Node* deleteBST(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteBST(root->right, key);
    }
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteBST(root->right, temp->key);
        }
    }
    return root;
}

// ���� Ž�� Ʈ������ Ư�� Ű�� Ž���ϴ� �Լ�
int search(Node* root, int key) {
    compareCount++;
    if (root == NULL) {
        return 0; // ã�� ����
    }
    compareCount++;
    if (root->key == key) {
        return 1; // ã��
    }
    else if (root->key > key) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// Ʈ�� �޸� ���� �Լ�
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
    else return;
}

// AVL Ʈ�� �۾� ��ġ ���� �Լ�
void doAVLBatch(Node* root) {
    searchCount = 0;
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            root = deleteAVL(root, B);
        }
        else if (A == 2) {
            searchCount++;
            search(root, B);
        }
    }

}

// ���� Ž�� Ʈ�� �۾� ��ġ ���� �Լ�
void doBinaryBatch(Node* root) {
    searchCount = 0;
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = insertBST(root, B); // ���� Ž�� Ʈ������ ����
        }
        else if (A == 1) {
            root = deleteBST(root, B); // ���� Ž�� Ʈ������ ����
        }
        else if (A == 2) {
            searchCount++;
            search(root, B);
        }
    }
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;


    // AVL Ʈ�� �۾� ����
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // ���� Ž�� Ʈ�� �۾� ����
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);
    freeTree(root);

    return 0;
}
