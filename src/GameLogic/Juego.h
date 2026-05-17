//
// Created by yoelr on 12/5/2026.
//

#ifndef TANQUITOS_JUEGO_H
#define TANQUITOS_JUEGO_H
#include "../data_estructures/Grafo.h"
#include "Player.h"
#include "Tanque.h"
#include <SFML/System/Clock.hpp>

class Juego {
private:
    Grafo* mapa;
    Player* player1;
    Player* player2;
    int turnoActual;
    time_t tiempo;
    bool juegoActivo;
    const int DURACIONMAXIMA = 300;
    Tanque* tanqueEnMovimiento;
    sf::Clock stepClock;
    float stepInterval = 0.3f;
    void ImprimirRuta(int* route, int size);

public:
    Juego(Grafo& mapa, Player* player1, Player* player2);
    void Iniciar();
    void Actualizar();
    bool TiempoTerminado();
    void CambiarTurno();
    int ObtenerTurnoActual();
    bool JuegoTerminado();
    int ObtenerGanador();
    void MoverTanque(int tanque, int destinoId);
    bool HayTanqueEnPosicion(int posicionId);
    void ProcesarMovimientoPendiente();
    int GetColumns();
    int GetRows();
    int IsWall(int nodeId);
    Tanque* GetTank(int playerId, int tankId);
    Tanque* TanquePerteneceAJugador(int tankPos, int playerId);
};


#endif //TANQUITOS_JUEGO_H