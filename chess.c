//
// Created by Sam Hoang on 3/25/17.
//
#include "chess.h";

Piece piece[32];

void init_game() {
    piece[0] = {KING, {4, 0}, WHITE, ALIVE};
    piece[1] = {QUEEN, {3, 0}, WHITE, ALIVE};
    piece[2] = {ROOK, {0, 0}, WHITE, ALIVE};
    piece[3] = {ROOK, {7, 0}, WHITE, ALIVE};
    piece[4] = {KNIGHT, {1, 0}, WHITE, ALIVE};
    piece[5] = {KNIGHT, {6, 0}, WHITE, ALIVE};
    piece[6] = {BISHOP, {2, 0}, WHITE, ALIVE};
    piece[7] = {BISHOP, {5, 0}, WHITE, ALIVE};
    piece[8] = {PAWN, {0, 1}, WHITE, ALIVE};
    piece[9] = {PAWN, {1, 1}, WHITE, ALIVE};
    piece[10] = {PAWN, {2, 1}, WHITE, ALIVE};
    piece[11] = {PAWN, {3, 1}, WHITE, ALIVE};
    piece[12] = {PAWN, {4, 1}, WHITE, ALIVE};
    piece[13] = {PAWN, {5, 1}, WHITE, ALIVE};
    piece[14] = {PAWN, {6, 1}, WHITE, ALIVE};
    piece[15] = {PAWN, {7, 1}, WHITE, ALIVE};
    piece[16] = {KING, {4, 7}, BLACK, ALIVE};
    piece[17] = {QUEEN, {3, 7}, BLACK, ALIVE};
    piece[18] = {ROOK, {0, 7}, BLACK, ALIVE};
    piece[19] = {ROOK, {7, 7}, BLACK, ALIVE};
    piece[20] = {KNIGHT, {1, 7}, BLACK, ALIVE};
    piece[21] = {KNIGHT, {6, 7}, BLACK, ALIVE};
    piece[22] = {BISHOP, {2, 7}, BLACK, ALIVE};
    piece[23] = {BISHOP, {5, 7}, BLACK, ALIVE};
    piece[24] = {PAWN, {0, 6}, BLACK, ALIVE};
    piece[25] = {PAWN, {1, 6}, BLACK, ALIVE};
    piece[26] = {PAWN, {2, 6}, BLACK, ALIVE};
    piece[27] = {PAWN, {3, 6}, BLACK, ALIVE};
    piece[28] = {PAWN, {4, 6}, BLACK, ALIVE};
    piece[29] = {PAWN, {5, 6}, BLACK, ALIVE};
    piece[30] = {PAWN, {6, 6}, BLACK, ALIVE};
    piece[31] = {PAWN, {7, 6}, BLACK, ALIVE};
}