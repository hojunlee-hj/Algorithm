#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, w, l;
    cin >> n >> w >> l;
    
    queue<int> trucks;
    
    int weights;
    for(int i = 0; i < n; ++i){
        cin >> weights;
        trucks.push(weights);
    }
    
    // {outTime, weight}
    queue<pair<int,int>> bridges;
    int unitTime = 0;
    int currentWeight = 0;
    while(!trucks.empty()){
        unitTime++;

        if(!bridges.empty() && bridges.front().first == unitTime){
            currentWeight -= bridges.front().second;
            bridges.pop();
        }

        if(bridges.size() < w && currentWeight + trucks.front() <= l){
            currentWeight += trucks.front();
            bridges.push({unitTime + w, trucks.front()});
            trucks.pop();
        }
    }

    while(!bridges.empty()){
        unitTime = bridges.front().first;
        bridges.pop();
    }
    
    cout << unitTime;

    return 0;
}