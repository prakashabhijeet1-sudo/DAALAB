#include <stdio.h>
#include<time.h>
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    clock_t start,end;
    double cpu_time;
    start=clock();

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\nChoose a sorting algorithm:\n");
    printf("1. Selection Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Bubble Sort\n");
    printf("Enter your choice (1-3): ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        selectionSort(arr, n);
        printf("\nArray sorted using Selection Sort: ");
        break;
    case 2:
        insertionSort(arr, n);
        printf("\nArray sorted using Insertion Sort: ");
        break;
    case 3:
        bubbleSort(arr, n);
        printf("\nArray sorted using Bubble Sort: ");
        break;
    default:
        printf("\nInvalid choice! Array remains unsorted: ");
        break;
    }
    end =clock();
    
    printArray(arr, n);
    return 0;
}