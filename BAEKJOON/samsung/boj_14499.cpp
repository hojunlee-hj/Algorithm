/*******************************************************************
14499 주사위 굴리기
2023/03/30 이호준
# 아이디어
1. 시뮬레이션
*******************************************************************/

#include <iostream>
#include <vector>

#define EAST 1
#define WEST 2
#define NORTH 3
#define SOUTH 4

using namespace std;

typedef struct DICE{
    int top, bottom, right, left, up, down;
};

int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, 1, -1, 0, 0};

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, x, y, k;

    cin >> n >> m >> x >> y >> k;

    vector<vector<int>> map(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }

    vector<int> commands(k, 0);

    for(int i = 0; i < k; i++){
        cin >> commands[i];
    }

    DICE dice = {0, 0 , 0 , 0, 0, 0};

    for(int command : commands){
        x += dx[command];
        y += dy[command];
        if(x < 0 || x >= n || y < 0 || y >= m){
            x -= dx[command];
            y -= dy[command];
            continue;
        }
        switch(command){
            int temp;
            case EAST :
                        temp = dice.right;
                        dice.right = dice.top;
                        dice.top = dice.left;
                        dice.left = dice.bottom;
                        dice.bottom = temp;
                        break;
            case WEST :
                        temp = dice.left;
                        dice.left = dice.top;
                        dice.top = dice.right;
                        dice.right = dice.bottom;
                        dice.bottom = temp;
                        break;
            case NORTH :
                        temp = dice.up;
                        dice.up = dice.top;
                        dice.top = dice.down;
                        dice.down = dice.bottom;
                        dice.bottom = temp;
                        break;
            case SOUTH :
                        temp = dice.down;
                        dice.down = dice.top;
                        dice.top = dice.up;
                        dice.up = dice.bottom;
                        dice.bottom = temp;
                        break;
            
        }
        if (map[x][y] == 0){
            map[x][y] = dice.bottom;
        }else {
            dice.bottom = map[x][y];
            map[x][y] = 0;
        }
        cout << dice.top << "\n";
    }

    return 0;
}