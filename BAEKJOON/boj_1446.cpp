/*******************************************************************
1461 도서관
2022/10/05 이호준
# 아이디어
1. Greedy
*******************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 2100000000

using namespace std;

int main(void) {

	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, d, from, to, dis;

	cin >> n >> d;

	vector<int> dist(d + 1, INF);
	vector<pair<int, int>> graph[10001];

	for (int i = 0; i < n; i++) {
		cin >> from >> to >> dis;
		if (to - from <= dis) continue;
		if (to > d) continue;
		graph[from].push_back({ to, dis });
	}

	int before;
	for (int i = 0; i <= d; i++) {
		if (i == 0) before = -1;
		else before = dist[i - 1];
		dist[i] = min(dist[i], before + 1);
		if (!graph[i].empty()) {
			for (int k = 0; k < graph[i].size(); k++) {
				int to = graph[i][k].first;
				int cost = graph[i][k].second;
				if (to > d) continue;
				if (dist[i] + cost < dist[to]) {
					dist[to] = dist[i] + cost;
				}
			}
		}
	}
	cout << dist[d];


	return 0;
}