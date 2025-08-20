#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1, rear = -1;

int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int x) {
    if (isFull()) {
        printf("Queue is FULL! Cannot enqueue %d\n", x);
        return;
    }
    if (front == -1)
        front = 0;
    rear = (rear + 1) % MAX;
    queue[rear] = x;
    printf("Enqueued %d\n", x);
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY! Cannot dequeue.\n");
        return;
    }
    printf("Dequeued %d\n", queue[front]);
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
        return;
    }
    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    int choice, val;
    do {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Check if Queue is Empty\n");
        printf("4. Check if Queue is Full\n");
        printf("5. Display Queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &val);
                enqueue(val);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                if (isEmpty())
                    printf("Queue is EMPTY\n");
                else
                    printf("Queue is NOT empty\n");
                break;
            case 4:
                if (isFull())
                    printf("Queue is FULL\n");
                else
                    printf("Queue is NOT full\n");
                break;
            case 5:
                display();
                break;
            case 0:
                printf("Exited the Program\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);
    return 0;
}
