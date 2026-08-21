//heap 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};
struct person *data = NULL;
int n = 0;
int capacity = 0;
struct person *minHeap = NULL;
int minHeapSize = 0;
int minHeapCap = 0;
struct person *maxHeap = NULL;
int maxHeapSize = 0;
void ensureDataCapacity(int needed)
{
    if (needed <= capacity) return;
    capacity = (needed > capacity * 2) ? needed : capacity * 2;
    if (capacity < 4) capacity = 4;
    data = (struct person *)realloc(data, capacity * sizeof(struct person));
    if (!data)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}
void ensureMinHeapCapacity(int needed)
{
    if (needed <= minHeapCap) return;
    minHeapCap = (needed > minHeapCap * 2) ? needed : minHeapCap * 2;
    if (minHeapCap < 4) minHeapCap = 4;
    minHeap = (struct person *)realloc(minHeap, minHeapCap * sizeof(struct person));
    if (!minHeap)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}
void readData(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Could not open file '%s'.\n", filename);
        return;
    }
    int count;
    if (fscanf(fp, "%d", &count) != 1)
    {
        printf("Invalid file format.\n");
        fclose(fp);
        return;
    }
    ensureDataCapacity(count);
    n = 0;
    char nameBuf[256];
    for (int i = 0; i < count; i++)
    {
        struct person p;
        if (fscanf(fp, "%d %255s %d %d %d",
                   &p.id, nameBuf, &p.age, &p.height, &p.weight) != 5)
        {
            printf("Warning: stopped early, malformed record at index %d.\n", i);
            break;
        }
        p.name = strdup(nameBuf);
        data[n++] = p;
    }
    fclose(fp);
    printf("Successfully read %d record(s) from '%s'.\n", n, filename);
}
void printTableHeader(void);
void printPerson(struct person p);
void minHeapSwap(struct person *a, struct person *b)
{
    struct person tmp = *a;
    *a = *b;
    *b = tmp;
}
void minHeapSiftUp(int i)
{
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (minHeap[parent].age > minHeap[i].age)
        {
            minHeapSwap(&minHeap[parent], &minHeap[i]);
            i = parent;
        }
        else break;
    }
}
void minHeapSiftDown(int i)
{
    while (1)
    {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (left < minHeapSize && minHeap[left].age < minHeap[smallest].age)
            smallest = left;
        if (right < minHeapSize && minHeap[right].age < minHeap[smallest].age)
            smallest = right;
        if (smallest == i) break;
        minHeapSwap(&minHeap[i], &minHeap[smallest]);
        i = smallest;
    }
}
void createMinHeap(void)
{
    if (n == 0)
    {
        printf("No data loaded yet. Choose option 1 first.\n");
        return;
    }
    ensureMinHeapCapacity(n);
    memcpy(minHeap, data, n * sizeof(struct person));
    minHeapSize = n;
    for (int i = minHeapSize / 2 - 1; i >= 0; i--)
        minHeapSiftDown(i);
    printf("Min-Heap based on age created successfully.\n\n");
    printTableHeader();
    for (int i = 0; i < minHeapSize; i++)
        printPerson(minHeap[i]);
}
void insertMinHeap(struct person p)
{
    if (minHeapSize == 0 && minHeapCap == 0)
        printf("Note: Min-heap was empty; inserting as the first element.\n");
    ensureMinHeapCapacity(minHeapSize + 1);
    minHeap[minHeapSize] = p;
    minHeapSiftUp(minHeapSize);
    minHeapSize++;
    printf("Inserted id=%d name=%s age=%d into the Min-Heap.\n", p.id, p.name, p.age);
}
void minHeapDeleteAt(int idx)
{
    if (idx < 0 || idx >= minHeapSize) return;
    free(minHeap[idx].name);
    minHeapSize--;
    if (idx != minHeapSize)
    {
        minHeap[idx] = minHeap[minHeapSize];
        minHeapSiftDown(idx);
        minHeapSiftUp(idx);
    }
}
void deleteOldest(void)
{
    if (minHeapSize == 0)
    {
        printf("Min-heap is empty. Create it first (option 2) or insert data.\n");
        return;
    }
    int oldestIdx = 0;
    for (int i = 1; i < minHeapSize; i++)
        if (minHeap[i].age > minHeap[oldestIdx].age)
            oldestIdx = i;
    printf("Deleting oldest person: id=%d name=%s age=%d\n",
           minHeap[oldestIdx].id, minHeap[oldestIdx].name, minHeap[oldestIdx].age);
    minHeapDeleteAt(oldestIdx);
}
void displayYoungestWeight(void)
{
    if (minHeapSize == 0)
    {
        printf("Min-heap is empty. Create it first (option 2).\n");
        return;
    }
    float kg = minHeap[0].weight * 0.453592f;
    printf("Weight of youngest student: %.2f kg\n", kg);
}
void maxHeapSwap(struct person *a, struct person *b)
{
    struct person tmp = *a;
    *a = *b;
    *b = tmp;
}
void maxHeapSiftDown(int i)
{
    while (1)
    {
        int left = 2 * i + 1, right = 2 * i + 2, largest = i;
        if (left < maxHeapSize && maxHeap[left].weight > maxHeap[largest].weight)
            largest = left;
        if (right < maxHeapSize && maxHeap[right].weight > maxHeap[largest].weight)
            largest = right;
        if (largest == i) break;
        maxHeapSwap(&maxHeap[i], &maxHeap[largest]);
        i = largest;
    }
}
void createMaxHeap(void)
{
    if (n == 0)
    {
        printf("No data loaded yet. Choose option 1 first.\n");
        return;
    }
    maxHeap = (struct person *)realloc(maxHeap, n * sizeof(struct person));
    memcpy(maxHeap, data, n * sizeof(struct person));
    maxHeapSize = n;
    for (int i = maxHeapSize / 2 - 1; i >= 0; i--)
        maxHeapSiftDown(i);
    printf("Max-Heap based on weight created successfully.\n\n");
    printTableHeader();
    for (int i = 0; i < maxHeapSize; i++)
        printPerson(maxHeap[i]);
}
void printTableHeader(void)
{
    printf("%-4s%-16s%-6s%-8s%-14s\n", "Id", "Name", "Age", "Height", "Weight(pound)");
}
void printPerson(struct person p)
{
    printf("%-4d%-16s%-6d%-8d%-14d\n", p.id, p.name, p.age, p.height, p.weight);
}
void printAllData(void)
{
    if (n == 0)
    {
        printf("No data loaded yet.\n");
        return;
    }
    printTableHeader();
    for (int i = 0; i < n; i++)
        printPerson(data[i]);
}
void printMenu(void)
{
    printf("\nMAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Exit\n");
    printf("\nEnter option: ");
}
int main(void)
{
    int choice;
    char filename[256];
    while (1)
    {
        printMenu();
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice)
        {
            case 1:
                printf("Enter data filename (e.g. students.txt): ");
                scanf("%255s", filename);
                readData(filename);
                printAllData();
                break;
            case 2:
                createMinHeap();
                break;
            case 3:
                createMaxHeap();
                break;
            case 4:
                displayYoungestWeight();
                break;
            case 5:
            {
                struct person p;
                char nameBuf[256];
                printf("Enter id name age height weight: ");
                scanf("%d %255s %d %d %d", &p.id, nameBuf, &p.age, &p.height, &p.weight);
                p.name = strdup(nameBuf);
                insertMinHeap(p);
                break;
            }
            case 6:
                deleteOldest();
                break;
            case 7:
                printf("Exiting...\n");
                free(data);
                free(minHeap);
                free(maxHeap);
                return 0;
            default:
                printf("Invalid option. Please choose 1-7.\n");
        }
    }
    return 0;
}