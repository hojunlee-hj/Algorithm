/*******************************************************************
4179 불!
2023/04/14 이호준
# 아이디어
1. BFS
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define INF 2100000000

using namespace std;

int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};

int fire[1001][1001];
int human[1001][1001];
int r, c;

void burning(vector<pair<int,int>> fires, vector<vector<char>>& map){
    queue<pair<int,int>> q;
    for(auto fire : fires){
        q.push({fire.first, fire.second});
    }
    while(!q.empty()){
        int current_x = q.front().first;
        int current_y = q.front().second;

        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int next_x = current_x + dx[dir];
            int next_y = current_y + dy[dir];

            if(next_x >= 0 && next_x < r && next_y >= 0 && next_y < c){
                if(!fire[next_x][next_y] && map[next_x][next_y] == '.'){
                    fire[next_x][next_y] = fire[current_x][current_y] + 1;
                    q.push({next_x, next_y});
                }
            }
        }
    }
}

int run(pair<int,int> start, vector<vector<char>>& map){
    queue<pair<int,int>> q;
    q.push(start);
    human[start.first][start.second] = 1;
    while(!q.empty()){
        int current_x = q.front().first;
        int current_y = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int next_x = current_x + dx[dir];
            int next_y = current_y + dy[dir];

            if(next_x < 0 || next_x >= r || next_y < 0 || next_y >= c){
                return human[current_x][current_y];
            }else{
                if(map[next_x][next_y] == '#' || human[next_x][next_y]) continue;
                if(human[current_x][current_y] + 1 < fire[next_x][next_y] || !fire[next_x][next_y]){
                    human[next_x][next_y] = human[current_x][current_y] + 1;
                    q.push({next_x, next_y});
                }
            }
        }
    }
    return -1;
}

void visualizeFire(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cout << fire[i][j] << " ";
        }
        cout << "\n";
    }
    cout <<"\n\n";
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> r >> c;

    vector<vector<char>> map(r, vector<char>(c, '#'));

    vector<pair<int,int>> fires;
    pair<int,int> start;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            char temp;
            cin >> temp;
            map[i][j] = temp;
            if(temp == 'J'){                
                start = {i, j};
                map[i][j] = '.';
            }
            else if (temp == 'F'){
                fires.push_back({i,j});
                fire[i][j] = 1;
            }
        }
    }

    burning(fires, map);

    //visualizeFire();
    
    int answer = run(start, map);
    if(answer == -1){
        cout << "IMPOSSIBLE";
    }else{
        cout << answer;
    }

    return 0;
}