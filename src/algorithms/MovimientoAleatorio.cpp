//
// Created by yoelr on 13/5/2026.
//

#include "MovimientoAleatorio.h"
#include <cstdlib>
#include <cmath>
#include "LineaVista.h"


int* MovimientoAleatorio(int startId, Grafo& grafo, int& size) {
    int columnas = grafo.ObtenerColumnas();
    int filas = grafo.ObtenerFilas();
    int startX, startY;
    IdACoordenadas(startId, columnas, startX, startY);

    // Primer intento: línea vista desde posición actual
    for (int i = 0; i < MAX_INTENTOS; i++) {
        int dx = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
        int dy = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
        int nuevaX = startX + dx;
        int nuevaY = startY + dy;

        if (nuevaX < 0 || nuevaX >= columnas || nuevaY < 0 || nuevaY >= filas) continue;
        int nuevoId = CoordenadasAId(nuevaX, nuevaY, columnas);
        if (grafo.EsNodoPared(nuevoId)) continue;

        if (HayLineaVista(startId, nuevoId, grafo)) {
            // Línea vista libre: moverse directo
            int* ruta = new int[2];
            ruta[0] = startId;
            ruta[1] = nuevoId;
            size = 2;
            return ruta;
        }

        // Hay obstáculo: elegir posición intermedia aleatoria UNA sola vez
        // y reintentar línea vista desde ahí (segundo intento)
        int midX, midY, midId;
        bool foundMid = false;
        for (int j = 0; j < MAX_INTENTOS; j++) {
            int mdx = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
            int mdy = (rand() % (RADIO_MOVIMIENTO * 2 + 1)) - RADIO_MOVIMIENTO;
            midX = startX + mdx;
            midY = startY + mdy;
            if (midX < 0 || midX >= columnas || midY < 0 || midY >= filas) continue;
            midId = CoordenadasAId(midX, midY, columnas);
            if (!grafo.EsNodoPared(midId)) { foundMid = true; break; }
        }

        if (!foundMid) break;

        // Segundo intento: línea vista desde posición intermedia al destino original
        if (HayLineaVista(startId, midId, grafo)) {
            int* ruta = new int[2];
            ruta[0] = startId;
            ruta[1] = midId;
            size = 2;
            return ruta;
        }

        // Avanzar hasta donde sea posible en dirección al midpoint
        // Buscar el último nodo accesible en línea recta desde startId hacia midId
        int lastValidId = startId;
        int pasos = abs(midX - startX) > abs(midY - startY)
                  ? abs(midX - startX) : abs(midY - startY);
        if (pasos > 0) {
            float incX = (float)(midX - startX) / pasos;
            float incY = (float)(midY - startY) / pasos;
            float cx = startX, cy = startY;
            for (int s = 1; s <= pasos; s++) {
                cx += incX; cy += incY;
                int candidateId = CoordenadasAId((int)round(cx), (int)round(cy), columnas);
                if (grafo.EsNodoPared(candidateId)) break;
                lastValidId = candidateId;
            }
        }

        if (lastValidId != startId) {
            int* ruta = new int[2];
            ruta[0] = startId;
            ruta[1] = lastValidId;
            size = 2;
            return ruta;
        }
        break; // si no pudo moverse nada, terminar
    }

    // No pudo moverse
    int* ruta = new int[1];
    ruta[0] = startId;
    size = 1;
    return ruta;
}

