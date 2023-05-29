#include <iostream>
#include <string>
#include <unordered_map>

#define MINUTE 60

using namespace std;

int calTimeInt(string timeInfo){
    int index = timeInfo.find(':');
    return stoi(timeInfo.substr(0, index)) * MINUTE + stoi(timeInfo.substr(index + 1));
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string start, end, last;
    cin >> start >> end >> last;

    int startTime = calTimeInt(start);
    int endTime = calTimeInt(end);
    int lastEndTime = calTimeInt(last);
    
    string input, user;
    unordered_map<string, bool> userBook;

    int answer = 0;
    while(cin >> input >> user){
        int inputTime = calTimeInt(input);
        if(inputTime <= startTime){
            userBook.insert({user, true});
        }else if(inputTime >= endTime && inputTime <= lastEndTime){
            if(userBook.find(user) != userBook.end()){
                answer++;
                userBook.erase(user);
            }
        }
    }

    cout << answer;

    return 0;
}