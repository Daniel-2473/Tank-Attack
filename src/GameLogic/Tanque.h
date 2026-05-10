//
// Created by yoelr on 10/5/2026.
//

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
    float ObtenerVida();





};


#endif //TANQUITOS_TANQUE_H