#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int prn;
    char name[50];
    struct node* next;
};


void create(struct node *head) {
    struct node *temp;
    struct node *curr;
    temp = head;
    int flag = 1;
    while(flag){
        curr = (struct node *)malloc(sizeof(struct node));
        printf("Enter PRN: ");
        scanf("%d", &curr->prn);
        printf("Enter Name: ");
        scanf("%s", curr->name);
        curr->next = NULL;
        temp->next = curr;
        temp = curr;
        printf("Do you want to add new node\n1->yes / 0->no: ");
        scanf("%d", &flag);
    } 
}


void display(struct node* H) {
    if ( H->next == NULL) {   //H == NULL ||
        printf("\nList is empty.\n");
        return;
    }
    struct node* curr = H->next;
    int pos = 1;
    printf("\nClub Members:\n");
    while (curr != NULL) {
        if (pos == 1)
            printf("President -> ");
        else if (curr->next == NULL)
            printf("Secretary -> ");
        else
            printf("Member -> ");
            printf("PRN: %d, Name: %s\n", curr->prn, curr->name);
            curr = curr->next;
            pos++;
    }
}

int len(struct node* H) {
    int i = 0;
    struct node* curr= H->next;

    while (curr != NULL) {
        i++;
        curr = curr->next;
    }
    return i;
}

void insertByPos(struct node* H) {
    int pos;
    printf("Enter position to insert (1 = President, ....): ");
    scanf("%d", &pos);

    int k = len(H);
    if (pos < 1 || pos > k + 1) {
        printf("Invalid position. Valid positions are 1 to %d\n", k + 1);
        return;
    }

    struct node* nnode = (struct node*)malloc(sizeof(struct node));
    printf("\nEnter PRN: ");
    scanf("%d", &nnode->prn);
    printf("Enter Name: ");  //with scanf- single word without spaces
    scanf("%s", nnode->name);

    struct node* curr = H;
    int i = 1;
    while (i < pos && curr != NULL) {
        curr = curr->next;
        i++;
    }
    nnode->next = curr->next;
    curr->next = nnode;
    printf("Inserted at position %d.\n", pos);
}


void deleteByPos(struct node* H) {
    if (H->next == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    int pos;
    printf("Enter position to delete (1 = President, ....): ");
    scanf("%d", &pos);

    int k = len(H);
    if (pos < 1 || pos > k) {
        printf("Invalid position. Valid positions are 1 to %d\n", k);
        return;
    }

    struct node *prev = H, *curr = H->next;
    int i = 1;
    while (i < pos && curr != NULL) {
        prev = curr;
        curr = curr->next;
        i++;
    }
    prev->next = curr->next;
    curr->next= NULL;
    free(curr);
    printf("Deleted node at position %d.\n", pos);
}


void reverseList(struct node* H) {
    struct node *prev = NULL, *curr = H->next, *future = NULL;
    while (curr != NULL) {
        future = curr->next;
        curr->next = prev;
        prev = curr;
        curr = future;
    }
    H->next = prev;
    printf("List reversed.\n");
}


void sortList(struct node* H) {
    int l = len(H);
    if (l <= 1) {
        printf("List is too short to sort.\n");
        return;
    }

    for (int i = 1; i < l-1; i++) {
        struct node *prev = H;
        struct node *curr = H->next;

        for (int j = 0; j < l - i; j++) {
            struct node *temp = curr->next;

            if (temp == NULL)
                break;

            if (curr->prn > temp->prn) {
                // Adjust links to swap curr and temp
                prev->next = temp;
                curr->next = temp->next;
                temp->next = curr;

                // Move prev to temp (new front of swapped pair)
                prev = temp;
            } else {
                // Move all one step forward
                prev = curr;
                curr = curr->next;
            }
        }
    }

    printf("List sorted by PRN using link swapping.\n");
}



struct node* mergeLists(struct node* H1, struct node* H2) {
    struct node *curr1 = H1->next, *curr2 = H2->next;
    struct node *temp = NULL;
    int flag;

    if (curr1 == NULL && curr2 == NULL) {
        printf("Both lists are empty.\n");
        return NULL;
    }
    if (curr1 == NULL) return H2;
    if (curr2 == NULL) return H1;

    // Decide which head will be used
    if (curr1->prn < curr2->prn) {
        temp = H1;
        flag = 1;
    } else {
        temp = H2;
        flag = 0;
    }

    // Merging process
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->prn < curr2->prn) {
            temp->next = curr1;
            temp = curr1;
            curr1 = curr1->next;
        } else {
            temp->next = curr2;
            temp = curr2;
            curr2 = curr2->next;
        }
    }

    // Attach remaining nodes
    if (curr1 == NULL)
        temp->next = curr2;
    else
        temp->next = curr1;

    // Return whichever list was the base (flag helps identify)
    if (flag == 1)
        return H1;
    else
        return H2;
}


/* ---------- main ---------- */
int main() {
    int choice;
    struct node* club1 = (struct node*)malloc(sizeof(struct node));
    struct node* club2 = (struct node*)malloc(sizeof(struct node));
    if (!club1 || !club2) {
        printf("Memory allocation failed\n");
        return 1;
    }
    club1->next = NULL;
    club2->next = NULL;

    do {
        printf("\n--- Pinnacle Club Menu ---\n");
        printf("1. Create / Append members to Club 1\n");
        printf("2. Display Club 1\n");
        printf("3. Insert by Position (Club 1)\n");
        printf("4. Delete by Position (Club 1)\n");
        printf("5. Count Members (Club 1)\n");
        printf("6. Reverse Club 1\n");
        printf("7. Sort Club 1 by PRN\n");
        printf("8. Create Club 2 and Merge (Club 1 + Club 2)\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: create(club1); break;
            case 2: display(club1); break;
            case 3: insertByPos(club1); break;
            case 4: deleteByPos(club1); break;
            case 5: printf("Total members in Club 1: %d\n", len(club1)); break;
            case 6: reverseList(club1); break;
            case 7: sortList(club1); break;
            case 8: 
                printf("Create Club 2 now:\n");
                create(club2);
                sortList(club1);
                sortList(club2);
                {
                    struct node* merged = mergeLists(club1, club2);
                    printf("\nMerged (Sorted) List:\n");
                    display(merged);
                }
                break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 9);

    return 0;
}