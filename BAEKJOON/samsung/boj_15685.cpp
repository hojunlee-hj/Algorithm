/*******************************************************************
15684 드래곤 커브
2023/04/04 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int map[101][101];

void visualize(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cout << map[j][i] << " ";
        }
        cout <<"\n";
    }
    cout <<"\n\n";
}

void drawDragonCurb(int x, int y, int d, int g, int step){
    vector<int> directions;
    int last_x = x;
    int last_y = y;
    for(int i = 0; i <= g; i++){
        if (i == 0){
            map[x][y] = step;
            last_x += dx[d];
            last_y += dy[d];
            map[last_x][last_y] = step;
            directions.push_back(d);
        }
        else{
            int size = directions.size();
            for(int direction = size - 1; direction >= 0; direction--){
                int current_direction = (directions[direction] + 1) % 4;
                last_x += dx[current_direction];
                last_y += dy[current_direction];
                map[last_x][last_y] = step;
                directions.push_back(current_direction);
            }
        }
    }
}

int getAnswer(){
    int answer = 0;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(map[i][j] && map[i][j+1] && map[i+1][j] && map[i+1][j+1])
                answer++;
        }
    }
    return answer;
}



int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;

    cin >> n;

    for(int i = 1; i <= n; i++){
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        drawDragonCurb(x, y, d, g, i);
    }

    cout << getAnswer();

    return 0;
}