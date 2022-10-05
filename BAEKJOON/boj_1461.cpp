/*******************************************************************
1461 도서관
2022/10/05 이호준
# 아이디어
1. Greedy
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);		
	int n,m,p_pos=0;
	cin >> n >> m; 
	vector<int> distance(n, 0);
	for(int i = 0 ; i < n ;i++){
		cin>>distance[i];
		if(distance[i]<0) p_pos++;
	}
    
	sort(distance.begin(),distance.end());
	
	int result = 0;
	for(int i = n-1; i>= p_pos ;i-=m){
		result += (distance[i]*2);
	}

	for(int i = 0; i< p_pos ;i+=m){
		result += (abs(distance[i]*2));
	}
	
	result -= max(distance[n-1], abs(distance[0]));
	cout<<result;

    return 0;
}