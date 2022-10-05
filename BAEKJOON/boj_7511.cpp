/*******************************************************************
7511 소셜 네트워킹 어플리케이션
2022/10/05 이호준
# 아이디어
1. Union - Find
*******************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int n[1000001];

int find(int x){
    if(x == n[x]){
        return x;
    }else{
        return n[x] = find(n[x]);
    }
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int case_size;

    cin >> case_size;

    for(int i = 1; i<= case_size; i++){
        int user, relationships;

        cin >> user;
        cin >> relationships;

        for(int a=0; a< user; a++){
            n[a] = a;
        }

        for(int a = 0; a < relationships; a++){
            int x, y;
            cin >> x >> y;
            if(find(x) > find(y)){
                n[find(x)] = find(y);
            }else{
                n[find(y)] = find(x);
            }
        }

        int m;
        cin >> m;

        cout << "Scenario " << i << ":\n";
        for(int a = 0; a < m; a++){
            int x, y;
            cin >> x >> y;
            if(find(x) == find(y)){
                cout << 1 << "\n";
            }else{
                cout << 0 << "\n";
            }
        }
        cout << "\n";
    }

    return 0;
}