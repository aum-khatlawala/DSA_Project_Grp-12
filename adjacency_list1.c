#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Node;
typedef struct Graph *Graph;
typedef struct Queue *Queue;
struct Node
{
    int data;
    Node Next;
};
struct Graph
{
    int num_elem;
    Node *pFirst;
};
struct Queue
{
    Node First;
    Node Last;
};
void Insert(Queue q,int a)
{
    Node P = (Node)malloc(sizeof(struct Node));
    P->data = a;
    P->Next = NULL;
    if(q->First == NULL && q->Last == NULL)
    {
        q->First = P;
        q->Last = P;
    }
    else
    {
        q->Last->Next = P;
        q->Last = P;
    }
}
void Pop(Queue q)
{
    if(q->First == NULL)
    {
        return ;
    }
    if(q->First == q->Last)
    {
        Node P = q->First;
        q->First = NULL;
        q->Last == NULL;
        free(P);
    }
    else
    {
        Node P = q->First;
        q->First = P->Next;
        free(P);
    }
}
void BFS(Graph g, int a, int pVisited[],Queue q)
{
    //Insert(q,a);
    Node Q =g->pFirst[a];
    //Q = Q->Next; 
    pVisited[a] = 1;
    while(Q != NULL)
    {
        if(pVisited[Q->data] == 0)
        {
            printf("%d ",Q->data);
            Insert(q,Q->data);
            pVisited[Q->data] =1;
        }
        Q = Q->Next;
    }
    Pop(q);
    while(q->First != NULL)
    {
        BFS(g,q->First->data,pVisited,q);
        Pop(q);
    }

}
void DFS(Graph g, int a, int pVisited[])
{
    Node P = g->pFirst[a];
    pVisited[a] = 1;
    while (P != NULL)
    {
        if (pVisited[P->data] == 0)
        {
            printf("%d ", P->data);
            DFS(g, P->data, pVisited);
        }
        P = P->Next;
    }
}
void InsertNode(Graph g, int a, int b)
{
    int flag = 0;
    Node P = (Node)malloc(sizeof(struct Node));
    Node Q = g->pFirst[a];
    if (Q == NULL)
    {
        g->pFirst[a] = P;
        P->data = b;
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
        P->Next = NULL;
        P->data = b;
    }
    flag = 0;
    Node T = (Node)malloc(sizeof(struct Node));
    Q = g->pFirst[b];
    if (Q == NULL)
    {
        g->pFirst[b] = T;
        T->data = a;
        T->Next = NULL;
        flag = 1;
    }
    if (!flag)
    {
        while (Q != NULL && Q->data != a)
        {
            Q = Q->Next;
        }
        Q = g->pFirst[b];
        while (Q->Next != NULL)
        {
            Q = Q->Next;
        }
        Q->Next = T;
        T->Next = NULL;
        T->data = a;
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
int main()
{
    int N;
    printf("Enter number of vertices: ");
    scanf("%d", &N);
    Graph g = CreateGraph(N + 1);
    int Q;
    printf("Enter the number of queries: ");
    scanf("%d", &Q);
    while (Q--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        InsertNode(g, a, b);
    }
    int pVisited[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        pVisited[i] = 0;
    }
    int U;
    printf("Enter the node: ");
    scanf("%d", &U);
    printf("%d ", U);
    DFS(g, U, pVisited);
    printf("\n");
    /*Queue q = (Queue)malloc(sizeof(struct Queue));
    Node T = (Node)malloc(sizeof(struct Node));
    T->Next = NULL;
    T->data = U;
    q->First = T;
    q->Last = T;
    BFS(g,U,pVisited,q);
    printf("\n");*/
}