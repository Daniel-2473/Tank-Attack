//
// Created by yoelr on 12/5/2026.
//

#ifndef TANQUITOS_JUEGO_H
#define TANQUITOS_JUEGO_H
#include <ctime>
#include "Grafo.h"
#include "Player.h"

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
    void ProcesarMovimientoPendiente() ;


};


#endif //TANQUITOS_JUEGO_H