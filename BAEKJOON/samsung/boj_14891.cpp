/*******************************************************************
14891 톱니바퀴
2023/03/31 이호준
# 아이디어
1. deque
2. Simulation
*******************************************************************/

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <math.h>

#define CLOCKWISE 1
#define COUNTERCLOCKWISE -1

using namespace std;

void moveClockwise(deque<int>& dq){
    int temp = dq.back();
    dq.pop_back();
    dq.push_front(temp);
}

void moveCounterClockwise(deque<int>& dq){
    int temp = dq.front();
    dq.pop_front();
    dq.push_back(temp);
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    deque<int> dq[4];

    for(int i = 0; i < 4; i++){
        string temp;
        cin >> temp;
        for(int j = 0; j < 8; j++){
            dq[i].push_back(temp[j] - '0');
        }
    }

    int rotation;
    cin >> rotation;
    
    for(int i = 0; i < rotation; i++){
        int gear, direction;
        cin >> gear >> direction;

        if(gear == 1){
            if(dq[0][2] != dq[1][6]){
                if(dq[1][2] != dq[2][6]){

                    if(dq[2][2] != dq[3][6]){
                        if(direction == CLOCKWISE){
                            moveCounterClockwise(dq[3]);
                        }else{
                            moveClockwise(dq[3]);
                        }
                    }

                    if(direction == CLOCKWISE){
                        moveClockwise(dq[2]);
                    }else{
                        moveCounterClockwise(dq[2]);
                    }
                }

                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[1]);
                }else{
                    moveClockwise(dq[1]);
                }
            }
            if(direction == CLOCKWISE){
                moveClockwise(dq[0]);
            }else{
                moveCounterClockwise(dq[0]);
            }
        }else if (gear == 2){

            if(dq[0][2] != dq[1][6]){
                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[0]);
                }else{
                    moveClockwise(dq[0]);
                }
            }

            if(dq[1][2] != dq[2][6]){

                if(dq[2][2] != dq[3][6]){
                    if(direction == CLOCKWISE){
                        moveClockwise(dq[3]);
                    }else{
                        moveCounterClockwise(dq[3]);
                    }
                }

                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[2]);
                }else{
                    moveClockwise(dq[2]);
                }
            }
            if(direction == CLOCKWISE){
                moveClockwise(dq[1]);
            }else{
                moveCounterClockwise(dq[1]);
            }
        }else if (gear == 3){

            if(dq[2][2] != dq[3][6]){
                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[3]);
                }else{
                    moveClockwise(dq[3]);
                }
            }

            if(dq[2][6] != dq[1][2]){
                if(dq[0][2] != dq[1][6]){
                    if(direction == CLOCKWISE){
                        moveClockwise(dq[0]);
                    }else{
                        moveCounterClockwise(dq[0]);
                    }
                }

                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[1]);
                }else{
                    moveClockwise(dq[1]);
                }
            }

            if(direction == CLOCKWISE){
                moveClockwise(dq[2]);
            }else{
                moveCounterClockwise(dq[2]);
            }

        }else if (gear == 4){

            if(dq[3][6] != dq[2][2]){
                if(dq[2][6] != dq[1][2]){
                    if(dq[1][6] != dq[0][2]){
                        if(direction == CLOCKWISE){
                            moveCounterClockwise(dq[0]);
                        }else{
                            moveClockwise(dq[0]);
                        }
                    }
                    if(direction == CLOCKWISE){
                        moveClockwise(dq[1]);
                    }else{
                        moveCounterClockwise(dq[1]);
                    }
                }

                if(direction == CLOCKWISE){
                    moveCounterClockwise(dq[2]);
                }else{
                    moveClockwise(dq[2]);
                }
            }

            if(direction == CLOCKWISE){
                moveClockwise(dq[3]);
            }else{
                moveCounterClockwise(dq[3]);
            }
        }
    }

    int answer = 0;

    for(int i = 0; i < 4; i++){
        if(dq[i].front() == 1){
            answer += pow(2, i);
        }
    }

    cout << answer;

    return 0;
}