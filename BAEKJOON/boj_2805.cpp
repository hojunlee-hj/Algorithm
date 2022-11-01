/*******************************************************************
2805 나무 자르기
2022/11/01 이호준
# 아이디어
1. Parametric Search (이진탐색)
*******************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    ll n, m;

    cin >> n >> m;

    vector<ll> trees(n, 0);

    for(int i = 0; i < n; i++){
        cin >> trees[i];
    }

    sort(trees.begin(), trees.end());

    ll left = 1;
    ll right = trees.back();
    ll answer = 0;

    while(left <= right){
        ll mid = (left + right) / 2;

        ll find_index = lower_bound(trees.begin(), trees.end(), mid) - trees.begin();

        ll get_trees = 0;
        for(ll i = find_index; i < trees.size(); i++){
            get_trees += (trees[i] - mid);
        }


        if(get_trees >= m){
            left = mid + 1;
            answer = max(answer, mid);
        }else{
            right = mid - 1;
        }
        
    }

    cout << answer;

    return 0;
}