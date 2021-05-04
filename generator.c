#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    time_t t;
    char bank_names[104][3];
    int i = 0;
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        for (char b = 'A'; b <= 'D'; ++b)
        {
            bank_names[i][0] = c;
            bank_names[i][1] = b;
            bank_names[i][2] = '\0';
            i++;
            if (i == 104)
                break;
        }
        if (i == 104)
            break;
    }
    char currencies[25][4] = {
        "NZD",
        "AUD",
        "SGD",
        "BND",
        "CAD",
        "USD",
        "CHF",
        "INR",
        "AED",
        "EUR",
        "GBP",
        "JOD",
        "OMR",
        "BHD",
        "KWD",
        "CLF",
        "BRL",
        "PLN",
        "BAM",
        "ZMW",
        "TWD",
        "SAR",
        "MAD",
        "JPY",
        "DKK"};
    srand((unsigned)time(&t));
    int bankoccupied[104];
    int currencyoccupiedfrom[25];
    int currencyoccupiedto[25];
    for (int i = 0; i < 104; i++)
    {
        bankoccupied[i] = 0;
    }
    for (int i = 0; i < 25; i++)
    {
        currencyoccupiedfrom[i] = 0;
        currencyoccupiedto[i] = 0;
    }
    int iterations = rand() % 16;
    for (int i = 0; i < iterations + 6; i++)
    {
        printf("Add trade_bank ");
        int banknumber = rand() % 104;
        if (bankoccupied[banknumber] != 0)
        {
            while (bankoccupied[banknumber] != 0)
            {
                banknumber = rand() % 104;
            }
        }
        bankoccupied[banknumber]++;
        printf("%s\n", bank_names[banknumber]);
        for (int i = 0; i < rand() % 25 + 5; i++)
        {
            int currencynumber1 = rand() % 25;
            int currencynumber2 = rand() % 25;
            currencyoccupiedfrom[currencynumber1]++;
            currencyoccupiedto[currencynumber2]++;
            int cost = rand() % 10 + 1;
            printf("Add currency %s %s %s %d\n", bank_names[banknumber], currencies[currencynumber1], currencies[currencynumber2], cost);
        }
    }
    for (int i = 0; i < rand() % 4; i++)
    {
        printf("Delete trade_bank ");
        int banknumber = rand() % 104;
        if (bankoccupied[banknumber] == 0)
        {
            while (bankoccupied[banknumber] == 0)
            {
                banknumber = rand() % 104;
            }
        }
        bankoccupied[banknumber]--;
        printf("%s\n", bank_names[banknumber]);
    }
    int largestfrom = 0;
    int largestto = 0;
    for (int i = 0; i < 25; i++)
    {
        if (currencyoccupiedfrom[i] > largestfrom)
            largestfrom = currencyoccupiedfrom[i];
        if (currencyoccupiedto[i] > largestto)
            largestto = currencyoccupiedto[i];
    }
    int from = largestfrom;
    int to = largestto;
    printf("%s %s\n", currencies[from], currencies[to]);
}