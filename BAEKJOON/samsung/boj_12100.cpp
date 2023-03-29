/*******************************************************************
12100 2048
2023/03/29 이호준
# 아이디어
1. BruteForce
2. Queue 사용
*******************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define FINISH_STAGE 5

using namespace std;

int max_number = 0;

int getMax(vector<vector<int>>& map){
    int max_value = -1;
    for(auto row : map){
        for(int num : row){
            if(num > max_value){
                max_value = num;
            }
        }
    }
    return max_value;
}

void visualize(vector<vector<int>>& map){
    for(auto a : map ){
        for(auto b : a)
            cout << b << " ";
        cout << "\n";
    }
    cout << "\n";
}

// int dfs(int stage, vector<vector<int>>& map){

//     if(stage == FINISH_STAGE){
//         // check it has max value
//         max_number = max(getMax(map), max_number);
//         return 0;
//     }

//     // 4방으로 change
//     vector<vector<int>> backup_map = map;
//     int n = map.size();
//     for(int i = 0; i < 4; i++){
//         if(i == 0){
//             // left
//             for(int row = 0; row < n; row++){
//                 vector<int> temp;
//                 for(int a = 0; a < n; a++){
//                     if(map[row][a] != 0){
//                         temp.push_back(map[row][a]);
//                     }
//                 }
//                 map[row] = vector<int>(n, 0);
//                 int addCursor = 0;
//                 int current_value = -2;
//                 for(int a = 0; a < temp.size(); a++){
//                     if(temp[a] != 0){
//                         current_value = temp[a];
//                         for(int b = a + 1; b < temp.size(); b++){
//                             if(temp[b]){
//                                 if(temp[b] == current_value){
//                                     map[row][addCursor++] = current_value * 2;
//                                     if(b + 1 < temp.size()){
//                                         current_value = temp[++b];
//                                     }else{
//                                         current_value = -1;
//                                     }
//                                 }else{
//                                     map[row][addCursor++] = current_value;
//                                     current_value = temp[b];
//                                 }
//                             }
//                         }
//                         if(current_value != -1){
//                             map[row][addCursor] = current_value;
//                         }
//                         break;
//                     }
//                 }
//             }
//             // cout << "LEFT\n";
//             // visualize(map);
//         }else if (i == 1){
//             // right
//             for(int row = 0; row < n; row++){
//                 vector<int> temp;
//                 for(int a = 0; a < n; a++){
//                     if(map[row][a] != 0){
//                         temp.push_back(map[row][a]);
//                     }
//                 }
//                 map[row] = vector<int>(n, 0);
//                 int addCursor = n - 1;
//                 int current_value = -1;
//                 for(int a = temp.size() - 1; a >= 0; a--){
//                     if(temp[a] != 0){
//                         current_value = temp[a];
//                         for(int b = a - 1; b >= 0; b--){
//                             if(temp[b]){
//                                 if(temp[b] == current_value){
//                                     map[row][addCursor--] = current_value * 2;
//                                     if(b - 1 >= 0){
//                                         current_value = temp[--b];
//                                     }else{
//                                         current_value = -1;
//                                     }
//                                 }else{
//                                     map[row][addCursor--] = current_value;
//                                     current_value = temp[b];
//                                 }
//                             }
//                         }
//                         if(current_value != -1){
//                             map[row][addCursor] = current_value;
//                         }
//                         break;
//                     }
//                 }
//             }
//             // cout << "RIGHT\n";
//             // visualize(map);
//         }else if (i == 2){
//             // up
//             for(int column = 0; column < n; column++){
//                 vector<int> temp;
//                 for(int a = 0; a < n; a++){
//                     if(map[a][column])
//                         temp.push_back(map[a][column]);
//                     map[a][column] = 0;
//                 }
//                 int addCursor = 0;
//                 int current_value = -1;
//                 for(int a = 0; a < temp.size(); a++){
//                     if(temp[a] != 0){
//                         current_value = temp[a];
//                         for(int b = a + 1; b < temp.size(); b++){
//                             if(temp[b]){
//                                 if(temp[b] == current_value){
//                                     map[addCursor++][column] = current_value * 2;
//                                     if(b + 1 < temp.size()){
//                                         current_value = temp[++b];
//                                     }else{
//                                         current_value = -1;
//                                     }
//                                 }else{
//                                     map[addCursor++][column] = current_value;
//                                     current_value = temp[b];
//                                 }
//                             }
//                         }
//                         if(current_value != -1){
//                             map[addCursor][column] = current_value;
//                         }
//                         break;
//                     }
//                 }
//             }
//             // cout << "UP\n";
//             // visualize(map);
//         }else {
//             // down
//             for(int column = n - 1; column >= 0; column--){
//                 vector<int> temp;
//                 for(int a = 0; a < n; a++){
//                     if(map[a][column])
//                         temp.push_back(map[a][column]);
//                     map[a][column] = 0;
//                 }
//                 int addCursor = n - 1;
//                 int current_value = -1;
//                 for(int a = temp.size() - 1; a >= 0; a--){
//                     if(temp[a] != 0){
//                         current_value = temp[a];
//                         for(int b = a - 1; b >=  0; b--){
//                             if(temp[b]){
//                                 if(temp[b] == current_value){
//                                     map[addCursor--][column] = current_value * 2;
//                                     if(b - 1 >= 0){
//                                         current_value = temp[--b];
//                                     }else{
//                                         current_value = -1;
//                                     }
//                                 }else{
//                                     map[addCursor--][column] = current_value;
//                                     current_value = temp[b];
//                                 }
//                             }
//                         }
//                         if(current_value != -1){
//                             map[addCursor][column] = current_value;
//                         }
//                         break;
//                     }
//                 }
//             }
//             // cout << "DOWN\n";
//             // visualize(map);
//         }
//         dfs(stage + 1, map);
//         map = backup_map;
//     }
//     return max_number;
// }

int dfs(int stage, vector<vector<int>>& map){

    if(stage == FINISH_STAGE){
        // check it has max value
        max_number = max(getMax(map), max_number);
        return 0;
    }
    vector<vector<int>> backup_map = map;
    int n = map.size();
    queue<int> q;
    for(int i = 0; i < 4; i++){
        if(i == 0){
            // Left
            for(int row = 0; row < n; row++){
                for(int a = 0; a < n; a++){
                    if(map[row][a] != 0){
                        q.push(map[row][a]);
                    }
                }
                map[row] = vector<int>(n, 0);
                int addCursor = 0;
                int cursor_data = -1;
                while(!q.empty()){
                    if(cursor_data != q.front()){
                        if(cursor_data != -1){
                            map[row][addCursor++] = cursor_data;
                        }
                        cursor_data = q.front();
                    }else{
                        map[row][addCursor++] = cursor_data * 2;
                        cursor_data = -1;
                    }
                    q.pop();
                }
                if(cursor_data != -1)
                    map[row][addCursor] = cursor_data;
            }
            // cout << "LEFT\n";
            // visualize(map);
        }else if (i == 1){
            // Right
            for(int row = n - 1; row >= 0; row--){
                for(int a = n - 1; a >= 0; a--){
                    if(map[row][a] != 0){
                        q.push(map[row][a]);
                    }
                }
                map[row] = vector<int>(n, 0);
                int addCursor = n - 1;
                int cursor_data = -1;
                while(!q.empty()){
                    if(cursor_data != q.front()){
                        if(cursor_data != -1){
                            map[row][addCursor--] = cursor_data;
                        }
                        cursor_data = q.front();
                    }else{
                        map[row][addCursor--] = cursor_data * 2;
                        cursor_data = -1;
                    }
                    q.pop();
                }
                if(cursor_data != -1)
                    map[row][addCursor] = cursor_data;
            }
            // cout << "RIGHT\n";
            // visualize(map);
        }else if (i == 2){
            // Up
            for(int column = 0; column < n; column++){
                for(int a = 0; a < n; a++){
                    if(map[a][column] != 0){
                        q.push(map[a][column]);
                    }
                    map[a][column] = 0;
                }
                int addCursor = 0;
                int cursor_data = -1;
                while(!q.empty()){
                    if(cursor_data != q.front()){
                        if(cursor_data != -1){
                            map[addCursor++][column] = cursor_data;
                        }
                        cursor_data = q.front();
                    }else{
                        map[addCursor++][column] = cursor_data * 2;
                        cursor_data = -1;
                    }
                    q.pop();
                }
                if(cursor_data != -1)
                    map[addCursor][column] = cursor_data;
            }
            // cout << "UP\n";
            // visualize(map);
        }else{
            // Down
            for(int column = 0; column < n; column++){
                for(int a = n - 1; a >= 0; a--){
                    if(map[a][column] != 0){
                        q.push(map[a][column]);
                    }
                    map[a][column] = 0;
                }
                int addCursor = n - 1;
                int cursor_data = -1;
                while(!q.empty()){
                    if(cursor_data != q.front()){
                        if(cursor_data != -1){
                            map[addCursor--][column] = cursor_data;
                        }
                        cursor_data = q.front();
                    }else{
                        map[addCursor--][column] = cursor_data * 2;
                        cursor_data = -1;
                    }
                    q.pop();
                }
                if(cursor_data != -1)
                    map[addCursor][column] = cursor_data;
            }
            // cout << "DOWN\n";
            // visualize(map);
        }
        dfs(stage + 1, map);
        map = backup_map;
    }

    return max_number;
}


int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;

    cin >> n;

    vector<vector<int>> map(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> map[i][j];
        }
    }

    dfs(0, map);

    cout << max_number;

    return 0;
}