/*******************************************************************
11723 집합
2023/05/08 이호준
# 아이디어
1. 비트마스킹
*******************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int m;
    cin >> m;

    int S = 0;
    for(int i = 0; i < m; i++){
        string operation;
        int num;
        cin >> operation;

        if(operation ==  "add"){
            cin >> num;
            S |= (1 << num);
        }else if(operation == "check"){
            cin >> num;
            cout << ((S & (1 << num)) > 0 ? 1 : 0) << '\n';
        }else if(operation == "remove"){
            cin >> num;
            S &= ~(1 << num);
        }else if(operation == "toggle"){
            cin >> num;
            S ^= (1 << num);
        }else if(operation == "all"){
            S = (1 << 21) - 1;
        }else if(operation == "empty"){
            S = 0;
        }

    }

    return 0;
}