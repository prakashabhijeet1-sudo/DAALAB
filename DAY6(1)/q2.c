//Krushkal's algo
#include<stdio.h>
#include<stdlib.h>

struct Edge{
    int u;
    int v;
    int w;
};
int parent[100];
int rank[100];
int find(int x)
{
    if(parent[x]!=x)
        parent[x]=find(parent[x]);

    return parent[x];
}
void unionSet(int a , int b)
{
    int rootA=find(a);
    int rootB=find(b);
    if(rootA!=rootB)
    {
        if(rank[rootA] < rank[rootB])
        {
            parent[rootA]=rootB;
        }
        else if (rank[rootA] > rank[rootB])
        {
            parent[rootB]=rootA;
        }
        else
        {
            parent[rootB]=rootA;
            rank[rootA]++;
        }
    }
}
int compare(const void *a,const void *b)
{
    struct Edge *e1=(struct Edge *)a;
    struct Edge *e2=(struct Edge *)b;
    return e1->w-e2->w;
}
int main()
{
    int n,m;
    struct Edge edges[1000];
    printf("Enter the number of vertices and edges :");
    scanf("%d%d",&n,&m);
    for(int i =0;i<m;i++)
    {
        scanf("%d %d %d",&edges[i].u,&edges[i].v,&edges[i].w);
    }
    for(int i =1;i<=n;i++)
    {
        parent[i]=i;
        rank[i]=0;
    }
    qsort(edges,m,sizeof(struct Edge),compare);
    int totalCost=0;
    int edgeCount=0;
    printf("Edge Cost\n");
    for(int i=0; i < m && edgeCount < n-1 ; i++)
    {
        int u= edges[i].u;
        int v=edges[i].v;
        if(find(u)!=find(v))
        {
            printf("%d -- %d %d \n ",u,v,edges[i].w);
           totalCost = totalCost + edges[i].w;
            edgeCount++;
            unionSet(u,v);
        }
    }
    printf("Total Weight of the Spanning Tree %d \n",totalCost);
    return 0;
}