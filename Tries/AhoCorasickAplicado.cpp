#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
using namespace std;

#define MAXS 1000001
#define SIZESTRING 10001

int pd[MAXS];
int f[MAXS];
int g[MAXS][26];
int aQueue[MAXS];

int out[MAXS];
int maxR = 0;

int n;

typedef struct uString {
    char string[SIZESTRING];
} stringX;

stringX arr[10001];

int compara(const void *a, const void *b)
{
    return strlen(((stringX *)a)->string) > strlen(((stringX *)b)->string);
}

int main()
{
    int n;

    while(scanf("%d", &n), n) {
        for(int i = 0;i < n;i++)
            scanf("%s", arr[i].string);

        qsort(arr, n, sizeof(stringX), compara);

        maxR = 0;

        for(int i = 0;i < MAXS;i++) {
            out[i] = pd[i] = 0;
            f[i] = -1;

            for(int j = 0;j < 26;j++) {
                g[i][j] = -1;
            }
        }


    int states = 1;

    for (int i = 0; i < n; ++i)
    {
        const stringX word = arr[i];
        int currentState = 0;

        for (int j = 0; word.string[j] != 0; ++j)
        {
            int ch = word.string[j] - 'a';

            if (g[currentState][ch] == -1)
                g[currentState][ch] = states++;

            currentState = g[currentState][ch];
        }

        out[currentState] = 1;

    }

    for (int ch = 0; ch < 26; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;



    int ini = 0, fim = 0;

    for (int ch = 0; ch < 26; ++ch)
    {
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            pd[g[0][ch]] = pd[0] + out[g[0][ch]];
            aQueue[fim++] = g[0][ch];
        }
    }


    while (fim > ini)
    {
        int state = aQueue[ini++];

        for (int ch = 0; ch < 26; ++ch)
        {
            if (g[state][ch] != -1)
            {
                int failure = f[state];

                while (g[failure][ch] == -1)
                      failure = f[failure];

                failure = g[failure][ch];

                pd[g[state][ch]] = (pd[state] < pd[failure] ? pd[failure] : pd[state]) + out[g[state][ch]];

                maxR = maxR < pd[g[state][ch]] ? pd[g[state][ch]] : maxR;

                f[g[state][ch]] = failure;

                aQueue[fim++] = g[state][ch];
            }
        }
    }

        printf("%d\n", maxR);
    }
	return 0;
}
