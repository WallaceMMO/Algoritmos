/*
    Jogo da Velha 1d com grundy

    O Objetivo é dado n campos e certa formação de jogo, definir se o jogador 1 ganha
    Os dois jogam com o X e para ganhar tem que alinhar 3 X

    Exemplo:
    5
    X.X.X -> XXX.X
    S
*/

#include <bits/stdc++.h>
#define TAM_MAX 100009

using namespace std;

int grundy[TAM_MAX];

int main()
{
    char text[TAM_MAX];
    memset(grundy, -1, sizeof grundy);

    grundy[0] = 0;
    grundy[1] = grundy[2] = grundy[3] = 1;
    grundy[4] = grundy[5] = 2;

    int sets[TAM_MAX];

    memset(sets, -1, sizeof sets);

    for(int k = 6;k <= TAM_MAX/10;k++) {
        sets[grundy[k-5]] = k;
        sets[grundy[k-4]] = k;
        sets[grundy[k-3]] = k;

        for(int i = 4;i <= k/2+1;i++) {
            int a = i-3,b = k-(i+2);

            sets[grundy[a]^grundy[b]] = k;
        }

        int i = 0;
        for(;i < TAM_MAX;i++) {
            if(sets[i] != k)
                break;
        }

        grundy[k] = i;
    }

    int n;

    while(scanf("%d", &n) == 1, n) {

        scanf("%s", &text);

        int freeX[n];
        int base = 0;

        int aux=0;

        bool foi = false;

        //Verifica se dá para ganhar em uma rodada
        for(int i = 2;i < n && !foi;i++) {
            if(text[i-2] == 'X' && text[i] == 'X' && text[i-1] != 'X' ||
               text[i-2] == 'X' && text[i] != 'X' && text[i-1] == 'X' ||
               text[i-2] != 'X' && text[i] == 'X' && text[i-1] == 'X') {
                foi = true;
            }
        }

        for(int i = 0;i < n && !foi;i++) {

            if(i > 2 && text[i-1] == 'X' && text[i-2] == 'X') {
                aux = 0;
            }
            else if(text[i] == 'X') {
                if(aux-2 > 0)
                    freeX[base++] = aux-2;

                i+=2;
                aux=0;
            }
            else {
                aux++;
            }
        }

        freeX[base++] = aux;

        int ans = 0;

        for(int i = 0;i < base;i++) {
            ans ^= grundy[freeX[i]];
        }

        if(ans || foi) {
            printf("S\n");
        }
        else {
            printf("N\n");
        }
    }

	return 0;
}
