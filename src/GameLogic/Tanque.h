//
// Created by yoelr on 10/5/2026.
//
#include <string>
using namespace std;
#ifndef TANQUITOS_TANQUE_H
#define TANQUITOS_TANQUE_H


class Tanque {
private:
    int id;
    int vida;
    int posicion;
    string color;
    int jugadorId;


public:
    Tanque(int id, int jugadorId, string color, int posicionInicial);
    int ObtenerPosicion();
    string ObtenerColor();
    int ObtenerId();
    int ObtenerVida();
    bool EstaVivo();

    void Mover(int nuevaposicion);
    void bajarVida(int porcentaje);
};


#endif //TANQUITOS_TANQUE_H