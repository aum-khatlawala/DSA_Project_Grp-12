#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct Node *Node;
typedef struct Graph *Graph;
int size;
struct Node
{
    int weights;
    int data;
    Node Next;
};
struct Graph
{
    int num_elem;
    Node *pFirst;
};
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void DownHeap(int a[], int i,int position[],int answers[])
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;
    if (l <= size - 1 && answers[a[l]] < answers[a[smallest]])
    {
        smallest = l;
    }
    if (r <= size - 1 && answers[a[r]] < answers[a[smallest]])
    {
        smallest = r;
    }
    if (smallest != i)
    {
        position[i] = smallest;
        position[smallest] = i;
        swap(&a[i], &a[smallest]);
        DownHeap(a,smallest, position,answers);
    }
}
void UpdateHeap(int a[],int i,int position[],int answers[])
{
    if(i == 0)
    {
        return ;
    }
    //a[position[i]] = final;
    int x = i - 1;
    if(answers[a[i]] < answers[a[x/2]])
    {
        position[a[i]] = x/2;
        position[a[x/2]] = i; 
        swap(&a[i],&a[x/2]);
        UpdateHeap(a,x/2,position,answers);
    }
   
}
void BuildHeap(int a[], int position[],int answers[])
{
    int n = size;
    for (int i = n / 2; i >= 0; i--)
    {
        DownHeap(a, i, position,answers);
    }
}
void InsertNode(Graph g, int a, int b, int weights)
{
    int flag = 0;
    Node P = (Node)malloc(sizeof(struct Node));
    Node Q = g->pFirst[a];
    if (Q == NULL)
    {
        g->pFirst[a] = P;
        P->data = b;
        P->weights = weights;
        P->Next = NULL;
        flag = 1;
    }
    if (!flag)
    {
        while (Q != NULL && Q->data != b)
        {
            Q = Q->Next;
        }
        Q = g->pFirst[a];
        while (Q->Next != NULL)
        {
            Q = Q->Next;
        }
        Q->Next = P;
        P->weights = weights;
        P->Next = NULL;
        P->data = b;
    }
}
Graph CreateGraph(int N)
{
    Graph g;
    g = (Graph)malloc(sizeof(struct Graph));
    g->pFirst = (Node *)malloc(N * sizeof(Node));
    for (int i = 0; i < N; i++)
    {
        g->pFirst[i] = NULL;
    }
    return g;
}
int ExtractMin(int heap[],int answers[],int position[])
{
    if(size <= 0)
    {
        return -1;
    }
    int x = heap[0];
    position[heap[0]] = size-1;
    position[heap[size-1]] = 0;
    swap(&heap[0],&heap[size-1]);
    size--;
    DownHeap(heap,0,position,answers);
    return x;

}
void Dijkstras(Graph g,int heap[],int position[],int answers[],int a)
{
    Node P = g->pFirst[a];
    while(P != NULL)
    {
        if(answers[P->data] > answers[a] + P->weights && answers[a] != INT_MAX)
        {
            answers[P->data] = answers[a] + P->weights;
            UpdateHeap(heap,position[P->data],position,answers);
        }
        P = P->Next;
    }
    int x = ExtractMin(heap,answers,position);
    if(x == -1)
    {
        return ;
    }
    Dijkstras(g,heap,position,answers,x);
}
int main()
{
    int N, M;
    scanf("%d %d", &N,&M);
    int answers[N +1];
    for (int i = 0; i < N + 1; i++)
    {
        answers[i] = INT_MAX;
    }
    size = N+1;
    //int heap[N+1];
    Graph g = CreateGraph(N + 1);
    answers[1] = 0;
    for (int i = 0; i < M; i++)
    {
        int a, b, weights;
        scanf("%d %d %d",&a,&b,&weights);
        InsertNode(g, a, b,weights);
    }
    int position[N+1],heap[N+1];
    for(int i = 0;i<N+1;i++)
    {
        heap[i] = i;
        position[i] = i;
    }
    BuildHeap(heap,position,answers);
    int min = heap[0];
    position[heap[0]] = size-1;
    position[heap[size-1]] = 0;
    swap(&heap[0],&heap[size-1]);
    size--;
    Dijkstras(g,heap,position,answers,min);
    for(int i =1;i<N+1;i++)
    {
        printf("%d ",answers[i]);
    }
    printf("\n");
}