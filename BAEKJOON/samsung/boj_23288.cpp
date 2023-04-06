/*******************************************************************
23288 주사위 굴리기2 (21년 하반기 오후 1번)
2023/04/06 이호준
# 아이디어
1. Simulation
2. BFS
*******************************************************************/

#include<iostream>
#include<vector>
#include<queue>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Dice{
    int up, right, left, bottom, front, back;
};

bool visited[21][21];

void resetVisited(int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            visited[i][j] = false;
    }
}

void rotateDice(Dice& dice, int direction){
    switch (direction){
        int temp;
        case RIGHT:
            temp = dice.right;
            dice.right = dice.up;
            dice.up = dice.left;
            dice.left = dice.bottom;
            dice.bottom = temp;
            break;
        case LEFT:
            temp = dice.left;
            dice.left = dice.up;
            dice.up = dice.right;
            dice.right = dice.bottom;
            dice.bottom = temp;
            break;
        case UP:
            temp = dice.back;
            dice.back = dice.up;
            dice.up = dice.front;
            dice.front = dice.bottom;
            dice.bottom = temp;
            break;
        case DOWN:
            temp = dice.front;
            dice.front = dice.up;
            dice.up = dice.back;
            dice.back = dice.bottom;
            dice.bottom = temp;
            break;
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    Dice dice = {1, 3, 4, 6, 5, 2};
    int direction = 0;

    int n, m, k;
    cin >> n >> m >> k;
    int answer = 0;

    pair<int,int> dice_coordinate = {0, 0};

    vector<vector<int>> map(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }

    for(int stage = 0; stage < k; stage++){
        dice_coordinate.first += dx[direction];
        dice_coordinate.second += dy[direction];

        if(dice_coordinate.first < 0 || dice_coordinate.second < 0){
            direction -= 2;
            dice_coordinate.first += dx[direction] * 2;
            dice_coordinate.second += dy[direction] * 2;
        }

        if (dice_coordinate.first >= n || dice_coordinate.second >= m){
            direction += 2;
            dice_coordinate.first += dx[direction] * 2;
            dice_coordinate.second += dy[direction] * 2;
        }

        // dice 돌리기
        rotateDice(dice, direction);

        queue<pair<int,int>> q;
        int check_num = map[dice_coordinate.first][dice_coordinate.second];
        q.push(dice_coordinate);
        visited[dice_coordinate.first][dice_coordinate.second] = true;
        int sum = check_num;
        while(!q.empty()){
            int current_x = q.front().first;
            int current_y = q.front().second;
            q.pop();

            for(int dir = 0; dir < 4; dir++){
                int next_x = current_x + dx[dir];
                int next_y = current_y + dy[dir];
                
                if(next_x >= 0 && next_x < n && next_y >= 0 && next_y < m){
                    if(!visited[next_x][next_y] && map[next_x][next_y] == check_num){
                        q.push({next_x, next_y});
                        sum += check_num;
                        visited[next_x][next_y] = true;
                    }
                }
            }
        }
        resetVisited(n, m);
        answer += sum;

        // set move direction
        if(dice.bottom > check_num){
            direction = (direction + 1) % 4;
        }else if (dice.bottom < check_num){
            direction -= 1;
            if(direction < 0)
                direction += 4;
        }

    }

    cout << answer;

    return 0;
}