/*******************************************************************
23290 (21년 하반기 오후 1번)
2023/04/07 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define DIR 8
#define SHARK_MOVE 3

int dx[DIR] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[DIR] = {-1, -1, 0, 1, 1, 1, 0, -1};

int smell[4][4];

int shark_dx[4] = {-1 ,0, 1, 0};
int shark_dy[4] = {0, -1, 0, 1};

int max_die = -1;


using namespace std;

pair<int,int> shark_next_move;
vector<pair<int,int>> max_kills;

struct Fish{
    int direction;
};

void visualzie(vector<Fish> map[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            if(map[i][j].empty())
                cout << 0 << " ";
            else
                cout << map[i][j][0].direction << " ";
        cout <<"\n";
    }
    cout <<"\n\n";
}

bool shark_visited[4][4];

void restSharkVisited(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            shark_visited[i][j] = false;
        }
    }
}

void visualizeSmell(){
    cout << "SMELL:\n";
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << smell[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void sharkMove(int x, int y, int step, int kill, vector<Fish> map[4][4], vector<pair<int,int>> kills){
    if(step == SHARK_MOVE){
        if(kill > max_die){
            max_die = kill;
            shark_next_move = {x, y};
            max_kills = kills;
        }
        return;
    }

    for(int i = 0; i < 4; i++){
        int next_x = x + shark_dx[i];
        int next_y = y + shark_dy[i];

        if(next_x >= 0 && next_x < 4 && next_y >= 0 && next_y < 4){
            if(!shark_visited[next_x][next_y]){
                shark_visited[next_x][next_y] = true;
                kills.push_back({next_x, next_y});
                sharkMove(next_x, next_y, step + 1, kill + map[next_x][next_y].size(), map, kills);
                shark_visited[next_x][next_y] = false;
                kills.pop_back();
            }else{
                sharkMove(next_x, next_y, step + 1, kill, map, kills);
            }
        }
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int m, s;
    cin >> m >> s;

    vector<Fish> map[4][4];

    for(int i = 0; i < m; i++){
        int x, y, dir;
        cin >> x >> y >> dir;
        map[x-1][y-1].push_back({dir - 1});
    }
    int shark_x, shark_y;
    cin >> shark_x >> shark_y;
    pair<int,int> shark = {shark_x - 1, shark_y - 1};

    while(s--){
        // copy
        vector<Fish> copy[4][4];
        vector<Fish> move_map[4][4];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                copy[i][j] = map[i][j];
            }
        }
        //move
        //visualzie(map);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(!map[i][j].empty()){
                    for(int fish = map[i][j].size() - 1; fish >= 0; fish--){
                        int direction = map[i][j][fish].direction;
                        
                        bool move = false;
                        for(int rotate = 0; rotate < 8; rotate++){
                            int next_x = i + dx[(direction - rotate + DIR) % DIR];
                            int next_y = j + dy[(direction - rotate + DIR) % DIR];
                            // cout << i << " " << j << " -> " << next_x << " " << next_y << "\n";
                            if(next_x < 0 || next_x >= 4 || next_y < 0 || next_y >= 4)
                                continue;
                            
                            if(!(next_x == shark.first && next_y == shark.second) && smell[next_x][next_y] == 0){
                                move_map[next_x][next_y].push_back(Fish{(direction - rotate + DIR) % DIR});
                                move = true;
                                // cout << i << " " << j << " -> " << next_x << " " << next_y << "\n";
                                break;
                            }
                        }

                        if(!move)
                            move_map[i][j].push_back(Fish{direction});
                    }
                }
            }
        }

        //visualzie(move_map);
        
        // shark move
        max_die = -1;
        sharkMove(shark.first, shark.second, 0, 0, move_map, vector<pair<int,int>>());
        restSharkVisited();

        shark = shark_next_move;
        for(pair<int,int> coordinate : max_kills){
            //cout << coordinate.first << " " << coordinate.second << " \n";
            if(!move_map[coordinate.first][coordinate.second].empty())
                smell[coordinate.first][coordinate.second] = s + 1;
            move_map[coordinate.first][coordinate.second].clear();
        }
        //visualzie(move_map);
        //visualizeSmell();
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(smell[i][j] >= s + 3){
                    smell[i][j] = 0;
                }
            }
        }
        //visualizeSmell();
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                move_map[i][j].insert(move_map[i][j].end(), copy[i][j].begin(), copy[i][j].end());
                map[i][j] = move_map[i][j];
            }
        }
        //visualzie(map);
    }

    int sum = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            sum += map[i][j].size();
        }
    }

    cout << sum;

    return 0;
}