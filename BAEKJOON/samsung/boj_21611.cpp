/*******************************************************************
211611 마법사 상어와 블리자드
2023/04/06 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void visualize(vector<vector<int>> map){
    for(auto a : map){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout <<"\n\n";
}

queue<int> reArange(vector<vector<int>>& map, int& score){
    queue<int> q;

    int size = map.size();
    vector<vector<int>> backup(size, vector<int>(size, 0));

    int current_step = 1;
    int sign = -1;
    pair<int, int> current_coordinate = {size / 2, size / 2};
    int current_monster = 0;
    int current_monster_count = 0;
    while(1){

        for(int i = 0; i < current_step; i++){
            current_coordinate.second += sign;
            if(current_coordinate.second == -1)
                break;
            if(map[current_coordinate.first][current_coordinate.second] != 0)
                q.push(map[current_coordinate.first][current_coordinate.second]);
        }
        if(current_coordinate.second == -1)
            break;
        sign *= -1;
        for(int i = 0; i < current_step; i++){
            current_coordinate.first += sign;
            if(map[current_coordinate.first][current_coordinate.second] != 0)
                q.push(map[current_coordinate.first][current_coordinate.second]);
        }
        current_step++;
    }
    
    while(1){
        deque<int> q2;
        int current_monster = 0;
        int current_monster_count = 0;
        int temp_sum = 0;
        queue<int> temp;

        while(!q.empty()){
            q2.push_back(q.front());
            if(current_monster != q.front()){
                current_monster = q.front();
                current_monster_count = 1;
            }else{
                current_monster_count++;
                if(current_monster_count >= 4){
                    if(current_monster_count == 4){
                        for(int a = 0; a < 3; a++){
                            q2.pop_back();
                            score += current_monster;
                            temp_sum += current_monster;
                        }
                    }
                    q2.pop_back();
                    score += current_monster;
                    temp_sum += current_monster;
                }
            }
            q.pop();
        }
        while(!q2.empty()){
            q.push(q2.front());
            q2.pop_front();
        }
        if(temp_sum == 0)
            break;
    }

    queue<int> return_q = q;
    current_step = 1;
    sign = -1;
    current_coordinate = {size / 2, size / 2};

    int current_queue_size = q.size();

    while(1){
        for(int i = 0; i < current_step; i++){
            if(current_queue_size == 0)
                break;
            current_coordinate.second += sign;
            if(current_coordinate.second == -1)
                break;
            backup[current_coordinate.first][current_coordinate.second] = q.front();
            q.pop();
            current_queue_size--;
        }
        if(current_queue_size == 0)
            break;
        if(current_coordinate.second == -1)
            break;
        sign *= -1;
        for(int i = 0; i < current_step; i++){
            if(current_queue_size == 0)
                break;
            current_coordinate.first += sign;
            if(q.empty())
                break;
            backup[current_coordinate.first][current_coordinate.second] = q.front();
            q.pop();
            current_queue_size--;
        }
        current_step++;
    }
    map = backup;

    return return_q;
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

    pair<int,int> player = {n / 2, n / 2};
    int score = 0;

    for(int stage = 0 ; stage < m ; stage++){
        int direction, range;
        cin >> direction >> range;

        for(int i = 1; i <= range; i++){
            int next_x = player.first + dx[direction - 1] * i;
            int next_y = player.second + dy[direction - 1] * i;
            // score += map[next_x][next_y];
            map[next_x][next_y] = 0;
        }
        //visualize(map);
        queue<int> q = reArange(map, score);
        //visualize(map);
        queue<int> new_monster;
        int current_monster = 0;
        int current_monster_count = 0;
        while(!q.empty()){
            if(q.front() == current_monster){
                current_monster_count++;
            }else{
                if(current_monster != 0){
                    new_monster.push(current_monster_count);
                    new_monster.push(current_monster);
                }
                current_monster = q.front();
                current_monster_count = 1;
            }
            q.pop();
        }
        new_monster.push(current_monster_count);
        new_monster.push(current_monster);

        vector<vector<int>> backup(n, vector<int>(n, 0));

        int current_step = 1;
        int sign = -1;
        pair<int,int> current_coordinate = {n / 2, n / 2};

        while(1){
            for(int i = 0; i < current_step; i++){
                current_coordinate.second += sign;
                if(current_coordinate.second == -1)
                    break;
                if(new_monster.empty())
                    break;
                backup[current_coordinate.first][current_coordinate.second] = new_monster.front();
                new_monster.pop();
            }
            if(current_coordinate.second == -1)
                break;
            sign *= -1;
            for(int i = 0; i < current_step; i++){
                current_coordinate.first += sign;
                if(new_monster.empty())
                    break;
                backup[current_coordinate.first][current_coordinate.second] = new_monster.front();
                new_monster.pop();
            }
            if(new_monster.empty())
                break;
            current_step++;
        }
        map = backup;
        // visualize(map);
    }

    cout << score;

    return 0;
}