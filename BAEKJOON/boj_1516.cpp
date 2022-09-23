#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int degree[501];
vector<int> map[501];
int time[501];
int duration[501];

int main(void) {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int t;
		cin >> t;
		duration[i] = t;
		while (true) {
			int n;
			cin >> n;
			if (n == -1) break;
			degree[i]++;
			map[n].push_back(i);
		}
	}
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (degree[i] == 0) {
			q.push(i);
			time[i] = duration[i];
		}
	}
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int i = 0; i <map[now].size(); i++) {
			int next = map[now][i];
			time[next] = max(time[next], time[now] + duration[next]);
			degree[next]--;
			if (degree[next] == 0) {
				q.push(next);
			}
		}
	}
	for (int i = 1; i <= N; i++) cout << time[i]<< "\n";

	return 0;
}