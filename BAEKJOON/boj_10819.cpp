/*******************************************************************
10819 차이를 최대로
2022/10/05 이호준
# 아이디어
1. Brute Force
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calculate(int x, int y){
    int result = x - y;
    if(result >= 0) return result;
    else return -result;
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int answer = 0;

    int n;
    cin >> n;

    vector<int> input(n, 0);

    for(int i = 0 ;i < n; i++){
        cin >> input[i];
    }


    vector<int> sequence(n, 0);
    for(int i = 0; i < n; i++){
        sequence[i] = i;
    }

    do{
        int current_sum = 0;
        for(int i = 0 ; i <= n-2; i++){
            current_sum += calculate(input[sequence[i]], input[sequence[i+1]]);
        }
        answer = max(answer, current_sum);
    }while(next_permutation(sequence.begin(), sequence.end()));

    cout << answer;

    return 0;
}