/*******************************************************************
14502 연구소
2023/03/30 이호준
# 아이디어
1. BruteForce
2. 제출 이후 생각 -> 벽놓는 위치를 DFS, 불확산을 BFS로 하면 더 빠르고 명확함.
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int safe_zones = 0;
int max_safe_zones = 0;

void moveFire(vector<pair<int,int>> fires, vector<vector<int>> map){
    int current_safe_zone = safe_zones;
    for(int i = 0; i < fires.size(); i++){
        queue<pair<int,int>> q;

        q.push({fires[i].first, fires[i].second});

        while(!q.empty()){
            int current_x = q.front().first;
            int current_y = q.front().second;

            q.pop();

            for(int direction = 0; direction < 4; direction++){
                int next_x = current_x + dx[direction];
                int next_y = current_y + dy[direction];

                if(next_x >= 0 && next_x < map.size() && next_y >= 0 && next_y < map[0].size()){
                    if(map[next_x][next_y] == 0){
                        map[next_x][next_y] = 2;
                        current_safe_zone--;
                        q.push({next_x, next_y});
                        if(current_safe_zone < max_safe_zones)
                            return;
                    }
                }
            }
        }
    }
    if(current_safe_zone > max_safe_zones){
        max_safe_zones = current_safe_zone;
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(m, 0));

    vector<pair<int,int>> fires;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int temp;
            cin >> temp;
            map[i][j] = temp;
            if(temp == 2){
                fires.push_back({i, j});
            }else if (temp == 0){
                safe_zones++;
            }
        }
    }

    safe_zones -= 3;

    for(int i = 0; i < n * m; i++){
        if(map[i/m][i%m] != 0)
            continue;
        map[i/m][i%m] = 1;
        for(int j = i + 1; j < n * m ; j++){
            if(map[j/m][j%m] != 0)
                continue;
            map[j/m][j%m] = 1;
            for(int w = j + 1; w < n * m ; w++){
                if(map[w/m][w%m] != 0)
                    continue;
                map[w/m][w%m] = 1;
                moveFire(fires, map);
                map[w/m][w%m] = 0;
            }
            map[j/m][j%m] = 0;
        }
        map[i/m][i%m] = 0;
    }

    cout << max_safe_zones;

    return 0;
}