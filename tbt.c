#include <stdio.h>
#include <stdlib.h>

// -------- Structure Definition --------
typedef struct node {
    int data;
    struct node *left, *right;
    int lthread, rthread;  // Flags: 1 = thread, 0 = child link
} Node;

// -------- Create a New Node --------
Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1; // Initially threads
    return temp;
}

// -------- Insert a Node into TBT --------
Node* insert(Node* root, int data) {
    Node* ptr = root;
    Node* parent = NULL;

    // Find the place to insert the new node
    while (ptr != NULL) {
        if (data == ptr->data) {
            printf("Duplicate data not allowed: %d\n", data);
            return root;
        }

        parent = ptr;

        if (data < ptr->data) {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    // Create new node
    Node* newNode = createNode(data);

    if (parent == NULL) {
        // First node
        root = newNode;
    } else if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = 0;
        parent->right = newNode;
    }

    return root;
}

// -------- Inorder Successor --------
Node* inorderSuccessor(Node* ptr) {
    if (ptr->rthread == 1)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == 0)
        ptr = ptr->left;

    return ptr;
}

// -------- Inorder Traversal (Without Recursion or Stack) --------
void inorder(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    // Go to the leftmost node
    Node* ptr = root;
    while (ptr->lthread == 0)
        ptr = ptr->left;

    printf("Inorder Traversal: ");
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = inorderSuccessor(ptr);
    }
    printf("\n");
}

// -------- Main Function --------
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\n========= Threaded Binary Tree Menu =========\n");
        printf("1. Insert Node\n");
        printf("2. Inorder Traversal\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;

            case 2:
                inorder(root);
                break;

            case 0:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
