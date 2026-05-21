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
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


Juego::Juego(Grafo &mapa, Player *player1, Player *player2) {
    this->mapa = &mapa;
    this->player1=player1;
    this->player2=player2;
    this->juegoActivo=false;
    this->turnoActual=1;
    this->tanqueEnMovimiento=nullptr;
    this->tiempo = 0;
    this->doubleTurn = false;
    this->doubleTurnCount = 0;
    this->doubleTurnPlayer = 0;
    this->applyPrecise = false;
    this->player1Precise = false;
    this->player2Precise = false;
    this->powerUpInterval = 30.f;
    this->powerUpUsedThisTurn = false;
}

void Juego::Iniciar() {
    this->juegoActivo=true;
    this->tiempo = time(NULL);
}

int Juego::ObtenerTiempoRestante() {
    time_t ahoraMismo = time(NULL);
    int tiempoTranscurrido = ahoraMismo - this->tiempo;

    return DURACIONMAXIMA - tiempoTranscurrido;
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
    if (powerUpClock.getElapsedTime().asSeconds() >= powerUpInterval) {
        GenerarPowerUp();
        powerUpClock.restart();
    }
}

void Juego::CambiarTurno() {
    if (doubleTurnCount > 0 && turnoActual == doubleTurnPlayer) {
        doubleTurnCount--;
    } else {
        turnoActual = (turnoActual == 1) ? 2 : 1;
    }
    powerUpUsedThisTurn = false;
    if (applyPrecise) {
        if (turnoActual == 1) {
            player1Precise = true;
        } else {
            player2Precise = true;
        }
        applyPrecise = false;
    }
}

void Juego::AplicarDoubleTurn(int playerId) {
    doubleTurnPlayer = playerId;
    doubleTurnCount = 2;
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
    cout<<"Funcion mover tanque"<<endl;
    if (juegoActivo==false) {
        return;
    }
    Player* jugadorActual;
    if (turnoActual==1) {
        jugadorActual = player1;
        cout<<"Moviendo tanque del jugador 1"<<endl;
    }
    if (turnoActual==2) {
        jugadorActual = player2;
        cout<<"Moviendo tanque del jugador 2"<<endl;
    }
    Tanque* tanque = jugadorActual->GetTank(tanqueId);
    cout<<"Tanque: " + tanque->ObtenerColor() + to_string(tanqueId)<<endl;
    if (tanque == nullptr) {
        return;
    }
    if (tanque->EstaVivo()==false) {
        return;
    }
    if (mapa->EsNodoPared(destinoId)) {
        cout<<"La posicion seleccionada es invalida"<<endl;
        return;
    }
    if (HayTanqueEnPosicion(destinoId)) {
        cout<<"La posicion seleccionada es invalida"<<endl;
        return;  // No se puede mover a una casilla ocupada
    }
    int posicionIinicial= tanque->ObtenerPosicion();
    cout<<"Posicion inicial:" + to_string(posicionIinicial)<<endl;
    string color=tanque->ObtenerColor();
    int* route = nullptr;
    int size=0;
    int probabilidadPorc;
    if (color == "azul" || color == "celeste") {
        probabilidadPorc = 50;
    }
    else {
        probabilidadPorc = 80;
    }
    if (player1Precise && turnoActual == 1) {
        probabilidadPorc = 90;
        player1Precise = false;
    } else if (player2Precise && turnoActual == 2) {
        probabilidadPorc = 90;
        player2Precise = false;
    }
    if (color=="azul" || color == "celeste") {
        //50 de bfs 50 de random
        int probabilidad = rand() %100;
        if (probabilidad<probabilidadPorc) {
            cout<<"Ejecutando BFS"<<endl;
            route= BFS(posicionIinicial,destinoId,*mapa,size);
        }
        else {
            cout<<"Ejecutando movimiento aleatorio (azul/celeste)"<<endl;
            route=MovimientoAleatorio(posicionIinicial,*mapa,size);
        }
    }
    if (color=="rojo"||color=="amarillo") {
        int probabilidad = rand()%100;
        if (probabilidad < probabilidadPorc) {
            cout<<"Ejecutando Dijsktra"<<endl;
            route=Dijsktra(posicionIinicial,destinoId,*mapa,size);
        }
        else {
            cout<<"Ejecutando movimiento aleatorio (rojo/amarillo)"<<endl;
            route=MovimientoAleatorio(posicionIinicial,*mapa,size);
        }
    }
    if (route != nullptr && size > 0) {
        ImprimirRuta(route, size);
        cout<<"Asignando ruta al tanque"<<endl;
        tanque->AsignarRuta(route,size);
        tanqueEnMovimiento=tanque;
        cout << "Moviendo tanque en pantalla" << endl;
    }
}


bool Juego::HayTanqueEnPosicion(int posicionId) {
    for (int i = 1; i <= 4; i++) {
        Tanque* tanque1 = player1->GetTank(i);
        if (tanque1 != nullptr && tanque1->EstaVivo() && tanque1->ObtenerPosicion() == posicionId)
            return true;
    }
    for (int i = 1; i <= 4; i++) {
        Tanque* tanque2 = player2->GetTank(i);
        if (tanque2 != nullptr && tanque2->EstaVivo() && tanque2->ObtenerPosicion() == posicionId)
            return true;
    }
    return false;
}

void Juego::ProcesarMovimientoPendiente() {

    if (tanqueEnMovimiento != nullptr && tanqueEnMovimiento->TieneRutaPendiente()) {
        if (stepClock.getElapsedTime().asSeconds() >= stepInterval) {
            tanqueEnMovimiento->AvanzarUnPaso();
            stepClock.restart();

            if (!tanqueEnMovimiento->TieneRutaPendiente()) {
                tanqueEnMovimiento = nullptr;
                CambiarTurno();
            }
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
                return player2->GetTank(i);
            }
        }
    }
    return nullptr;
}

void Juego::ImprimirRuta(int* route, int size) {
    cout << "Ruta calculada (" << size << " pasos): ";
    for (int i = 0; i < size; i++) {
        int col = route[i] % mapa->ObtenerColumnas();
        int row = route[i] / mapa->ObtenerColumnas();
        cout << "[" << route[i] << " (" << col << "," << row << ")]";
        if (i < size - 1) cout << " -> ";
    }
    cout << endl;
}

void Juego::ApplyPrecise() {
    applyPrecise = true;
}

void Juego::UsePowerUp() {
    if (powerUpUsedThisTurn) {
        cout << "Ya se usó un power-up este turno" << endl;
        return;
    }
    int powerUpId;
    if (turnoActual == 1) {
        powerUpId = player1->SacarYAplicarPowerUp();
    } else {
        powerUpId = player2->SacarYAplicarPowerUp();
    }
    if (powerUpId == -1) return;

    if (powerUpId == 1) {
        AplicarDoubleTurn(turnoActual);
    } else if (powerUpId == 2) {
        ApplyPrecise();
    }
    powerUpUsedThisTurn = true;
}

void Juego::GenerarPowerUp() {
    int tipo = (rand() % 4) + 1;
    int jugador = (rand() % 2) + 1;
    if (jugador == 1) {
        player1->AgregarPowerUp(tipo);
    } else {
        player2->AgregarPowerUp(tipo);
    }
}

int Juego::PeakPowerUpPlayer(int id) {
    if (id == 1) {
        return player1->PeakPowerUp();
    }
    else {
        return player2->PeakPowerUp();
    }
}

