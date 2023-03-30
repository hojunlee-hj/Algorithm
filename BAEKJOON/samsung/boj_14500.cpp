/*******************************************************************
14500 테트로미노
2023/03/30 이호준
# 아이디어
1. BruteForce
2. Cross 모양 (십자가 형태) 따로 탐색필요. -> 이때 그냥 연사로직이 더 빠르다.
*******************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool visited[501][501];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1,  0, -1, 0};
int n, m;
vector<vector<int>> map;

int max_sum = 0;

void dfs(int x, int y, int count, int sum){
    if(count == 3){
        max_sum = max(max_sum, sum);
        return;
    }
    for(int i = 0; i < 4; i++){
        int next_x = x + dx[i];
        int next_y = y + dy[i];
        if(next_x < n && next_x >= 0 && next_y < m && next_y >=0){
            if(!visited[next_x][next_y]){
                visited[next_x][next_y] = true;
                dfs(next_x, next_y, count + 1, sum + map[next_x][next_y]);
                visited[next_x][next_y] = false;
            }
        }
    }
}

void cross(int x, int y){
    vector<int> cross_value(4, 0);
    int center = map[x][y];
    int sum = center;
    int outOfRange = 0;
    for(int i = 0; i < 4; i++){
        int next_x = x + dx[i];
        int next_y = y + dy[i];

        if(next_x < n && next_x >= 0 && next_y < m && next_y >= 0){
            cross_value[i] = map[next_x][next_y];
            sum += map[next_x][next_y];
        }else{
            outOfRange++;
        }
    }

    if(!outOfRange){
        for(int value : cross_value){
            if(value){
                max_sum = max(max_sum, sum - value);
            }
        }
    }else if(outOfRange == 1){
        max_sum = max(max_sum, sum);
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    map = vector<vector<int>>(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            visited[i][j] = true;
            dfs(i, j , 0, map[i][j]);
            visited[i][j] = false;
            cross(i, j);
        }
    }

    cout << max_sum;

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <algorithm>

// bool visited[501][501];

// using namespace std;

// void dfs(vector<vector<int>>& map, int sum, int current, int x, int y);

// int dy[4] = { -1, 0 , 0 };
// int dx[4] = { 0, -1, 1 };
// int max_value;
// int main(void) {

// 	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// 	int n, m;
// 	int x = 0;

// 	cin >> n >> m;

// 	vector<vector<int>> map(n, vector<int>(m, 0));

// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			cin >> map[i][j];
// 		}
// 	}

// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			visited[i][j] = true;
// 			dfs(map, map[i][j], 1, i, j);
// 			visited[i][j] = false;
// 		}
// 	}

// 	//	ㅗ 모양확인 dfs로 확인 불가능하므로

// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			int sum = 0;
// 			// 1. ㅜ
// 			if (i + 1 < n && j + 2 < m) {
// 				sum = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i + 1][j + 1];
// 				max_value = max(max_value, sum);
// 			}

// 			// 2. ㅏ
// 			if (i + 2 < n && j + 1 < m) {
// 				sum = map[i][j] + map[i + 1][j] + map[i + 2][j] + map[i + 1][j + 1];
// 				max_value = max(max_value, sum);
// 			}

// 			// 3. ㅗ
// 			if (i - 1 >= 0 && i < n && j + 2 < m) {
// 				sum = map[i][j] + map[i][j + 1] + map[i][j + 2] + map[i - 1][j + 1];
// 				max_value = max(max_value, sum);
// 			}

// 			// 4. ㅓ
// 			if (i - 1 >= 0 && i + 1 < n && j + 1 < m) {
// 				sum = map[i][j] + map[i][j + 1] + map[i - 1][j + 1] + map[i + 1][j + 1];
// 				max_value = max(max_value, sum);
// 			}
// 		}
// 	}

// 	cout << max_value << endl;

// 	return 0;
// }

// void dfs(vector<vector<int>>& map, int sum, int current, int x, int y)
// {
// 	if (current == 4) {
// 		max_value = max(max_value, sum);
// 		return;
// 	}

// 	int n = map.size();
// 	int m = map[0].size();

// 	for (int i = 0; i < 3; i++) {
// 		int nx = x + dx[i];
// 		int ny = y + dy[i];
// 		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
// 			if (!visited[nx][ny]) {
// 				visited[nx][ny] = true;
// 				dfs(map, sum + map[nx][ny], current + 1, nx, ny);
// 				visited[nx][ny] = false;
// 			}
// 		}
// 	}
// }