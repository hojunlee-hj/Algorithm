#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n;

    vector<int> inputs(n, 0);
    for(int i = 0; i< n; i++){
        cin >> inputs[i];
    }

    sort(inputs.begin(), inputs.end());

    cin >> m;
    vector<int> checks(m, 0);
    for(int i = 0; i < m; i++){
        cin >> checks[i];
    }

    for(auto check : checks){
        vector<int>::iterator iter = lower_bound(inputs.begin(), inputs.end(), check);
        if( iter != inputs.end() && *iter == check){
            cout << 1 << "\n";
        }else{
            cout << 0 << "\n";
        }
    }

    return 0;
}