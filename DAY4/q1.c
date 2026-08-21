#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

/* Merge Function */
void merge(int arr[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
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

/* Merge Sort - Divide and Conquer */
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        /* Divide */
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        /* Combine */
        merge(arr, left, mid, right);
    }
}

int main()
{
    FILE *fin, *fout;

    char inputFile[30];
    char outputFile[30];

    int arr[1000];
    int n = 0;
    int choice;
    int i;

    clock_t start, end;
    double executionTime;

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

    /* Open input file */
    fin = fopen(inputFile, "r");

    if (fin == NULL)
    {
        printf("\nError opening input file: %s\n", inputFile);
        return 0;
    }

    /* Read elements */
    while (n < 1000 && fscanf(fin, "%d", &arr[n]) == 1)
    {
        n++;
    }

    fclose(fin);

    if (n == 0)
    {
        printf("\nInput file is empty!\n");
        return 0;
    }

    printf("\nNumber of elements: %d\n", n);

    /* Before Sorting */
    printf("\nBefore Sorting: Content of the input file\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    /* Reset comparisons */
    comparisons = 0;

    /*
       Start timer ONLY before Merge Sort
    */
    start = clock();

    mergeSort(arr, 0, n - 1);

    end = clock();

    /*
       Convert time to nanoseconds
    */
    executionTime =
        ((double)(end - start) * 1000000000.0)
        / CLOCKS_PER_SEC;

    /* Open output file */
    fout = fopen(outputFile, "w");

    if (fout == NULL)
    {
        printf("\nError creating output file: %s\n", outputFile);
        return 0;
    }

    /* Write sorted elements */
    for (i = 0; i < n; i++)
    {
        fprintf(fout, "%d ", arr[i]);
    }

    fclose(fout);

    /* After Sorting */
    printf("\nAfter Sorting: Content of the output file\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    /* Results */
    printf("\nNumber of Comparisons: %lld\n", comparisons);
    printf("Execution Time: %.0f nanoseconds\n", executionTime);

    printf("\nSorted data has been stored in %s\n", outputFile);

    return 0;
}