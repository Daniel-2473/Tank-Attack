//
// Created by yoelr on 25/4/2026.
//

#include "Grafo.h"


/*
 *atributos del grafo
int filas;
int columnas;
int** adyacenciaDeNodos;
Nodo** MatrizDeNodos;

atributos del nodo
int id;

    float x;
    float y;
    bool Pared;
*/

Grafo::Grafo(int filas, int columnas) {
    this->filas=filas;
    this->columnas=columnas;
    int totalNodos=filas*columnas;//para la matriz de adyacencia

    MatrizDeNodos= new Nodo*[filas];//primeramente se hace una matriz de punteros de nodo
    for (int i=0;i<filas;i++) {
        MatrizDeNodos[i]= new Nodo[columnas];//por cada fila se expanden las columnas
        for (int j =0;j<columnas;j++) {

            int id =i*columnas+j;// formula para que queden de forma ascendente desde 0 horizontalmente
            MatrizDeNodos[i][j]=Nodo(id,j,i);//se crean los nodos correctamente es j, i porque filas es el y y columnas el x


        }
    }

    adyacenciaDeNodos= new int*[totalNodos];//inicializacion de matriz de adyacencia, ejemplo Total de nodos =100, matriz de adyacencia = 100x100
    for (int i = 0; i < totalNodos; i++) {
        adyacenciaDeNodos[i] = new int[totalNodos];
        for (int j = 0; j < totalNodos; j++) {
            adyacenciaDeNodos[i][j] = 0; //todas las conexiones en 0
        }
    }

    //como va iterando por la matriz, solo es necesario ir agarrando el de la derecha y el de abajo, y lo tira alrevez igualmente
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int idActual = i * columnas + j; // ID del nodo actual


            if (j + 1 < columnas) {
                int idDerecha = i * columnas + (j + 1);
                adyacenciaDeNodos[idActual][idDerecha] = 1;
                adyacenciaDeNodos[idDerecha][idActual] = 1;
            }

            if (i + 1 < filas) {
                int idAbajo = (i + 1) * columnas + j;
                adyacenciaDeNodos[idActual][idAbajo] = 1;
                adyacenciaDeNodos[idAbajo][idActual] = 1;
            }
        }
    }
}









