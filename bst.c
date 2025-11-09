#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 50
#define MEANING_SIZE 100

// ---------- Structure Definition ----------
typedef struct Node {
    char keyword[WORD_SIZE];
    char meaning[MEANING_SIZE];
    struct Node *left, *right;
} Node;

// ---------- Queue for Level-wise Display ----------
#define SIZE 100
Node* queue[SIZE];
int front = -1, rear = -1;

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

int isQueueEmpty() {
    return (front == -1 || front > rear);
}

// ---------- Create New Node ----------
Node* createNode(char key[], char mean[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->keyword, key);
    strcpy(newNode->meaning, mean);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ---------- Insert Keyword ----------
Node* insert(Node* root, char key[], char mean[]) {
    if (root == NULL) return createNode(key, mean);

    int cmp = strcmp(key, root->keyword);
    if (cmp < 0)
        root->left = insert(root->left, key, mean);
    else if (cmp > 0)
        root->right = insert(root->right, key, mean);
    else
        printf("Keyword '%s' already exists!\n", key);

    return root;
}

// ---------- Find Minimum (for deletion) ----------
Node* findMin(Node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// ---------- Delete Keyword ----------
Node* delete(Node* root, char key[]) {
    if (root == NULL) {
        printf("Keyword not found!\n");
        return root;
    }

    int cmp = strcmp(key, root->keyword);
    if (cmp < 0)
        root->left = delete(root->left, key);
    else if (cmp > 0)
        root->right = delete(root->right, key);
    else {
        // Node found
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* temp = findMin(root->right);
            strcpy(root->keyword, temp->keyword);
            strcpy(root->meaning, temp->meaning);
            root->right = delete(root->right, temp->keyword);
        }
    }
    return root;
}

// ---------- Copy Tree ----------
Node* copyTree(Node* root) {
    if (root == NULL) return NULL;
    Node* newNode = createNode(root->keyword, root->meaning);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// ---------- Create Mirror Image ----------
Node* mirror(Node* root) {
    if (root == NULL) return NULL;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
    return root;
}

// ---------- Level-wise Display ----------
void displayLevelWise(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    front = rear = -1;
    enqueue(root);
    printf("\nLevel-wise display:\n");

    while (!isQueueEmpty()) {
        int count = rear - front + 1; // nodes in current level
        while (count--) {
            Node* curr = dequeue();
            printf("[%s : %s]  ", curr->keyword, curr->meaning);
            if (curr->left) enqueue(curr->left);
            if (curr->right) enqueue(curr->right);
        }
        printf("\n");
    }
}

// ---------- Inorder Display (sorted order) ----------
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%s : %s\n", root->keyword, root->meaning);
    inorder(root->right);
}

// ---------- Main Function ----------
int main() {
    Node* root = NULL;
    Node* copiedTree = NULL;
    int choice;
    char key[WORD_SIZE], mean[MEANING_SIZE];

    do {
        printf("\n========= Dictionary Menu =========\n");
        printf("1. Insert Keyword\n");
        printf("2. Delete Keyword\n");
        printf("3. Display Dictionary (Inorder)\n");
        printf("4. Create Mirror Image and Display\n");
        printf("5. Copy Dictionary\n");
        printf("6. Display Level-wise\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter keyword: ");
                scanf("%s", key);
                printf("Enter meaning: ");
                scanf(" %[^\n]", mean);
                root = insert(root, key, mean);
                break;

            case 2:
                printf("Enter keyword to delete: ");
                scanf("%s", key);
                root = delete(root, key);
                break;

            case 3:
                printf("\nDictionary (Sorted by Keyword):\n");
                inorder(root);
                break;

            case 4:
                mirror(root);
                printf("\nMirror Image Created.\n");
                displayLevelWise(root);
                break;

            case 5:
                copiedTree = copyTree(root);
                printf("\nCopied Tree (Inorder):\n");
                inorder(copiedTree);
                break;

            case 6:
                displayLevelWise(root);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
