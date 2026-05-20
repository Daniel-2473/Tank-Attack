//
// Created by yoelr on 25/4/2026.






#ifndef TANQUITOS_GRAFO_H
#define TANQUITOS_GRAFO_H

#include "Nodo.h"
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
    void HacerPared(int id);
    void QuitarPared(int id);
    bool EsVecino(int id, int j);
    int ObtenerFilas();
    int ObtenerColumnas();
    int CalculateHeuristic(int currentId, int endId);
    int RandomPos();

};


#endif //TANQUITOS_GRAFO_H