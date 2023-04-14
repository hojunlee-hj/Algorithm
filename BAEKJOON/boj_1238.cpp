/*******************************************************************
1238 파티
2023/04/15 이호준
# 아이디어
1. 다잌스트라
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define INF 2100000000

using namespace std;

vector<pair<int,int>> graph1[1001];
vector<pair<int,int>> graph2[1001];

int cost[1001];
int answer[1001];

int n, m, x;

void dijkstra(vector<pair<int,int>> graph[1001]){
    for(int i = 0; i <= n; i++)
        cost[i] = INF;
    
    cost[x] = 0;

    priority_queue<pair<int, int>> q;

    q.push({0, x});

    while(!q.empty()){
        int current_cost = -q.top().first;
        int current = q.top().second;
        q.pop();
        if (current_cost > cost[current])
            continue;
        
        for(auto edge : graph[current]){
            int next_cost = current_cost + edge.second;
            int next_node = edge.first;

            if(next_cost < cost[next_node]){
                cost[next_node] = next_cost;
                q.push({-next_cost, next_node});
            }
        }
    }

    for(int i = 0; i <= n; i++)
        answer[i] += cost[i];

}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    cin >> n >> m >> x;

    for(int i = 0; i < m; i++){
        int start, end, cost;
        cin >> start >> end >> cost;
        graph1[start].push_back({end, cost});
        graph2[end].push_back({start, cost});
    }

    dijkstra(graph1);
    dijkstra(graph2);


    int max_value = 0;
    for(int i = 1; i <= n; i++){
        max_value = max(max_value, answer[i]);
    }
    cout << max_value;

    return 0;
}