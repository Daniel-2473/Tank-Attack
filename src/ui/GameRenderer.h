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
    void DrawHUD();
    void DrawTurnText(int hudY);
    void DrawTimeText(int hudY);
    void DrawPlayerHUD(int playerId, int startX, int hudY);
    void DrawTankHUD(Tanque* tank, int x, int y);
    void DrawHUDBackground(int hudY);
    void DrawPowerUpHUD(int hudY, int x, int playerId);

    int ScreenToNodeId(int mouseX, int mouseY);

    sf::RenderWindow window;
    Juego* juego;

    sf::Texture wallTexture;
    sf::Texture* tankTextures;

    sf::RectangleShape background;

    sf::Clock movementClock;

    sf::Font font;

    int columns;
    int rows;

    Tanque* selectedTank;

    sf::Texture& SelectColor(const string& color);
};


#endif //TANQUITOS_GAMERENDERER_H
