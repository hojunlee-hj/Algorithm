/*******************************************************************
16948 데스나이트
2022/09/30 이호준
# 아이디어
1. BFS 기본 구현
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[6] = {-2,-2,0,0,2,2};
int dy[6] = {-1,1,-2,2,-1,1};

bool visited[201][201];

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,r1,c1,r2,c2;

    cin >> n;

    cin >> r1 >> c1 >> r2 >> c2;

    // {횟수, 좌표}
    queue<pair<int, pair<int,int>>> q;

    q.push({0, {r1, c1}});
    visited[r1][c1] = true;

    while(!q.empty()){

        int current_step = q.front().first;
        int current_x = q.front().second.first;
        int current_y = q.front().second.second;

        q.pop();

        if(current_x == r2 && current_y == c2){
            cout << current_step;
            return 0;
        }

        for(int i = 0; i <6; i++){
            int next_x = current_x + dx[i];
            int next_y = current_y + dy[i];

            if(next_x >= 0 && next_x < n && next_y >=0 && next_y < n){
                if(!visited[next_x][next_y]){
                    q.push({current_step+1, {next_x, next_y}});
                    visited[next_x][next_y] = true;
                }
            }
        }
    }
    
    cout << -1;

    return 0;
}