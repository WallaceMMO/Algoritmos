/*
    N planetas, M rotas,
    1... N temperaturas,
    Q Consultas,
    1... Q -> x planeta inicial para y planeta destino, para obter a menor rota entre os k planetas
    t=0 frios ou t=1 quentes
*/


#include <bits/stdc++.h>
#define MAXN 409
#define INT_MAX 2147483648
#define ll long long

using namespace std;

struct Planet {
    int index, t;

    bool operator<(const Planet& b) {
        return this->t < b.t;
    }
};

struct Consult {
    int x, y, k, t;
};

int matriz[MAXN][MAXN];
Planet planets[MAXN];

int main()
{
    memset(matriz, -1, sizeof matriz);

    int N, M;
    scanf("%d%d", &N, &M);

    for(int i = 1;i <= N;i++) {
        scanf("%d", &planets[i].t);
        planets[i].index = i;
    }

    sort(planets+1, planets + N + 1);

    int a, b, w;
    for(int i = 0;i < M;i++) {
        scanf("%d%d%d", &a, &b, &w);

        matriz[a][b] = w;
        matriz[b][a] = w;
    }

    int Q;
    scanf("%d", &Q);

    Consult consults[Q];
    list<int> cLevels[N+1];
    int results[Q];
    bool levels[N+1];

    for(int i = 0;i < Q;i++) {
        scanf("%d%d%d%d", &consults[i].x, &consults[i].y, &consults[i].k, &consults[i].t);

        cLevels[consults[i].k > N ? N : consults[i].k].push_back(i);
        levels[consults[i].k > N ? N : consults[i].k] = 1;
    }

    int pd[N+1][N+1];

    for(int i = 1;i <= N;i++) for(int j = 1;j <= N;j++) pd[i][j] = matriz[i][j];

    int rank = 0;
    for(int i = 1;i <= N;i++) {
        int index = planets[i].index;

        for(int j = 1;j <= N;j++) {
            for(int k = 1;k <= N;k++) {
                if(j != index && k != index && j != k) {
                    if((pd[j][index] != -1 && pd[index][k] != -1) && (pd[j][k] == -1 ||
                        pd[j][k] > pd[j][index] + pd[index][k])) {
                        pd[j][k] = pd[j][index] + pd[index][k];
                    }
                }
            }
        }

        if(i != N && planets[i].t != planets[i+1].t) rank++;
        else if(i == N) rank++;
        else continue;

        for(int l = rank;l <= (i == N ? N : rank);l++) {
            if(levels[l] != 1) continue;
            for(auto it = cLevels[l].begin();it != cLevels[l].end();it++) {
                int ind = *it;

                if(consults[ind].t == 0) {
                    int x = consults[ind].x, y = consults[ind].y;
                    results[ind] = pd[x][y];
                }
            }
        }
    }

    for(int i = 1;i <= N;i++) for(int j = 1;j <= N;j++) pd[i][j] = matriz[i][j];

    rank = 0;
    for(int i = N;i > 0;i--) {
        int index = planets[i].index;

        for(int j = 1;j <= N;j++) {
            for(int k = 1;k <= N;k++) {
                if(j != index && k != index && j != k) {
                    if((pd[j][index] != -1 && pd[index][k] != -1) && (pd[j][k] == -1 ||
                        pd[j][k] > pd[j][index] + pd[index][k])) {
                        pd[j][k] = pd[j][index] + pd[index][k];
                    }
                }
            }
        }

//        for(int u = 1;u <= N;u++) {
//            for(int v = 1;v <= N;v++) {
//                cout << pd[u][v] << ' ';
//            }
//            cout << endl;
//        }
//        cout << endl;

        if(i != 1 && planets[i].t != planets[i-1].t) rank++;
        else if(i == 1) rank++;
        else continue;

        for(int l = rank;l <= (i == 1 ? N : rank);l++) {
            if(levels[l] != 1) continue;
            for(auto it = cLevels[l].begin();it != cLevels[l].end();it++) {
                int ind = *it;

                if(consults[ind].t == 1) {
                    int x = consults[ind].x, y = consults[ind].y;
                    results[ind] = pd[x][y];
                }
            }
        }
    }

    for(int i = 0;i < Q;i++) {
        printf("%d\n", results[i]);
    }
}
