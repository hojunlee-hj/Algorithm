/*******************************************************************
2573 빙산
2023/04/16 이호준
# 아이디어
1. BFS
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};

bool visited[301][301];
int n, m;

void visualize(vector<vector<int>> map){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
}

void resetVisited(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            visited[i][j] = false;
    }
}

bool inRange(int x, int y){
    return x >= 0 && x < n && y >= 0 && y < m;
}

bool isFinish(vector<vector<int>>& map, bool& allMelt){
    int iceberg_cnt = 0;
    for(int i = 1; i < n - 1; i++){
        for(int j = 1; j < m - 1; j++){
            if(map[i][j] > 0 && !visited[i][j]){
                visited[i][j] = true;
                iceberg_cnt++;

                if(iceberg_cnt >= 2){
                    return true;
                }

                queue<pair<int,int>> q;
                q.push({i, j});

                while(!q.empty()){
                    int current_x = q.front().first;
                    int current_y = q.front().second;
                    q.pop();

                    for(int dir = 0; dir < 4; dir++){
                        int next_x = current_x + dx[dir];
                        int next_y = current_y + dy[dir];

                        if(inRange(next_x, next_y) && !visited[next_x][next_y] ){
                            if(map[next_x][next_y] > 0){
                                q.push({next_x, next_y});
                            }
                            visited[next_x][next_y] = true;
                        }
                    }
                }
            }
        }
    }
    if(iceberg_cnt == 0){ allMelt = true; return true;}
    return false;
}

bool isAllMelt(vector<vector<int>>& map){
    for(int i = 1; i < n-1; i++){
        for(int j = 1; j < m-1; j++){
            if(map[i][j] > 0)
                return false;
        }
    }
    return true;
}

void meltIce(vector<vector<int>>& map){
    
    vector<vector<int>> backup = map;

    for(int i = 1; i < n-1; i++){
        for(int j = 1; j < m-1; j++){
            if(backup[i][j] > 0){
                for(int dir = 0; dir < 4; dir++){
                    int next_x = i + dx[dir];
                    int next_y = j + dy[dir];
                    if(inRange(next_x, next_y)){
                        if(backup[next_x][next_y] <= 0)
                            map[i][j]--;
                    }
                }
            }
        }
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(m, 0));

    int year = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }
    
    bool allMelt = false;
    while(!isFinish(map, allMelt)){
        resetVisited();
        meltIce(map);
        year++;
    }

    cout << (allMelt ? 0 : year);

    return 0;
}