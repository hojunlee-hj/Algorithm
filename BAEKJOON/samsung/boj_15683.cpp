/*******************************************************************
15683 감시
2023/03/31 이호준
# 아이디어
1. BruteFroce
2. Simulation
3. %4 방법 획득
*******************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

#define INF 2100000000

using namespace std;

typedef struct CCTV{
    int x;
    int y;
    int direction;
};

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int minBlindSpot = INF;

int getBlindSpot(vector<vector<int>> map){
    int blindSpot = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if(map[i][j] == 0)
                blindSpot++;
        }
    }
    return blindSpot;
}

void monitoring(int direction, CCTV cctv, vector<vector<int>>& map){
    direction %= 4;
    int next_x = cctv.x;
    int next_y = cctv.y;
    while(1){
        next_x += dx[direction];
        next_y += dy[direction];
        if(next_x >= 0 && next_x < map.size() && next_y >= 0 && next_y < map[0].size()){
            if(map[next_x][next_y] == 0 || map[next_x][next_y] == -1){
                map[next_x][next_y] = -1;
            }
            if(map[next_x][next_y] == 6){
                break;
            }
        }else{
            break;
        }
    }
}

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout <<"\n";
}

void dfs(vector<CCTV> cctv, int step, vector<vector<int>>& map){
    if(step == cctv.size()){
        minBlindSpot = min(minBlindSpot, getBlindSpot(map));
        return;
    }

    vector<vector<int>> backupMap = map;

    if(cctv[step].direction == 1){
        for(int i = 0; i < 4; i++){
            monitoring(i, cctv[step], map);
            dfs(cctv, step + 1, map);
            map = backupMap;
        }
    }else if (cctv[step].direction == 2){
        for(int i = 0; i < 2; i++){
            monitoring(i, cctv[step], map);
            monitoring(i + 2, cctv[step], map);
            dfs(cctv, step + 1, map);
            map = backupMap;
        }

    }else if (cctv[step].direction == 3){
        for(int i = 0; i < 4; i++){
            monitoring(i, cctv[step], map);
            monitoring(i + 1, cctv[step], map);
            dfs(cctv, step + 1, map);
            map = backupMap;
        }
    }else{
        for(int i = 0; i < 4; i++){
            monitoring(i, cctv[step], map);
            monitoring(i + 1, cctv[step], map);
            monitoring(i + 2, cctv[step], map);
            dfs(cctv, step + 1, map);
            map = backupMap;
        }
    }
}



int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;
    
    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(m, 0));

    vector<CCTV> cctv;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
            if(map[i][j] > 0 && map[i][j] < 6){
                cctv.push_back({i, j, map[i][j]});
            }
        }
    }


    for(int i = 0; i < cctv.size(); i++){
        if(cctv[i].direction == 5){
            monitoring(i, cctv[i], map);
            monitoring(i + 1, cctv[i], map);
            monitoring(i + 2, cctv[i], map);
            monitoring(i + 3, cctv[i], map);
            cctv.erase(cctv.begin() + i);
            i--;
        }
    }
    dfs(cctv, 0, map);

    cout << minBlindSpot;

    return 0;
}