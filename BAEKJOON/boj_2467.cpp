#include <iostream>
#include <vector>

#define INF 2100000000

using namespace std;

int abs(int x){
    if(x >= 0) return x;
    else return -x;
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    int answer = INF;

    cin >> n;

    vector<int> solution(n, 0);

    for(int i = 0; i< n; i++){
        cin >> solution[i];
    }

    int left = 0;
    int right = n - 1;

    vector<int> answers;

    while(left < right){
        int current = solution[left] + solution[right];

        if(abs(current) < answer){
            answer = abs(current);
            answers.clear();
            answers.push_back(solution[left]);
            answers.push_back(solution[right]);
            if(answer == 0)
                break;
        }
        if(current < 0){
            left++;
        }else{
            right--;
        }
    }

    cout << answers[0] << " " << answers[1];

    return 0;
}