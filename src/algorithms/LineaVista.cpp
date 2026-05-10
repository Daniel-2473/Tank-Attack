//
// Created by yoelr on 10/5/2026.
//
#include <cmath>
#include "LineaVista.h"
#include <iostream>
using namespace std;
// Convierte cordenadas x,y en un id
int CoordenadasAId(int x, int y, int columnas) {
    return y*columnas+x;//formula de siempre
}

//convierte un id en coordenadas
void IdACoordenadas(int id, int columnas, int& x, int& y) {
    x = id % columnas;      // columna
    y = id / columnas;      // fila
}


Punto* ObtenerLinea(int x1, int y1, int x2, int y2, int& size) {
    // Calcular diferencias
    int dx = x2 - x1;
    int dy = y2 - y1;
    //ejemplo (0,0) (5,3) -> dx=5 dy=3
    // Calcular valor absoluto de dx
    int absDx;
    if (dx < 0) {
        absDx = -dx; //simplemente si es negativo se vuelve positivo
    } else {
        absDx = dx;
    }

    // valor absoluto de dy
    int absDy;
    if (dy < 0) {
        absDy = -dy;
    } else {
        absDy = dy;
    }

    // Calcular cuántos pasos (el más grande entre absDx y absDy)
    int pasos;
    if (absDx > absDy) {
        pasos = absDx;
    } else {
        pasos = absDy;
    }

    // Crear arreglo de puntos
    Punto* puntos = new Punto[pasos + 1];
    size = 0;

    // Si pasos es 0 (mismo punto)
    if (pasos == 0) {
        puntos[size].x = x1;
        puntos[size].y = y1;
        size++;
        return puntos;
    }

    // Calcular incrementos
    float incX = (float)dx / pasos;// define cuanto avanzar en cada paso
    float incY = (float)dy / pasos;

    // Recorrer paso a paso
    float x = x1;
    float y = y1;
// esto calcula todos los puntos intermedios entre el inicio y el fin
    for (int i = 0; i <= pasos; i++) {
        puntos[size].x = round(x);// redondea al entero mas cercano siempre
        puntos[size].y = round(y);
        size++;

        x = x + incX;//los avances
        y = y + incY;
    }

    return puntos;
}

bool HayLineaVista(int idInicio, int idFin, Grafo& grafo) {
    if (idInicio == idFin) {
        return true;
    }

    int columnas = grafo.ObtenerColumnas();

    int x1, y1, x2, y2;
    IdACoordenadas(idInicio, columnas, x1, y1);
    IdACoordenadas(idFin, columnas, x2, y2);

    int size;
    Punto* puntos = ObtenerLinea(x1, y1, x2, y2, size);//calcula todos los puntos entre ambos nodos

    bool bloqueado = false;
//revisa cada punto y si encuentra una pared la linea esta bloqueada
    for (int i = 0; i < size; i++) {
        int id = CoordenadasAId(puntos[i].x, puntos[i].y, columnas);


        if (grafo.EsNodoPared(id)) {
            if (id != idInicio && id != idFin) {
                bloqueado = true;
                break;
            }
        }
    }

    delete[] puntos;

    if (bloqueado) {
        return false;
    } else {
        return true;
    }
}





