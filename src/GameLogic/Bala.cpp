//
// Created by yoelr on 17/5/2026.
//
#include <cmath>
#include "../algorithms/LineaVista.h"
#include "Bala.h"

#include <iostream>

Bala::Bala(int OrigenId, int DestinoId, int owner, Grafo &grafo) {
    this-> owner = owner;
    this-> MAXREBOTES=1;
    this-> rebotesActuales=0;
    this->route= nullptr;
    this->routLength=0;
    this->pasoActual=0;
    CalcularTrayectoria(OrigenId,DestinoId,grafo);
}

Bala::~Bala() {
    if (this->route) {
        delete[] this->route;
    }
}

void Bala::CalcularTrayectoria(int origenId, int destinoId, Grafo &grafo) {
    int columnas= grafo.ObtenerColumnas();
    int filas   = grafo.ObtenerFilas();
    int x1,y1,x2,y2;
    IdACoordenadas(origenId,columnas,x1,y1);
    IdACoordenadas(destinoId,columnas,x2,y2);
    //vector
    float dx = x2 - x1;
    float dy = y2 - y1;
    if (dx==0 &&dy==0) {
        return;
    }

    float distancia = sqrt(dx * dx + dy * dy);
    float dirX = dx / distancia;
    float dirY = dy / distancia;

    int factorFantasma = filas + columnas;
    int xFantasma = x1 + round(dirX *  factorFantasma);
    int yFantasma = y1 + round(dirY * factorFantasma);


    int sizeLinea1;
    Punto* puntosLinea1= ObtenerLinea(x1,y1,xFantasma,yFantasma,sizeLinea1);

    int puntosTramo1=0;
    bool huboChoque = false;
    int xReboteOrigen = x1;
    int yReboteOrigen = y1;
    for (int i=0;i<sizeLinea1;i++) {
        int currentX= puntosLinea1[i].x;
        int currentY= puntosLinea1[i].y;
        if (currentX<0||currentX>=columnas||currentY<0||currentY>=filas) {
            break;
        }
        puntosTramo1++;

        int NodoActual= CoordenadasAId(currentX,currentY,columnas);
        if (grafo.EsNodoPared((NodoActual))) {
            if (i>0){
                huboChoque=true;
                this->rebotesActuales=1;

                xReboteOrigen = puntosLinea1[i-1].x;
                yReboteOrigen = puntosLinea1[i-1].y;
                if (puntosLinea1[i].x!=puntosLinea1[i-1].x&&puntosLinea1[i].y==puntosLinea1[i-1].y) {
                    dirX= -dirX;
                }
                else if (puntosLinea1[i].x==puntosLinea1[i-1].x&&puntosLinea1[i].y!=puntosLinea1[i-1].y) {
                    dirY= -dirY;
                }
                else {
                    dirX = -dirX;
                    dirY = -dirY;
                }
            }
            break;
        }

    }
    Punto* puntosLinea2 = nullptr;
    int puntosTramo2=0;
    if (huboChoque) {
        int xFantasma2 = xReboteOrigen + round(dirX * factorFantasma);
        int yFantasma2 = yReboteOrigen + round(dirY * factorFantasma);

        int sizeLinea2;
        puntosLinea2 = ObtenerLinea(xReboteOrigen, yReboteOrigen, xFantasma2, yFantasma2, sizeLinea2);

        for (int i = 0; i < sizeLinea2; i++) {
            int currentX = puntosLinea2[i].x;
            int currentY = puntosLinea2[i].y;

            if (currentX < 0 || currentX >= columnas || currentY < 0 || currentY >= filas) {
                break;
            }

            puntosTramo2++;

            int NodoActual = CoordenadasAId(currentX, currentY, columnas);
            if (grafo.EsNodoPared(NodoActual)) {
                break;
            }
        }
    }
    this->routLength = puntosTramo1 + puntosTramo2;
    this->route = new int[this->routLength];

    int indice =0;
    for (int i = 0; i < puntosTramo1; i++) {
        this->route[indice++] = CoordenadasAId(puntosLinea1[i].x, puntosLinea1[i].y, columnas);
    }
    for (int i = 0; i < puntosTramo2; i++) {
        this->route[indice++] = CoordenadasAId(puntosLinea2[i].x, puntosLinea2[i].y, columnas);
    }
    delete[] puntosLinea1;
    if (puntosLinea2 != nullptr) {
        delete[] puntosLinea2;
    }

}


void Bala::AvanzarUnPaso() {
    if (this->route != nullptr && this->pasoActual < this->routLength - 1) {
        this->pasoActual++;
    }
}


int Bala::GetPosicionActualId() {
    if (this->route!=nullptr&&this->pasoActual<routLength) {
        return this->route[this->pasoActual];
    }
    return -1;
}


bool Bala::BalaTermino() {
    if (this->pasoActual>=(this->routLength)-1) {
        return true;
    }
    else return false;
}
