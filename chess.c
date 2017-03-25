//
// Created by Sam Hoang on 3/25/17.
//
#include "chess.h"
#include <string.h>
Piece piece[32];

void init_game() {
    Piece tmp[] = {
            {KING,   {4, 0}, WHITE, ALIVE},
            {QUEEN,  {3, 0}, WHITE, ALIVE},
            {ROOK,   {0, 0}, WHITE, ALIVE},
            {ROOK,   {7, 0}, WHITE, ALIVE},
            {KNIGHT, {1, 0}, WHITE, ALIVE},
            {KNIGHT, {6, 0}, WHITE, ALIVE},
            {BISHOP, {2, 0}, WHITE, ALIVE},
            {BISHOP, {5, 0}, WHITE, ALIVE},
            {PAWN,   {0, 1}, WHITE, ALIVE},
            {PAWN,   {1, 1}, WHITE, ALIVE},
            {PAWN,   {2, 1}, WHITE, ALIVE},
            {PAWN,   {3, 1}, WHITE, ALIVE},
            {PAWN,   {4, 1}, WHITE, ALIVE},
            {PAWN,   {5, 1}, WHITE, ALIVE},
            {PAWN,   {6, 1}, WHITE, ALIVE},
            {PAWN,   {7, 1}, WHITE, ALIVE},
            {KING,   {4, 7}, BLACK, ALIVE},
            {QUEEN,  {3, 7}, BLACK, ALIVE},
            {ROOK,   {0, 7}, BLACK, ALIVE},
            {ROOK,   {7, 7}, BLACK, ALIVE},
            {KNIGHT, {1, 7}, BLACK, ALIVE},
            {KNIGHT, {6, 7}, BLACK, ALIVE},
            {BISHOP, {2, 7}, BLACK, ALIVE},
            {BISHOP, {5, 7}, BLACK, ALIVE},
            {PAWN,   {0, 6}, BLACK, ALIVE},
            {PAWN,   {1, 6}, BLACK, ALIVE},
            {PAWN,   {2, 6}, BLACK, ALIVE},
            {PAWN,   {3, 6}, BLACK, ALIVE},
            {PAWN,   {4, 6}, BLACK, ALIVE},
            {PAWN,   {5, 6}, BLACK, ALIVE},
            {PAWN,   {6, 6}, BLACK, ALIVE},
            {PAWN,   {7, 6}, BLACK, ALIVE},
    };

    memcpy(piece, tmp, sizeof(tmp));
}