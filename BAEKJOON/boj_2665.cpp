/*******************************************************************
2665 미로만들기
2022/10/6 이호준
# 아이디어
1. BFS
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <string>

#define INF 2100000000

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0 ,-1, 0};

int visited[51][51];

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    
    cin >> n;

    vector<vector<int>> map(n, vector<int>(n, 0));

    for(int i = 0; i< n; i++){
        string temp;
        cin >> temp;
        for(int j = 0; j < n; j++){
            map[i][j] = temp[j] - '0';
        }
    }

    for(int i = 0; i< n; i++){
        for(int j = 0; j < n; j++){
            visited[i][j] = INF;
        }
    }

    // for(auto& a : visited){
    //     for(auto& b : a)
    //         b = INF;
    // }

    visited[0][0] = 0 ;

    queue<pair<int,int>> q;

    q.push({0,0});

    while(!q.empty()){
        int current_x = q.front().first;
        int current_y = q.front().second;

        q.pop();

        for(int i = 0; i< 4; i++){
            int next_x = current_x + dx[i];
            int next_y = current_y + dy[i];

            if(next_x >= 0 && next_x < n && next_y >=0 && next_y < n){
                if(map[next_x][next_y]){
                    if(visited[next_x][next_y] > visited[current_x][current_y]){
                        q.push({next_x, next_y});
                        visited[next_x][next_y] = visited[current_x][current_y];
                    }
                }else{
                    if(visited[next_x][next_y] > visited[current_x][current_y] + 1 ){
                        visited[next_x][next_y] = visited[current_x][current_y] + 1 ;
                        q.push({next_x, next_y});
                    }
                }
            }
        }
       
    }


    cout << visited[n-1][n-1];

    return 0;
}