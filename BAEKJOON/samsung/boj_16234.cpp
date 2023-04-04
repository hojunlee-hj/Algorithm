/*******************************************************************
16234 인구 이동
2023/04/04 이호준
# 아이디어
1. BFS
*******************************************************************/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool visited[51][51];

bool check(int x, int y, int l, int r) {
	return (abs(x-y) <= r && abs(x-y) >= l);
}

int main(void) {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, l, r;

	cin >> n >> l >> r;

	vector<vector<int>> map(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int day = 0;

	while (1) {
		vector<pair<int, int>> current;
		bool ismoved = false;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!visited[i][j]) {
					current.push_back({ i,j });
					visited[i][j] = true;
					queue<pair<int, int>> q;
					int current_bfs_sum = map[i][j];
					q.push({ i,j });
					while (!q.empty()) {
						int current_x = q.front().first;
						int current_y = q.front().second;
						q.pop();
						for (int a = 0; a < 4; a++) {
							int next_x = current_x + dx[a];
							int next_y = current_y + dy[a];
                            if (next_x < 0 || next_x >= n || next_y < 0 || next_y >=n)
                                continue;
                            if (check(map[current_x][current_y], map[next_x][next_y], l, r)
                                    && !visited[next_x][next_y]) {
                                visited[next_x][next_y] = true;
                                ismoved = true;
                                current_bfs_sum += map[next_x][next_y];
                                current.push_back({ next_x,next_y });
                                q.push({ next_x,next_y });
                            }
						}
					}
					int change_value = current_bfs_sum / current.size();
					for (auto a : current) {
						map[a.first][a.second] = change_value;
					}
					current.clear();
				}
			}
		}
		// 국경이동 존재하지 않을 때
		if (!ismoved) {
			break;
		}else {
			day++;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				visited[i][j] = false;
			}
		}
	}

	cout << day;

	return 0;
}