#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *lchild;
    struct Node *rchild;
};

// Function to create tree recursively
void create_r(struct Node *root) {
    struct Node *curr;
    char ch;

    // For left child
    printf("Do you want to add left child of %d? (y/n): ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        curr = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter data for left child of %d: ", root->data);
        scanf("%d", &curr->data);
        curr->lchild = NULL;
        curr->rchild = NULL;
        root->lchild = curr;
        create_r(curr);
    }

    // For right child
    printf("Do you want to add right child of %d? (y/n): ", root->data);
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        curr = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter data for right child of %d: ", root->data);
        scanf("%d", &curr->data);
        curr->lchild = NULL;
        curr->rchild = NULL;
        root->rchild = curr;
        create_r(curr);
    }
}

// Tree traversals
void preorder(struct Node *temp){
    if(temp!=NULL){
        printf("%d ",temp->data);
        preorder(temp->lchild);
        preorder(temp->rchild);
    }
}

void inorder(struct Node *temp){
    if(temp!=NULL){
        inorder(temp->lchild);
        printf("%d ",temp->data);
        inorder(temp->rchild);
    }
}

void postorder(struct Node *temp){
    if(temp!=NULL){
        postorder(temp->lchild);
        postorder(temp->rchild);
        printf("%d ",temp->data);
    }
}

// Delete node function (simple)
int deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return 0;

    // Check if left child matches
    if (root->lchild != NULL && root->lchild->data == key) {
        free(root->lchild);
        root->lchild = NULL;
        return 1;
    }

    // Check if right child matches
    if (root->rchild != NULL && root->rchild->data == key) {
        free(root->rchild);
        root->rchild = NULL;
        return 1;
    }

    // Recursively search subtrees
    if (deleteNode(root->lchild, key)) return 1;
    if (deleteNode(root->rchild, key)) return 1;

    return 0;
}

// Copy tree
struct Node* copyTree(struct Node *root) {
    struct Node *temp = NULL;

    if (root != NULL) {
        temp = (struct Node *)malloc(sizeof(struct Node));
        temp->data = root->data;
        temp->lchild = copyTree(root->lchild);
        temp->rchild = copyTree(root->rchild);
    }

    return temp;
}

// Mirror tree
void mirror_r(struct Node *root) {
    struct Node *temp;
    if (root != NULL) {
        // Swap left and right
        temp = root->lchild;
        root->lchild = root->rchild;
        root->rchild = temp;

        // Recurse
        mirror_r(root->lchild);
        mirror_r(root->rchild);
    }
}

int main() {
    struct Node *root = NULL, *copy = NULL;
    int choice, key;

    while (1) {
        printf("\n===== Binary Tree Operations =====\n");
        printf("1. Create Tree\n");
        printf("2. Display Preorder Traversal\n");
        printf("3. Display Inorder Traversal\n");
        printf("4. Display Postorder Traversal\n");
        printf("5. Copy Tree\n");
        printf("6. Mirror Tree\n");
        printf("7. Delete Node\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("Tree already created.\n");
                    break;
                }
                root = (struct Node *)malloc(sizeof(struct Node));
                printf("Enter data for root node: ");
                scanf("%d", &root->data);
                root->lchild = NULL;
                root->rchild = NULL;
                create_r(root);
                printf("Tree created successfully.\n");
                break;

            case 2:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 3:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 5:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                copy = copyTree(root);
                printf("Copied tree (preorder): ");
                preorder(copy);
                printf("\n");
                break;

            case 6:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                mirror_r(root);
                printf("Mirror tree created (preorder): ");
                preorder(root);
                printf("\n");
                break;

            case 7:
                if (root == NULL) { printf("Tree not created yet.\n"); break; }
                printf("Enter value to delete: ");
                scanf("%d", &key);
                if (deleteNode(root, key))
                    printf("Node %d deleted successfully.\n", key);
                else
                    printf("Node %d not found.\n", key);
                break;

            case 8:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
