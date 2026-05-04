//
// Created by danie on 4/25/2026.
//

#ifndef TANQUITOS_PRIORITYQUEUE_H
#define TANQUITOS_PRIORITYQUEUE_H
#include "Nodo.h"

struct NodeCosts {//Struct de utilidad para Djisktra y A*
    Nodo* node;
    int weight;
    float heuristic;
    float total;
};

class PriorityQueue {
public:
    void Insert(NodeCosts element);
    NodeCosts Dequeue();
    PriorityQueue();
    ~PriorityQueue();
    bool IsEmpty();

private:
    NodeCosts* arr;
    void Resize();
    int count;
    int size;
    void Swap(int indexA, int indexB);
};


#endif //TANQUITOS_PRIORITYQUEUE_H
