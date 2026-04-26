//
// Created by danie on 4/24/2026.
//

#include "Queue.h"

Queue::Queue() {
    this->arr = new int*[10];
    this->front = 0;
    this->rear = 0;
    this->size = 10;
    this->used = 0;
    for (int i = 0; i<size; i++) {
        arr[i] = nullptr;
    }
}

void Queue::Insert(int* element) {
    if (used == 0) {
        arr[front] = element;
    }
    else if (rear == size-1) {
        if (arr[0] == nullptr) {
            arr[0] = element;
            rear = 0;
        }
        else {
            Resize();
            rear++;
            arr[rear] = element;
        }
    }
    else {
        rear++;
        arr[rear] = element;
    }
    used += 1;
}

int* Queue::Dequeue() {
    if (used == 0) {
        return nullptr;
    }
    int* element = arr[front];
    arr[front] = nullptr;
    if (rear == front) {
        rear = 0;
        front = 0;
    }
    else {
        if (front == size-1) {
            front = 0;
        }
        else {
            front++;
        }
    }
    used--;
    return element;
}

void Queue::Resize() {
    int** newArr = new int*[size*2];
    int count  = 0;
    if (rear >= front) {
        for (int i = front; i <= rear; i++) {
            newArr[count] = arr[i];
            count++;
        }
    } else {
        for (int i = front; i < size; i++) {
            newArr[count++] = arr[i];
            count++;
        }
        for (int i = 0; i <= rear; i++) {
            newArr[count] = arr[i];
            count++;
        }
    }
    size *= 2;
    front = 0;
    rear = count-1;
    delete[] arr;
    arr = newArr;
    newArr = nullptr;
}

bool Queue::isEmpty() {
    return used == 0;
}

Queue::~Queue() {
    delete[] arr;
}
