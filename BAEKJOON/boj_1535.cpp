/*******************************************************************
1535 안녕
2023/04/20 이호준
# 아이디어
1. DP
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int happy[21];
int loseHealthy[21];

int dp[21][101]; // dp[i][j] i 번째 사람과 인사 & j 체력 소모

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> loseHealthy[i];
    }

    for(int i = 1; i <= n; i++){
        cin >> happy[i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 100; j++){
            if (j - loseHealthy[i] >= 0)
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - loseHealthy[i]] + happy[i]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][99];

    return 0;
}

