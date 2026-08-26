#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Max Heapify
void maxHeapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;

    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        maxHeapify(a, n, largest);
    }
}

// Build Max Heap
void buildMaxHeap(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(a, n, i);
    }
}

int main()
{
    int a[100], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    buildMaxHeap(a, n);

    printf("Max Heap:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}