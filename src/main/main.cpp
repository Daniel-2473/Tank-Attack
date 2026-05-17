#include <SFML/Graphics.hpp>
#include "../ui/GameRenderer.h"
#include "../GameLogic/Juego.h"
#include "../GameLogic/Player.h"
#include "../GameLogic/Tanque.h"
#include "../GameLogic/GeneradorDeMapa.h"
#include "../data_estructures/Grafo.h"

const int COLUMNS = 40;
const int ROWS = 24;

void GenerateTanksPos(Grafo& grafo, int* posArr) {
    for (int i = 0; i < 8; i++) {
        int newPos;
        bool repeated;
        do {
            repeated = false;
            newPos = grafo.RandomPos();
            // Verificar si ya existe
            for (int j = 0; j < i; j++) {
                if (posArr[j] == newPos) {
                    repeated = true;
                    break;
                }
            }
        } while (repeated);
        posArr[i] = newPos;
    }
}

int main(){
    Grafo* grafo = new Grafo(COLUMNS, ROWS);
    GeneradorDeMapa generador;
    generador.Generar(*grafo);
    int* posArr = new int[8];
    GenerateTanksPos(*grafo, posArr);
    Tanque* tank1 = new Tanque(1, 1, "rojo", posArr[0]);
    Tanque* tank2 = new Tanque(2, 1, "rojo", posArr[1]);
    Tanque* tank3 = new Tanque(3, 1, "azul", posArr[2]);
    Tanque* tank4 = new Tanque(4, 1, "azul", posArr[3]);
    Player* player1 = new Player(1, tank1, tank2, tank3, tank4, "rojo");
    Tanque* tank5 = new Tanque(1, 2, "celeste", posArr[4]);
    Tanque* tank6 = new Tanque(2, 2, "celeste", posArr[5]);
    Tanque* tank7 = new Tanque(3, 2, "amarillo", posArr[6]);
    Tanque* tank8 = new Tanque(4, 2, "amarillo", posArr[7]);
    Player* player2 = new Player(2, tank5, tank6, tank7, tank8, "celeste");
    Juego* game = new Juego(*grafo, player1, player2);
    GameRenderer* renderer = new GameRenderer(game, COLUMNS, ROWS);
    renderer->Run();
}

