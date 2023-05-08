/*******************************************************************
2579 계단오르기
2023/05/08 이호준
# 아이디어
1. DP
*******************************************************************/

#include <iostream>
#include <string>
#include <vector>

#define MAX 301

using namespace std;

int dp[MAX];
int costs[MAX];
int n;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> costs[i];
    }

    dp[1] = costs[1];
	dp[2] = costs[1] + costs[2];
	dp[3] = max(costs[1]+costs[3], costs[2]+costs[3]);

	for (int j = 4; j <= n; j++) {
		dp[j] = max(dp[j - 2] + costs[j], dp[j - 3] + costs[j - 1] + costs[j]);
	}

	cout << dp[n];

    return 0;
}