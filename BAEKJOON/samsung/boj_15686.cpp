/*******************************************************************
15686 치킨배달
2023/04/04 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>

#define INF 2100000000

using namespace std;

bool visited[14];
vector<pair<int,int>> homes;
vector<pair<int,int>> chickens;
int min_chicken_distance = INF;

void updateChickenDistance(){
    int chicken_distance = 0;
    for(int home = 0; home < homes.size(); home++){
        int current_distance = INF;
        for(int chicken = 0; chicken < chickens.size(); chicken++){
            if(visited[chicken]){
                int current_chicken_distance = abs(chickens[chicken].first - homes[home].first) 
                                                + abs(chickens[chicken].second - homes[home].second);
                current_distance = min(current_chicken_distance, current_distance);
            }
        }
        chicken_distance += current_distance;
    }
    min_chicken_distance = min(min_chicken_distance, chicken_distance);
}


void dfs(int step_size, int current_step, int last_chicken, vector<vector<int>> map){
    if(current_step == step_size){
        // check
        updateChickenDistance();
        return;
    }

    for(int i = last_chicken; i < chickens.size(); i++){
        if(!visited[i]){
            visited[i] = true;
            dfs(step_size, current_step + 1, i + 1, map);
            visited[i] = false;
        }
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;

    cin >> n >> m;

    vector<vector<int>> map (n, vector<int>(n, 0));
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int temp;
            cin >> temp;
            if(temp == 1){
                homes.push_back({i, j});
            }else if (temp == 2){
                chickens.push_back({i, j});
            }
            map[i][j] = temp;
        }
    }

    dfs(m, 0, 0, map);

    cout << min_chicken_distance;

    return 0;
}


// Combination (Next_Permutation) -> 4ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, max;
	cin >> n >> max;

	int answer = 210000000;

	vector<vector<int>> map(n, vector<int>(n, 0));
	vector<pair<int, int>> chicken;
	vector<pair<int, int>> house;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			map[i][j] = temp;
			if (temp == 1) {
				house.push_back({ i, j });
			}
			else if (temp == 2) {
				chicken.push_back({ i, j });
			}
		}
	}

	int current_store_size = chicken.size();

	vector<bool> combination(current_store_size, false);


    for (int j = current_store_size - max; j < current_store_size; j++) {
        combination[j] = true;
    }
    do {
        vector < pair<int, int>> selected;
        for (int i = 0; i < current_store_size; i++) {
            if (combination[i]) {
                selected.push_back({ chicken[i] });
            }
        }
        int current_answer = 0;
        for (int a = 0; a < house.size(); a++) {
            int min = 2100000000;
            int current_x = house[a].first;
            int current_y = house[a].second;
            for (int b = 0; b < selected.size(); b++) {
                int current_distance = abs(current_x - selected[b].first) + abs(current_y - selected[b].second);
                if (min > current_distance) {
                    min = abs(current_x - selected[b].first) + abs(current_y - selected[b].second);
                }
            }
            current_answer += min;
        }
        if (answer > current_answer) {
            answer = current_answer;
        }

    } while (next_permutation(combination.begin(), combination.end()));

	cout << answer;

	return 0;
}