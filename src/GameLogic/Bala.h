//
// Created by yoelr on 17/5/2026.
//

#ifndef TANQUITOS_BALA_H
#define TANQUITOS_BALA_H
#include "../data_estructures/Grafo.h"

class Bala {
private:
    float x;
    float y;
    float dirX;
    float diry;
    int damage;
    int owner;
    int* route;
    int routLength;
    int pasoActual;
    int MAXREBOTES;
    int rebotesActuales;
    void CalcularTrayectoria(int origenId, int destinoId, Grafo& grafo);

public:
    Bala(int OrigenId, int DestinoId, int owner, Grafo& grafo, bool Astar);
    ~Bala();
    void AvanzarUnPaso();
    int GetPosicionActualId();
    bool BalaTermino();
};


#endif //TANQUITOS_BALA_H