/*******************************************************************
15684 사다리 조작
2023/04/01 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int min_value = 5;
bool check(vector<vector<int>> &map);
void print(vector<vector<int>> &map);

void dfs(vector<vector<int>> &map, int current,int x, bool& flag);

int main(void) {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, h, m;

	cin >> n >> h >> m;

	vector<vector<int>> map(m + 1, vector<int>(n+1, 0));

	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;
		map[x][y] = 1;
	}

	bool flag = false;
	dfs(map, 1, 1, flag);

	cout << (min_value == 5 ? -1 : min_value )<< endl;

	return 0;
}

bool check(vector<vector<int>>& map){
	for(int i = 1; i < map[0].size(); i++){
        int start_index = i;
        for(int j = 1; j < map.size(); j++){
            if(map[j][start_index])
                start_index++;
            else if (map[j][start_index - 1])
                start_index--;
        }
        if(start_index != i){
            return false;
        }
    }
    return true;
}

void print(vector<vector<int>>& map){
	for(auto a : map){
		for (auto b : a)
			cout << b << " ";
		cout << "\n";
	}
	cout << "\n";
}

void dfs(vector<vector<int>>& map, int current, int x, bool& flag){
	if (flag || current > 4 || current-1 >= min_value)
		return;

	if (check(map)) {
		min_value = min(current-1, min_value);
		if (min_value == 0)
			flag = true;
		return;
	}

	for (int i = x; i < map.size(); i++) {
		for (int j = 1; j < map[0].size() - 1; j++) {
            if (map[i][j - 1] || map[i][j] || map[i][j + 1]) continue;
            map[i][j] = 1;
            dfs(map, current + 1,i, flag);
            map[i][j] = 0;
		}
	}
}
