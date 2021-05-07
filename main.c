#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////
/*
This is the main driver function for the code which takes in string arguments from the command line interface and performs the required task
*/
//////////////

int main()
{
    graph Graph[101];
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
//                 long long int hashval = 0, i = 0;
//                 while (bank[i] != '\0')
//                 {
//                     hashval = (37 * hashval) + (int)bank[i++];
//                 }
//                 hashval = hashval % 101;
                /*
                Initialise a trade bank graph in the graph array
                */
                Initialise(Graph);
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
                InsertInGraph(Graph, from, to, cost);
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
                DeleteGraph(Graph);
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
                DeleteNodeInGraph(Graph, from, to);
            }
        }
        if (strcmp(op, "End") == 0)
        {
            break;
        }
    }
    int from;
    int to;
    scanf("%d", &from);
    scanf("%d", &to);
    int mincost = findmincost(bank[0], from, to);
    /*
    Iterate through all graphs and find the minimum cost from a currency to a currency in each one and in turn 
    keep storing the minimum of each in mincost
    */
    for (int i = 1; i < numgraphs; i++)
    {
        if (findmincost(bank[i], from, to) <= mincost)
            mincost = findmincost(bank[i], from, to);
    }
    printf("%d\n", mincost);
}
