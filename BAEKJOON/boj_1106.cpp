/*******************************************************************
1106 호텔
2023/04/20 이호준
# 아이디어
1. DP
2. dp 배열의 차원과 무엇을 놓느냐를 정하는 것이 매우 어렵다. 점화식을 잘 정의해야한다.
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2100000000

using namespace std;

int cost[21];
int customerIncrease[21];

int dp[1101]; // dp[고객수] = 최소비용

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int c, n;
    cin >> c >> n;

    for(int i = 1; i <= n; i++){
        cin >> cost[i] >> customerIncrease[i];
    }

    fill(&dp[1], &dp[c + 101], INF);
    
    for(int i = 1; i <= n; i++){
        for(int j = customerIncrease[i]; j < c + 101; j++){
            dp[j] = min(dp[j], dp[j - customerIncrease[i]] + cost[i]);
        }
    }

    cout << *min_element(&dp[c], &dp[c + 101]);

    return 0;
}

