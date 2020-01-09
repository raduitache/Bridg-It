#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

struct obj{
    int val;
    obj *next, *prev;
    obj(int v, obj *n, obj * p){
        val = v;
        next = n;
        prev = p;
    }
};

struct stack{
    int size = 0;
    obj* top = nullptr;
};

struct queue{
    int size = 0;
    obj *front = nullptr, *back = nullptr;
};

void push(stack &s, int v);

void push(queue &q, int v);

void pop(stack &s);

void pop(queue &q);

#endif // DATASTRUCTURES_H
