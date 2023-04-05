/*******************************************************************
색깔폭탄 (21년 상반기 오전 2번)
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/
/*******************************************************************
색깔폭탄 (21년 상반기 오전 2번)
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/
/*******************************************************************
색깔폭탄 (21년 상반기 오전 2번)
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define DIR_NUM 4
#define RED 0
#define BLANK -2
#define BLOCK -1
#define VISITED -3

using namespace std;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};

bool visited[21][21];

struct BoomBundle{
    int red;
    int max_row;
    int min_column;
    vector<pair<int,int>> booms;
};

bool isRange(int x, int y, int n){
    return x >= 0 && x < n && y >=0 && y < n;
}

void clearVisited(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            visited[i][j] = false;
        }
    }
}

bool compare(BoomBundle& a, BoomBundle& b){
    if(a.booms.size() == b.booms.size()){
        if(a.red == b.red){
            if(a.max_row == b.max_row){
                return a.min_column < b.min_column;
            }else
                return a.max_row > b.max_row;
        }else
            return a.red < b.red;
    }else
        return a.booms.size() > b.booms.size();
    
}

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout << "\n\n";
}

void gravity(vector<vector<int>>& map){
    for(int column = 0; column < map.size(); column++){
        queue<int> q;
        for(int row = map.size() - 1; row >= 0; row--){
            if(map[row][column] >= BLOCK){
                q.push(map[row][column]);
            }
        }

        int row = map.size() - 1;
        while(!q.empty()){
            if(q.front() != BLOCK){
                map[row--][column] = q.front();
                q.pop();
            }else{
                if(map[row][column] == BLOCK){
                    row--;
                    q.pop();
                }else{
                    map[row--][column] = BLANK;
                }
            }
        }
        for(int i = row; i >= 0; i--){
            map[i][column] = BLANK;
        }   
    }
}


vector<vector<int>> rotateMap(vector<vector<int>> map){
    int size = map.size();
    vector<vector<int>> new_map(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            new_map[size - 1 - j][i] = map[i][j];
        }
    }
    // for(int j = size - 1; j >= 0; j--)
    //     for(int i = 0; i < size; i++)
    //         new_map[size - 1 - j][i] = map[i][j];

    return new_map;
}

int main(void) {

    int n, m;

    cin >> n >> m;

    vector<vector<int>> map(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> map[i][j];
        }
    }
    int answer = 0;
    // BFS
    while(1){
        // BFS로 폭탄 묶음들 만들기
        vector<BoomBundle> boomBundles;
        vector<vector<int>> backup = map;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(map[i][j] > RED){
                    if(!visited[i][j]){
                        int current_color = map[i][j];
                        visited[i][j] = true;
                        queue<pair<int,int>> q;
                        q.push({i, j});
                        int current_max_row = i;
                        int current_min_column = j;
                        int current_red = 0;
                        vector<pair<int,int>> booms;
                        booms.push_back({i, j});
                        vector<pair<int,int>> reds;
                        while(!q.empty()){
                            int current_x = q.front().first;
                            int current_y = q.front().second;

                            q.pop();

                            for(int dir = 0; dir < DIR_NUM; dir++){
                                int next_x = current_x + dx[dir];
                                int next_y = current_y + dy[dir];

                                if(isRange(next_x, next_y, n) && !visited[next_x][next_y]){
                                    if(map[next_x][next_y] == current_color || map[next_x][next_y] == RED){
                                    
                                        booms.push_back({next_x, next_y});
                                        q.push({next_x, next_y});
                                        visited[next_x][next_y] = true;
                                        if(map[next_x][next_y] == RED){
                                            current_red++;
                                            reds.push_back({next_x, next_y});
                                        }else{
                                            if(current_max_row < next_x){
                                                current_max_row = next_x;
                                                current_min_column = next_y;
                                            }else if (current_max_row == next_x){
                                                if(current_min_column > next_y){
                                                    current_min_column = next_y;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if(booms.size() >= 2)
                            boomBundles.push_back({current_red, current_max_row, current_min_column, booms});
                        for(auto red : reds){
                            visited[red.first][red.second] = false;
                        }
                        // cout << booms.size() << "\n";
                    }
                }
            }
        }
        if(boomBundles.empty()){
            break;
        }else{
            sort(boomBundles.begin(), boomBundles.end(), compare);
            // cout << "zz" << boomBundles.size() <<"\n";
            // for(auto boom : boomBundles){
            //     cout << boom.booms.size() << " " << boom.max_row << " " << boom.min_column << " " << boom.red << "\n";
            // }
            // cout << "\n\n";
            for(pair<int,int> boom : boomBundles[0].booms){
                map[boom.first][boom.second] = BLANK;
            }
            clearVisited(n);
            //visualize(map);
            gravity(map);
                        //visualize(map);
            map = rotateMap(map);
                        //visualize(map);
            gravity(map);
                        //visualize(map);
            answer += boomBundles[0].booms.size() * boomBundles[0].booms.size();
        }        
    }
    
    cout << answer;

    return 0;
}