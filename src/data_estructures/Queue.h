//
// Created by danie on 4/24/2026.
//

#ifndef TANQUITOS_QUEUE_H
#define TANQUITOS_QUEUE_H


class Queue {
public:

    void Insert(int element);
    Queue();
    int Dequeue();
    bool IsEmpty();
    ~Queue();

private:
    int* arr;
    int front;
    int rear;
    int used;
    int size;
    void Resize();

};


#endif //TANQUITOS_QUEUE_H
