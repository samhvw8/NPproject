//
// Created by Sam Hoang on 3/21/17.
//

#ifndef NPROGRAM_PROTOCOLS_H
#define NPROGRAM_PROTOCOLS_H

typedef enum mode_e {
    JOIN,
    MOVE,
    RESIGN,
    RESTART
} Mode;

typedef struct protocols_s {
    Mode mode;

    unsigned int xf : 3;
    unsigned int yf : 3;

    unsigned int xt : 3;
    unsigned int yt : 3;
} Protocols;


#endif //NPROGRAM_PROTOCOLS_H