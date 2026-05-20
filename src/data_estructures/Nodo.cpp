//
// Created by yoelr on 25/4/2026.
//
#include <iostream> //la de siempre

using namespace std;
#include "Nodo.h"

Nodo::Nodo(int id, float x, float y) {
    this-> id = id;
    this-> x  = x;
    this-> y  = y;
    this-> Pared = false;
}
Nodo::Nodo() {
    id = -1;
    x = 0;
    y = 0;
    Pared = false;
}

int Nodo::getid() {
    return id;
}

float Nodo::getx() {
    return x;
}

float Nodo::gety() {
    return y;
}

bool Nodo::esPared() {
    return Pared;
}

void Nodo::HacerQuitarPared(bool estado) {
    Pared = estado;
}

Nodo::~Nodo() {
    //vacio por el momento
}

