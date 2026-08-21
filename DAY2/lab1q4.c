#include <stdio.h>

void exchange(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ROTATE_RIGHT(int arr[], int p1, int p2)
{
    int i;

    for (i = p2 - 1; i > p1; i--)
    {
        exchange(&arr[i], &arr[i - 1]);
    }
}

int main()
{
    int n, p2, i;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter number of elements to rotate: ");
    scanf("%d", &p2);

    printf("\nBefore ROTATE:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    ROTATE_RIGHT(arr, 0, p2);

    printf("\nAfter ROTATE:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}