#include <stdio.h>
#include <string.h>
#define MAX 100
int main(){
    char a[MAX], b[MAX];
    int dp[MAX][MAX];
    printf("Enter the first string into an array: ");
    scanf("%s", a);
    printf("Enter the second string into an array: ");
    scanf("%s", b);
    int m = strlen(a);
    int n = strlen(b);
    for(int i = 0; i <= m; i++){
        dp[i][0] = 0;
    }
    for(int j = 0; j <= n; j++){
        dp[0][j] = 0;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                if(dp[i-1][j] > dp[i][j-1])
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
    }
    int length = dp[m][n];
    char lcs[MAX];
    lcs[length] = '\0';
    int i = m;
    int j = n;
    int index = length - 1;
    while(i > 0 && j > 0){
        if(a[i-1] == b[j-1]){
            lcs[index] = a[i-1];
            index--;
            i--;
            j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }
        else{
            j--;
        }
    }
    printf("\nLCS: %s\n", lcs);
    printf("LCS Length: %d\n", length);
    return 0;
}