/*******************************************************************
1003 피보나치 함수
2023/05/04 이호준
# 아이디어
1. DP
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// n을 호출할 때 필요한 0, 1;
ll dp[41];

ll fibonacci(int n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return 1;
    }

    if(dp[n] != 0)
        return dp[n];

    return dp[n] = fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    vector<int> inputs(t, 0);
    for(int i = 0; i < t; i++)
        cin >> inputs[i];
    
    int max_value = *max_element(inputs.begin(), inputs.end());
    fibonacci(max_value);
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 0; i < inputs.size(); i++){
        if(inputs[i] == 0)
            cout << 1 << " " << 0 << "\n";
        else
            cout << dp[inputs[i]- 1] << " " << dp[inputs[i]] <<"\n";
    }

    return 0;
}