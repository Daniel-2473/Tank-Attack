//
// Created by danie on 5/4/2026.
//

#include "Dijkstra.h"
#include <cfloat>
#include "../data_estructures/PriorityQueue.h"
#include "../data_estructures/Grafo.h"

int* Dijsktra(int startId, int endId, Grafo& grafo, int& size) {
    if (startId == endId) { //Caso especial donde sean iguales
        int* route = new int[1] {startId};
        size = 1;
        return route;
    }
    PriorityQueue queue;
    int graphSize = grafo.ObtenerCantidadNodos(); //Cantidad de nodos (filas*columnas)
    int* parents = new int[graphSize]; //Lista de padres para cada nodo
    bool* visited = new bool[graphSize](); //Lista para verificar si han sido visitados
    int* costsSoFar = new int[graphSize];
    for (int i = 0; i < graphSize; i++) {
        costsSoFar[i] = INT_MAX;
    }
    //Las listas se basan en que cada nodo tiene un Id unico, dicho Id es un numero de 0 a la cantidad de nodos
    NodeCosts startNode = {startId, 0, 0, 0};
    queue.Insert(startNode);
    parents[startId] = -1;
    costsSoFar[startId] = 0;
    NodeCosts currentNode;
    while (!queue.IsEmpty()) { //Minetras tengamamos elementos en cola
        currentNode = queue.Dequeue(); //Tomamos un elemento de la cola
        if (visited[currentNode.nodeId]) continue;
        visited[currentNode.nodeId] = true;
        if (endId == currentNode.nodeId) { //Si es el nodo final no recorremos los demas, ya hemos encontrado la ruta
            break;
        }
        InsertNeighbors(queue, graphSize, currentNode, grafo, parents, costsSoFar); //Si no, seguimos visitando nodos
    }
    if (!visited[endId]) { //Caso especial en el que no haya ruta posible (caso que no deberia ser posible)
        delete[] parents;
        delete[] visited;
        delete[] costsSoFar;
        throw std::logic_error("No possible route");
    }
    int* route = CreateRoute(parents, currentNode.nodeId, graphSize, size); //Creamos la ruta en un array de los ids de cada nodo
    delete[] parents;
    delete[] visited;
    delete[] costsSoFar;
    return route;
}

int* ReverseArray(int* arr, int used) { //Invierte un array el cual puede no estar lleno
    int* newArr = new int[used];
    int arrPos;
    for (int i = 0; i < used; i++) {
        arrPos = used-i-1;
        newArr[i] = arr[arrPos];
    }
    delete[] arr;
    return newArr;
}

int *CreateRoute(int *parents, int lastNode, int graphSize, int& size) { //Recrear la ruta de nodos
    int* route = new int[graphSize];
    int currentNode = lastNode;
    int count = 0;
    while (currentNode != -1) { //Vamos visitando los padres de cada nodo desde el ultimo que visitamos anteriormente, asi se obtiene la ruta
        route[count] = currentNode;
        count++;
        currentNode = parents[currentNode];
    }
    size = count;
    return ReverseArray(route, count); //Necesitamos invetir la ruta, ya que va desde el nodo final al inicial
}

void InsertNeighbors(PriorityQueue &queue, int graphSize, NodeCosts& currentNode, Grafo& grafo, int*& parents, int* costSoFar) {
    int currentCost;
    for (int i = 0; i < graphSize; i++) {
        if (grafo.EsVecino(currentNode.nodeId, i)) { //Recorrer los nodos del grafo y verificar cuales son vecinos de donde estamos posicionados
            currentCost = costSoFar[currentNode.nodeId] + 1;
            if (!grafo.EsNodoPared(i) && costSoFar[i] > currentCost) {
                NodeCosts newNode = {i, 1, 0, currentCost};
                queue.Insert(newNode);
                parents[i] = currentNode.nodeId;
                costSoFar[i] = currentCost;
            }
        }
    }
}



