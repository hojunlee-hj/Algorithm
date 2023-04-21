/*******************************************************************
16493 최대 페이지 수
2023/04/21 이호준
# 아이디어
1. Knapsack
*******************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int day[21];
int page[21];

int dp[21][201];

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= m; i++){
        cin >> day[i] >> page[i];
    }

    for(int i = 1; i <= m; i++){
        for(int j = 0; j <= n; j++){
            if (j - day[i] >= 0)
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - day[i]] + page[i]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    cout << dp[m][n];

    return 0;
}