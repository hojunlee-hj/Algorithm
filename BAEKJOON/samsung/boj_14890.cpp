/*******************************************************************
14890 경사로
2023/03/30 이호준
# 아이디어
1. BruteForce
*******************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, l;

    cin >> n >> l;

    vector<vector<int>> map(n, vector<int>(n, 0));
    vector<int> check_list[2*n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> map[i][j];
        }
        check_list[i] = map[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            check_list[n + i].push_back(map[j][i]);
        }
    }
    
    int path = 0;
    for(int i = 0; i < 2 * n; i++){
        int check_value = check_list[i][0];
        int same_height = 1;
        bool okay = true;
        for(int j = 1; j < n; j++){
            if(check_list[i][j] == check_value){
                same_height++;
            }
            else if(abs(check_list[i][j] - check_value) >= 2){
                okay = false;
                break;
            }else{
                if(check_list[i][j] - check_value == 1){
                    if(same_height >= l){
                        check_value = check_list[i][j];
                        same_height = 1;
                    }else{
                        okay = false;
                        break;
                    }
                }else{
                    if(j + l - 1< n){
                        for(int a = 1; a < l; a++){
                            if(check_list[i][j] != check_list[i][j + a]){
                                okay = false;
                                break;
                            }
                        }
                    }else{
                        okay = false;
                    }
                    if(!okay)
                        break;
                    same_height = 0;
                    check_value = check_list[i][j];
                    j += l - 1;
                }
            }
        }
        if(okay)
            path++;
    }

    cout << path;

    return 0;
}