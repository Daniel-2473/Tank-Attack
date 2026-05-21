//
// Created by danie on 5/15/2026.
//

#include "GameRenderer.h"

const int CELL_SIZE = 32;

GameRenderer::GameRenderer(Juego* juego, int columns, int rows)
: window(sf::VideoMode(sf::Vector2u(CELL_SIZE * columns, CELL_SIZE * rows + 75)),"Tank Attack")
{
    this->rows = rows;
    this->columns = columns;
    this->juego = juego;
    this->background.setSize({static_cast<float>(CELL_SIZE*columns), static_cast<float>(CELL_SIZE*rows)});
    this->background.setFillColor(sf::Color::Green);
    this->background.setPosition({0.f, 0.f});
    this->selectedTank = nullptr;
    if (!wallTexture.loadFromFile("../assets/Map/Wall1.png")) {
        throw std::runtime_error("Could not load wall texture");
    }
    this->tankTextures = new sf::Texture[4];
    if (!tankTextures[0].loadFromFile("../assets/Tanks/Azul.png")) {
        throw std::runtime_error("Could not load wall texture");
    }
    if (!tankTextures[1].loadFromFile("../assets/Tanks/Celeste.png")) {
        throw std::runtime_error("Could not load wall texture");
    }
    if (!tankTextures[2].loadFromFile("../assets/Tanks/Rojo.png")) {
        throw std::runtime_error("Could not load wall texture");
    }
    if (!tankTextures[3].loadFromFile("../assets/Tanks/Amarillo.png")) {
        throw std::runtime_error("Could not load wall texture");
    }
    if (!font.openFromFile("../assets/font.ttf")) {
        throw std::runtime_error("Could not load font");
    }
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
    DrawHUD();

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
        for (int j = 0; j < 4; j++) {
            tank = juego->GetTank(i+1,j+1);
            if (tank != nullptr && tank->EstaVivo()) {
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
    if (color == "azul") {
        return tankTextures[0];
    }
    if (color == "celeste") {
        return tankTextures[1];
    }
    if (color == "rojo") {
        return tankTextures[2];
    }
    return tankTextures[3];
}

void GameRenderer::Update() {
    if (movementClock.getElapsedTime().asSeconds() >= 1.f) {
        juego->ProcesarMovimientoPendiente();
        movementClock.restart();
    }
    juego->Actualizar();
}

int GameRenderer::ScreenToNodeId(int mouseX, int mouseY) {
    int column = mouseX/CELL_SIZE;
    int row = mouseY/CELL_SIZE;
    return row * columns + column;
}

void GameRenderer::HandleEvents() {
    Tanque* tankAux = nullptr;
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::KeyPressed>()) {
            auto key = event->getIf<sf::Event::KeyPressed>();
            if (key->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
            if (key->code == sf::Keyboard::Key::LShift) {
                cout << "Usar powerUp" << endl;
                juego->UsePowerUp();
            }
        }
        if (event->is<sf::Event::MouseButtonPressed>()) {
            auto mouse = event->getIf<sf::Event::MouseButtonPressed>();
            if (mouse->button == sf::Mouse::Button::Left) {
                int mouseX = mouse->position.x;
                int mouseY = mouse->position.y;
                if (mouseY > CELL_SIZE*rows) {
                    return;
                }
                int posId = ScreenToNodeId(mouseX, mouseY);
                if (selectedTank != nullptr) {
                    if (!juego->HayTanqueEnPosicion(posId)) {
                        cout<<"Moviendo tanque de: " + to_string(selectedTank->ObtenerPosicion()) + to_string(posId)<<endl;
                        juego->MoverTanque(selectedTank->ObtenerId(), posId);
                        selectedTank = nullptr;
                    }
                }
                else if (juego->HayTanqueEnPosicion(posId)) {
                    //Verificar si el tanque le pertenece al jugador que corresponde
                    tankAux = juego->TanquePerteneceAJugador(posId, juego->ObtenerTurnoActual());
                    if (tankAux != nullptr) {
                        selectedTank = tankAux;
                        cout<<"Tanque seleccionado:" + tankAux->ObtenerColor() <<endl;
                        tankAux = nullptr;
                    }
                }
            }
            else if (mouse->button == sf::Mouse::Button::Right) {
                if (selectedTank != nullptr) {
                    //Disparar
                }
            }
        }
    }
}

void GameRenderer::DrawHUD() {
    int hudY = CELL_SIZE * rows;

    DrawHUDBackground(hudY);

    DrawTurnText(hudY);

    DrawTimeText(hudY);

    DrawPlayerHUD(1, 200, hudY);

    DrawPlayerHUD(2, CELL_SIZE * columns - 260, hudY);

    DrawPowerUpHUD(hudY, 200, 1);
    DrawPowerUpHUD(hudY, CELL_SIZE * columns - 260, 2);
}

void GameRenderer::DrawHUDBackground(int hudY) {
    sf::RectangleShape hudBackground;

    hudBackground.setSize({
        static_cast<float>(CELL_SIZE * columns),
        75.f
    });

    hudBackground.setPosition({
        0.f,
        static_cast<float>(hudY)
    });

    hudBackground.setFillColor(sf::Color(30, 30, 30));

    window.draw(hudBackground);
}

void GameRenderer::DrawTurnText(int hudY) {

    int turno = juego->ObtenerTurnoActual();

    sf::Text turnoText(font);

    turnoText.setCharacterSize(16);

    turnoText.setFillColor(
        turno == 1
        ? sf::Color(255, 100, 100)
        : sf::Color(100, 200, 255)
    );

    turnoText.setString(
        "Turno: Jugador " + to_string(turno)
    );

    turnoText.setPosition({
        10.f,
        static_cast<float>(hudY + 15)
    });

    window.draw(turnoText);
}

void GameRenderer::DrawPowerUpHUD(int hudY, int x, int playerId) {
    sf::Text powerUpText(font);
    powerUpText.setCharacterSize(16);
    powerUpText.setFillColor(sf::Color::White);
    string powerUpString;
    int powerUpId = juego->PeakPowerUpPlayer(playerId);
    if (powerUpId == 1) {
        powerUpString = "Doble turno";
    } else if (powerUpId == 2) {
        powerUpString = "Precision movimiento";
    } else if (powerUpId == 3) {
        powerUpString = "Presicion bala";
    } else if (powerUpId == 4) {
        powerUpString = "Ataque 100%";
    } else {
        powerUpString = "Ninguno";
    }
    powerUpText.setString(
        "Player" + to_string(playerId) + ": " + powerUpString
    );

    powerUpText.setPosition({
        static_cast<float>(x),
        static_cast<float>(hudY + 30)
    });

    window.draw(powerUpText);
}

void GameRenderer::DrawTimeText(int hudY) {

    int tiempo = juego->ObtenerTiempoRestante();

    if (tiempo < 0) {
        tiempo = 0;
    }

    int minutos = tiempo / 60;
    int segundos = tiempo % 60;

    string tiempoTexto =
        "Tiempo: " +
        to_string(minutos) +
        ":" +
        (segundos < 10 ? "0" : "") +
        to_string(segundos);

    sf::Text tiempoText(font);

    tiempoText.setCharacterSize(16);

    tiempoText.setFillColor(sf::Color::White);

    tiempoText.setString(tiempoTexto);

    tiempoText.setPosition({
        static_cast<float>((CELL_SIZE * columns) / 2),
        static_cast<float>(hudY + 15)
    });

    window.draw(tiempoText);
}

void GameRenderer::DrawPlayerHUD(int playerId, int startX, int hudY) {

    int offsetX = startX;

    for (int j = 1; j <= 4; j++) {

        Tanque* tank = juego->GetTank(playerId, j);

        if (tank == nullptr) {
            continue;
        }

        DrawTankHUD(
            tank,
            offsetX,
            hudY + 10
        );

        offsetX += 60;
    }
}

void GameRenderer::DrawTankHUD(
    Tanque* tank,
    int x,
    int y
) {

    sf::Sprite miniSprite(
        SelectColor(tank->ObtenerColor())
    );

    miniSprite.setScale({0.5f, 0.5f});

    miniSprite.setPosition({
        static_cast<float>(x),
        static_cast<float>(y)
    });

    if (!tank->EstaVivo()) {

        miniSprite.setColor(
            sf::Color(100, 100, 100, 150)
        );
    }

    window.draw(miniSprite);

    sf::Text vidaText(font);

    vidaText.setCharacterSize(14);

    vidaText.setFillColor(sf::Color::White);

    vidaText.setString(
        to_string(tank->ObtenerVida()) + "%"
    );

    vidaText.setPosition({
        static_cast<float>(x + 18),
        static_cast<float>(y + 6)
    });

    window.draw(vidaText);
}




