#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "Board.h"

// Evaluación heurística
int evaluateBoard(const Board& b);

// Minimax
int minimax(Board b,
            int depth,
            bool maximizingPlayer);

// Alpha-Beta
int alphabeta(Board b,
              int depth,
              int alpha,
              int beta,
              bool maximizingPlayer);

// Obtener mejor movimiento
int getBestMove(Board b,
                int depth);

#endif