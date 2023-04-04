/*******************************************************************
16236 아기상어
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define INF 2100000000

using namespace std;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

bool visited[21][21];

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout << "\n";
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> map(n, vector<int>(n, 0));

    pair<int,int> shark;
    int shark_size = 2;
    int eat_fish = 0;
    int fish_count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int temp;
            cin >> temp;
            map[i][j] = temp;
            if(temp == 9){
                shark = {i, j};
                map[i][j] = 0;
            }else if(temp > 0){
                fish_count++;
            }
        }
    }


    int answer = 0;
    while(1){
        if(!fish_count)
                break;
        queue<pair<pair<int,int>, int>> q;
        q.push({{shark.first, shark.second}, 0});

        int min_distance = INF;
        pair<int,int> min_fish;
        
        // 물고기들과 상어간의 거리 찾기
        while(!q.empty()){
            int current_x = q.front().first.first;
            int current_y = q.front().first.second;
            int current_time = q.front().second;
            q.pop();

            if(current_time + 1 > min_distance)
                break;

            if(!fish_count)
                break;

            for(int i = 0; i < 4; i++){
                int next_x = current_x + dx[i];
                int next_y = current_y + dy[i];

                if(next_x < 0 || next_x >= n || next_y < 0 || next_y >= n )
                    continue;
                
                if(map[next_x][next_y] > shark_size)
                    continue;
                else if(map[next_x][next_y] == 0 || map[next_x][next_y] == shark_size){
                    if(!visited[next_x][next_y]){
                        q.push({{next_x, next_y}, current_time + 1});
                        visited[next_x][next_y] = true;
                    }
                }else{
                    if(min_distance >= current_time + 1){
                        if(min_distance == current_time + 1){
                            if(min_fish.first < next_x)
                                continue;
                            else if (min_fish.first == next_x){
                                if(min_fish.second < next_y)
                                    continue;
                                else if(min_fish.second > next_y){
                                    min_distance = current_time + 1;
                                    min_fish = {next_x, next_y};
                                }
                            }else{
                                min_distance = current_time + 1;
                                min_fish = {next_x, next_y};
                            }
                        }else{
                            min_distance = current_time + 1;
                            min_fish = {next_x, next_y};
                        }
                    }
                }
            }
        }
        // 최단거리 물고기 먹기 및 상어 성장
        if(min_distance != INF){
            eat_fish++;
            fish_count--;
            map[min_fish.first][min_fish.second] = 0;
            shark = min_fish;
            answer += min_distance;
            if(eat_fish == shark_size){
                shark_size++;
                eat_fish = 0;
            }
            for(int i = 0; i < 21; i++){
                for(int j = 0; j < 21; j++)
                    visited[i][j] = false;
            }
        }else{
            break;
        }
    }

    cout << answer;

    return 0;
}