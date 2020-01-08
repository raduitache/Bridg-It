#include "dataStructures.hpp"

void push(stack &s, int v){
    if(s.size == 0){
        obj *toPush = new obj(v, nullptr, nullptr);
        s.top = toPush;
        s.size++;
        return;
    }
    obj *toPush = new obj(v, nullptr, s.top);
    s.top->next = toPush;
    s.top = toPush;
    s.size++;
}

void push(queue &q, int v){
    if(q.size == 0){
        obj *toPush = new obj(v, nullptr, nullptr);
        q.front = q.back = toPush;
        q.size++;
        return;
    }
    obj *toPush = new obj(v, nullptr, q.back);
    q.back->next = toPush;
    q.back = toPush;
    q.size++;
}

void pop(stack &s){
    if(s.size == 0) return;
    if(s.size == 1){
        delete s.top;
        s.top = nullptr;
        s.size = 0;
        return;
    }
    s.top = s.top->prev;
    delete s.top->next;
    s.size--;
}

void pop(queue &q){
    if(q.size == 0) return;
    if(q.size == 1){
        delete q.back;
        q.back = q.front = nullptr;
        q.size = 0;
        return;
    }
    q.front = q.front->next;
    delete q.front->prev;
    q.size--;
}
