//
// Created by Sam Hoang on 3/23/17.
//

#ifndef PROJECTNP_CHESS_H
#define PROJECTNP_CHESS_H

#define MAX_CHESS_PLACE_SIZE 64
#define MAX_CHESS_SIDE_SIZE 8

#define _VALIDATE(x) ((x < MAX_CHESS_SIDE_SIZE) && (x >= 0))
#define LOCATION_VALIDATE(x, y) (_VALIDATE(x) && _VALIDATE(y))


// location
typedef struct loc_s {
    unsigned int x;
    unsigned int y;
} Loc;



typedef enum piecestype_e {

    KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN

} PieceType;

typedef enum gamestate_e {
    YTURN, // your turn start
    ATURN, // act turn // need to choose action
    ETURN, // end turn // wait another player recv move
    OTURN, // another player turn // wait
    ENDGAME
} GameState;

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

extern Piece piece[32];

void init_game();

void new_game();

#endif //PROJECTNP_CHESS_H
