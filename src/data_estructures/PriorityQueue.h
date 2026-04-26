//
// Created by danie on 4/25/2026.
//

#ifndef TANQUITOS_PRIORITYQUEUE_H
#define TANQUITOS_PRIORITYQUEUE_H


class PriorityQueue {
public:
    void Insert(int* element);
    int* Dequeue();
    PriorityQueue();
    ~PriorityQueue();
private:
    int** arr;
    void Resize();
    int count;
    int size;
    void Swap(int indexA, int indexB);
};


#endif //TANQUITOS_PRIORITYQUEUE_H
