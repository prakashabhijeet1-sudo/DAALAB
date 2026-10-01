#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int M[MAX][MAX];
int S[MAX][MAX];
int p[MAX];
void printMTable(int n){
    int i, j;
    printf("\nM Table:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++){
            if (i > j)
                printf("0 ");
            else
                printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}
void printSTable(int n){
    int i, j;
    printf("\nS Table:\n");
    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            if (i >= j)
                printf("0 ");
            else
                printf("%d ", S[i][j]);
        }
        printf("\n");
    }
}
void printParenthesis(int i, int j){
    if (i == j){
        printf("A%d", i);
        return;
    }
    printf("(");
    printParenthesis(i, S[i][j]);
    printf(" ");
    printParenthesis(S[i][j] + 1, j);
    printf(")");
}
int main(){
    int n,i ,j,k,q,length;
    int rows[MAX], cols[MAX];
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    if (n <= 0 || n >= MAX) {
        printf("Invalid number of matrices.\n");
        return 0;
    }
    for (i = 1; i <= n; i++){
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &rows[i], &cols[i]);
        if (rows[i] <= 0 || cols[i] <= 0){
            printf("Invalid matrix dimensions.\n");
            return 0;
        }
    }
    for (i = 1; i < n; i++){
        if (cols[i] != rows[i + 1]){
            printf("\nDimension mismatch!\n");
            printf("A%d has %d columns, but A%d has %d rows.\n",
                   i, cols[i], i + 1, rows[i + 1]);
            printf("Matrix chain multiplication is not possible.\n");
            return 0;
        }
    }
    p[0] = rows[1];
    for (i = 1; i <= n; i++){
        p[i] = cols[i];
    }
    for (i = 1; i <= n; i++){
        M[i][i] = 0;
        S[i][i] = 0;
    }
    for (length = 2; length <= n; length++){
        for (i = 1; i <= n - length + 1; i++){
            j = i + length - 1;
            M[i][j] = 2147483647;
            for (k = i; k < j; k++){
                q = M[i][k]
                    + M[k + 1][j]
                    + p[i - 1] * p[k] * p[j];
                if (q < M[i][j]){
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
    printMTable(n);
    printSTable(n);
    printf("\nOptimal parenthesization: ");
    printParenthesis(1, n);
    printf("\n\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n",
           M[1][n]);
    return 0;
}