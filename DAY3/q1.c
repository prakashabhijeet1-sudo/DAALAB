#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

// Merge Function
void merge(int arr[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0;
    int temp[1000];

    while (i <= mid && j <= right)
    {
        comparisons++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

// Merge Sort
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main()
{
    FILE *fin, *fout;
    char inputFile[30], outputFile[30];
    int arr[1000];
    int n = 0;
    int choice, i;

    printf("\nMAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");

    printf("\nEnter option: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            sprintf(inputFile, "inAsce.dat");
            sprintf(outputFile, "outMergeAsce.dat");
            break;

        case 2:
            sprintf(inputFile, "inDesc.dat");
            sprintf(outputFile, "outMergeDesc.dat");
            break;

        case 3:
            sprintf(inputFile, "inRand.dat");
            sprintf(outputFile, "outMergeRand.dat");
            break;

        case 4:
            printf("Program Exited.\n");
            return 0;

        default:
            printf("Invalid Choice!\n");
            return 0;
    }

    fin = fopen(inputFile, "r");

    if (fin == NULL)
    {
        printf("Error opening input file!\n");
        return 0;
    }

    while (fscanf(fin, "%d", &arr[n]) == 1)
        n++;

    fclose(fin);

    printf("\nBefore Sorting:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    comparisons = 0;

    clock_t start, end;

    start = clock();

    mergeSort(arr, 0, n - 1);

    end = clock();

    double executionTime =
        ((double)(end - start) * 1000000000.0) / CLOCKS_PER_SEC;

    fout = fopen(outputFile, "w");

    if (fout == NULL)
    {
        printf("Error creating output file!\n");
        return 0;
    }

    for (i = 0; i < n; i++)
        fprintf(fout, "%d ", arr[i]);

    fclose(fout);

    printf("\n\nAfter Sorting:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n\nNumber of Comparisons: %lld\n", comparisons);
    printf("Execution Time: %.0f nanoseconds\n", executionTime);

    printf("\nSorted data has been stored in %s\n", outputFile);

    return 0;
}