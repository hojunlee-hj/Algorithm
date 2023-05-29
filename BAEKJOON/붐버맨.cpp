#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {0, -1, 1, 0};
int dy[4] = {-1, 0, 0, 1};

int r, c;

bool inRange(int x, int y){
    return x >= 0 && x < r && y >= 0 && y < c;
}

void visualizeMap(vector<vector<char>> graph){
    for(int i = 0; i < graph.size(); ++i){
        for(int j = 0; j < graph[0].size(); ++j){
            cout << graph[i][j];
        }
        cout << "\n";
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> r >> c >> n;

    vector<vector<char>> graph(r, vector<char>(c, '.'));
    vector<pair<int,int>> bombs;
    char temp;
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            cin >> graph[i][j];
        }
    }

    int currentTime = 1;
    while(currentTime < n){
        currentTime++;
        if(currentTime % 2 == 0){
            //fill
            for(int i = 0; i < r; ++i){
                for(int j = 0; j < c; ++j){
                    if(graph[i][j] == 'O'){
                        bombs.push_back({i,j});
                    }else{
                        graph[i][j] = 'O';
                    }
                }
            }
        }else{
            // 펑
            for(pair<int,int> bomb : bombs){
                int bomb_x = bomb.first;
                int bomb_y = bomb.second;
                graph[bomb_x][bomb_y] = '.';
                for(int dir = 0; dir < 4; ++dir){
                    int neighbor_x = bomb_x + dx[dir];
                    int neighbor_y = bomb_y + dy[dir];
                    if(inRange(neighbor_x, neighbor_y)){
                        graph[neighbor_x][neighbor_y] = '.';
                    }
                }
            }
            bombs.clear();
        }
    }

    visualizeMap(graph);

    return 0;
}