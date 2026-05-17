//
// Created by yoelr on 12/5/2026.
//
#include "../algorithms/BFS.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/MovimientoAleatorio.h"

#include "Juego.h"
#include <ctime>
#include <iostream>
#include "Tanque.h"
Juego::Juego(Grafo &mapa, Player *player1, Player *player2) {
    this->mapa = &mapa;
    this->player1=player1;
    this->player2=player2;
    this->juegoActivo=false;
    this->turnoActual=1;
    this->tanqueEnMovimiento=nullptr;
}

void Juego::Iniciar() {
    this->juegoActivo=true;
    this->tiempo = time(NULL);
}


bool Juego::TiempoTerminado() {
    time_t ahoraMismo = time(NULL);
    int TiempoTranscurrido = ahoraMismo - this->tiempo;
    if (TiempoTranscurrido >= this->DURACIONMAXIMA) {
        return true;
    }
    else {
        return false;
    }
}

void Juego::Actualizar() {
    if (player1->GetTanksLeft()==0||player2->GetTanksLeft()==0||TiempoTerminado()==true) {
        this->juegoActivo=false;
    }
}

void Juego::CambiarTurno() {
    if (this->turnoActual==1) {
        this->turnoActual=2;
    }
    else {
        this->turnoActual=1;
    }
}

int Juego::ObtenerTurnoActual() {
    return this->turnoActual;
}


bool Juego::JuegoTerminado() {
    if (this->juegoActivo==true) {
        //el juego no ha terminado
        return false;
    }
    else {
        return true;
    }
}


int Juego::ObtenerGanador() {
    if (player1->GetTanksLeft()==0) return 2;
    if (player2->GetTanksLeft()==0) return 1;

    if (TiempoTerminado()==true) {
        if (player1->GetTanksLeft()>player2->GetTanksLeft()) return 1;
        if (player2->GetTanksLeft()>player1->GetTanksLeft()) return 2;
        if (player1->GetTanksLeft()==player2->GetTanksLeft()) return 0;
    }
    return 0;
}


void Juego::MoverTanque(int tanqueId, int destinoId) {
    if (juegoActivo==false) {
        return;
    }
    Player* jugadorActual;
    if (turnoActual==1) {
        jugadorActual = player1;
    }
    if (turnoActual==2) {
        jugadorActual = player2;
    }
    Tanque* tanque =  jugadorActual->GetTank(tanqueId);
    if (tanque == nullptr) {
        return;
    }
    if (tanque->EstaVivo()==false) {
        return;
    }
    if (mapa->EsNodoPared(destinoId)) {
        return;
    }
    if (HayTanqueEnPosicion(destinoId)) {
        return;  // No se puede mover a una casilla ocupada
    }
    int posicionIinicial= tanque->ObtenerPosicion();
    string color=tanque->ObtenerColor();
    int* route = nullptr;
    int size=0;
    if (color=="azul" || color == "celeste") {
        //50 de bfs 50 de random
        int probabilidad = rand() %100;
        if (probabilidad<50) {
            route= BFS(posicionIinicial,destinoId,*mapa,size);
        }
        else {
            route=MovimientoAleatorio(posicionIinicial,*mapa,size);
        }
    }
    if (color=="rojo"||color=="amarillo") {
        int probabilidad = rand()%100;
        if (probabilidad<80) {
            route=Dijsktra(posicionIinicial,destinoId,*mapa,size);
        }
        else {
            route=MovimientoAleatorio(posicionIinicial,*mapa,size);
        }
    }
    if (route != nullptr && size > 0) {
        tanque->AsignarRuta(route,size);
        tanqueEnMovimiento=tanque;
    }
}


bool Juego::HayTanqueEnPosicion(int posicionId) {
    for (int i =0;i<4;i++) {
        Tanque* tanque1=player1->GetTank(i);
        if (tanque1 != nullptr && tanque1->EstaVivo()&&tanque1->ObtenerPosicion()==posicionId) {
            return true;
        }
    }

    for (int i = 0; i < 4; i++) {
        Tanque* tanque2 = player2->GetTank(i);
        if (tanque2 != nullptr && tanque2->EstaVivo() && tanque2->ObtenerPosicion() == posicionId) {
            return true;
        }
    }
    return false;
}

void Juego::ProcesarMovimientoPendiente() {
    if (tanqueEnMovimiento != nullptr && tanqueEnMovimiento->TieneRutaPendiente()) {
        tanqueEnMovimiento->AvanzarUnPaso();

        // Si ya no tiene ruta, llegó al destino
        if (!tanqueEnMovimiento->TieneRutaPendiente()) {
            tanqueEnMovimiento = nullptr;
            CambiarTurno();  // solo cambia turno cuando termina
        }
    }
}

int Juego::GetColumns() {
    return  mapa->ObtenerColumnas();
}

int Juego::GetRows() {
    return  mapa->ObtenerFilas();
}

int Juego::IsWall(int nodeId) {
    return mapa->EsNodoPared(nodeId);
}

Tanque *Juego::GetTank(int playerId, int tankId) {
    if (playerId ==1) {
        return player1->GetTank(tankId);
    } else {
        return player2->GetTank(tankId);
    }
}

Tanque* Juego::TanquePerteneceAJugador(int tankPos, int playerId) {
    if (playerId == 1) {
        for (int i = 1; i < 5; i++) {
            if (tankPos == player1->GetTank(i)->ObtenerPosicion()) {
                return player1->GetTank(i);
            }
        }
    } else {
        for (int i = 1; i < 5; i++) {
            if (tankPos == player2->GetTank(i)->ObtenerPosicion()) {
                return player1->GetTank(i);
            }
        }
    }
    return nullptr;
}




