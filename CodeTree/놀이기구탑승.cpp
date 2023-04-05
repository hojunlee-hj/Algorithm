/*******************************************************************
놀이기구 탑승 (21년 상반기 오전 1번)
2023/04/05 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 해당 친구가 놓여져 있느냐
bool visited[401];
pair<int,int> coordinate[401];


int main() {
    // 여기에 코드를 작성해주세요.

    int n;
    cin >> n;

    vector<vector<int>> map(n, vector<int>(n, 0));
    vector<int> sequence(n * n, 0);
    vector<vector<int>> likes(n * n, vector<int>(4, 0));
    for(int i = 0; i < n * n; i++){
        cin >> sequence[i] >> likes[i][0] >> likes[i][1] >> likes[i][2] >> likes[i][3];
    }
    map[1][1] = sequence[0];
    visited[sequence[0]] = true;
    coordinate[sequence[0]] = {1,1};

    for(int i = 1; i < n * n; i++){
        // 현재 좋아하는 학생들의 좌표를 얻어 해당 위치에서 상하좌우 후보를 얻어 가장 많이 인접한 곳으로 넣는다
        int current_student = sequence[i];
        vector<pair<int,int>> neighbors;
        for(int a = 0; a < 4; a++){
            if(visited[likes[i][a]]){
                int friend_x = coordinate[likes[i][a]].first;
                int friend_y = coordinate[likes[i][a]].second;
                for(int b = 0; b < 4; b++){
                    int neighbor_x = friend_x + dx[b];
                    int neighbor_y = friend_y + dy[b];

                    if (neighbor_x >= 0 && neighbor_x < n && neighbor_y >= 0 && neighbor_y < n){
                        if(!map[neighbor_x][neighbor_y])
                            neighbors.push_back({neighbor_x, neighbor_y});
                    }
                }
            }
        }

        int max_friend = 0;
        int max_empty_room = 0;
        pair<int,int> max_friend_coordinate;
        for(auto neighbor : neighbors){
            int room_x = neighbor.first;
            int room_y = neighbor.second;
            int current_friend = 0;
            int current_empty_room = 0;
            for(int a = 0; a < 4; a++){
                int friend_x = room_x + dx[a];
                int friend_y = room_y + dy[a];

                if (friend_x >= 0 && friend_x < n && friend_y >= 0 && friend_y < n){
                    for(auto bestfriend : likes[i]){
                        if(map[friend_x][friend_y]==bestfriend){
                            current_friend++;
                            break;
                        }
                    }
                    if(!map[friend_x][friend_y])
                        current_empty_room++;
                }
            }
            if(max_friend < current_friend){
                max_friend = current_friend;
                max_friend_coordinate = {room_x, room_y};
                max_empty_room = current_empty_room;
            }else if (max_friend == current_friend){
                if(current_empty_room > max_empty_room){
                    max_friend_coordinate = {room_x, room_y};
                    max_empty_room = current_empty_room;
                }else if (current_empty_room == max_empty_room){
                    if(max_friend_coordinate.first > room_x){
                        max_friend_coordinate = {room_x, room_y};
                    }else if (max_friend_coordinate.first == room_x){
                        if(max_friend_coordinate.second > room_y){
                            max_friend_coordinate = {room_x, room_y};
                        }
                    }
                }
                
            }
        }

        if(max_friend != 0){
            map[max_friend_coordinate.first][max_friend_coordinate.second] = current_student;
            visited[current_student] = true;
            coordinate[current_student] = max_friend_coordinate;
        }else{
            // 좋아하는 학생들이 없는 경우 인접한 칸 중 비어있는 칸이 가장 많은 위치로 간다. (가장위, 가장 왼쪽부터..)
            int max_room = -1;
            pair<int,int> max_room_coordinate;
            bool finish = false;
            for(int a = 0; a < n; a++){
                for(int b = 0; b < n; b++){
                    if(!map[a][b]){
                        int current_empty_room = 0;
                        for(int dir = 0; dir < 4; dir++){
                            int neighbor_x = a + dx[dir];
                            int neighbor_y = b + dy[dir];

                            if(neighbor_x >= 0 && neighbor_x < n && neighbor_y >= 0 && neighbor_y < n){
                                if(!map[neighbor_x][neighbor_y]){
                                    current_empty_room++;
                                }
                            }
                        }
                        if(max_room < current_empty_room){
                            max_room = current_empty_room;
                            max_room_coordinate = {a, b};
                            if(max_room == 4){
                                finish = true;
                                break;
                            }
                        }
                    }
                }
                if(finish)
                    break;
            }
            map[max_room_coordinate.first][max_room_coordinate.second] = current_student;
            visited[current_student] = true;
            coordinate[current_student] = max_room_coordinate;
        }

    }
    int answer = 0;
    for(int i = 0; i < n * n ; i++){
        int current_student = sequence[i];
        int current_x = coordinate[current_student].first;
        int current_y = coordinate[current_student].second;

        int current_friend_count = 0;
        for(int dir = 0; dir < 4; dir++){
            int neighbor_x = current_x + dx[dir];
            int neighbor_y = current_y + dy[dir];

            if (neighbor_x >=0 && neighbor_x < n && neighbor_y >=0 && neighbor_y < n){
                for(auto like : likes[i]){
                    pair<int,int> like_friend_coordinate = coordinate[like];
                    if(like_friend_coordinate.first == neighbor_x && like_friend_coordinate.second == neighbor_y){
                        current_friend_count++;
                        break;
                    }
                }
            }
        }
        if (current_friend_count > 0){
            answer += pow(10, current_friend_count - 1);
            // cout << pow(10, current_friend_count - 1) << "\n";
        }
    }

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }

    cout << answer;

    return 0;
}