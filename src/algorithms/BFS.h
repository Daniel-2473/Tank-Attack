//
// Created by danie on 4/30/2026.
//

#ifndef TANQUITOS_BFS_H
#define TANQUITOS_BFS_H
#include "../data_estructures/Queue.h"
#include "../data_estructures/Grafo.h"

#endif //TANQUITOS_BFS_H

int* BFS(int startId, int endId, Grafo& grafo, int& size);
int* ResizeArray(int* arr, int& size);
int* ReverseArray(int* arr, int used);
int* CreateRoute(int* parents, int lastNode, int graphSize, int& size);
void InsertNeighbors(Queue& queue, int graphSize, int node, Grafo& grafo, int*& parents, bool*& visited);

