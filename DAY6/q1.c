// greedy techniques
#include <stdio.h>
#include <stdlib.h>

// Structure declaration as per the assignment note
struct ITEM {
    int item_id;
    double item_profit;
    double item_weight;
    double profit_weight_ratio;
};

// Function to heapify a subtree rooted with node i
void heapify(struct ITEM arr[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // For non-increasing order sorting, build a Min-Heap based on ratio
    if (left < n && arr[left].profit_weight_ratio < arr[smallest].profit_weight_ratio)
        smallest = left;

    if (right < n && arr[right].profit_weight_ratio < arr[smallest].profit_weight_ratio)
        smallest = right;

    if (smallest != i) {
        struct ITEM temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        heapify(arr, n, smallest);
    }
}

// Function to perform heap sort to sort items in non-increasing order
void heapSort(struct ITEM arr[], int n) {
    // Build min-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        struct ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call min heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    double capacity;

    printf("Enter the number of items: ");
    if (scanf("%d", &n) != 1) return 1;

    struct ITEM *items = (struct ITEM *)malloc(n * sizeof(struct ITEM));

    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        if (scanf("%lf %lf", &items[i].item_profit, &items[i].item_weight) != 2) return 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    printf("Enter the capacity of knapsack: ");
    if (scanf("%lf", &capacity) != 1) return 1;

    // Apply heap sort technique to sort items in non-increasing order of ratio
    heapSort(items, n);

    printf("\nOutput:\n\n");
    printf("%-7s %-14s %-14s %s\n\n", "Item No", "profit", "Weight", "Amount to be taken");

    double total_profit = 0.0;
    double current_weight = 0.0;

    for (int i = 0; i < n; i++) {
        double amount_taken = 0.0;

        if (current_weight + items[i].item_weight <= capacity) {
            amount_taken = 1.0;
            current_weight += items[i].item_weight;
            total_profit += items[i].item_profit;
        } else {
            double remaining_capacity = capacity - current_weight;
            if (remaining_capacity > 0) {
                amount_taken = remaining_capacity / items[i].item_weight;
                total_profit += amount_taken * items[i].item_profit;
                current_weight = capacity;
            } else {
                amount_taken = 0.0;
            }
        }

        printf("%-7d %-14f %-14f %-f\n", 
               items[i].item_id, 
               items[i].item_profit, 
               items[i].item_weight, 
               amount_taken);
    }

    printf("Maximum profit: %f\n", total_profit);

    free(items);
    return 0;
}
