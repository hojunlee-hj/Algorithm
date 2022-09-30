/*******************************************************************
1300 K번째 수
2022/09/30 이호준
# 아이디어
1. Parametric Search (이진탐색)
-> O(N^2)해결 불가능
-> 이진탐색
답을 찾아야하는 값으로 설정
-> K번째 수를 mid로 설정
mid보다 작은 수가 K개보다 큰경우, k보다 작은경우로 이분탐색하여 서칭
그렇다면 mid보다 작은 수는 어떻게 찾지?
i*j 라는 공식으로 부터 값들이 유츌되기 때문에
i행마다 mid보다 작은 수를 쉽게 카운트 할 수 있다.
i * j < mid
j -> mid / i
그러므로 mid 보다 작은 수는 min(mid / i, n);
*******************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, k;

    cin >> n >> k;

    int left = 1;
    int right = n*n;

    int answer = 0;

    while(left <= right){
        int mid = (left + right) / 2;

        int lower_count = 0;
        for(int i = 1; i<=n; i++){
            lower_count += min(mid / i, n);
        }

        if(lower_count >= k){
            right = mid - 1;
            answer = mid;
        }else{
            left = mid + 1;
        }
    }

    cout << answer;

    return 0;
}