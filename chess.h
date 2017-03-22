//
// Created by Sam Hoang on 3/21/17.
//

#ifndef NPROGRAM_CHESS_H
#define NPROGRAM_CHESS_H

// location
typedef struct loc_s {
    unsigned int x : 3;
    unsigned int y : 3;
} Loc;


typedef enum piecestype_e {

    KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN

} PieceType;

typedef struct piece_s {
    PieceType pieceType;
    Loc currentLoc;
} Piece;



#endif //NPROGRAM_CHESS_H
