//
// Created by danie on 5/10/2026.
//

#include "Player.h"
#include <string>
using namespace std;
#include "Tanque.h"
#include "../data_estructures/Queue.h"


Player::Player(int id,Tanque* tank0, Tanque* tank1, Tanque* tank2,Tanque* tank3, string color) {
    this->id = id; // 1 o 2
    this->tanks = new Tanque*[TANKCOUNT];
    tanks[0] = tank0;
    tanks[1] = tank1;
    tanks[2] = tank2;
    tanks[3] = tank3;
    this->color = color; //Rojo y celeste

}

int Player::GetId() {
    return id;
}

int Player::GetTanksLeft() {
    int count = 0;
    for (int i = 0; i < TANKCOUNT; i++) {
        if (tanks[i]->EstaVivo()) {
            count++;
        }
    }
    return count;
}

Tanque* Player::GetTank(int id) {
    for (int i = 0; i < TANKCOUNT; i++) {
        if (tanks[i]->ObtenerId() == id) {
            return tanks[i];
        }
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



