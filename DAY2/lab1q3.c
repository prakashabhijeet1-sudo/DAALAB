#include <stdio.h>

int main() {
    int n, i;
    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    int arr[n];
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read numbers from file
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    printf("The content of the array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Frequency analysis
    int freq[n];
    for (i = 0; i < n; i++) {
        freq[i] = 0;
    }

    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                freq[i]++;
            }
        }
    }

    // Count distinct duplicates
    int duplicate_count = 0;
    for (i = 0; i < n; i++) {
        if (freq[i] > 1) {
            int already_counted = 0;
            for (int j = 0; j < i; j++) {
                if (arr[i] == arr[j]) {
                    already_counted = 1;
                    break;
                }
            }
            if (!already_counted) {
                duplicate_count++;
            }
        }
    }

    // Find most repeating element
    int max_freq = freq[0];
    int most_repeating = arr[0];
    for (i = 1; i < n; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            most_repeating = arr[i];
        }
    }

    printf("Total number of duplicate values = %d\n", duplicate_count);
    printf("The most repeating element in the array = %d\n", most_repeating);

    return 0;
}