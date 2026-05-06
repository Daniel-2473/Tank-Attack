//
// Created by yoelr on 5/5/2026.
//

#ifndef TANQUITOS_GENERADORDEMAPA_H
#define TANQUITOS_GENERADORDEMAPA_H


#include "../data_estructures/Grafo.h"
#include "../algorithms/BFSExplorador.h"



class GeneradorDeMapa {

public:
    void Generar(Grafo& grafo);


private:

    void ColocarParedesAleatorias(Grafo& grafo);
    bool EsNodoUsable(int id, Grafo& grafo);
    bool RevisorMapa(Grafo& grafo);
    void LimpiarMapa(Grafo& grafo);


};


#endif //TANQUITOS_GENERADORDEMAPA_H