//
// Created by yoelr on 25/4/2026.
//
#include <iostream> //la de siempre

using namespace std;
#ifndef TANQUITOS_NODO_H
#define TANQUITOS_NODO_H
// este es el header de la clase nodo, el cual define sus atributos y su constructor y destructor

class Nodo {
private:
    //identificador para cada nodo
    int id;
    //coordenadas x ^ y de cada nodo
    float x;
    float y;
    //para definir si es una pared o no
    bool Pared;

public:
    // constructor publico para poder crearlo fuera
    Nodo(int id, float x,float y);
    Nodo();
    // destructor
    ~Nodo();

    //geters de los nodos
    int getid();
    float getx();
    float gety();
    bool esPared();
    //creador de pared
    void HacerQuitarPared(bool estado);
};


#endif //TANQUITOS_NODO_H