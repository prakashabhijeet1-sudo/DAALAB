#include <stdio.h>

struct Pair
{
    int max;
    int min;
};

struct Pair maxMin(int a[], int low, int high)
{
    struct Pair result, left, right;
    int mid;

    if (low == high)
    {
        result.max = a[low];
        result.min = a[low];
        return result;
    }

    if (high == low + 1)
    {
        if (a[low] > a[high])
        {
            result.max = a[low];
            result.min = a[high];
        }
        else
        {
            result.max = a[high];
            result.min = a[low];
        }

        return result;
    }

    mid = (low + high) / 2;

    left = maxMin(a, low, mid);
    right = maxMin(a, mid + 1, high);

    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    return result;
}

int main()
{
    int a[100], n, i;
    struct Pair result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    result = maxMin(a, 0, n - 1);

    printf("Maximum = %d\n", result.max);
    printf("Minimum = %d\n", result.min);

    return 0;
}