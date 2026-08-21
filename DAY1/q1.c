#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void copyArray(int source[], int dest[], int n) 
{
    for (int i = 0; i < n; i++) dest[i] = source[i];
}
void bubblesort(int arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j =0;j<n-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
void selectionsort(int arr[],int n)
{
    int j;
    for(int i =0;i<n-i-1;i++)
    {
        int min_idx=i;
        for(int j=i+1;j<n;j++)
        {
            if (arr[j]<arr[min_idx]);
        }
        int temp=arr[min_idx];
        arr[min_idx]=arr[j];
        arr[j]=temp;
    }
}
void insertionsort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main() {
    int sizes[] = {10000, 20000, 30000, 40000, 50000};
    int numSizes = 5;
    srand(time(NULL));
    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int *original = malloc(n * sizeof(int));
        int *temp = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 100000;
        }
        printf("\nArray size: %d\n", n);
        copyArray(original, temp, n);
        clock_t start = clock();
        bubblesort(temp, n);
        clock_t end = clock();
        printf("Bubble Sort time: %.4f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC); 
        copyArray(original, temp, n);
        start = clock();
        selectionsort(temp, n);
        end = clock();
        printf("Selection Sort time: %.4f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC);
        copyArray(original, temp, n);
        start = clock();
        insertionsort(temp, n);
        end = clock();
        printf("Insertion Sort (Random/Worst) time: %.4f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC);
        start = clock();
        insertionsort(temp, n);  
        end = clock();
        printf("Insertion Sort (Best) time: %.4f seconds\n",
               (double)(end - start) / CLOCKS_PER_SEC);
        free(original);
        free(temp);
    }
    return 0;
}