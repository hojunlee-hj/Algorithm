/*******************************************************************
19583 싸이버개강총회
2023/04/14 이호준
# 아이디어
1. HashMap
2. 문자열
*******************************************************************/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int getTime(string timeInfo){
    int delimiter = timeInfo.find(':');
    int hour = stoi(timeInfo.substr(0, 2));
    int minute = stoi(timeInfo.substr(delimiter + 1, 2));
    return hour * 60 + minute;
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string start, end, streamingEnd;

    cin >> start >> end >> streamingEnd;

    int start_time = getTime(start), end_time = getTime(end), streamingEnd_time = getTime(streamingEnd);

    string input_time, name;
    int answer = 0;

    unordered_map<string,bool> members;

    while(cin >> input_time >> name){
        int current_time = getTime(input_time);

        if(current_time <= start_time){
            members.insert({name, true}); 
        }else if(current_time >= end_time && current_time <= streamingEnd_time){
            if(members.find(name) != members.end()){
                if(members[name] == true){
                    members[name] = false;
                    answer++;
                }
            }
        }
    }

    cout <<answer;
    return 0;
}