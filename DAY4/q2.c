#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long comparisons = 0;

int partition(int a[], int low, int high)
{
    int pivot = a[high];

    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        comparisons++;

        if(a[j] <= pivot)
        {
            i++;

            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if(low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);

        quickSort(a, p + 1, high);
    }
}

int main()
{
    FILE *in, *out;

    int a[500];
    int n = 0;
    int choice;

    char inputFile[30];
    char outputFile[30];

    printf("\nMAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");

    printf("\nEnter option: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            strcpy(inputFile, "inAsce.dat");
            strcpy(outputFile, "outQuickAsce.dat");
            break;

        case 2:
            strcpy(inputFile, "inDesc.dat");
            strcpy(outputFile, "outQuickDesc.dat");
            break;

        case 3:
            strcpy(inputFile, "inRand.dat");
            strcpy(outputFile, "outQuickRand.dat");
            break;

        case 4:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid option!\n");
            return 0;
    }

    in = fopen(inputFile, "r");

    if(in == NULL)
    {
        printf("Input file not found!\n");
        return 0;
    }

    while(fscanf(in, "%d", &a[n]) == 1)
    {
        n++;
    }

    fclose(in);

    printf("\nBefore Sorting:\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    comparisons = 0;

    quickSort(a, 0, n - 1);

    out = fopen(outputFile, "w");

    if(out == NULL)
    {
        printf("Cannot create output file!\n");
        return 0;
    }

    for(int i = 0; i < n; i++)
    {
        fprintf(out, "%d ", a[i]);
    }

    fclose(out);

    printf("\n\nAfter Sorting:\n");

    out = fopen(outputFile, "r");

    int x;

    while(fscanf(out, "%d", &x) == 1)
    {
        printf("%d ", x);
    }

    fclose(out);

    printf("\n\nNumber of Comparisons: %lld", comparisons);

    if(comparisons > (long long)n * n / 4)
    {
        printf("\nScenario: Worst-case partitioning");
    }
    else
    {
        printf("\nScenario: Best-case partitioning");
    }

    return 0;
}