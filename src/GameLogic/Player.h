//
// Created by danie on 5/10/2026.
//

#ifndef TANQUITOS_PLAYER_H
#define TANQUITOS_PLAYER_H
#include <string>
using namespace std;
#include "Tanque.h"

class Player {
public:
    int GetId();
    int GetTanksLeft();
    Tanque* GetTank(int id);
    Player(int id, Tanque* tank1, Tanque* tank2, string color);
    ~Player();

private:
    const int TANKCOUNT = 2;
    int id;
    string color;
    Tanque** tanks;
};


#endif //TANQUITOS_PLAYER_H
