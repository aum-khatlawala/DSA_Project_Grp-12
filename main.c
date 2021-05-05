#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    graph Graph[101];
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
                long long int hashval = 0, i = 0;
                while (bank[i] != '\0')
                {
                    hashval = (37 * hashval) + (int)bank[i++];
                }
                hashval = hashval % 101;
                Initialise(Graph[hashval]);
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
                long long int hashval = 0, i = 0;
                while (bank[i] != '\0')
                {
                    hashval = (37 * hashval) + (int)bank[i++];
                }
                hashval = hashval % 101;
                // InsertInGraph (bankname, curr_a, curr_b, weight)
                InsertInGraph(Graph[hashval], from, to, cost);
            }
        }
        if (strcmp(op, "Delete") == 0)
        {
            scanf("%s", arr);
            if (strcmp(arr, "trade_bank") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                long long int hashval = 0, i = 0;
                while (bank[i] != '\0')
                {
                    hashval = (37 * hashval) + (int)bank[i++];
                }
                hashval = hashval % 101;
                DeleteGraph(Graph[hashval]);
            }
            if (strcmp(arr, "currency") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                char from[20];
                char to[20];
                scanf("%s", from);
                scanf("%s", to);
                long long int hashval = 0, i = 0;
                while (bank[i] != '\0')
                {
                    hashval = (37 * hashval) + (int)bank[i++];
                }
                hashval = hashval % 101;
                DeleteNodeInGraph(Graph[hashval], from, to);
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
    for (int i = 1; i < numgraphs; i++)
    {
        if (findmincost(bank[i], from, to) <= mincost)
            mincost = findmincost(bank[i], from, to);
    }
    printf("%d\n", mincost);
}
