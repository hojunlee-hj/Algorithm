/*******************************************************************
1967 트리의 지름
2022/10/05 이호준
# 아이디어
1. DFS
*******************************************************************/

#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> tree[10001];
int answer;
int node;

bool visited[10002];

void dfs(int current, int costs){

    if(costs > answer){
        answer = costs;
        node = current;
    }

    for(int i = 0; i < tree[current].size(); i++){
        if(!visited[tree[current][i].first]){
            visited[tree[current][i].first] = true;
            dfs(tree[current][i].first, costs + tree[current][i].second);
            visited[tree[current][i].first] = false;
        }
    }
}


int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    for(int i = 0; i< n - 1; i++){
        int parent, child, cost;
        cin >> parent >> child >> cost;
        tree[parent].push_back({child, cost});
        tree[child].push_back({parent, cost});
    }

    visited[1] = true;
    dfs(1, 0);

    for(int i = 0; i <=n; i++){
        visited[i] = false;
    }
    answer = 0;
    visited[node] = true;
    dfs(node, 0);
    cout << answer;
    return 0;
}