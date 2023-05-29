#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> inputs(n, 0);
    for(int i = 0; i < n; ++i){
        cin >> inputs[i];
    }
    
    int answer = 0;
    int sum = 0;
    sort(inputs.begin(), inputs.end());
    for(int i = 0; i < k; ++i){
        answer += inputs[n - 1 - i];
        answer -= sum;
        sum++;
    }
    
    cout << answer;

    return 0;
}