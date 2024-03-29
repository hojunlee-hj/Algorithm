/*******************************************************************
7579 앱
2022/11/01 이호준
# 아이디어
1. DP
*******************************************************************/

#include <iostream>
#include <algorithm>
#define COST_LIMIT 10001

using namespace std;

int N, M;
int m[100];
int c[100];
int DP[COST_LIMIT];

void input(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    for(int i = 0; i < N; i++){
        cin >> m[i];
    }

    for(int i = 0; i < N; i++){
        cin >> c[i];
    }
}

void calcDP(){
    for(int i = 0; i < N; i++){
        for(int j = COST_LIMIT - 1; j >= c[i]; j--){
            DP[j] = max(DP[j], DP[j - c[i]] + m[i]);
        }
    }
}

void findAns(int require_mem){
    for(int i = 0; i < COST_LIMIT; i++){
        if(DP[i] >= require_mem){
            cout << i;
            return;
        }
    }
}

int main(void){
    input();

    calcDP();

    findAns(M);

    return 0;
}