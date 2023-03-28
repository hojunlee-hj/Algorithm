/*******************************************************************
13460 구슬탈출
2023/03/28 이호준
# 아이디어
1. BFS
*******************************************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool visited[11][11][11][11];

typedef struct Point{
	int x;
	int y;
};

typedef struct Marble{
	Point red;
	Point blue;
};

int main(void){

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;

	cin >> n >> m;

	vector<vector<char>> map(n, vector<char>(m, ' '));
	Point red;
	Point blue;
	Point finish;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			cin >> map[i][j];
			if (map[i][j] == 'R')
				red = { i, j };
			else if (map[i][j] == 'B')
				blue = { i, j };
			else if (map[i][j] == 'O')
				finish = { i, j };
		}
	}

	Marble marble = { red, blue };

	queue<pair<Marble, int>> q;

	q.push({ marble, 0 });

	visited[marble.red.x][marble.red.y][marble.blue.x][marble.blue.y] = true;

	while (!q.empty()){
		int r_x = q.front().first.red.x;
		int r_y = q.front().first.red.y;
		int b_x = q.front().first.blue.x;
		int b_y = q.front().first.blue.y;
		int level = q.front().second;
		q.pop();

		if (level >= 10)
			break;

		for (int i = 0; i < 4; i++){
			int n_r_x = r_x;
			int n_r_y = r_y;
			int n_b_x = b_x;
			int n_b_y = b_y;

			int r_move = 0;
			int b_move = 0;

			while (map[n_r_x][n_r_y] != '#' && map[n_r_x][n_r_y] != 'O'){
				n_r_x += dx[i];
				n_r_y += dy[i];
				r_move++;
			}
			while (map[n_b_x][n_b_y] != '#' && map[n_b_x][n_b_y] != 'O'){
				n_b_x += dx[i];
				n_b_y += dy[i];
				b_move++;
			}

			// O을 만나는 케이스 (blue 빠지거나 red 만)
			if (map[n_b_x][n_b_y] == 'O')
				continue;
			if (map[n_r_x][n_r_y] == 'O' && map[n_b_x][n_b_y] != 'O'){
				cout << level+1;
				return 0;
			}

			// 새로운 빨간, 파란공의 좌표가 #라 종료된 조건이므로 이동한 방향을 한번 되돌려준다. (벽은 이동 불가능)
			n_r_x -= dx[i]; n_r_y -= dy[i];
			n_b_x -= dx[i]; n_b_y -= dy[i];

			// 한 위치에 2개의 구슬이 존재하지 못함
            // 이동거리를 기반으로 위치 조정
			if (n_r_x == n_b_x && n_r_y == n_b_y){
				if (r_move < b_move){
					n_b_x -= dx[i];
					n_b_y -= dy[i];
				}
				else{
					n_r_x -= dx[i];
					n_r_y -= dy[i];
				}
			}
			if (!visited[n_r_x][n_r_y][n_b_x][n_b_y]){
				visited[n_r_x][n_r_y][n_b_x][n_b_y] = true;
				q.push({ {{n_r_x, n_r_y}, {n_b_x, n_b_y}}, level + 1 });
			}
		}
	}
	cout << -1;

	return 0;
}