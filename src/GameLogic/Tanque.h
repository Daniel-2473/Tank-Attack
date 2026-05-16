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
    //atributos para que el tanque vaya poco a poco
    int* rutaPendiente;
    int lengthRuta;
    int pasoActual;


public:
    Tanque(int id, int jugadorId, string color, int posicionInicial);
    int ObtenerPosicion();
    string ObtenerColor();
    int ObtenerId();
    int ObtenerVida();
    bool EstaVivo();

    void Mover(int nuevaposicion);
    void bajarVida(int porcentaje);


    void AsignarRuta(int* ruta, int tamaño);
    bool TieneRutaPendiente();
    void AvanzarUnPaso();
    void LimpiarRuta();
};


#endif //TANQUITOS_TANQUE_H