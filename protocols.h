//
// Created by Sam Hoang on 3/21/17.
//

#ifndef NPROGRAM_PROTOCOLS_H
#define NPROGRAM_PROTOCOLS_H

#include "chess.h"

typedef enum mode_e {
    JOIN,
    MOVE,
    RESIGN,
    RESTART
} Mode;

typedef struct protocols_s {
    Mode mode;

    Loc from;
    Loc to;

} Protocols;


#endif //NPROGRAM_PROTOCOLS_H