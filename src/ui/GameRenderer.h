//
// Created by danie on 5/15/2026.
//

#ifndef TANQUITOS_GAMERENDERER_H
#define TANQUITOS_GAMERENDERER_H
#include <SFML/Graphics.hpp>
#include "../GameLogic/Juego.h"

class GameRenderer {
public:
    GameRenderer(Juego* juego, int columns, int rows);
    void Run();

private:
    void HandleEvents();
    void Update();
    void Draw();

    void DrawGrid();
    void DrawWalls();
    void DrawTanks();

    int ScreenToNodeId(int mouseX, int mouseY);

    sf::RenderWindow window;
    Juego* juego;

    sf::Texture wallTexture;
    sf::Texture* tankTextures;

    sf::RectangleShape background;

    int columns;
    int rows;

    Tanque* selectedTank;

    sf::Texture& SelectColor(const string& color);
};


#endif //TANQUITOS_GAMERENDERER_H
