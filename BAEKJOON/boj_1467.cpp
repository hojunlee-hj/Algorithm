/*******************************************************************
1467 도시분할계획
2023/04/07 이호준
# 아이디어
1. Kruskal
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int parent[100001];

int find(int x){
    if(parent[x] == x)
        return x;
    else
        return parent[x] = find(parent[x]);
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<pair<int, pair<int,int>>> graph;

    for(int i = 0; i < m; i++){
        int x, y, c;
        cin >> x >> y >> c;
        graph.push_back({c,{x, y}});
    }

    sort(graph.begin(), graph.end());

    int answer = 0;

    for(int i = 1; i <= n; i++)
        parent[i] = i;

    int last_edge = 0;
    for(auto g : graph){
        int first = find(g.second.first);
        int second = find(g.second.second);

        if(first != second){
            if(first > second){
                parent[first] = second;
            }else{
                parent[second] = first;
            }
            answer += g.first;
            last_edge = g.first;
        }
    }

    // 신장트리를 만든다. 가장 큰 가중치의 간선을 뺀다..
    
    cout << answer - last_edge;

    return 0;
}