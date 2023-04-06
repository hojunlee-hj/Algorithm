/*******************************************************************
23289 온풍기 안녕! (21년 하반기 오전 2번)
2023/04/06 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define UP_BLOCK 0
#define RIGHT_BLOCK 1

using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool wall[21][21][2];

bool visited[21][21];

void resetVisited(int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            visited[i][j] = false;
        }
    }
}

struct Heater{
    int x;
    int y;
    int direction;
};

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout <<"\n";
    }
    cout <<"\n\n";
}

bool checkTemperature(vector<pair<int,int>> check_rooms, vector<vector<int>> map, int k){
    for(pair<int,int> room_coordinate : check_rooms){
        if(map[room_coordinate.first][room_coordinate.second] < k)
            return false;
    }
    return true;
}

bool inRange(int x, int y, int r, int c){
    return x >= 0 && x < r && y >=0 && y < c;
}

void workHeaters(vector<Heater> heaters, vector<vector<int>>& map){
    int r = map.size();
    int c = map[0].size();

    for(Heater heater : heaters){
        int heater_x = heater.x;
        int heater_y = heater.y;
        int direction = heater.direction;

        // start
        heater_x += dx[direction];
        heater_y += dy[direction];
        map[heater_x][heater_y] += 5;
        queue<pair<pair<int,int>, int>> q;
        int step_size = 4;
        q.push({{heater_x, heater_y}, step_size});
        visited[heater_x][heater_y] = true;
        while(1){
            if(q.empty())
                break;
            
            int current_x = q.front().first.first;
            int current_y = q.front().first.second;
            int current_step = q.front().second;

            q.pop();

            if(current_step != step_size){
                step_size = current_step;
                if(step_size == 0)
                    break;
            }

            // can effect three rooms
            int next_x = current_x + dx[direction];
            int next_y = current_y + dy[direction];
            if(direction == RIGHT || direction == LEFT){
                if(inRange(next_x, next_y, r, c) && !visited[next_x][next_y]){
                    if(direction == RIGHT){
                        if(!wall[current_x][current_y][RIGHT_BLOCK]){
                            map[next_x][next_y] += step_size;
                            q.push({{next_x, next_y}, step_size - 1});
                            visited[next_x][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y <<"\n";
                        }
                    }else{
                        if(!wall[next_x][next_y][RIGHT_BLOCK]){
                            map[next_x][next_y] += step_size;
                            q.push({{next_x, next_y}, step_size - 1});
                            visited[next_x][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y <<"\n";
                        }
                    }
                }
                if (inRange(next_x + 1, next_y, r, c) && !visited[next_x + 1][next_y]){
                    if(direction == RIGHT){
                        if(!wall[next_x+1][next_y - 1][UP_BLOCK] && !wall[next_x+1][next_y-1][RIGHT_BLOCK]){
                            map[next_x + 1][next_y] += step_size;
                            q.push({{next_x + 1, next_y}, step_size - 1});
                            visited[next_x + 1][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x + 1 << " " << next_y <<"\n";                        
                        }
                    }else{
                        if(!wall[current_x + 1][current_y][UP_BLOCK] && !wall[next_x+1][next_y][RIGHT_BLOCK]){
                            map[next_x + 1][next_y] += step_size;
                            q.push({{next_x + 1, next_y}, step_size - 1});
                            visited[next_x + 1][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x + 1 << " " << next_y <<"\n";
                        }
                    }
                }
                if (inRange(next_x - 1, next_y, r, c) && !visited[next_x - 1][next_y]){
                    if(direction == RIGHT){
                        if(!wall[current_x][current_y][UP_BLOCK] && !wall[current_x - 1][current_y][RIGHT_BLOCK]){
                            map[next_x - 1][next_y] += step_size;
                            q.push({{next_x - 1, next_y}, step_size - 1});
                            visited[next_x - 1][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x - 1 << " " << next_y <<"\n";
                        }
                    }else{
                        if(!wall[current_x][current_y][UP_BLOCK] && !wall[next_x - 1][next_y][RIGHT_BLOCK]){
                            map[next_x - 1][next_y] += step_size;
                            q.push({{next_x - 1, next_y}, step_size - 1});
                            visited[next_x - 1][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x - 1 << " " << next_y <<"\n";                        
                        }
                    }
                }
            }else{
                if(inRange(next_x, next_y, r, c) && !visited[next_x][next_y]){
                    if(direction == UP){
                        if(!wall[current_x][current_y][UP_BLOCK]){
                            map[next_x][next_y] += step_size;
                            q.push({{next_x, next_y}, step_size - 1});
                            visited[next_x][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y <<"\n";
                        }
                    }else{
                        if(!wall[next_x][next_y][UP_BLOCK]){
                            map[next_x][next_y] += step_size;
                            q.push({{next_x, next_y}, step_size - 1});
                            visited[next_x][next_y] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y <<"\n";
                        }
                    }
                }
                if (inRange(next_x, next_y + 1, r, c) && !visited[next_x][next_y + 1]){
                    if(direction == UP){
                        if(!wall[current_x][current_y][RIGHT_BLOCK] && !wall[current_x][current_y + 1][UP_BLOCK]){
                            map[next_x][next_y + 1] += step_size;
                            q.push({{next_x, next_y + 1}, step_size - 1});
                            visited[next_x][next_y + 1] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y + 1 <<"\n";
                        }
                    }else{
                        if(!wall[current_x][current_y][RIGHT_BLOCK] && !wall[next_x][current_y + 1][UP_BLOCK]){
                            map[next_x][next_y + 1] += step_size;
                            q.push({{next_x, next_y + 1}, step_size - 1});
                            visited[next_x][next_y + 1] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y + 1 <<"\n";
                        }
                    }
                }
                if (inRange(next_x, next_y - 1, r, c) && !visited[next_x][next_y - 1]){
                    if(direction == UP){
                        if(!wall[current_x][current_y - 1][RIGHT_BLOCK] && !wall[current_x][current_y - 1][UP_BLOCK]){
                            map[next_x][next_y - 1] += step_size;
                            q.push({{next_x, next_y - 1}, step_size - 1});
                            visited[next_x][next_y - 1] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y - 1 <<"\n";
                        }
                    }else{
                        if(!wall[current_x][current_y - 1][RIGHT_BLOCK] && !wall[next_x][current_y - 1][UP_BLOCK]){
                            map[next_x][next_y - 1] += step_size;
                            q.push({{next_x, next_y - 1}, step_size - 1});
                            visited[next_x][next_y - 1] = true;
                            //cout << "Dir : " << direction <<": " << current_x << " " << current_y << "->" << next_x << " " << next_y - 1 <<"\n";
                        }
                    }
                }
            }
        }
        
        resetVisited(r, c);
    }
    
}

void manipulateTemperature(vector<vector<int>>& map){
    int r = map.size();
    int c = map[0].size();
    vector<vector<int>> backup(r, vector<int>(c, 0));

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int current_temperature = map[i][j];
            if(current_temperature == 0)
                continue;
            
            // 상하좌우 돌면서 온도 확산할 수 있나 체크
            for(int dir = 0; dir < 4; dir++){
                int next_x = i + dx[dir];
                int next_y = j + dy[dir];
                
                if(next_x < 0 || next_x >= r || next_y < 0 || next_y >= c)
                    continue;
                
                int check_temperature = map[next_x][next_y];

                if(check_temperature >= current_temperature)
                    continue;

                int difference = (current_temperature - check_temperature) / 4;
                switch (dir){
                    case RIGHT:
                        if(!wall[i][j][RIGHT_BLOCK]){
                            backup[i][j] -= difference;
                            backup[next_x][next_y] += difference;
                        }
                        break;
                    case LEFT:
                        if(!wall[next_x][next_y][RIGHT_BLOCK]){
                            backup[i][j] -= difference;
                            backup[next_x][next_y] += difference;
                        }
                        break;
                    case UP:
                        if(!wall[i][j][UP_BLOCK]){
                            backup[i][j] -= difference;
                            backup[next_x][next_y] += difference;
                        }
                        break;
                    case DOWN:
                        if(!wall[next_x][next_y][UP_BLOCK]){
                            backup[i][j] -= difference;
                            backup[next_x][next_y] += difference;
                        }
                        break;
                }
            }
        }
    }
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            map[i][j] += backup[i][j];
        }
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int r, c, k;
    cin >> r >> c >> k;

    vector<vector<int>> map(r, vector<int>(c, 0));

    vector<pair<int,int>> check_coordinates;
    vector<Heater> heaters;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int temp;
            cin >> temp;
            if(temp > 0){
                if(temp == 5){
                    check_coordinates.push_back({i, j});
                }else{
                    heaters.push_back({i, j, temp - 1});
                }
            }
        }
    }

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x, y, t;
        cin >> x >> y >> t;
        wall[x - 1][y - 1][t] = true;
    }

    int chocolate = 0;
    while(1){
        //visualize(map);
        workHeaters(heaters, map);
        //visualize(map);
        manipulateTemperature(map);
        //visualize(map);

        pair<int,int> edge_check = {0, 0};
        int sign = 1;
        int row_step = c - 1;
        int column_step = r - 1;
        while(1){
            for(int i = 0; i < row_step; i ++){
                edge_check.second += sign;
                if(map[edge_check.first][edge_check.second])
                    map[edge_check.first][edge_check.second] -= 1;
            }  
            for(int i = 0; i < column_step; i++){
                edge_check.first += sign;
                if(map[edge_check.first][edge_check.second])
                    map[edge_check.first][edge_check.second] -= 1;
            }
            sign *= -1;
            if(edge_check.first == 0 && edge_check.second == 0){
                break;
            }
        }
        // visualize(map);
        chocolate += 1;

        if(checkTemperature(check_coordinates, map, k)){
            break;
        }

        if(chocolate > 100){
            break;
        }
    }

    cout << chocolate;

    return 0;
}