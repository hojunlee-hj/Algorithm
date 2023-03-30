/*******************************************************************
14503 로봇청소기
2023/03/30 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, r, c, current_direction;

    cin >> n >> m;

    cin >> r >> c >> current_direction;

    vector<vector<int>> map(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }

    int cleanCount = 0;

    while(1){
        if(map[r][c] == 0){
            map[r][c] = 2;
            cleanCount++;
        }
        bool dirtyRoom = false;
        for(int direction = 0; direction < 4; direction++){
            int check_x = r + dx[direction];
            int check_y = c + dy[direction];
            
            if(check_x >= 0 && check_x < n && check_y >= 0 && check_y < m){
                if(map[check_x][check_y] == 0){
                    dirtyRoom = true;
                    break;
                }
            }
        }

        if(dirtyRoom){
            current_direction--;
            if(current_direction < 0)
                current_direction = 3;
            int check_x = r + dx[current_direction];
            int check_y = c + dy[current_direction];
            if(check_x >= 0 && check_x < n && check_y >= 0 && check_y < m){
                if(map[check_x][check_y] == 0){
                    r = check_x;
                    c = check_y;
                }
            }
        }else{
            // no dirtyRoom
            int back_direction = current_direction + 2;
            if(back_direction > 3)
                back_direction = current_direction - 2;
            
            int check_x = r + dx[back_direction];
            int check_y = c + dy[back_direction];
            
            if(check_x >= 0 && check_x < n && check_y >= 0 && check_y < m){
                if(map[check_x][check_y] != 1){
                    r = check_x;
                    c = check_y;
                }else if (map[check_x][check_y] == 1){
                    break;
                }
            }
        }
    }

    cout << cleanCount;

    return 0;
}