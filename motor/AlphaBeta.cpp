#include "AlphaBeta.h"
#include <limits>

const int INF = 1000000;

// -----------------------------------
// Heurística
// -----------------------------------

int evaluateBoard(const Board& b) {

    // -------------------------------
    // Aquí puedes mejorar la heurística
    // después
    // -------------------------------

    int player1Score = b.pits[6];
    int player2Score = b.pits[13];

    return player1Score - player2Score;
}

// -----------------------------------
// Minimax
// -----------------------------------

int minimax(Board b,
            int depth,
            bool maximizingPlayer) {

    // -------------------------------
    // Caso base
    // -------------------------------

    if (depth == 0 || isGameOver(b)) {

        return evaluateBoard(b);
    }

    std::vector<int> moves =
        getLegalMoves(b);

    // -------------------------------
    // Maximizar
    // -------------------------------

    if (maximizingPlayer) {

        int maxEval = -INF;

        for (int move : moves) {

            Board next =
                makeMove(b, move);

            int eval =
                minimax(next,
                        depth - 1,
                        false);

            if (eval > maxEval)
                maxEval = eval;
        }

        return maxEval;
    }

    // -------------------------------
    // Minimizar
    // -------------------------------

    int minEval = INF;

    for (int move : moves) {

        Board next =
            makeMove(b, move);

        int eval =
            minimax(next,
                    depth - 1,
                    true);

        if (eval < minEval)
            minEval = eval;
    }

    return minEval;
}

// -----------------------------------
// Alpha-Beta
// -----------------------------------

int alphabeta(Board b,
              int depth,
              int alpha,
              int beta,
              bool maximizingPlayer) {

    // -------------------------------
    // Caso base
    // -------------------------------

    if (depth == 0 || isGameOver(b)) {

        return evaluateBoard(b);
    }

    std::vector<int> moves =
        getLegalMoves(b);

    // -------------------------------
    // Maximizar
    // -------------------------------

    if (maximizingPlayer) {

        int value = -INF;

        for (int move : moves) {

            Board next =
                makeMove(b, move);

            int eval =
                alphabeta(next,
                          depth - 1,
                          alpha,
                          beta,
                          false);

            if (eval > value)
                value = eval;

            if (value > alpha)
                alpha = value;

            // PODA
            if (alpha >= beta)
                break;
        }

        return value;
    }

    // -------------------------------
    // Minimizar
    // -------------------------------

    int value = INF;

    for (int move : moves) {

        Board next =
            makeMove(b, move);

        int eval =
            alphabeta(next,
                      depth - 1,
                      alpha,
                      beta,
                      true);

        if (eval < value)
            value = eval;

        if (value < beta)
            beta = value;

        // PODA
        if (alpha >= beta)
            break;
    }

    return value;
}

// -----------------------------------
// Mejor movimiento
// -----------------------------------

int getBestMove(Board b,
                int depth) {

    std::vector<int> moves =
        getLegalMoves(b);

    int bestMove = moves[0];

    int bestValue = -INF;

    // --------------------------------
    // Aquí después puedes agregar
    // OpenMP:
    //
    // #pragma omp parallel for
    // --------------------------------

    for (int move : moves) {

        Board next =
            makeMove(b, move);

        int value =
            alphabeta(next,
                      depth - 1,
                      -INF,
                      INF,
                      false);

        if (value > bestValue) {

            bestValue = value;
            bestMove = move;
        }
    }

    return bestMove;
}