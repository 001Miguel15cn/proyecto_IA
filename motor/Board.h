#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <vector>
#include <iostream>

struct Board {

    int pits[14];

    bool player1Turn;
};

// Crear tablero inicial
Board createInitialBoard();

// Mostrar tablero
void printBoard(const Board& b);

// Verificar movimiento legal
bool isLegalMove(const Board& b, int pit);

// Obtener movimientos legales
std::vector<int> getLegalMoves(const Board& b);

// Realizar movimiento
Board makeMove(Board b, int pit);

// Verificar fin del juego
bool isGameOver(const Board& b);

// Recolectar semillas restantes
void collectRemainingSeeds(Board& b);

// Obtener ganador
int getWinner(const Board& b);

#endif