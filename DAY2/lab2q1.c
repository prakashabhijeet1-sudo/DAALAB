#include <stdio.h>
#include <stdlib.h>

void binary(int n, FILE *fp)
{
    if (n > 1)
        binary(n / 2, fp);

    fprintf(fp, "%d", n % 2);
}

int main()
{
    int n;
    char inputFile[100], outputFile[100];

    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Enter input file name: ");
    scanf("%s", inputFile);

    printf("Enter output file name: ");
    scanf("%s", outputFile);

    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");

    if (fin == NULL || fout == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int num, count = 0;

    while (count < n && fscanf(fin, "%d", &num) == 1)
    {
        fprintf(fout, "The binary equivalent of %d is ", num);

        if (num == 0)
            fprintf(fout, "0");
        else
            binary(num, fout);

        fprintf(fout, "\n");

        count++;
    }

    fclose(fin);
    fclose(fout);

    /* Display output file */
    fout = fopen(outputFile, "r");

    printf("\nContents of Output File:\n\n");

    char ch;
    while ((ch = fgetc(fout)) != EOF)
    {
        putchar(ch);
    }

    fclose(fout);

    return 0;
}