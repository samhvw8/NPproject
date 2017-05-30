//
// Created by Sam Hoang on 3/25/17.
//

#include "ui.h"

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

    int i;


    for (i = 0; i < 32; i++) {
        int x = piece[i].currentLoc.x;
        int y = piece[i].currentLoc.y;
        appData->squareMap[x][y]->p = &piece[i];
        switch (piece[i].team) {

            case BLACK:
                switch (piece[i].pieceType) {

                    case KING:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BKING]);
                        break;
                    case QUEEN:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BQUEEN]);
                        break;
                    case ROOK:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BROOK]);
                        break;
                    case KNIGHT:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BKIGHT]);
                        break;
                    case BISHOP:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BBISHOP]);
                        break;
                    case PAWN:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[BPAWN]);
                        break;
                }
                break;
            case WHITE:
                switch (piece[i].pieceType) {

                    case KING:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WKING]);
                        break;
                    case QUEEN:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WQUEEN]);
                        break;
                    case ROOK:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WROCK]);
                        break;
                    case KNIGHT:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WKIGHT]);
                        break;
                    case BISHOP:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WBISTHOP]);
                        break;
                    case PAWN:
                        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[WPAWN]);
                        break;
                }
                break;
        }
    }

    appData->flag = 0;
    gtk_label_set_text(appData->labelTimer, "");

}

void new_game() {
    int i;

    for (i = 0; i < MAX_CHESS_PLACE_SIZE; i++) {
        int x = placeLoc[i].loc.x;
        int y = placeLoc[i].loc.y;

        appData->squareMap[x][y]->p = NULL;
        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[SPACE]);
    }

    appData->flag = 0;

    init_game();
}