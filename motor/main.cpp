#include "Board.h"
#include "AlphaBeta.h"

int main() {

    Board board =
        createInitialBoard();

    // --------------------------------
    // Juego principal
    // --------------------------------

    while (!isGameOver(board)) {

        printBoard(board);

        // ----------------------------
        // Turno jugador humano
        // ----------------------------

        if (board.player1Turn) {

            int move;

            std::cout
                << "Ingrese movimiento: ";

            std::cin >> move;

            if (!isLegalMove(board, move)) {

                std::cout
                    << "Movimiento invalido\n";

                continue;
            }

            board =
                makeMove(board, move);

        } else {

            // ------------------------
            // IA Alpha-Beta
            // ------------------------

            int bestMove =
                getBestMove(board, 6);

            std::cout
                << "IA juega: "
                << bestMove
                << "\n";

            board =
                makeMove(board,
                         bestMove);
        }
    }

    // --------------------------------
    // Final del juego
    // --------------------------------

    collectRemainingSeeds(board);

    printBoard(board);

    int winner =
        getWinner(board);

    if (winner == 0)
        std::cout << "Empate\n";

    else
        std::cout
            << "Gana jugador "
            << winner
            << "\n";

    return 0;
}