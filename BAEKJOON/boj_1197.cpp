/*******************************************************************
1197 최소신장트리
2023/04/07 이호준
# 아이디어
1. Kruskal
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int parent[10001];

int find(int x){
    if(parent[x] == x)
        return x;
    else
        return parent[x] = find(parent[x]);
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int v, e;

    cin >> v >> e;

    vector<pair<int, pair<int,int>>> graph;

    for(int i = 0; i < e; i++){
        int x, y, c;
        cin >> x >> y >> c;
        graph.push_back({c,{x, y}});
    }

    sort(graph.begin(), graph.end());

    int answer = 0;

    for(int i = 1; i <= v; i++)
        parent[i] = i;

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
        }
    }
    
    cout << answer;

    return 0;
}