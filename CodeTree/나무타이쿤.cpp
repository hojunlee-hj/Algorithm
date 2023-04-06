/*******************************************************************
나무 타이쿤 (21년 상반기 오후 1번)
2023/04/06 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>

#define DIR 9;

using namespace std;

int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};

int digonal_x[4] = {1, 1, -1, -1};
int digonal_y[4] = {-1, 1, 1, -1};

bool isMedicine[16][16];

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout <<"\n\n";
}

int main(void) {
    // 여기에 코드를 작성해주세요.
    
    int n, m;

    cin >> n >> m;


    vector<vector<int>> map(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
             cin >> map[i][j];
        }
    }

    vector<pair<int,int>> specialMedicine;
    vector<pair<int,int>> moveMedicines;

    specialMedicine.push_back({n-1, 0}); specialMedicine.push_back({n-1, 1});
    specialMedicine.push_back({n-2, 0}); specialMedicine.push_back({n-2, 1});

    for(int year = 0; year < m; year++){
        int direction, move_distance;
        
        cin >> direction >> move_distance;
        
        // move medicine
        for(auto medicine : specialMedicine){
            int move_x = medicine.first + dx[direction] * move_distance;
            int move_y = medicine.second + dy[direction] * move_distance;

            if(move_x >= n){
                move_x %= n;
            }else if (move_x < 0){
                move_x = (n + move_x);
            }

            if(move_y >= n){
                move_y %= n;
            }else if (move_y < 0){
                move_y = (n + move_y);
            }

            moveMedicines.push_back({move_x, move_y});
            map[move_x][move_y] += 1;
            isMedicine[move_x][move_y] = true;
        }

        for(auto medicine : moveMedicines){
            int current_x = medicine.first;
            int current_y = medicine.second;

            for(int dir = 0; dir < 4; dir++){
                int next_x = current_x + digonal_x[dir];
                int next_y = current_y + digonal_y[dir];

                if(next_x >= 0 && next_x < n && next_y >= 0 && next_y < n){
                    if(map[next_x][next_y] > 0)
                        map[current_x][current_y] += 1;
                }
            }
        }
        // visualize(map);
        specialMedicine.clear();
        moveMedicines.clear();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(map[i][j] >= 2 && !isMedicine[i][j]){
                    map[i][j]-=2;
                    specialMedicine.push_back({i,j});
                }
            }
        }
        // visualize(map);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                isMedicine[i][j] = false;
            }
        }
    }

    int sum = 0; 

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            sum += map[i][j];
        }
    }

    cout << sum;

    return 0;
}