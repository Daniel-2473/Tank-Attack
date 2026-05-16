//
// Created by danie on 5/15/2026.
//

#include "GameRenderer.h"

const int CELL_SIZE = 32;

GameRenderer::GameRenderer(Juego* juego)
: window(sf::VideoMode(sf::Vector2u(CELL_SIZE * columns, CELL_SIZE * rows)),"Tank Attack")
{
    this->juego = juego;
    this->background.setSize({static_cast<float>(CELL_SIZE*columns), static_cast<float>(CELL_SIZE*rows)});
    this->background.setFillColor(sf::Color::Green);
    this->background.setPosition({0.f, 0.f});
}

void GameRenderer::Run() {
    juego->Iniciar();
    while(window.isOpen()) {
        HandleEvents();
        Update();
        Draw();
    }
}

void GameRenderer::Draw() {
    window.clear();

    DrawGrid();
    DrawWalls();
    DrawTanks();

    window.display();
}

void GameRenderer::DrawGrid() {
    window.draw(background);
}

void GameRenderer::DrawWalls() {
    for (int i=0;i<rows;i++) {
        for (int j =0;j<columns;j++) {
            int id =i*columns+j;
            if (juego->IsWall(id)) {
                sf::Sprite tile(wallTexture);

                tile.setPosition({
                    j * 32.f,
                    i* 32.f
                });

                window.draw(tile);
            }
        }
    }
}

void GameRenderer::DrawTanks() {
    Tanque* tank;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            tank = juego->GetTank(i,j);
            if (tank->EstaVivo()) {
                sf::Sprite tankSprite(SelectColor(tank->ObtenerColor()));

                float x = static_cast<float>(CELL_SIZE * (tank->ObtenerPosicion() % columns));
                float y = static_cast<float>(CELL_SIZE * (tank->ObtenerPosicion() / columns));

                tankSprite.setPosition({x, y});

                window.draw(tankSprite);
            }
        }
    }
}

sf::Texture& GameRenderer::SelectColor(const string& color) {
    if (color == "red") {
        return tankTextures[0];
    }
    if (color == "blue") {
        return tankTextures[1];
    }
    if (color == "cyan") {
        return tankTextures[2];
    }
    return tankTextures[3];
}

void GameRenderer::Update() {
    juego->ProcesarMovimientoPendiente();
    juego->Actualizar();
}


