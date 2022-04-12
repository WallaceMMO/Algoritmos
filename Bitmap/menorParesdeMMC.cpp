#include <bits/stdc++.h>
using namespace std;
int n = 0;

int mdc(int a, int b)
{
    while(b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int mmc(int a, int b)
{
    return a * (b / mdc(a, b));
}

int main()
{

    int t;

    scanf("%d", &t);

    for(int k = 1;k <= t;k++) {

        n = 4;

        int pd[600];

        memset(pd, 0, sizeof pd);

        int graph[9][9];

        scanf("%d", &n);

        int a[2][n];

        for(int i = 0;i < 2;i++) {
            for(int j = 0;j < n;j++) {
                scanf("%d", &a[i][j]);
            }
        }

        for(int i = 0;i < n;i++) {
            for(int j = 0;j < n;j++) {
                graph[i][j] = mmc(a[0][i], a[1][j]);
            }
        }


        int binBase[n];


        memset(binBase, 0, sizeof(binBase));

        binBase[n-1] = 1;
        int idx = 1;

        for(int i = n-1;i >= 0;i--) {
            pd[idx] = graph[0][i];

            idx = idx << 1;
        }
        for(int i = 1;i < n;i++) {
            bitset<9> binary;

            binBase[n-1-i] = 1;

            int bin[n];

            memcpy(bin, binBase, sizeof(bin));

            do{
                string sBin = "";

                for(int l = 0;l < n;l++)
                    sBin.push_back(bin[l] + 48);

                binary = bitset<9>{sBin};

                int minimo = 2147483647;

                int index = 1;

                for(int j = n-1;j >= 0;j--) {
                    bitset<9> assertBinary{binary & bitset<9>{index}};

                    if(assertBinary.to_ulong()) {
                        int regress = (binary ^ bitset<9>{index}).to_ulong();
                        minimo = min(minimo, max(pd[regress], graph[i][j]));
                        //cout << (binary ^ bitset<9>{index}) << ' ' << pd[regress] << ' ' << graph[i][j] << '\n';
                    }

                    index = index << 1;
                }
                pd[binary.to_ulong()] = minimo;

            } while(next_permutation(bin, bin + n));

        }

        string sResponse = "";

        for(int i = 0;i < n;i++)
            sResponse += "1";

        bitset<9> response(sResponse);

        cout << "Caso #" << k << ": " << pd[response.to_ulong()] << endl;
    }
}