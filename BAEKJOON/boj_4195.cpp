/*******************************************************************
4195 친구 네트워크
2022/10/13 이호준
# 아이디어
1. Union-Find
*******************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define MAXRANGE 200004

using namespace std;

int friend_maps[MAXRANGE];
int costs[MAXRANGE];

int find(int x){
    if(x == friend_maps[x]){
        return x;
    }else{
        return friend_maps[x] = find(friend_maps[x]);
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;

    cin >> t;

    for(int i = 0; i < t; i++){
        int f;
        cin >> f;
        unordered_map<string, int> members;
        int member_index = 1;
        for(int j = 1; j < MAXRANGE; j++){
            friend_maps[j] = j;
        }
        for(int j = 0; j < MAXRANGE ; j++){
            costs[j] = 0;
        }
        for(int j = 0; j < f ; j++){
            string a, b;
            cin >> a >> b;
            if(members.find(a) == members.end()){
                costs[member_index] = 1;
                members.insert({a, member_index++});
            }

            if(members.find(b) == members.end()){
                costs[member_index] = 1;
                members.insert({b, member_index++});
            }
            int x = find(members[a]);
            int y = find(members[b]);
            if(x != y){
                if(x > y){
                    friend_maps[x] = y;
                    costs[y] += costs[x];
                    cout << costs[y] <<"\n";
                }else{
                    friend_maps[y] = x;
                    costs[x] += costs[y];
                    cout << costs[x] <<"\n";
                }
            }else{
                cout << costs[x] << "\n";
            }
            
        }
    }

    return 0;
}