/*******************************************************************
1643 랜선 자르기
2023/04/21 이호준
# 아이디어
1. Parametric Search
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int k, n;
    cin >> k >> n;

    vector<ll> lans(k, 0);

    for(int i = 0; i < k; ++i){
        cin >> lans[i];
    }

    sort(lans.begin(), lans.end());

    ll left = 1;
    ll right = lans.back();
    ll answer = 0;

    while(left <= right){
        ll mid = (left + right) / 2;
        
        ll sum = 0;
        for(int i = 0; i < k; i++){
            sum += lans[i] / mid;
        }

        if(sum >= n){
            left = mid + 1;
            answer = max(answer, mid);
        }else{
            right = mid - 1;
        }
    }

    cout << answer;

    return 0;
}