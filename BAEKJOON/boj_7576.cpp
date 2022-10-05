/*******************************************************************
7576 토마토
2022/09/30 이호준
# 아이디어
1. BFS
2. 최적화 -> 토마토 개수로 처리하기!
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool visited[1001][1001];

vector<vector<int>> map;

vector<pair<int,int>> tomatoes;

bool isAllRipen(){
    for(auto a : map){
       for(auto b : a){
            if(b == 0)
                return false;
       }
    }
    return true;
}
int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int m, n;

    cin >> m >> n;

    map = vector(n, vector<int>(m,0));
 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m ; j++){
            cin >> map[i][j];
            if(map[i][j] == 1)
                tomatoes.push_back({i,j});
        }
    }
    
    int current_level = 0;

    if(isAllRipen()){
        cout << 0;
        return 0;
    }else{
        queue<pair<int,pair<int,int>>> q;

        for(auto tomato : tomatoes){
            if(map[tomato.first][tomato.second]){
                q.push({0, {tomato.first, tomato.second}});
                visited[tomato.first][tomato.second] = true;
            }
        }

        
        while(!q.empty()){
            int current_day = q.front().first;
            int current_x = q.front().second.first;
            int current_y = q.front().second.second;

            q.pop();

            if(current_level < current_day){
                if(isAllRipen()){
                    cout << current_day;
                    return 0;
                }else{
                    current_level++;
                }
            }

            for(int i = 0; i < 4; i++){
                int next_x = current_x + dx[i];
                int next_y = current_y + dy[i];

                if(next_x >= 0 && next_x < n && next_y >= 0 && next_y < m){
                    if(!visited[next_x][next_y] && map[next_x][next_y] == 0){
                        visited[next_x][next_y] = true;
                        map[next_x][next_y] = 1;
                        q.push({current_day+1, {next_x, next_y}});
                    }
                }

            }

        }
    }
    if(isAllRipen()){
        cout << current_level + 1;
    }else{
        cout << -1;
    }

    return 0;
}