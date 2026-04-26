//
// Created by danie on 4/25/2026.
//

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
    this->arr = new int*[10];
    this->count = -1;
    this->size = 10;
}

void PriorityQueue::Insert(int* element) {
    if (count == size-1) {
        Resize();
    }
    count++;
    arr[count] = element;
    int index = count;
    while (index > 0 && *arr[index] < *arr[(index-1)/2]) {
        Swap(index, (index-1)/2);
        index = (index-1)/2;
    }
}

int* PriorityQueue::Dequeue() {
    if (count == -1) {
        return nullptr;
    }
    int* element = arr[0];
    arr[0] = arr[count];
    arr[count] = nullptr;
    count--;
    int index = 0;
    while (true) {
        int left = 2*index+1;
        int right = 2*index+2;
        int smallest = index;

        if (left <= count && *arr[left] < *arr[smallest]) {
            smallest = left;
        }
        if (right <= count && *arr[right] < *arr[smallest]) {
            smallest = right;
        }
        if (smallest == index) break;

        Swap(index, smallest);
        index = smallest;
    }
    return element;
}

void PriorityQueue::Resize() {
    int** newArr = new int*[size*2];
    for (int i = 0; i<size; i++) {
        newArr[i] = arr[i];
    }
    size *= 2;
    delete[] arr;
    arr = newArr;
    newArr = nullptr;
}

void PriorityQueue::Swap(int indexA, int indexB) {
    int* temp = arr[indexA];
    arr[indexA] = arr[indexB];
    arr[indexB] = temp;
}

PriorityQueue::~PriorityQueue() {
    delete[] arr;
}
