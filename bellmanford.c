#include <stdio.h>
#include <limits.h>
int answer[100], weights[100][100];
void Bellman_Ford(int a, int N)
{
    int flag = 2;
    for (int k = 0; k < N - 1; k++)
    {
        if(flag == 0)
        {
            return ;
        }
        flag = 0;
        for (int i = 1; i < N + 1; i++)
        {
            for (int j = 2; j < N + 1; j++)
            {
                if(i == j)
                {
                    continue;
                }
                if (weights[i][j] < INT_MAX -1 && answer[i] + weights[i][j] < answer[j])
                {
                    flag = 1;
                    answer[j] = answer[i] + weights[i][j];
                }
            }
        }
    }
}
int main()
{
    int N, Q;
    printf("Enter the number of vertices: ");
    scanf("%d", &N);
    printf("Enter number of queries: ");
    scanf("%d", &Q);
    printf("Enter the edges and weights: ");
    for(int i=1;i<N+1;i++)
    {
        for(int j=1;j<N+1;j++)
        {
            weights[i][j] = INT_MAX;
        }
    }
    while (Q--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        scanf("%d", &weights[a][b]);
        //weights[b][a] = weights[a][b];
    }

    answer[1] = 0;
    for (int i = 2; i < N + 1; i++)
    {
        answer[i] = INT_MAX;
    }
    Bellman_Ford(1, N);
    for(int i=1;i<N+1;i++)
    {
        printf("%d ",answer[i]);
    }
    printf("\n");
}