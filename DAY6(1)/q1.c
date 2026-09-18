// prims algo
#include <stdio.h>
#include <stdlib.h>

#define INF 99999

struct Node
{
    int vertex;
    int key;
};

void swap(struct Node *a, struct Node *b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct Node heap[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].key < heap[smallest].key)
        smallest = left;

    if (right < n && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

struct Node extractMin(struct Node heap[], int *n)
{
    struct Node min = heap[0];

    heap[0] = heap[*n - 1];
    (*n)--;

    minHeapify(heap, *n, 0);

    return min;
}

void decreaseKey(struct Node heap[], int n, int vertex, int key)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (heap[i].vertex == vertex)
            break;
    }

    if (i == n)
        return;

    heap[i].key = key;

    while (i > 0 && heap[(i - 1) / 2].key > heap[i].key)
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main()
{
    int n, start;
    int graph[100][100];
    int mst[100][100] = {0};

    int parent[100];
    int key[100];
    int inMST[100] = {0};

    struct Node heap[100];
    int heapSize;

    FILE *fp = fopen("inUnAdjMat.dat", "r");

    if (fp == NULL)
    {
        printf("Unable to open input file.\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }

    fclose(fp);

    for (int i = 0; i < n; i++)
    {
        key[i] = INF;
        parent[i] = -1;
    }

    key[start - 1] = 0;

    heapSize = n;

    for (int i = 0; i < n; i++)
    {
        heap[i].vertex = i;
        heap[i].key = key[i];
    }

    for (int i = heapSize / 2 - 1; i >= 0; i--)
        minHeapify(heap, heapSize, i);

    while (heapSize > 0)
    {
        struct Node minNode = extractMin(heap, &heapSize);

        int u = minNode.vertex;
        inMST[u] = 1;

        if (parent[u] != -1)
        {
            mst[u][parent[u]] = graph[u][parent[u]];
            mst[parent[u]][u] = graph[u][parent[u]];
        }

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] != 0 && !inMST[v] &&
                graph[u][v] < key[v])
            {

                key[v] = graph[u][v];
                parent[v] = u;

                decreaseKey(heap, heapSize, v, key[v]);
            }
        }
    }

    int totalCost = 0;

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", mst[i][j]);

            if (j < n - 1)
                printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            totalCost += mst[i][j];
        }
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
    return 0;
}