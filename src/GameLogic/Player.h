//
// Created by danie on 5/10/2026.
//

#ifndef TANQUITOS_PLAYER_H
#define TANQUITOS_PLAYER_H
#include <string>
using namespace std;
#include "Tanque.h"
#include <string>
using namespace std;
#include "Tanque.h"
#include "../data_estructures/Queue.h"
class Player {
public:
    int GetId();
    int GetTanksLeft();
    Tanque* GetTank(int id);
    Player(int id,Tanque* tank0, Tanque* tank1, Tanque* tank2,Tanque* tank3, string color);
    ~Player();
    void AgregarPowerUp(int tipo);
    bool TienePowerUps();
    int SacarYAplicarPowerUp();
private:
    const int TANKCOUNT = 4;
    int id;
    string color;
    Tanque** tanks;
    Queue powerUps;
};


#endif //TANQUITOS_PLAYER_H
