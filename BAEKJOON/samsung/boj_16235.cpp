/*******************************************************************
16235 나무 재테크
2023/04/04 이호준
# 아이디어
1. Simulation
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dx[8] = { -1, 0, 1, 0, 1, 1, -1, -1};
int dy[8] = { 0, 1, 0, -1, 1, -1, 1, -1};

typedef struct ground {
    int feed;
    vector<int> trees;
}Ground;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, k;

    cin >> n >> m >> k;

    vector<vector<Ground>> map(n, vector<Ground>(n, {5}));

    vector<vector<int>> feedMap(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> feedMap[i][j];
        }
    }

    for(int i = 0; i < m; i++){
        int x, y, age;
        cin >> x >> y >> age;
        map[x-1][y-1].trees.push_back(age);
    }

    while(k--){
        vector<vector<Ground>> new_map(n, vector<Ground>(n, {0}));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!map[i][j].trees.empty()){
                    sort(map[i][j].trees.begin(), map[i][j].trees.end());
                    for(int tree = 0; tree < map[i][j].trees.size(); tree++){
                        if(map[i][j].feed - map[i][j].trees[tree] >=0){
                            map[i][j].feed -= map[i][j].trees[tree];
                            map[i][j].trees[tree] += 1;
                        }else{
                            for(int die = tree; die < map[i][j].trees.size(); die++){
                                map[i][j].feed += map[i][j].trees[die] / 2;
                            }
                            map[i][j].trees.erase(map[i][j].trees.begin()+tree, map[i][j].trees.end());
                            break;
                        }
                    }
                    for(int tree : map[i][j].trees){
                        if(tree % 5 == 0){
                            for(int direction = 0; direction < 8; direction++){
                                int neighbor_x = i + dx[direction];
                                int neighbor_y = j + dy[direction];
                                if(neighbor_x < 0 || neighbor_x >= n || neighbor_y < 0 || neighbor_y >= n)
                                    continue;
                                new_map[neighbor_x][neighbor_y].trees.push_back(1);
                            }
                        }
                    }
                }
                map[i][j].feed += feedMap[i][j];
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!new_map[i][j].trees.empty())
                    map[i][j].trees.insert(map[i][j].trees.begin(), new_map[i][j].trees.begin(), new_map[i][j].trees.end());
            }
        }
    }
    int answer = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(!map[i][j].trees.empty())
                answer += map[i][j].trees.size();
        }
    }

    cout << answer;

    return 0;
}