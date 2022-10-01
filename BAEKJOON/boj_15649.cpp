/*******************************************************************
15649 N과 M
2022/10/1 이호준
# 아이디어
1. 백트래킹
*******************************************************************/

#include <iostream>
using namespace std;

int n,m;
int arr[9];
bool visited[9];

void dfs(int cnt)
{
    if(cnt == m)
    {
        for(int i = 0; i < m; i++)
            cout << arr[i] << ' ';
        cout << '\n';
        return;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!visited[i])
        {
            visited[i] = true;
            arr[cnt] = i;
            dfs(cnt+1);
            visited[i] = false;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;

    dfs(0);
}