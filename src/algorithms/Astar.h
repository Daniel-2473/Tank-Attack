//
// Created by danie on 5/4/2026.
//

#ifndef TANQUITOS_AASTERISK_H
#define TANQUITOS_AASTERISK_H

#endif //TANQUITOS_AASTERISK_H

#include "../data_estructures/Grafo.h"
#include "../data_estructures/PriorityQueue.h"

int* Astar(int startId, int endId, Grafo& grafo, int& size);
int* ResizeArray(int* arr, int& size);
int* ReverseArray(int* arr, int used);
int* CreateRoute(int* parents, int lastNode, int graphSize, int& size);
void InsertNeighbors(PriorityQueue& queue, int graphSize, NodeCosts& node, Grafo& grafo, int*& parents, int* costSoFar, int endId);
void SetNodeData(NodeCosts node, int Id, Grafo& grafo);