//
// Created by yoelr on 5/5/2026.
//
#include "GeneradorDeMapa.h"
#include "../data_estructures/Grafo.h"
#include "../algorithms/BFSExplorador.h"

const int porcentajeParedes= 20;

bool GeneradorDeMapa::EsNodoUsable(int id, Grafo& grafo) {
    int filas= grafo.ObtenerFilas();
    int columnas = grafo.ObtenerColumnas();
    int totalNodos= filas*columnas;

    if (id!=0&&id!=totalNodos-1) {
        return true;
    }
    else {
        return false;
    }
}



void GeneradorDeMapa::ColocarParedesAleatorias(Grafo& grafo) {
    int filas= grafo.ObtenerFilas();
    int columnas = grafo.ObtenerColumnas();
    int totalNodos= filas*columnas;

    for (int i =0;i<totalNodos;i++) {
        int numeroaleatorio= rand() % 100;
        if (numeroaleatorio<porcentajeParedes && EsNodoUsable(i,grafo)==true) {
            grafo.HacerPared(i);
        }
    }


}

void GeneradorDeMapa::LimpiarMapa(Grafo& grafo) {
    int filas= grafo.ObtenerFilas();
    int columnas = grafo.ObtenerColumnas();
    int totalNodos= filas*columnas;

    for (int i=0;i<totalNodos;i++) {
    if (grafo.EsNodoPared(i)) {
        grafo.QuitarPared(i);
    }

    }


}


bool GeneradorDeMapa::RevisorMapa(Grafo &grafo) {
    int nodosAccesibles= ContarNodosConCamino(0,grafo);
    int filas= grafo.ObtenerFilas();
    int columnas = grafo.ObtenerColumnas();
    int totalNodos= filas*columnas;
    int totalParedes=0;

    for (int i=0;i<totalNodos;i++) {
        if (grafo.EsNodoPared(i)) {
            totalParedes++;
        }
    }
    int TotalNoParedes= totalNodos-totalParedes;

    return (nodosAccesibles==TotalNoParedes);

}

void GeneradorDeMapa::Generar(Grafo &grafo) {

    bool mapaValido=false;
    while (mapaValido==false) {
        LimpiarMapa(grafo);
        ColocarParedesAleatorias(grafo);
        if (RevisorMapa(grafo)==true) {
            mapaValido=true;
        }

    }


}




