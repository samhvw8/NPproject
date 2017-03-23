//
// Created by Sam Hoang on 3/23/17.
//

#ifndef PROJECTNP_CHESS_H
#define PROJECTNP_CHESS_H

// location
typedef struct loc_s {
    unsigned int x : 3;
    unsigned int y : 3;
} Loc;


typedef enum piecestype_e {

    KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN

} PieceType;

typedef enum team_e {
    BLACK, WHITE
} Team;

typedef enum status_e {
    DEAD, ALIVE
} Status;

typedef struct piece_s {
    PieceType pieceType;
    Loc currentLoc;
    Team team;
    Status status;
} Piece;

#endif //PROJECTNP_CHESS_H
