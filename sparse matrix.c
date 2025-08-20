#include <stdio.h>
#define MAX 100

void accept(int n,int m,int arr[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("Enter element at index (%d,%d): ",i,j);
            scanf("%d",&arr[i][j]);
        }
    }
}

void display(int n,int m,int arr[n][m]){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}

int compact(int r,int c,int mat[r][c],int sparse[][3]){
    int k=1;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(mat[i][j]!=0){
                sparse[k][0] = i;          // row index
                sparse[k][1] = j;          // col index
                sparse[k][2] = mat[i][j];  // value
                k++;
            }
        }
    }
    sparse[0][0] = r;
    sparse[0][1] = c;
    sparse[0][2] = k-1;  // non-zeros
    return k;            // return total rows in sparse (header + non-zeros)
}

void simpleTranspose(int sparse[][3], int transposed[][3]){
    int rows = sparse[0][0];   // original row count
    int cols = sparse[0][1];   // original col count
    int nonZero = sparse[0][2];

    // Header for transposed
    transposed[0][0] = cols;
    transposed[0][1] = rows;
    transposed[0][2] = nonZero;

    int k = 1;
    // For each column in original
    for(int i=0; i<cols; i++){
        for(int j=1; j<=nonZero; j++){
            if(sparse[j][1] == i){   // if column matches
                transposed[k][0] = sparse[j][1];  // new row = old col
                transposed[k][1] = sparse[j][0];  // new col = old row
                transposed[k][2] = sparse[j][2];  // value stays same
                k++;
            }
        }
    }
}

void fastTranspose(int sparse[][3], int transpose[][3]) {
    int row = sparse[0][0];
    int col = sparse[0][1];
    int num = sparse[0][2];

    int count[MAX] = {0};   // count of elements in each column
    int start[MAX] = {0};   // starting position for each row in transpose

    // Step 1: Count elements in each column
    for (int i = 1; i <= num; i++) {
        count[sparse[i][1]]++;
    }

    // Step 2: Compute starting positions
    start[0] = 1;
    for (int i = 1; i < col; i++) {
        start[i] = start[i-1] + count[i-1];
    }

    // Step 3: Fill transpose directly
    transpose[0][0] = col;
    transpose[0][1] = row;
    transpose[0][2] = num;

    for (int i = 1; i <= num; i++) {
        int colIndex = sparse[i][1];
        int pos = start[colIndex];

        transpose[pos][0] = sparse[i][1];  // new row
        transpose[pos][1] = sparse[i][0];  // new col
        transpose[pos][2] = sparse[i][2];  // value

        start[colIndex]++;
    }
}

int main(){
    int r,c;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d",&r,&c);
    int mat[r][c];
    int sparse[MAX][3], transposed[MAX][3],fastT[MAX][3];

    printf("\nAccepting elements............\n");
    accept(r,c,mat);

    printf("\n------------ Original Matrix -----------\n");
    display(r,c,mat);

    int size = compact(r,c,mat,sparse);

    printf("\n------- Sparse Matrix ---------\n");
    display(size,3,sparse);

    simpleTranspose(sparse, transposed);
    printf("\n------- Simple Transpose (Sparse) ---------\n");
    display(size,3,transposed);

    fastTranspose(sparse, fastT);
    printf("\n------- Fast Transpose (Sparse) ---------\n");
    display(size,3,fastT);

    return 0;
}
