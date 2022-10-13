/*******************************************************************
9465 스티커
2022/10/13 이호준
# 아이디어
1. dp
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;

    cin >> t;

    for(int i = 0; i<t; i++){
        int n;
        cin >> n;
        vector<vector<int>> sticker(2, vector<int>(n, 0));
        for(int a = 0; a<2; a++){
            for(int b = 0; b < n; b++){
                cin >> sticker[a][b];
            }
        }
        vector<vector<int>> dp(2, vector<int>(n + 1, 0));
        dp[0][0] = sticker[0][0]; dp[1][0] = sticker[1][0]; 
        dp[1][1] = sticker[1][1] + dp[0][0]; dp[0][1] = sticker[0][1] + dp[1][0];
        for(int a = 2; a < n; a++){
            dp[0][a] = sticker[0][a] + max(dp[1][a-2], dp[1][a-1]);
            dp[1][a] = sticker[1][a] + max(dp[0][a-2], dp[0][a-1]);
        }
        cout << max(dp[0][n - 1], dp[1][n - 1]) <<"\n";
    }


    return 0;
}