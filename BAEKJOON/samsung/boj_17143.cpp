/*******************************************************************
17143 낚시왕
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define INF 2100000000

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Shark{
    int speed;
    int size;
    int direction;
};

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int R, C, m;
    cin >> R >> C >> m;

    vector<Shark> map[R][C];

    for(int i = 0; i < m; i++){
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        if(d <= 2){
            map[r-1][c-1].push_back({s % ((R-1) * 2), z, d-1});
        }else{
            map[r-1][c-1].push_back({s % ((C-1) * 2), z, d-1});
        }
    }

    int eat_shark_sizes = 0;
    
    for(int column = 0; column < C; column++){
        // 잡아먹기
        for(int row = 0; row < R; row++){
            if(!map[row][column].empty()){
                eat_shark_sizes += map[row][column][0].size;
                map[row][column].clear();
                break;
            }
        }

        if (column == C - 1)
            break;
        
        // 상어 이동
        vector<Shark> new_map[R][C];
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                if(!map[i][j].empty()){
                    // 이동시키기
                    int direction = map[i][j][0].direction;
                    int size = map[i][j][0].size;
                    int speed = map[i][j][0].speed;
                    int next_x = i + dx[direction] * speed;
                    int next_y = j + dy[direction] * speed;

                    if (next_x < 0 || next_x >= R || next_y < 0 || next_y >= C){
                        if(direction < 2){
                            // up, down
                            if(next_x < 0){
                                next_x = -next_x;
                                direction = 1;
                            }
                            if(next_x >= R){
                                if(((next_x / (R-1)) % 2) != 0){
                                    direction = 0;
                                    next_x %= (R - 1);
                                    next_x = (R - 1) - next_x;
                                }else{
                                    next_x %= (R - 1);
                                }
                            }
                        }else{
                            // right, left
                            if(next_y < 0){
                                next_y = -next_y;
                                direction = 2;
                            }

                            if(next_y >= C){
                                if(((next_y / (C-1)) % 2) != 0){
                                    direction = 3;
                                    next_y %= (C - 1);
                                    next_y = (C - 1) - next_y;
                                }else{
                                    next_y %= (C - 1);
                                }
                            }
                        }
                    }

                    // 상어 죽이기
                    if(!new_map[next_x][next_y].empty()){
                        int current_size = new_map[next_x][next_y][0].size;
                        if(current_size < size){
                            new_map[next_x][next_y].clear();
                            new_map[next_x][next_y].push_back({speed, size, direction});
                        }
                    }else{
                        new_map[next_x][next_y].push_back({speed, size, direction});
                    }

                }
            }
        }
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++)
                map[i][j] = new_map[i][j];
        }
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++)
                if(!map[i][j].empty())
                    cout << "(" <<  map[i][j][0].speed << ", " <<map[i][j][0].direction << ") ";
                else
                    cout << 0 <<" ";
            cout << "\n"; 
        }
        cout << "\n";
    }

    cout << eat_shark_sizes;

    return 0;
}