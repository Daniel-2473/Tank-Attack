//
// Created by danie on 5/10/2026.
//

#include "Player.h"
#include <string>
using namespace std;

#include "../GameLogic/Tanque.h"
#include "../data_estructures/Queue.h"


Player::Player(int id,Tanque* tank0, Tanque* tank1, Tanque* tank2,Tanque* tank3) {
    this->id = id; // 1 o 2
    this->tanks = new Tanque*[TANKCOUNT];
    tanks[0] = tank0;
    tanks[1] = tank1;
    tanks[2] = tank2;
    tanks[3] = tank3;
}

int Player::GetId() {
    return id;
}

int Player::GetTanksLeft() {
    int count = 0;
    for (int i = 0; i < TANKCOUNT; i++) {
        if (tanks[i]!= nullptr&&tanks[i]->EstaVivo()) {
            count++;
        }
    }
    return count;
}

Tanque* Player::GetTank(int tankid) {
    int index = tankid - 1;
    if (index >= 0 && index < TANKCOUNT) {
        return tanks[index];
    }
    return nullptr;
}

Player::~Player() {
    delete[] tanks;
}

void Player::AgregarPowerUp(int tipo) {
    this->powerUps.Insert(tipo);
}

bool Player::TienePowerUps() {
    if (this->powerUps.IsEmpty()==true) {
        return false;
    }
    else {
        return true;
    }
}

int Player::SacarYAplicarPowerUp() {
    if (TienePowerUps()==true){
        return this->powerUps.Dequeue();
    }
    else {
        return -1;
    }
}

int Player::PeakPowerUp() {
    return powerUps.Peak();
}



