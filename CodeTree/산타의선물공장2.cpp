/*******************************************************************
산타의 선물공장2 (22년 하반기 오후 2번)
2023/04/08 이호준
# 아이디어
1. Linked List
*******************************************************************/

#include <iostream>
#include <unordered_map>

using namespace std;

struct Box{
    int belt;
    int id;
    Box* prev;
    Box* next;

    Box(){
        id = -1, belt = -1;
        prev = NULL, next = NULL;
    }
};

struct Belt{
    int count;
    Box* head;
    Box* tail;

    Belt(){
        count = 0;
        head = new Box();
        tail = new Box();
        head->next = tail, tail->prev = head;
        head->prev = NULL, tail->next = NULL;
    }
};

int q, cmd, n, m;
Box box[100001];
Belt belt[100001];
unordered_map<int, Box*> box_map;

bool empty(int belt_num){
    return belt[belt_num].count == 0;
}

void push_back(int belt_num, Box* item){
    box_map[item->id] = item;
    Box* prev = belt[belt_num].tail->prev;
    Box* next = belt[belt_num].tail;

    item->next = next;
    item->prev = prev;
    prev->next = item;
    next->prev = item;

    ++belt[belt_num].count;
}

void move(int dst, int src, Box* from, Box* to, int count){
    Box* fprev = from->prev;
    Box* tnext = to->next;

    Box* prev = belt[dst].head;
    Box* next = belt[dst].head->next;

    fprev->next = tnext;
    tnext->prev = fprev;

    from->prev = prev;
    to->next = next;
    
    prev->next = from;
    next->prev = to;

    belt[src].count -= count;
    belt[dst].count += count;
}

void move(int dst, int src, int count){
    Box* from = belt[src].head->next;
    Box* to = from;
    for(int i = 1; i < count; ++i){
        to = to->next;
    }

    move(dst, src, from, to, count);
}


void cmd_100(){
    cin >> n >> m;

    int belt_num;
    for(int i = 0; i < m; i++){
        cin >> belt_num;
        --belt_num;

        box[i].id = i;
        box[i].belt = belt_num;
        push_back(belt_num, &box[i]);
    }
}

int cmd_200(){
    int src, dst;

    cin >> src >> dst;
    src--;
    dst--;
    int count = belt[src].count;
    if(count > 0){
        Box* from = belt[src].head->next;
        Box* to = belt[src].tail->prev;

        move(dst, src, from, to, count);
    }

    return belt[dst].count;
}

int cmd_300(){
    int src, dst;

    cin >> src >> dst;
    src--;
    dst--;

    if(empty(src) && empty(dst))
        return 0;
    else if (empty(src)){
        move(src, dst, 1);
    }else if (empty(dst)){
        move(dst, src, 1);
    }else{
        move(dst, src, 1);
        move(src, dst, 2);
        move(dst, src, 1);
    }

    return belt[dst].count;
}

int cmd_400(){
    int src, dst;

    cin >> src >> dst;
    src--;
    dst--;

    int count = belt[src].count / 2;

    if(count > 0){
        move(dst, src, count);
    }

    return belt[dst].count;
}

int cmd_500(){
    int id;

    cin >> id;
    id--;

    Box* item = box_map[id];
    Box* prev = item->prev;
    Box* next = item->next;

    int a = (prev->belt == -1) ? (-1) : (prev->id + 1);
    int b = (next->belt == -1) ? (-1) : (next->id + 1);

    return (a + (b * 2));
}

int cmd_600(){
    int belt_num;
    cin >> belt_num;
    --belt_num;

    Box* begin = belt[belt_num].head->next;
    Box* end = belt[belt_num].tail->prev;

    int a = (begin->belt == -1) ? (-1) : (begin->id + 1);
    int b = (end->belt == -1) ? (-1) : (end->id + 1);
    int c = belt[belt_num].count;

    return (a + (b * 2) + (c * 3));
}

int main(void){

    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> q;

    while(q--){
        cin >> cmd;
        switch(cmd){
            case 100:
                cmd_100();
                break;
            case 200:
                cout << cmd_200() << "\n";
                break;
            case 300:
                cout << cmd_300() << "\n";
                break;
            case 400:
                cout << cmd_400() << "\n";
                break;
            case 500:
                cout << cmd_500() << "\n";
                break;
            case 600:
                cout << cmd_600() << "\n";
                break;
        }
    }

    return 0;
}