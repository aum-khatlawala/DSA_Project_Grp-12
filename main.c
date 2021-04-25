#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
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
                CreateGraph(bank);
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
                // InsertInGraph (bankname, curr_a, curr_b, weight)
                InsertInGraph(bank, from, to, cost);
            }
        }
        if (strcmp(op, "Delete") == 0)
        {
            scanf("%s", arr);
            if (strcmp(arr, "trade_bank") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                DeleteGraph(bank);
            }
            if (strcmp(arr, "currency") == 0)
            {
                char bank[100];
                scanf("%s", bank);
                char from[20];
                char to[20];
                scanf("%s", from);
                scanf("%s", to);
                DeleteNodeInGraph(bank, from, to);
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
