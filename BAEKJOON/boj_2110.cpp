/*******************************************************************
2110 공유기 설치
2022/10/07 이호준
# 아이디어
1. 이분탐색
1 2 4 8 9
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, c;

    cin >> n >> c;

    vector<int> houses(n, 0);
    for(int i = 0; i< n; i++){
        cin >> houses[i];
    } 
    
    sort(houses.begin(), houses.end());

    int left = 0;
    int right = houses.back();
    int answer = 0;

	while (left <= right) {
		int iptime_cnt = 1;
		int pre_idx = 0;
		int mid = (left + right) / 2;
		for (int i = 1; i < n; i++) {
			if (houses[i] - houses[pre_idx] >= mid) {
				pre_idx = i;
				iptime_cnt++;
			}
		}
		if (iptime_cnt >= c){
            answer = max(answer, mid);
            left = mid + 1;
        }
		else right = mid - 1;
	}

    cout << answer;

    return 0;
}