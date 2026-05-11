//
// Created by danie on 5/10/2026.
//

#include "Player.h"

Player::Player(int id, Tanque* tank1, Tanque* tank2, string color) {
    this->id = id;
    this->tanks = new Tanque*[TANKCOUNT];
    tanks[0] = tank1;
    tanks[1] = tank2;
    this->color = color;
}

int Player::GetId() {
    return id;
}

int Player::GetTanksLeft() {
    int count = 0;
    for (int i = 0; i < 2; i++) {
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



