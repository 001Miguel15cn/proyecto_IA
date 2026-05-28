#include "Board.h"

// -----------------------------------
// Crear tablero inicial
// -----------------------------------

Board createInitialBoard() {

    Board b;

    for (int i = 0; i < 14; i++)
        b.pits[i] = 0;

    // Jugador 1
    for (int i = 0; i < 6; i++)
        b.pits[i] = 4;

    // Jugador 2
    for (int i = 7; i < 13; i++)
        b.pits[i] = 4;

    b.player1Turn = true;

    return b;
}

// -----------------------------------
// Mostrar tablero
// -----------------------------------

void printBoard(const Board& b) {

    std::cout << "\n";

    std::cout << "          ";

    for (int i = 12; i >= 7; i--)
        std::cout << b.pits[i] << " ";

    std::cout << "\n";

    std::cout << "      "
              << b.pits[13]
              << "                   "
              << b.pits[6]
              << "\n";

    std::cout << "          ";

    for (int i = 0; i < 6; i++)
        std::cout << b.pits[i] << " ";

    std::cout << "\n\n";

    if (b.player1Turn)
        std::cout << "Turno: Jugador 1\n";
    else
        std::cout << "Turno: Jugador 2\n";
}

// -----------------------------------
// Movimiento legal
// -----------------------------------

bool isLegalMove(const Board& b, int pit) {

    if (b.player1Turn) {

        return pit >= 0 &&
               pit <= 5 &&
               b.pits[pit] > 0;
    }

    return pit >= 7 &&
           pit <= 12 &&
           b.pits[pit] > 0;
}

// -----------------------------------
// Movimientos legales
// -----------------------------------

std::vector<int> getLegalMoves(const Board& b) {

    std::vector<int> moves;

    if (b.player1Turn) {

        for (int i = 0; i < 6; i++) {

            if (b.pits[i] > 0)
                moves.push_back(i);
        }

    } else {

        for (int i = 7; i < 13; i++) {

            if (b.pits[i] > 0)
                moves.push_back(i);
        }
    }

    return moves;
}

// -----------------------------------
// Realizar movimiento
// -----------------------------------

Board makeMove(Board b, int pit) {

    int stones = b.pits[pit];

    b.pits[pit] = 0;

    int index = pit;

    while (stones > 0) {

        index = (index + 1) % 14;

        // Saltar kalaha rival
        if (b.player1Turn && index == 13)
            continue;

        if (!b.player1Turn && index == 6)
            continue;

        b.pits[index]++;
        stones--;
    }

    // --------------------------------
    // Captura
    // --------------------------------

    if (b.player1Turn &&
        index >= 0 &&
        index <= 5 &&
        b.pits[index] == 1) {

        int opposite = 12 - index;

        if (b.pits[opposite] > 0) {

            b.pits[6] += b.pits[opposite] + 1;

            b.pits[index] = 0;
            b.pits[opposite] = 0;
        }
    }

    if (!b.player1Turn &&
        index >= 7 &&
        index <= 12 &&
        b.pits[index] == 1) {

        int opposite = 12 - index;

        if (b.pits[opposite] > 0) {

            b.pits[13] += b.pits[opposite] + 1;

            b.pits[index] = 0;
            b.pits[opposite] = 0;
        }
    }

    // --------------------------------
    // Turno extra
    // --------------------------------

    bool extraTurn = false;

    if (b.player1Turn && index == 6)
        extraTurn = true;

    if (!b.player1Turn && index == 13)
        extraTurn = true;

    if (!extraTurn)
        b.player1Turn = !b.player1Turn;

    return b;
}

// -----------------------------------
// Fin del juego
// -----------------------------------

bool isGameOver(const Board& b) {

    bool side1Empty = true;
    bool side2Empty = true;

    for (int i = 0; i < 6; i++) {

        if (b.pits[i] != 0)
            side1Empty = false;
    }

    for (int i = 7; i < 13; i++) {

        if (b.pits[i] != 0)
            side2Empty = false;
    }

    return side1Empty || side2Empty;
}

// -----------------------------------
// Recolectar semillas restantes
// -----------------------------------

void collectRemainingSeeds(Board& b) {

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < 6; i++) {

        sum1 += b.pits[i];
        b.pits[i] = 0;
    }

    for (int i = 7; i < 13; i++) {

        sum2 += b.pits[i];
        b.pits[i] = 0;
    }

    b.pits[6] += sum1;
    b.pits[13] += sum2;
}

// -----------------------------------
// Obtener ganador
// -----------------------------------

int getWinner(const Board& b) {

    if (b.pits[6] > b.pits[13])
        return 1;

    if (b.pits[13] > b.pits[6])
        return 2;

    return 0;
}