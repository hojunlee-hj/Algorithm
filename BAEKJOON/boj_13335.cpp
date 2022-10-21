/*******************************************************************
13335 트럭
2022/10/21 이호준
# 아이디어
1. 
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,w,l;

    cin >> n >> w >> l;


    vector<int> weights(n, 0);

    for(int i = 0; i < n; i++){
        cin >> weights[i];
    }

    int current_weight = weights[0];
    int right = 1;

    // {time, index}
    int time = 2;
    queue<pair<int,int>> q;
    q.push({1, 0});
    if(n == 1){
        cout << w + 1;
        return 0;
    }
    /*
        1. q.front() 가 나올 시간에 refresh
        2. 시간이 계속 흐르고 전체 weight 가 L을 넘지 않으면 계속 넣어준다.
    
    */
    while(!q.empty() && right < weights.size()){
        if(time == q.front().first + w){
            int decrease_weight = weights[q.front().second];
            current_weight -= decrease_weight;
            q.pop();
        }

        if(current_weight < l){
            if(weights[right] + current_weight <= l){
                current_weight += weights[right];
                q.push({time, right++});
            }
        }

        if(right >= weights.size()){
            break;
        }
        // cout << time << " " << right << " " << current_weight << " \n";
        time++;
    }

    time += w;

    cout << time;

    return 0;
}