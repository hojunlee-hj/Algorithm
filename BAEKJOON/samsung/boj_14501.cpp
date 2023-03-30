/*******************************************************************
14501 퇴사
2023/03/30 이호준
# 아이디어
1. DP
2. BruteForce
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n; 

    cin >> n;

    vector<pair<int,int>> schedule(n, {0, 0});

    for(int i = 0; i < n; i++){
        cin >> schedule[i].first >> schedule[i].second;
    }

    vector<int> costs(n + 1, 0);



    for(int day = 0; day < n + 1; day++){
        for(int check = 0; check < n; check++){
            if(day == check + schedule[check].first){
                costs[day] = max(costs[day], costs[check] + schedule[check].second);
            }else{
                costs[day] = max(costs[day], costs[check]);
            }
        }
        
    }

    cout << costs[n];

    return 0;
}