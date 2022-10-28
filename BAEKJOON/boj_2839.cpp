/*******************************************************************
2839 설탕 배달
2022/10/28 이호준
# 아이디어
1. DP
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>


#define INF 210000000

using namespace std;


int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> sugar({3, 5});
    vector<int> dp(n+1, INF);

    // dp[어떤 값] = min (dp[i] + 1, dp[어떤 값] )
    dp[3] = 1;
    dp[5] = 1;
    for(int i = 6; i<= n; i++){
        dp[i] = min(dp[i - 3] + 1, dp[i - 5] + 1);
    }

    if(dp[n] >= INF){
        cout << -1;
    }else{
        cout << dp[n];
    }

    return 0;
}