//
// Created by yoelr on 25/4/2026.

#include <iostream> //la de siempre
using namespace std;

#include "Nodo.h"
#include <cstdlib>
#ifndef TANQUITOS_GRAFO_H
#define TANQUITOS_GRAFO_H


class Grafo {
private:
    int filas;
    int columnas;
    int** adyacenciaDeNodos;
    Nodo** MatrizDeNodos;


public:
    Grafo(int filas, int columnas);
    ~Grafo();

    void CreadorDeConecciones(int idA, int idB);
    int ObtenerCantidadNodos();
    bool EsNodoPared(int id);
    bool EsVecino(int id, int j);
    int CalculateHeuristic(int currentId, int endId);

};


#endif //TANQUITOS_GRAFO_H