//
// Created by Sam Hoang on 3/23/17.
//

#ifndef PROJECTNP_PROTOCOL_H
#define PROJECTNP_PROTOCOL_H

#include "chess.h"

typedef enum mode_e {
    JOIN,
    MOVE,
    RESIGN,
    RESTART,
    ACK,
    ERR
} Mode;

typedef struct protocol_s {
    Mode mode;

    Loc from;
    Loc to;

} Protocol;

#endif //PROJECTNP_PROTOCOL_H
