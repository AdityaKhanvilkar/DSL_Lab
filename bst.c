#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct Node {
    char keyword[50];    
    char meaning[255];    
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(const char* keyword, const char* meaning) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        return NULL;
    }
    strcpy(newNode->keyword, keyword);
    strcpy(newNode->meaning, meaning);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* create_tree() {
    char keyword[50];
    char meaning[255];

    printf("Enter keyword (or @ to stop): ");
    scanf("%s", keyword);

    if (strcmp(keyword, "@") == 0) {
        return NULL;  
    }

    printf("Enter meaning: ");
    getchar();  
    fgets(meaning, sizeof(meaning), stdin);

    
    meaning[strcspn(meaning, "\n")] = '\0';

    Node* root = createNode(keyword, meaning);

    printf("Enter left child of %s:\n", keyword);
    root->left = create_tree();

    printf("Enter right child of %s:\n", keyword);
    root->right = create_tree();

    return root;
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* delete_node(Node* root, const char* keyword) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(keyword, root->keyword);

    if (cmp < 0) {
        
        root->left = delete_node(root->left, keyword);
    } else if (cmp > 0) {
        
        root->right = delete_node(root->right, keyword);
    } else {
        

        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: One child (right)
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        // Case 2: One child (left)
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Two children
        else {
            Node* temp = findMin(root->right);  // Find inorder successor
            strcpy(root->keyword, temp->keyword);
            strcpy(root->meaning, temp->meaning);
            root->right = delete_node(root->right, temp->keyword);
        }
    }
    return root;
}


void print_tree(Node* root) {
    if (root == NULL) return;
    print_tree(root->left);
    printf("%s: %s\n", root->keyword, root->meaning);
    print_tree(root->right);
}

Node* insert(Node* root, const char* keyword, const char* meaning) {
    if (root == NULL) {
        return createNode(keyword, meaning);
    }
    int cmp = strcmp(keyword, root->keyword);
    if (cmp < 0) {
        root->left = insert(root->left, keyword, meaning);
    } else if (cmp > 0) {
        root->right = insert(root->right, keyword, meaning);
    } else {
        strcpy(root->meaning, meaning);  // update meaning if keyword exists
    }
    return root;
}

char* search(Node* root, const char* keyword) {
    if (root == NULL) return NULL;
    int cmp = strcmp(keyword, root->keyword);
    if (cmp == 0) return root->meaning;
    else if (cmp < 0) return search(root->left, keyword);
    else return search(root->right, keyword);
}

void mirrortree(Node* root){
    if(root == NULL){
        return;
    }
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrortree(root->left);
    mirrortree(root->right);
}

Node* copy_tree(Node* root) {
    if (root == NULL)
        return NULL;
    Node* newNode = createNode(root->keyword, root->meaning);
    newNode->left = copy_tree(root->left);
    newNode->right = copy_tree(root->right);
    return newNode;
}

int main() {
    Node* root = NULL;
    int choice;
    char keyword[50];
    char meaning[255];

    do {
        printf("\n--- Dictionary Menu ---\n");
        printf("1. Create dictionary tree\n");
        printf("2. Insert keyword\n");
        printf("3. Delete keyword\n");
        printf("4. Search keyword\n");
        printf("5. Print dictionary\n");
        printf("6. Mirror image\n");    // Added newline
        printf("7. Exit\n");
    
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  
    
        switch (choice) {
            case 1:
                printf("Creating dictionary tree:\n");
                root = create_tree();
                break;
    
            case 2:
                printf("Enter keyword to insert: ");
                scanf("%s", keyword);
                getchar();
                printf("Enter meaning: ");
                fgets(meaning, sizeof(meaning), stdin);
                meaning[strcspn(meaning, "\n")] = '\0'; // remove trailing newline
                root = insert(root, keyword, meaning);
                printf("Keyword inserted/updated.\n");
                break;
    
            case 3:
                printf("Enter keyword to delete: ");
                scanf("%s", keyword);
                root = delete_node(root, keyword);
                printf("Keyword deleted if it existed.\n");
                break;
    
            case 4:
                printf("Enter keyword to search: ");
                scanf("%s", keyword);
                {
                    char* found = search(root, keyword);
                    if (found) {
                        printf("Meaning: %s\n", found);
                    } else {
                        printf("Keyword not found.\n");
                    }
                }
                break;
    
            case 5:
                printf("Dictionary contents (inorder traversal):\n");
                print_tree(root);
                break;
            
            case 6:
                mirrortree(root);  // Pass root, not keyword
                printf("Tree mirrored and printed.\n");
                break;
    
            case 7:
                printf("Exiting program.\n");
                break;
    
            default:
                printf("Invalid choice! Try again.\n");
                break;
        }

    } while (choice != 7);  // Exit condition
return 0;    
}