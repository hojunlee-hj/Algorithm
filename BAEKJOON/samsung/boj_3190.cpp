/*******************************************************************
3190 뱀
2023/03/29 이호준
# 아이디어
1. Deque
*******************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void visualzie(vector<vector<int>>& map){
    for(auto a : map){
        for(auto b : a)
            cout << b <<" ";
        cout <<"\n";
    }
    cout <<"\n\n";
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;

    cin >> n;

    vector<vector<int>> map(n, vector<int>(n, 0));

    int k;

    cin >> k;

    for(int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y;
        map[x-1][y-1] = 1;
    }

    int move;

    cin >> move;

    queue<pair<int, char>> rotations;

    for(int i = 0 ; i < move; i++){
        int time;
        char direction;
        cin >> time >> direction;
        rotations.push({time, direction});
    }

    deque<pair<int,int>> snail;

    snail.push_back({0,0});
    map[0][0] = 2;
    int current_direction = 0;
    int current_step = 0;
    while(1){
        current_step++;
        int head_x = snail.front().first;
        int head_y = snail.front().second;

        int next_x = head_x + dx[current_direction];
        int next_y = head_y + dy[current_direction];

        if(next_x >= 0 && next_x < n && next_y >=0 && next_y < n){
            if(map[next_x][next_y] == 0){
                map[next_x][next_y] = 2;
                map[snail.back().first][snail.back().second] = 0;
                snail.push_front({next_x, next_y});
                snail.pop_back();
            }else if (map[next_x][next_y] == 1){
                map[next_x][next_y] = 2;
                snail.push_front({next_x, next_y});
            }else{
                cout << current_step;
                return 0;
            }
        }else{
            cout << current_step;
            return 0;
        }

        if(!rotations.empty() && current_step == rotations.front().first){
            if(rotations.front().second == 'D'){
                current_direction++;
                if(current_direction == 4)
                    current_direction = 0;
            }else{
                current_direction--;
                if(current_direction == -1)
                    current_direction = 3;
            }
            rotations.pop();
        }
        // cout << current_direction <<"\n";
        // visualzie(map);
    }

    return 0;
}