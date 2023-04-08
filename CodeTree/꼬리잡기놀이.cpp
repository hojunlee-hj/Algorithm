/*******************************************************************
꼬리잡기놀이 (21년 하반기 오전 1번)
2023/04/08 이호준
# 아이디어
1. Simulation
*******************************************************************/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int dx[4] = {0, 1, 0 ,-1};
int dy[4] = {1, 0, -1, 0};

int round_x[4] = {0, -1, 0, 1};
int roudn_y[4] = {1, 0, -1, 0};

struct Team{
    int size;
    bool direction;
    deque<pair<int,int>> members;
};

bool visited[21][21];

int teamMap[21][21];
vector<Team> teams;

void clearVisited(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            visited[i][j] = false;
    }
}

bool inRange(int x, int y, int n){
    return x < n && x >= 0 && y < n && y >= 0;
}

void makeTeam(int x, int y, vector<vector<int>> map, deque<pair<int,int>>& dq, int size, bool memberFinish, int step){
    for(int dir = 0; dir < 4; dir++){
        int next_x = x + dx[dir];
        int next_y = y + dy[dir];

        if(inRange(next_x, next_y, map.size()) && !visited[next_x][next_y]){
            visited[next_x][next_y] = true;
            if(step != 0 && map[next_x][next_y] == 3){
                dq.push_back({next_x, next_y});
                teamMap[next_x][next_y] = size + 4;
                memberFinish = true;
                makeTeam(next_x, next_y, map, dq, size, memberFinish, step + 1);
            }else if(map[next_x][next_y] == 2){
                dq.push_back({next_x, next_y});
                makeTeam(next_x, next_y, map, dq, size, memberFinish, step + 1);
                teamMap[next_x][next_y] = size + 4;
                visited[next_x][next_y] = true;
            }else if (memberFinish){
                if(map[next_x][next_y] == 4){
                    makeTeam(next_x, next_y, map, dq, size, memberFinish, step + 1);
                    teamMap[next_x][next_y] = size + 4;
                }else if(map[next_x][next_y] == 1){
                    return;
                }
            }else{
                if(step == 0 || map[next_x][next_y] == 4)
                    visited[next_x][next_y] = false;
            }
            
        }
    }
}

void visualizeMap(vector<vector<int>> map){
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map.size(); j++){
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout <<"\n\n";
}

void visualizeTeamMap(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << teamMap[i][j] << " ";
        }
        cout << "\n";
    }
    cout <<"\n\n";
}

int main() {
    // 여기에 코드를 작성해주세요.

    int n, m, k;

    cin >> n >> m >> k;

    vector<vector<int>> map(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> map[i][j];
        }
    }

    int answer = 0;

    // makeTeams
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(map[i][j] == 1){
                visited[i][j] = true;
                deque<pair<int,int>> teamMembers;
                teamMembers.push_back({i, j});
                bool finish = false;
                makeTeam(i, j, map, teamMembers, teams.size(), finish, 0);
                teamMap[i][j] = teams.size() + 4;
                teams.push_back(Team{(int)teamMembers.size(), true, teamMembers});
                clearVisited(n);
            }
        }
    }

    // for(auto team : teams){
    //     cout << team.size << " ";
    //     for(auto a : team.members)
    //         cout << "(" << a.first << " " << a.second << ") ";
    //     cout << "\n";
    // }
    //visualizeMap(map);
    //visualizeTeamMap(n);
    for(int round = 0; round < k; round++){
        // team move
        for(int t = 0; t < teams.size(); t++){
            if(teams[t].direction){
                pair<int,int> head = teams[t].members.front();
                pair<int,int> back = teams[t].members.back();
                map[head.first][head.second] = 2;
                map[back.first][back.second] = 4;                
                teams[t].members.pop_back();
                map[teams[t].members.back().first][teams[t].members.back().second] = 3;                

                for(int dir = 0; dir < 4; dir++){
                    int next_x = head.first + dx[dir];
                    int next_y = head.second + dy[dir];

                    if(inRange(next_x, next_y, n) && (map[next_x][next_y] == 4)){
                        map[next_x][next_y] = 1;
                        teams[t].members.push_front({next_x, next_y});
                        break;
                    }
                }
            }else{
                pair<int,int> head = teams[t].members.back();
                pair<int,int> back = teams[t].members.front();
                map[head.first][head.second] = 2;
                map[back.first][back.second] = 4;  
                teams[t].members.pop_front();
                map[teams[t].members.front().first][teams[t].members.front().second] = 3;                              

                for(int dir = 0; dir < 4; dir++){
                    int next_x = head.first + dx[dir];
                    int next_y = head.second + dy[dir];

                    if(inRange(next_x, next_y, n) && (map[next_x][next_y] == 4)){
                        map[next_x][next_y] = 1;
                        teams[t].members.push_back({next_x, next_y});
                        break;
                    }
                }
            }
        }
        //visualizeMap(map);
        // round shoot
        int round_direction = (round / n) % 4;
        int round_step = round % n;

        // 맞으면 몇번째 그룹인지 어떻게 알지? -> group
        int start_x, start_y;
        bool find = false;
        if(round_direction == 0){
            start_x = round_step;
            start_y = 0;
        }else if (round_direction == 1){
            start_x = n - 1;
            start_y = round_step;
        }else if (round_direction == 2){
            start_x = n - 1 - round_step;
            start_y = n - 1;
        }else{
            start_x = 0;
            start_y = n - 1 - round_step;
        }
        int next_x, next_y;
        //cout << round << " " << round_direction << " " << round_step  << ": " <<next_x << " " << next_y << "\n";
        for(int check = 0; check < n; check++){
            
            next_x = start_x + round_x[round_direction] * check;
            next_y = start_y + roudn_y[round_direction] * check;

            if(map[next_x][next_y] != 0 && map[next_x][next_y] != 4){
                int team_index = teamMap[next_x][next_y];

                Team checkTeam = teams[team_index - 4];
                if(checkTeam.direction){
                    for(int i = 0; i < checkTeam.members.size(); i++){
                        //cout << checkTeam.members[i].first << " " << checkTeam.members[i].second <<"\n";
                        if(checkTeam.members[i].first == next_x && checkTeam.members[i].second == next_y){
                            answer += ((i + 1) * (i + 1));
                            find = true;
                            teams[team_index - 4].direction = !teams[team_index - 4].direction;
                            map[teams[team_index - 4].members.front().first][teams[team_index - 4].members.front().second] = 3;
                            map[teams[team_index - 4].members.back().first][teams[team_index - 4].members.back().second] = 1;
                            break;
                        }
                    }
                }else{
                    for(int i = checkTeam.members.size() - 1; i >= 0; i--){
                        if(checkTeam.members[i].first == next_x && checkTeam.members[i].second == next_y){
                            answer += ((checkTeam.members.size() - i) * (checkTeam.members.size() - i));
                            find = true;
                            teams[team_index - 4].direction = !teams[team_index - 4].direction;
                            map[teams[team_index - 4].members.back().first][teams[team_index - 4].members.back().second] = 3;
                            map[teams[team_index - 4].members.front().first][teams[team_index - 4].members.front().second] = 1;
                            break;
                        }
                    }
                }
                if(find)
                    break;
            } 
        }
        //visualizeMap(map);
    }

    cout << answer;

    return 0;
}