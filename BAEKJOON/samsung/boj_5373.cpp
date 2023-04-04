/*******************************************************************
5373 큐빙
2023/04/04 이호준
# 아이디어
1. Simulation
2. 결국 작은 하나의 큐브가 회전하는 것과 동일하다.
*******************************************************************/
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef struct cuve {
	char top, front, bot, back, left, right;
};
cuve cuv[3][3][3];	

void init_cuve() {
	for (int h = 0; h < 3; ++h) {
		for (int y = 0; y < 3; ++y) {
			for (int x = 0; x < 3; ++x) {
				cuv[h][y][x].top = 'w';
				cuv[h][y][x].bot = 'y';
				cuv[h][y][x].front = 'r';
				cuv[h][y][x].back = 'o';
				cuv[h][y][x].left = 'g';
				cuv[h][y][x].right = 'b';
			}
		}
	}
}

// 큐브 from에서 큐브 to로 값을 복사
void copy_cuve(cuve from[][3][3], cuve to[][3][3]) {
	int h, y, x;
	for (h = 0; h < 3; ++h)
		for (y = 0; y < 3; ++y)
			for (x = 0; x < 3; ++x)
				to[h][y][x] = from[h][y][x];
}

// 명령어를 입력받고 면을 회전하는 코드 (side: 면, direction: 시계/반시계)
void rotate(char side, char direction) {
	char temp;
	int h, y, x;
	cuve new_cuve[3][3][3];
	copy_cuve(cuv, new_cuve);
	if (side == 'U' || side == 'D') { // 윗면 또는 아랫면인 경우 (h고정, yx가변)
		h = (side == 'U' ? 0 : 2); // 높이 고정
		if ((direction == '+' && side == 'U') ||
			(direction == '-' && side == 'D')) {
			// 윗면 시계, 바닥면 반시계
			for (y = 0; y < 3; ++y) {
				for (x = 0; x < 3; ++x) {
					// back -> right -> front -> left -> back
					temp = cuv[h][y][x].left;
					cuv[h][y][x].left = cuv[h][y][x].front;
					cuv[h][y][x].front = cuv[h][y][x].right;
					cuv[h][y][x].right = cuv[h][y][x].back;
					cuv[h][y][x].back = temp;

					new_cuve[h][x][2 - y] = cuv[h][y][x];
				}
			}
		}
		else { // 윗면 반시계, 바닥면 시계
			for (y = 0; y < 3; ++y) {
				for (x = 0; x < 3; ++x) {
					// back -> left -> front -> right -> back
					temp = cuv[h][y][x].right;
					cuv[h][y][x].right = cuv[h][y][x].front;
					cuv[h][y][x].front = cuv[h][y][x].left;
					cuv[h][y][x].left = cuv[h][y][x].back;
					cuv[h][y][x].back = temp;

					new_cuve[h][2 - x][y] = cuv[h][y][x];
				}
			}
		}
	}
	else if (side == 'F' || side == 'B') { // 앞면 또는 뒷면인 경우 (y고정, hx가변)
		y = (side == 'F' ? 2 : 0); // y 고정 (앞면: 2, 뒷면: 0)
		if ((direction == '+' && side == 'F') ||
			(direction == '-' && side == 'B')) { // 앞면 시계, 뒷면 반시계
			for (h = 0; h < 3; ++h) {
				for (x = 0; x < 3; ++x) {
					// top -> right -> bot -> left -> top
					temp = cuv[h][y][x].left;
					cuv[h][y][x].left = cuv[h][y][x].bot;
					cuv[h][y][x].bot = cuv[h][y][x].right;
					cuv[h][y][x].right = cuv[h][y][x].top;
					cuv[h][y][x].top = temp;

					new_cuve[x][y][2 - h] = cuv[h][y][x];
				}
			}
		}
		else { // 앞면 반시계, 뒷면 시계
			for (h = 0; h < 3; ++h) {
				for (x = 0; x < 3; ++x) {
					// top -> left -> bot -> right -> top
					temp = cuv[h][y][x].right;
					cuv[h][y][x].right = cuv[h][y][x].bot;
					cuv[h][y][x].bot = cuv[h][y][x].left;
					cuv[h][y][x].left = cuv[h][y][x].top;
					cuv[h][y][x].top = temp;

					new_cuve[2 - x][y][h] = cuv[h][y][x];
				}
			}
		}
	}
	else if (side == 'L' || side == 'R') { // 왼쪽 또는 오른쪽 (x고정, hy가변) 
		x = (side == 'L' ? 0 : 2); // x 고정 (왼쪽: 0, 오른쪽: 2)
		if ((direction == '+' && side == 'R') ||
			(direction == '-' && side == 'L')) { 
			// 오른쪽 시계, 왼쪽 반시계
			for (h = 0; h < 3; ++h) {
				for (y = 0; y < 3; ++y) {
					// top -> back -> bot -> front -> top
					temp = cuv[h][y][x].front;
					cuv[h][y][x].front = cuv[h][y][x].bot;
					cuv[h][y][x].bot = cuv[h][y][x].back;
					cuv[h][y][x].back = cuv[h][y][x].top;
					cuv[h][y][x].top = temp;

					new_cuve[2 - y][h][x] = cuv[h][y][x];
				}
			}
		}
		else { // 오른쪽 반시계, 왼쪽 시계
			for (h = 0; h < 3; ++h) {
				for (y = 0; y < 3; ++y) {
					// top -> front -> bot -> back -> top
					temp = cuv[h][y][x].back;
					cuv[h][y][x].back = cuv[h][y][x].bot;
					cuv[h][y][x].bot = cuv[h][y][x].front;
					cuv[h][y][x].front = cuv[h][y][x].top;
					cuv[h][y][x].top = temp;

					new_cuve[y][2 - h][x] = cuv[h][y][x];
				}
			}
		}
	}
	copy_cuve(new_cuve, cuv); // new -> cuv로 copy
}

void print_cuve() {
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			cout << cuv[0][y][x].top;
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int T, N;
	char side, direction;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		init_cuve();
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> side >> direction;
			rotate(side, direction);
		}
		print_cuve();
	}
	return 0;
}