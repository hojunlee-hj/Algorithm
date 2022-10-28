/*******************************************************************
1026 보물
2022/10/28 이호준
# 아이디어
1. Greedy
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

    vector<int> a(n, 0);
    vector<int> b(n, 0);
    for(int i = 0; i< n; i++){
        cin >> a[i];
    }

    for(int i = 0; i< n; i++){
        cin >> b[i];
    }
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<>());

    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += (a[i] * b[i]);
    }

    cout << sum;

    return 0;
}