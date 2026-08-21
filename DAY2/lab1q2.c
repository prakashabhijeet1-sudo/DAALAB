#include <stdio.h>
int main()
{
    int i, n;
    printf("Enter tye size");
    scanf("%d", &n);
    int arr[n], prefix[n];
    printf("Enter the elsments : \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    printf("Prefix sum array : \n");
    for (int i = 0; i < n; i++)
        printf("%d", prefix[i]);
    return 0;
}