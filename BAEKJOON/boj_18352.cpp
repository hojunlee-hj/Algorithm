/*******************************************************************
18352 특정 거리의 도시 찾기
2022/10/07 이호준
# 아이디어
1. 다잌스트라
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 2100000000

using namespace std;

int costs[300001];

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, k, x ;

    cin >> n >> m >> k >> x ;

    vector<int> map[300001];

    for(int i = 0; i< m; i++){
        int a, b;
        cin >> a >> b;
        map[a].push_back(b);
    }

    for(int i = 0; i <= n; i++){
        costs[i] = INF;
    }

    costs[x] = 0;

    queue<int> q;

    q.push(x);

    while(!q.empty()){
        int current_node = q.front();

        q.pop();

        for(int i = 0; i < map[current_node].size(); i++){
            int next_node = map[current_node][i];

            if(costs[next_node] > costs[current_node] + 1){
                costs[next_node] = costs[current_node] + 1;
                q.push({next_node});
            }
        }
    }
    vector<int> answers;
    for(int i = 0; i<= n; i++){
        if(costs[i] == k)
            answers.push_back(i);
    }

    if(!answers.empty()){
        sort(answers.begin(), answers.end());
        for(int node : answers){
            cout << node << "\n";
        }
    }else{
        cout << -1;
    }


    return 0;
}