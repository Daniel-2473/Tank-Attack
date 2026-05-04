//
// Created by danie on 4/24/2026.
//

#include "Queue.h"
#include <stdexcept>

Queue::Queue() {
    this->arr = new int[10];
    this->front = 0;
    this->rear = 0;
    this->size = 10;
    this->used = 0;
}

void Queue::Insert(int element) {
    if (used == size) { //Caso en el que array este lleno lo expandimos
        Resize();
    }
    if (used == 0) {
        arr[rear] = element;
    } else {
        rear = (rear + 1) % size; //Ir al siguiente elemento. La cola es circular, por lo que se calcula de esta manera
        arr[rear] = element;
    }
    used++;
}

int Queue::Dequeue() {
    if (IsEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    int element = arr[front];
    front = (front + 1) % size; //Movemos la "cabeza" de la cola una posicion y deja el anterior libre
    used--;
    if (used == 0) { //Caso en que queden vacia
        front = 0;
        rear = 0;
    }
    return element;
}

void Queue::Resize() { //Expande el array manteniendo el orden aunque sea circular, termina siendo un array normal
    int* newArr = new int[size*2];
    int count  = 0;
    if (rear >= front) { //Caso en el que no sea circular hasta el momento
        for (int i = front; i <= rear; i++) {
            newArr[count] = arr[i];
            count++;
        }
    } else { //Si hay circularidad
        for (int i = front; i < size; i++) { //Copiamos primero del front hasta el final del array
            newArr[count] = arr[i];
            count++;
        }
        for (int i = 0; i <= rear; i++) { //Seguimos copiando pero desde el inicio hasta el rear y respetando los elementos que ya hemos insertado en el nuevo array
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

bool Queue::IsEmpty() {
    return used == 0;
}

Queue::~Queue() {
    delete[] arr;
}