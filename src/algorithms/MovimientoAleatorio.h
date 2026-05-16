//
// Created by yoelr on 13/5/2026.
//#include "../data_estructures/Grafo.h"
#include "../algorithms/LineaVista.h"
#include "../data_estructures/Queue.h"
#include "../data_estructures/Grafo.h"
#ifndef TANQUITOS_MOVIMIENTOALEATORIO_H
#define TANQUITOS_MOVIMIENTOALEATORIO_H

const int MAX_INTENTOS = 50;
const int RADIO_MOVIMIENTO = 3;

    int* MovimientoAleatorio(int startId, Grafo& grafo, int& size);



#endif //TANQUITOS_MOVIMIENTOALEATORIO_H