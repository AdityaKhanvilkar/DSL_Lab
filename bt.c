#include <stdio.h>
#include <stdlib.h>

// ---------- Structure Definition ----------
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// ---------- Stack for Non-Recursive Traversal ----------
#define SIZE 100
Node* stack[SIZE];
int top = -1;

// ---------- Queue for Level Order Creation ----------
Node* queue[SIZE];
int front = -1, rear = -1;

// ---------- Stack Operations ----------
void push(Node* node) {
    if (top < SIZE - 1)
        stack[++top] = node;
}

Node* pop() {
    if (top >= 0)
        return stack[top--];
    return NULL;
}

int isStackEmpty() {
    return top == -1;
}

// ---------- Queue Operations ----------
void enqueue(Node* node) {
    if (rear < SIZE - 1) {
        if (front == -1) front = 0;
        queue[++rear] = node;
    }
}

Node* dequeue() {
    if (front == -1 || front > rear) return NULL;
    return queue[front++];
}

// ---------- Create New Node ----------
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ---------- Create Binary Tree (Level-Wise) ----------
Node* createTree() {
    int data;
    printf("Enter root data (-1 for no node): ");
    scanf("%d", &data);
    if (data == -1) return NULL;

    Node* root = createNode(data);
    enqueue(root);

    while (front <= rear) {
        Node* temp = dequeue();
        printf("Enter left child of %d (-1 for no node): ", temp->data);
        scanf("%d", &data);
        if (data != -1) {
            temp->left = createNode(data);
            enqueue(temp->left);
        }

        printf("Enter right child of %d (-1 for no node): ", temp->data);
        scanf("%d", &data);
        if (data != -1) {
            temp->right = createNode(data);
            enqueue(temp->right);
        }
    }

    printf("\nBinary Tree Created Successfully!\n");
    return root;
}

// ---------- Recursive Traversals ----------
void inorderRec(Node* root) {
    if (root == NULL) return;
    inorderRec(root->left);
    printf("%d ", root->data);
    inorderRec(root->right);
}

void preorderRec(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorderRec(root->left);
    preorderRec(root->right);
}

void postorderRec(Node* root) {
    if (root == NULL) return;
    postorderRec(root->left);
    postorderRec(root->right);
    printf("%d ", root->data);
}

// ---------- Non-Recursive Inorder ----------
void inorderNonRec(Node* root) {
    Node* curr = root;
    top = -1;
    while (curr != NULL || !isStackEmpty()) {
        while (curr != NULL) {
            push(curr);
            curr = curr->left;
        }
        curr = pop();
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

// ---------- Non-Recursive Preorder ----------
void preorderNonRec(Node* root) {
    if (root == NULL) return;
    top = -1;
    push(root);
    while (!isStackEmpty()) {
        Node* temp = pop();
        printf("%d ", temp->data);
        if (temp->right) push(temp->right);
        if (temp->left) push(temp->left);
    }
}

// ---------- Non-Recursive Postorder ----------
void postorderNonRec(Node* root) {
    Node* stack1[SIZE];
    Node* stack2[SIZE];
    int top1 = -1, top2 = -1;

    if (root == NULL) return;

    stack1[++top1] = root;
    while (top1 >= 0) {
        Node* temp = stack1[top1--];
        stack2[++top2] = temp;
        if (temp->left) stack1[++top1] = temp->left;
        if (temp->right) stack1[++top1] = temp->right;
    }

    while (top2 >= 0)
        printf("%d ", stack2[top2--]->data);
}

// ---------- Main Menu ----------
int main() {
    Node* root = NULL;
    int choice;

    do {
        printf("\n========= Binary Tree Menu =========\n");
        printf("1. Create Binary Tree\n");
        printf("2. Recursive Inorder\n");
        printf("3. Recursive Preorder\n");
        printf("4. Recursive Postorder\n");
        printf("5. Non-Recursive Inorder\n");
        printf("6. Non-Recursive Preorder\n");
        printf("7. Non-Recursive Postorder\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: root = createTree(); break;
            case 2: printf("Inorder (Recursive): "); inorderRec(root); break;
            case 3: printf("Preorder (Recursive): "); preorderRec(root); break;
            case 4: printf("Postorder (Recursive): "); postorderRec(root); break;
            case 5: printf("Inorder (Non-Recursive): "); inorderNonRec(root); break;
            case 6: printf("Preorder (Non-Recursive): "); preorderNonRec(root); break;
            case 7: printf("Postorder (Non-Recursive): "); postorderNonRec(root); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}
