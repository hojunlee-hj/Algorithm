/*******************************************************************
11053 가장 긴 증가하는 부분 수열
2022/10/19 이호준
# 아이디어
1. dp
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

int dp[1001];

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> numbers(n, 0);

    for(int i = 0 ; i< n; i++){
        cin >> numbers[i];
    }

    int answer = 0;
    for(int i = 0; i<n; i++){
        dp[i] = 1;
        for(int j = i-1; j >=0; j--){
            if(numbers[i] > numbers[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        answer = max(dp[i], answer);
    }

    cout << answer;

    return 0;
}