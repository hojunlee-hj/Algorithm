/*******************************************************************
1944 복제로봇
2022/10/28 이호준
# 아이디어
1. BFS + MST
2. 로봇을 복제할 수 있으므로 열쇠까지의 최소거리들을 구하고 MST를 만족하면 정답
*******************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
int n, m;
int sy, sx;
int cnt = 0;
char mat[51][51];
int key_num[51][51];
int isVisited[51][51];
int parents[251];
 
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
 
vector<pair<int, int> > nodes;
vector<pair<pair<int, int>, int> > edges;
 
 
bool inRange(int y, int x){
    return y >= 0 && y < n && x>=0 && x<n ;
}
 
bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    return a.second < b.second;
}
 
// 간선 비용 구하기  
void get_cost(int y, int x, int s){
 
    memset(isVisited, 0, sizeof(isVisited));
    
    queue<pair<int, int> > q;
    q.push({y, x});
    
    int dist = 1;
    
    while(!q.empty()){
        
        int size = q.size();
        
        for(int i=0; i<size; i++){
            y = q.front().first;
            x = q.front().second;
            isVisited[y][x] = 1;
            q.pop();
 
        
            for(int d=0; d<4; d++){
                int ny = y + dy[d];
                int nx = x + dx[d];
            
                if(isVisited[ny][nx]) continue;
                if(!inRange(ny, nx)) continue;
                if(mat[ny][nx] == '1') continue;
            
                isVisited[ny][nx] = 1;
                
                q.push({ny, nx});
                
                if(mat[ny][nx] == 'K'){
                    edges.push_back({{s, key_num[ny][nx]}, dist});
                }
                
            }
        }
        
        dist++;
    }
}
 
 
int getParent(int x){
    if(parents[x] == x) return x;
    return parents[x] = getParent(parents[x]);
}
 
void unionParents(int a, int b){
    a = getParent(a);
    b = getParent(b);
    
    if(a > b) parents[b] = a;
    else parents[a] = b;
}
 
void kruskal(){
    
    for(int i=1; i<=cnt; i++) parents[i] = i;
    
    sort(edges.begin(), edges.end(), cmp);
    
    int answer = 0;
    for(int i=0; i<edges.size(); i++){
        if(getParent(edges[i].first.first) != getParent(edges[i].first.second)){
            unionParents(edges[i].first.first, edges[i].first.second);
            answer += edges[i].second;
        }
    }
 
    int p = getParent(1);
    for(int i=2; i<=cnt; i++){
        if(p != getParent(i)) {
            cout << -1 << endl;
            return;
        }
    }
    
    cout << answer << endl;
}
 
 
void solution(){
    // 간선의 비용을 구한다. 
    for(int i=0; i<nodes.size(); i++)
        get_cost(nodes[i].first, nodes[i].second, i+1);
 
    // 크루스칼 알고리즘  
    kruskal();
}
 
int main(void){
    
    cin >> n >> m;
    
    // 시작점과 키 위치를 노드로 정의한다. 
    for(int i=0; i<n; i++){
        cin >> mat[i];
        for(int j=0; j<n; j++){
            if(mat[i][j] == 'S'){
                mat[i][j] = 'K';
            }
            
            if(mat[i][j] == 'K'){
                nodes.push_back({i,j});
                key_num[i][j] = ++cnt;
            }
        }
    }
 
    solution();
}
