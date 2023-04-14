/*******************************************************************
14698 전생했더니 슬라임 연구자였던 건에 대하여 (Hard)
2023/04/14 이호준
# 아이디어
1. PQ
*******************************************************************/

#include <iostream>
#include <queue>

#define REMAINDER 1000000007

using namespace std;

typedef long long int ll;

struct compare{

    bool operator()(ll& a, ll&b){
        return a > b;
    }
};

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;

    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        ll temp, sum = 1;
        priority_queue<ll, vector<ll>, compare> q;
        for(int j = 0; j < n; j++){
            cin >> temp;
            q.push(temp);
        }

        while(q.size() > 1){
            ll first_value = q.top(); q.pop();
            ll second_value = q.top(); q.pop();
            ll next_value = ((first_value % REMAINDER) * (second_value % REMAINDER)) % REMAINDER;
            sum = (sum * next_value) % REMAINDER;
            q.push(first_value * second_value);
        }
        cout << sum <<"\n";
    }

    return 0;
}