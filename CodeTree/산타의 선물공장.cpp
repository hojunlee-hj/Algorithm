/*******************************************************************
산타의 선물공장 (22년 하반기 오후 2번)
2023/04/08 이호준
# 아이디어
1. Linked List
*******************************************************************/

#include <iostream>
#include <unordered_map>

using namespace std;

struct Box{
    int id;
    int weight;
    int belt;
    Box* prev;
    Box* next;

    Box(){
        id = -1, weight = -1, belt = -1;
        prev = NULL, next = NULL;
    }
};

struct Belt{
    bool is_broken;
    Box* head;
    Box* tail;

    Belt(){
        is_broken = false;
        head = new Box();
        tail = new Box();
        head->next = tail, tail->prev = head;
        head->prev = NULL, tail->next = NULL;
    }
};

int q, cmd, n, m;
Box box[100000];
Belt belt[10];
unordered_map<int, Box*> box_map;

bool empty(int belt_num){
    return (belt[belt_num].head->next == belt[belt_num].tail);
}

void push_back(int belt_num, Box* item){
    box_map[item->id] = item;
    Box* prev = belt[belt_num].tail->prev;
    Box* next = belt[belt_num].tail;

    item->next = next;
    item->prev = prev;
    prev->next = item;
    next->prev = item;
}

void pop_front(int belt_num){
    if(empty(belt_num))
        return;
    
    Box* item = belt[belt_num].head->next;
    box_map.erase(item->id);
    Box* prev = belt[belt_num].head;
    Box* next = belt[belt_num].head->next->next;

    prev->next = next;
    next->prev = prev;

    item->next = NULL;
    item->prev = NULL;
}

void cmd_100(){
    cin >> n >> m;
    int id[100000], w[100000];
    for(int i = 0; i < n; ++i){
        cin >> id[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> w[i];
    }
    int pos = 0;
    for(int belt_num = 0; belt_num < m; ++belt_num){
        for(int i = 0; i < n / m; ++i){
            box[pos].id = id[pos];
            box[pos].weight = w[pos];
            box[pos].belt = belt_num;
            push_back(belt_num, &box[pos]);
            ++pos;
        }
    }
}

int cmd_200(){
    int remove_weight = 0;
    int target_weight;
    cin >> target_weight;

    for(int i = 0; i < m; ++i){
        if(empty(i) || belt[i].is_broken)
            continue;
        
        Box* front = belt[i].head->next;
        if(front->weight <= target_weight){
            remove_weight += front->weight;
            pop_front(i);
        }else{
            pop_front(i);
            push_back(i, front);
        }
    }
    return remove_weight;
}

int cmd_300(){
    int id;
    cin >> id;
    if(box_map.find(id) == box_map.end())
        return -1;
    
    Box* item = box_map[id];
    Box* prev = item->prev;
    Box* next = item->next;

    prev->next = next;
    next->prev = prev;

    item->prev = NULL;
    item->next = NULL;
    box_map.erase(id);
    return id;
}

int cmd_400(){
    int id;
    cin >> id;

    if(box_map.find(id) == box_map.end())
        return -1;

    Box* item = box_map[id];
    Box* prev = item->prev;
    Box* begin = belt[item->belt].head->next;
    Box* end = belt[item->belt].tail->prev;

    if(item != begin){
        item->prev = belt[item->belt].head;
        belt[item->belt].head->next = item;

        begin->prev = end;
        end->next = begin;

        prev->next = belt[item->belt].tail;
        belt[item->belt].tail->prev = prev;
    }

    return item->belt + 1;
    
}

int cmd_500(){
    int belt_num;
    cin >> belt_num;

    if(belt[--belt_num].is_broken)
        return -1;

    belt[belt_num].is_broken = true;

    if(!empty(belt_num)){
        int target_belt = (belt_num + 1) % m;
        while(belt[target_belt].is_broken){
            target_belt = (target_belt + 1) % m;
        }

        Box* prev = belt[target_belt].tail->prev;
        Box* begin = belt[belt_num].head->next;
        Box* end = belt[belt_num].tail->prev;

        for(auto it = begin; it != belt[belt_num].tail; it = it->next){
            it->belt = target_belt;
        }

        prev->next = begin;
        begin->prev = prev;

        end->next = belt[target_belt].tail;
        belt[target_belt].tail->prev = end;

        belt[belt_num].head->next = belt[belt_num].tail;
        belt[belt_num].tail->prev = belt[belt_num].head;
    }

    return belt_num + 1;
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
        }
    }

    return 0;
}