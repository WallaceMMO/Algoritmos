using namespace std;
#include <bits/stdc++.h>

const int MAXS = 1000;
const int MAXC = 26;

unsigned long long out[MAXS];
int f[MAXS];

int g[MAXS][MAXC];


int buildAho(string arr[], int k)
{
    for(int i = 0;i < MAXS;i++)
        out[i] = 0;

    memset(g, -1, sizeof g);

    int states = 1;

    for (int i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        int currentState = 0;

        for (int j = 0; j < word.size(); ++j)
        {
            int ch = word[j] - 'a';

            if (g[currentState][ch] == -1)
                g[currentState][ch] = states++;

            currentState = g[currentState][ch];
        }

        out[currentState] |= (1 << i);
    }

    for (int ch = 0; ch < MAXC; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;

    memset(f, -1, sizeof f);

    int aQueue[MAXS];
    int base = 0;

    for (int ch = 0; ch < MAXC; ++ch)
    {
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            aQueue[base++] = g[0][ch];
        }
    }

    while (base)
    {
        int state = aQueue[--base];

        for (int ch = 0; ch < MAXC; ++ch)
        {
            if (g[state][ch] != -1)
            {
                int failure = f[state];

                while (g[failure][ch] == -1)
                      failure = f[failure];

                failure = g[failure][ch];
                f[g[state][ch]] = failure;

                out[g[state][ch]] |= out[failure];

                aQueue[base++] = g[state][ch];
            }
        }
    }

    return states;
}

int findNextState(int currentState, char nextInput)
{
    int answer = currentState;
    int ch = nextInput - 'a';

    while (g[answer][ch] == -1)
        answer = f[answer];

    return g[answer][ch];
}

void searchWords(string arr[], int k)
{
    int pd[k];

    memset(pd, 0, sizeof pd);

	buildAho(arr, k);

	int maxGlobal = 0;
	for (int i = 0; i < k; ++i)
	{
        int currentState = 0;

        unsigned long long binary = 0;
		for(int j = 0;j < arr[i].size();j++) {
            currentState = findNextState(currentState, arr[i][j]);

            binary |= out[currentState];
		}

		int maxAux = 0;

		for(int j = 0;binary != 1;j++) {

            if(binary % 2 != 0)
                maxAux = max(maxAux, pd[j]);

            binary /= 2;
		}

		pd[i] = maxAux + 1;


		maxGlobal = max(pd[i], maxGlobal);

	}

	printf("%d\n", maxGlobal);
}

bool compara(string a, string b)
{
    if(a.size() < b.size())
        return true;

    return false;
}
// Driver program to test above
int main()
{
    int n;

    while(scanf("%d", &n) && n != 0) {
        string arr[n];

        for(int i = 0;i < n;i++) {
            cin >> arr[i];
        }

        sort(arr, arr + n, compara);

        searchWords(arr, n);
    }
	return 0;
}
