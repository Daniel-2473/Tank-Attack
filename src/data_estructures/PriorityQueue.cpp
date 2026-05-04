//
// Created by danie on 4/25/2026.
//

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() { //Cola de prioridad basada en min-heap
    this->arr = new NodeCosts[10];
    this->count = -1;
    this->size = 10;
}

void PriorityQueue::Insert(NodeCosts element) {
    if (count == size-1) { //Si el array esta lleno expandimos
        Resize();
    }
    count++;
    arr[count] = element;
    int index = count;
    while (index > 0 && arr[index].total < arr[(index-1)/2].total) { //Funcion de insercion del min-heap
        Swap(index, (index-1)/2);
        index = (index-1)/2;
    }
}

NodeCosts PriorityQueue::Dequeue() {
    NodeCosts element = arr[0]; //Tomamos el primer elemento, ya que min-heap lo garantiza
    arr[0] = arr[count];
    count--;
    int index = 0;
    while (true) { //Funcion de elimincacion de la raiz en min-heap
        int left = 2*index+1;
        int right = 2*index+2;
        int smallest = index;

        if (left <= count && arr[left].total < arr[smallest].total) {
            smallest = left;
        }
        if (right <= count && arr[right].total < arr[smallest].total) {
            smallest = right;
        }
        if (smallest == index) break;

        Swap(index, smallest);
        index = smallest;
    }
    return element;
}

void PriorityQueue::Resize() { //Expandir el array simplementa copiando valores a otro array del doble de tamano
    NodeCosts* newArr = new NodeCosts[size*2];
    for (int i = 0; i<size; i++) {
        newArr[i] = arr[i];
    }
    size *= 2;
    delete[] arr;
    arr = newArr;
    newArr = nullptr;
}

void PriorityQueue::Swap(int indexA, int indexB) {
    NodeCosts temp = arr[indexA];
    arr[indexA] = arr[indexB];
    arr[indexB] = temp;
}

PriorityQueue::~PriorityQueue() {
    delete[] arr;
}

bool PriorityQueue::IsEmpty() {
    return count == -1;
}
