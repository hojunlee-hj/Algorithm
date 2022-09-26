/*******************************************************************
Algorithm Study
BAEKJOON 이분탐색
2512 예산
2022/09/26 이호준
# 아이디어
1. 이분탐색 연습 (Parametric Search Problem)
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

int request_budget_sum[10001];

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    int total_request_budget = 0;
    int total_budget;
    int answer = 0;
    cin >> n;

    vector<int> budgets(n, 0);
    

    for(int i = 0; i < n; i++){
        cin >> budgets[i];
    }

    sort(budgets.begin(), budgets.end());
    request_budget_sum[0] = budgets[0];
    for(int i = 1; i < n; i++){
        request_budget_sum[i] = request_budget_sum[i-1] + budgets[i];
    }

    total_request_budget = request_budget_sum[n-1];

    cin >> total_budget;


    if(total_budget >= total_request_budget){
        cout << budgets.back();
        return 0;
    }else{
        // 정수 상한액 정해서 찾기.
        int left = 1;
        int right = budgets.back();
         
        while(left <= right){
            int mid = (left + right) / 2;
            int find = lower_bound(budgets.begin(), budgets.end(), mid) - budgets.begin();
            int current_sum = mid * (budgets.size() - find);
            // for(int i = 0 ; i < find; i++){
            //     current_sum += budgets[i];
            // }
            current_sum += request_budget_sum[find-1];
            // cout << "STEP : " << left << " " << right << " " << mid << " " << find << " "<< current_sum << " " << total_budget << " \n";
            if (current_sum <= total_budget){
                answer = max(answer, mid);
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
    }
    cout << answer;

    return 0;
}