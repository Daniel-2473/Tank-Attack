//
// Created by danie on 4/30/2026.
//
#include "BFS.h"

#include "../data_estructures/Queue.h"
#include "../data_estructures/Grafo.h"

int* BFS(int startId, int endId, Grafo& grafo, int& size) {
    if (startId == endId) { //Caso especial donde sean iguales
        int* route = new int[1] {startId};
        size = 1;
        return route;
    }
    Queue queue;
    int graphSize = grafo.ObtenerCantidadNodos(); //Cantidad de nodos (filas*columnas)
    int currentNode = startId;
    int* parents = new int[graphSize]; //Lista de padres para cada nodo
    bool* visited = new bool[graphSize](); //Lista para verificar si han sido visitados
    //Las listas se basan en que cada nodo tiene un Id unico, dicho Id es un numero de 0 a la cantidad de nodos
    queue.Insert(startId);
    visited[startId] = true;
    parents[startId] = -1;
    while (!queue.IsEmpty()) { //Minetras tengamamos elementos en cola
        currentNode = queue.Dequeue(); //Tomamos un elemento de la cola
        if (endId == currentNode) { //Si es el nodo final no recorremos los demas, ya hemos encontrado la ruta
            break;
        }
        InsertNeighbors(queue, graphSize, currentNode, grafo, parents, visited); //Si no, seguimos visitando nodos
    }
    if (!visited[endId]) { //Caso especial en el que no haya ruta posible (caso que no deberia ser posible)
        delete[] parents;
        delete[] visited;
        throw std::logic_error("No possible route");
    }
    int* route = CreateRoute(parents, currentNode, graphSize, size); //Creamos la ruta en un array de los ids de cada nodo
    delete[] parents;
    delete[] visited;
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

void InsertNeighbors(Queue &queue, int graphSize, int currentNode, Grafo& grafo, int*& parents, bool*& visited) {
    for (int i = 0; i < graphSize; i++) {
        if (grafo.EsVecino(currentNode, i)) { //Recorrer los nodos del grafo y verificar cuales son vecinos de donde estamos posicionados
            if (!visited[i] && !grafo.EsNodoPared(i)) {
                queue.Insert(i);
                visited[i] = true;
                parents[i] = currentNode;
            }
        } //Se podria optimizar ya sea guardando en los nodos los vecinos o detenernos cuando ya encontramos 4 vecinos que son los maximos
    }
}



