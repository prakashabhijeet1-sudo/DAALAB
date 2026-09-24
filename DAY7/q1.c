#include <stdio.h>

#define INF 99999
#define MAX 100

void printPath(int parent[], int vertex) {
    if (parent[vertex] == -1) {
        printf("%d", vertex + 1);
        return;
    }

    printPath(parent, parent[vertex]);
    printf("->%d", vertex + 1);
}

void dijkstra(int graph[MAX][MAX], int n, int source) {
    int dist[MAX];
    int visited[MAX];
    int parent[MAX];
    int i, j, u, min;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (i = 0; i < n; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (graph[u][j] != 0 && !visited[j]) {
                if (dist[u] + graph[u][j] < dist[j]) {
                    dist[j] = dist[u] + graph[u][j];
                    parent[j] = u;
                }
            }
        }
    }

    printf("\nSource Destination Cost Path\n");

    for (i = 0; i < n; i++) {
        printf("%d %d ", source + 1, i + 1);

        if (dist[i] == INF) {
            printf("INF ");
            printf("No Path");
        } else {
            printf("%d ", dist[i]);

            if (i == source)
                printf("-");
            else
                printPath(parent, i);
        }

        printf("\n");
    }
}

int main() {
    int graph[MAX][MAX];
    int n, source;
    int i, j;
    FILE *fp;

    fp = fopen("inDiAdjMat1.dat", "r");

    if (fp == NULL) {
        printf("Unable to open input file.\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Enter the Source Vertex: ");
    scanf("%d", &source);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }

    fclose(fp);

    dijkstra(graph, n, source - 1);

    return 0;
}