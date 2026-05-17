//
// Created by yoelr on 13/5/2026.
//

#include "MovimientoAleatorio.h"
#include <cstdlib>
#include <cmath>


int *MovimientoAleatorio(int startId, Grafo &grafo, int &size) {
    int columnas = grafo.ObtenerColumnas();
    int filas = grafo.ObtenerFilas();
    int startX;
    int startY;
    IdACoordenadas(startId,columnas,startX,startY);

    for (int i=0;i<MAX_INTENTOS;i++) {
        int dx = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
        int dy = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
        int nuevaX = startX + dx;
        int nuevaY = startY + dy;


        if (nuevaX < 0 || nuevaX >= columnas || nuevaY < 0 || nuevaY >= filas) {
            continue;  // fuera del mapa, intentar de nuevo
        }
        int nuevoId = CoordenadasAId(nuevaX, nuevaY, columnas);
        if (grafo.EsNodoPared(nuevoId)) {
            continue;  // es pared, intentar de nuevo
        }

        if (HayLineaVista(startId, nuevoId, grafo)) {
            // Éxito: mover a esta posición
            int* ruta = new int[2];
            ruta[0] = startId;
            ruta[1] = nuevoId;
            size = 2;
            return ruta;
        }
    }
    int* ruta = new int[1];
    ruta[0] = startId;
    size = 1;
    return ruta;
}


