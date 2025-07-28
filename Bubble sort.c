#include <stdio.h> 
typedef struct stud {
    int rn;        
    char name[10];
    int marks;    
} stud;

void accept(stud s[10], int n) {
    int i;
    printf("\nEnter student details (Roll No., Name, Marks):\n");
    for (i = 0; i < n; i++) {
        printf("Student %d:\n", i + 1);
        scanf("%d %s %d", &s[i].rn, s[i].name, &s[i].marks);
    }
}

void display(stud s[10], int n) {
    int i;
    printf("\nStudent Records \n");
    printf("Roll No.\tName\tMarks\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%s\t%d\n", s[i].rn, s[i].name, s[i].marks);
    }
}

void bubblesort(stud s[10], int n) {
    int i, j;
    stud temp; 

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (s[j].rn > s[j + 1].rn) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
    printf("\nRecords sorted by Roll No. using Bubble Sort.\n");
}
void selectionsort(stud s[10], int n) {
    int i, j, min_idx;
    stud temp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (s[j].rn < s[min_idx].rn) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            temp = s[min_idx];
            s[min_idx] = s[i];
            s[i] = temp;
        }
    }
    printf("\nRecords sorted by Roll No. using Selection Sort.\n");
}

void insertionsort(stud s[10], int n) {
    int i, j;
    stud key; 

    for (i = 1; i < n; i++) {
        key = s[i]; 
        j = i - 1;

        while (j >= 0 && s[j].rn > key.rn) {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = key; 
    }
    printf("\nRecords sorted by Roll No. using Insertion Sort.\n");
}

int main() {
    stud s[10];
    int n;    
    int choice; 
    printf("Enter total no. of records (max 10):\n");
    scanf("%d", &n);

    if (n <= 0 || n > 10) {
        printf("Invalid number of records. Please enter a number between 1 and 10.\n");
        return 1; 
    }
    accept(s, n);
    display(s, n);

    do {
        printf("\nChoose a Sorting Method: \n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        stud s_copy[10];
        for(int i = 0; i < n; i++) {
            s_copy[i] = s[i];
        }

        switch (choice) {
            case 1:
                bubblesort(s_copy, n);
                display(s_copy, n);
                break;
            case 2:
                selectionsort(s_copy, n);
                display(s_copy, n);
                break;
            case 3:
                insertionsort(s_copy, n);
                display(s_copy, n);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0); 

    return 0; 
}
