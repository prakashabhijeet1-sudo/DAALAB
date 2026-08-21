//heap sort
#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Max Heap - for Ascending Order */
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

/* Min Heap - for Descending Order */
void minHeapify(int a[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] < a[smallest])
        smallest = left;

    if (right < n && a[right] < a[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&a[i], &a[smallest]);
        minHeapify(a, n, smallest);
    }
}

/* Heap Sort - Ascending */
void ascendingHeapSort(int a[], int n)
{
    int i;

    // Build Max Heap
    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapify(a, n, i);

    // Move largest to the end
    for (i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        maxHeapify(a, i, 0);
    }
}

/* Heap Sort - Descending */
void descendingHeapSort(int a[], int n)
{
    int i;

    // Build Min Heap
    for (i = n / 2 - 1; i >= 0; i--)
        minHeapify(a, n, i);

    // Move smallest to the end
    for (i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);
        minHeapify(a, i, 0);
    }
}

int main()
{
    int n, choice, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\n1. Ascending Order");
    printf("\n2. Descending Order");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        ascendingHeapSort(a, n);

        printf("\nAscending Order:\n");
    }
    else if (choice == 2)
    {
        descendingHeapSort(a, n);

        printf("\nDescending Order:\n");
    }
    else
    {
        printf("\nInvalid choice.");
        return 0;
    }

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}