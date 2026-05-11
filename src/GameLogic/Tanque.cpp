//
// Created by yoelr on 10/5/2026.
//

#include "Tanque.h"
#include <iostream>
using namespace std;
//CONSTRUCTOR




Tanque::Tanque(int id, int jugadorId, string color, int posicionInicial) {
    this->id=id;
    this->posicion=posicionInicial;
    this->vida=100;
    this->color=color;
    this->jugadorId=jugadorId;
}

//GETERS
int Tanque::ObtenerPosicion() {
    return this->posicion;
}

string Tanque::ObtenerColor() {
    return this->color;
}

int Tanque::ObtenerId() {
    return this->id;
}

int Tanque::ObtenerVida() {
    return this->vida;
}


bool Tanque::EstaVivo() {
    int vida = ObtenerVida();
    if (vida > 0) {
        return true;
    }
    else {
        return false;
    }
}


void Tanque::bajarVida(int porcentaje) {
    this-> vida = this->vida - porcentaje;
    if (this->vida<0) {
        this->vida =0;
    }
    cout<< "La vida del tanque ahora es: "<<this->vida<<endl;
}


void Tanque::Mover(int nuevaposicion) {
    this->posicion=nuevaposicion;
}
