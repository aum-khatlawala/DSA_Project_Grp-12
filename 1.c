#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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
    char name[10];
    int num_elem;
    Node *pFirst;
};
struct answers
{
    char* a;
    int answer;
};
/*struct Bank //An array of this struct will be used to store info of each bank.
{
    char *name;        //name of bank
    GraphPtr Currency; //all the values of different currency conversions
};*/

struct HashT;
typedef struct HashT HashTable;
typedef HashTable *HashPtr;
/* This HashTable will be used to register a bank or currency, and assign it a unique key, which can preferably be set
as the order in which they are registered. This unique key will be used to access the arrays in which graphs for each bank
will be store. In case of currencies, this key will be used to store currencies in the graph.
It is easier to deal with numbers, so in short, this hash table turns string names of currencies and banks
into numerical keys and thus making it easier for us to run different algorithms*/
struct HashT
{
    char name[100]; //name of the bank/currency(whichever of the two the hashtable is used for)
    int index;      /*the unique of the bank/currency added, which is like the roll no. of bank/currency,
    please note that it is 'not' the hash key value*/
    HashPtr next;   // for separate chaining
};
HashPtr MakeHashNode(int srno, char *name) // to create a node in hash table
{
    HashPtr P = (HashPtr)malloc(sizeof(HashTable));
    P->index = srno;
    strcpy(P->name, name);
    P->next = NULL;
    return P;
}
/////////////////////////
int hash(char *name) //hash function
{
    long long int hashval = 0, i = 0;
    while (name[i] != '\0')
    {
        hashval = (37 * hashval) + (int)name[i++];
    }
    hashval = hashval % 501; // change according to total number of banks possible (next prime number after that value)
    return hashval;
}
////////////////////////
void AddIntoHashTable(HashPtr table[], char *name, int serial) /*to register a new bank or currency into a
particular hashtable under the unique key"serial"*/
{
    int key = hash(name);
    HashPtr P = MakeHashNode(serial, name);
    HashPtr dummy = table[key];
    /*To check if in case the given bank already exists in the hash table, in order to avoid duplicates*/
    while (dummy != NULL)
    {
        if (strcmp(dummy->name, name) == 0)
            return;

        dummy = dummy->next;
    }
    /*Duplicate checker ends here, now we register the bank, since it isn't already registered*/
    P->next = table[key];
    table[key] = P;
}
int FindUniqueKey(HashPtr table[], char *name) //to find the unique key value of the bank/currency
{
    int key = hash(name);

    HashPtr dummy = table[key];

    while (dummy != NULL)
    {
        if (strcmp(dummy->name, name) == 0)
            return dummy->index;

        dummy = dummy->next;
    }
    return -1; //since the given bank/currency isn't registered
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void DownHeap(int a[], int i, int position[], int answers[])
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
        DownHeap(a, smallest, position, answers);
    }
}
void UpdateHeap(int a[], int i, int position[], int answers[])
{
    if (i == 0)
    {
        return;
    }
    //a[position[i]] = final;
    int x = i - 1;
    if (answers[a[i]] < answers[a[x / 2]])
    {
        position[a[i]] = x / 2;
        position[a[x / 2]] = i;
        swap(&a[i], &a[x / 2]);
        UpdateHeap(a, x / 2, position, answers);
    }
}
void BuildHeap(int a[], int position[], int answers[])
{
    int n = size;
    for (int i = n / 2; i >= 0; i--)
    {
        DownHeap(a, i, position, answers);
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
void DeleteGraph(Graph g)
{
    for(int i =1;i<1005;i++)
    {
        Node P = g->pFirst[i];
        while(P != NULL)
        {
            Node Q = P->Next;
            free(P);
            P = Q;
        } 
    }
}
int ExtractMin(int heap[], int answers[], int position[])
{
    if (size <= 0)
    {
        return -1;
    }
    int x = heap[0];
    position[heap[0]] = size - 1;
    position[heap[size - 1]] = 0;
    swap(&heap[0], &heap[size - 1]);
    size--;
    DownHeap(heap, 0, position, answers);
    return x;
}
void Dijkstras(Graph g, int heap[], int position[], int answers[], int a)
{
    Node P = g->pFirst[a];
    while (P != NULL)
    {
        if (answers[P->data] > answers[a] + P->weights && answers[a] != INT_MAX)
        {
            answers[P->data] = answers[a] + P->weights;
            UpdateHeap(heap, position[P->data], position, answers);
        }
        P = P->Next;
    }
    int x = ExtractMin(heap, answers, position);
    if (x == -1)
    {
        return;
    }
    Dijkstras(g, heap, position, answers, x);
}
//int main()
//{
int findmincost(Graph g, int from, int to)
{
    //int N, M;               // Number of edges and vertices
    //scanf("%d %d", &N, &M); //scanning
    int answers[101];
    int N = 100;
    for (int i = 0; i < N+1; i++)
    {
        answers[i] = INT_MAX;
    }
    size = N + 1;
    //int heap[N+1];
    //Graph g = CreateGraph(N + 1);
    answers[from] = 0;
    /*for (int i = 0; i < M; i++)
    {
        int a, b, weights;
        scanf("%d %d %d", &a, &b, &weights);
        InsertNode(g, a, b, weights);
    }*/
    int position[N + 1], heap[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        heap[i] = i;
        position[i] = i;
    }
    BuildHeap(heap, position, answers);
    int min = heap[0];
    position[heap[0]] = size - 1;
    position[heap[size - 1]] = 0;
    swap(&heap[0], &heap[size - 1]);
    size--;
    Dijkstras(g, heap, position, answers, min);
    /*for (int i = 1; i < N + 1; i++)
    {
        printf("%d ", answers[i]);
    }
    printf("\n");*/
    return answers[to];
}
void DeleteNodeInGraph(Graph g,int a,int b)
{
    Node P = g->pFirst[a];
    while (P != NULL)
    {
        if(P->Next->data == b)
        {
            Node Q = P->Next;
            P->Next = P->Next->Next;
            free(Q);
            return;
        }
        P = P->Next;
    }
    
}
int main()
{
    Graph G[101];
    int B_index = -1;
    int C_index = -1;
    //HashTable Hash_B[501];//for banks
    HashPtr* Hashptr_B = (HashPtr*)malloc(501*sizeof(HashPtr));
    //HashTable Hash_C[1001];//for currencies
    HashPtr* Hashptr_C = (HashPtr*)malloc(1001*sizeof(HashPtr));  
    /*
    The program keeps running until it is explicity instructed to "End"
    */
    while (1)
    {
        char op[10];
        char arr[20];
        scanf("%s", op);
        if (strcmp(op, "Add") == 0)
        {
            scanf("%s", arr);
            if (strcmp(arr, "trade_bank") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                /*long long int hashval = 0, i = 0;
                while (bank[i] != '\0')
                {
                    hashval = (37 * hashval) + (int)bank[i++];
                }
                hashval = hashval % 101;*/
                /*
                Initialise a trade bank graph in the graph array
                */
                if(FindUniqueKey(Hashptr_B,bank) != -1)
                {
                    continue;
                }
                AddIntoHashTable(Hashptr_B,bank,B_index+1);
                G[B_index + 1] = CreateGraph(1005);
                for(int i=0;i <strlen(bank);i++)
                {
                    G[B_index+1]->name[i] = bank[i];
                }
                B_index++;
            }
            if (strcmp(arr, "currency") == 0)
            {

                char bank[100];
                scanf("%s", bank);
                char from[20];
                char to[20];
                scanf("%s", from);
                scanf("%s", to);
                int cost;
                scanf("%d", &cost);
                //                 long long int hashval = 0, i = 0;
                //                 while (bank[i] != '\0')
                //                 {
                //                     hashval = (37 * hashval) + (int)bank[i++];
                //                 }
                //                 hashval = hashval % 101;
                /*
                Insert the unidirectional edge from a particular currency to a particular currency in the trade bank graph array
                */
                int key = FindUniqueKey(Hashptr_B,bank);
                int index1 = FindUniqueKey(Hashptr_C,from);
                int index2 = FindUniqueKey(Hashptr_C,to);
                if(index1 == -1)
                {
                    AddIntoHashTable(Hashptr_C,from,C_index+1);
                    C_index++;
                    //InsertNode(g,index1,index2,cost);
                    //continue;
                }
                if(index2 == -1)
                {
                    AddIntoHashTable(Hashptr_C,to,C_index+1);
                    C_index++;
                }
                index1 = FindUniqueKey(Hashptr_C,from);
                index2 = FindUniqueKey(Hashptr_C,to);
                InsertNode(G[key],index1,index2,cost);
            }
        }
        if (strcmp(op, "Delete") == 0)
        {
            scanf("%s", arr);
            if (strcmp(arr, "trade_bank") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                //                 long long int hashval = 0, i = 0;
                //                 while (bank[i] != '\0')
                //                 {
                //                     hashval = (37 * hashval) + (int)bank[i++];
                //                 }
                //                 hashval = hashval % 101;
                /*
                Delete a trade bank (implicitly) from the trade bank array
                */
                int key = FindUniqueKey(Hashptr_B,bank);
                DeleteGraph(G[key]);
                G[key] = NULL;
            }
            if (strcmp(arr, "currency") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                char from[20];
                char to[20];
                scanf("%s", from);
                scanf("%s", to);
                //                 long long int hashval = 0, i = 0;
                //                 while (bank[i] != '\0')
                //                 {
                //                     hashval = (37 * hashval) + (int)bank[i++];
                //                 }
                //                 hashval = hashval % 101;
                /*
                Delete every occurrence of a currency in the bank graph (by traversing the adjacency list array 
                and in turn traversing all the pointers of each valid entry in the adjacency list)
                */
                int key = FindUniqueKey(Hashptr_B,bank);
                int index1 = FindUniqueKey(Hashptr_C,from);
                int index2 = FindUniqueKey(Hashptr_C,to); 
                DeleteNodeInGraph(G[key], index1, index2);
            }
        }
        if (strcmp(op, "End") == 0)
        {
            break;
        }
    }
    char from[10];
    char to[10];
    scanf("%s", from);
    scanf("%s", to);
    int index1 = FindUniqueKey(Hashptr_C,from);
    int index2 = FindUniqueKey(Hashptr_C,to);
    if(index1 == -1 || index2 == -1)
    {
        printf("THIS EXACHANGE DOESN'T EXIST!\n");
        exit(0);
    }
    int mincost = INT_MAX;
    /*
    Iterate through all graphs and find the minimum cost from a currency to a currency in each one and in turn 
    keep storing the minimum of each in mincost
    */
    struct answers final[B_index];
    int index = 0;
    for (int i = 0; i <= B_index; i++)
    {
        if(G[i] == NULL)
        {
            final[i].answer = INT_MAX;
            continue;
        }
        int x = findmincost(G[i],index1,index2);
        final[i].a = G[i]->name;
        final[i].answer = x;
        if (x <= mincost)
        {
            mincost = x;
            index = i;
        }
    }
    if(mincost == INT_MAX)
    {
        printf("THIS EXACHANGE DOESN'T EXIST!\n");
        exit(0);
    }
    printf("%d -> ", mincost);
    for(int i =0;i<strlen(G[index]->name);i++)
    {
        printf("%c",G[index]->name[i]);
    }
    printf("\n");
    int difference = INT_MAX; 
    struct answers a ;
    for(int i =0;i<=B_index;i++)
    {
        if(final[i].answer == mincost)
        {
            continue;
        }
        if(difference > final[i].answer - mincost)
        {
            difference = final[i].answer - mincost;
            a.a = final[i].a;
        }
    }
    if(difference + mincost == INT_MAX)
    {
        printf("Second best conversion doesn't exist!\n");
        exit(0);
    }
    printf("%d -> %s\n",difference + mincost, a.a);
}
