//
// Created by yoelr on 10/5/2026.
//

#ifndef TANQUITOS_LINEAVISTA_H
#define TANQUITOS_LINEAVISTA_H
#include "../data_estructures/Grafo.h"

struct Punto {
    int x;
    int y;
};


int CoordenadasAId(int x, int y, int columnas);
void IdACoordenadas(int id, int columnas, int& x, int& y);
Punto* ObtenerLinea(int x1, int y1, int x2, int y2, int& size);
bool HayLineaVista(int idInicio, int idFin, Grafo& grafo);


#endif //TANQUITOS_LINEAVISTA_H