#include <stdio.h>
#include <stdlib.h>

struct tbtNode {
    char data;
    int lbit, rbit;
    struct tbtNode *leftc, *rightc;
};

void create(struct tbtNode *head){
    int flag, conti;
    char ch;
    struct tbtNode *temp, *curr;
    struct tbtNode *root = (struct tbtNode *)malloc(sizeof(struct tbtNode));

    printf("Enter data for root: ");
    scanf(" %c", &root->data);

    root->leftc = root->rightc = head;
    root->lbit = root->rbit = 0;
    head->leftc = root;
    head->lbit = 1;
    do{
        flag = 0;
        temp = root;
        while (flag == 0){
            printf("Do you want to add  node to (l/r) of %c? ", temp->data);
            scanf(" %c", &ch);

            if (ch == 'l') {
                if (temp->lbit == 0){
                    curr = (struct tbtNode *)malloc(sizeof(struct tbtNode));

                    printf("Enter data for current node: ");
                    scanf(" %c", &curr->data);
                    curr->lbit = curr->rbit = 0;
                    curr->leftc = temp->leftc;
                    curr->rightc = temp;
                    temp->leftc = curr;
                    temp->lbit = 1;
                    flag = 1;
                } else {
                    temp = temp->leftc;
                }
            } else {
                if (temp->rbit == 0){
                    curr = (struct tbtNode *)malloc(sizeof(struct tbtNode));

                    printf("Enter data for current node: ");
                    scanf(" %c", &curr->data);
                    curr->lbit = curr->rbit = 0;
                    curr->rightc = temp->rightc;
                    curr->leftc = temp;
                    temp->rightc = curr;
                    temp->rbit = 1;
                    flag = 1;
                } else {
                    temp = temp->rightc;
                }
            }
        }

        printf("Do you want to continue? (1-Yes / 0-No): ");
        scanf("%d", &conti);

    } while (conti == 1);
}

struct tbtNode *inorder_succ(struct tbtNode *temp){
    struct tbtNode *x = temp->rightc;
    if (temp->rbit == 1){
        while (x->lbit == 1)
            x = x->leftc;
    }
    return x;
}

void inorder(struct tbtNode *head){
    struct tbtNode *temp = head;
    while (1){
        temp = inorder_succ(temp);
        if (temp == head)
            break;
        printf("%c\t", temp->data);
    }
}
void preorder(struct tbtNode *head){
    struct tbtNode *temp = head->leftc;
    while(temp!=head){
        printf("%c\t",temp->data);
        while(temp->lbit!=0){
            temp = temp->leftc;
            printf("%c\t",temp->data);
        }
        while(temp->rbit == 0){
            temp = temp->rightc;
        }
        temp = temp->rightc;
    }
}

int main(){
    struct tbtNode *head = (struct tbtNode *)malloc(sizeof(struct tbtNode));
    head->rbit = 1;
    head->lbit = 0;
    head->leftc = head;
    head->rightc = head;

    create(head);

    printf("\nInorder Traversal: ");
    inorder(head);
    printf("\nPreorder Traversal: ");
    preorder(head);
    return 0;
}
