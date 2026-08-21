#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int main()
{
    char inputFile[100], outputFile[100];

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

    int a, b;

    while (fscanf(fin, "%d %d", &a, &b) == 2)
    {
        fprintf(fout, "The GCD of %d and %d is %d\n", a, b, gcd(a, b));
    }

    fclose(fin);
    fclose(fout);

    /* Display contents of the output file */
    fout = fopen(outputFile, "r");

    if (fout == NULL)
    {
        printf("Error opening output file.\n");
        return 1;
    }

    char ch;
    printf("\nContents of Output File:\n\n");

    while ((ch = fgetc(fout)) != EOF)
    {
        putchar(ch);
    }

    fclose(fout);

    return 0;
}