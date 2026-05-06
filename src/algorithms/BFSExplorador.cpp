//
// Created by yoelr on 4/5/2026.
//
#include "../data_estructures/Queue.h"
#include "../data_estructures/Grafo.h"
#include "BFSExplorador.h"


int ContarNodosConCamino( int startId, Grafo& grafo) {
    if (grafo.EsNodoPared(starId)==true) {
        return 0;

    }
    Queue queue;
    int graphSize = grafo.ObtenerCantidadNodos();
    bool* visited = new bool[graphSize]();
    int contador = 0;

    queue.Insert(startId);
    visited[startId] = true;

    while (!queue.IsEmpty()) {
        int currentNode = queue.Dequeue();
        contador++;
        for (int i = 0; i < graphSize; i++) {
            if (grafo.EsVecino(currentNode, i)) {
                //solo si no es ta visitado y no es pared
                if (!visited[i] && !grafo.EsNodoPared(i)) {
                    queue.Insert(i);
                    visited[i] = true;
                }
            }
        }
    }
    delete[] visited;
    return contador;
    }






