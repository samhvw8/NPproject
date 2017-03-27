//
// Created by Sam Hoang on 3/24/17.
//

#ifndef PROJECTNP_UI_H
#define PROJECTNP_UI_H

#include <gtk/gtk.h>
#include "protocol.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define LISTENQ 8 /*maximum number of client connections */


/* Macros for obtaining objects from UI file */
#define CH_GET_OBJECT(builder, name, type, data) \
data->name = type ( gtk_builder_get_object(builder, #name ))

#define CH_GET_WIDGET(builder, name, data)                    \
CH_GET_OBJECT( builder, name, GTK_WIDGET, data )

typedef struct effectloc_s {
    int x;
    int y;
    gchar *style_name;
} EffectLoc;

typedef struct placeLoc_s {
    Loc loc;
    char *placeId;
    char *imgId;
} PlaceLoc;

typedef struct square_s {
    GtkButton *place;
    GtkImage *img;
    Piece *p;
} Square;

struct appData_s {
    /* Windows */
    GtkWindow *wPlay;
    GtkWindow *wStart;
    GtkWindow *wRestart;
    GtkWindow *wResign;
    GtkWindow *wWait;

    /*
     *  Dialog
     */

    GtkDialog *wJoinInfo;
    GtkDialog *wGameInfo;
    /*
     *  GtkWindow wStart
     */

    GtkButton *btnCreateRoom;
    GtkButton *btnJoinRoom;
    /*
     *  GtkDialog wJoinInfo
     */

    GtkButton *btnJoin2;
    GtkButton *btnCancel;
    GtkEntry *entryIP;
    GtkEntry *entryPort;


    /*
     *  GtkWindow wPlay
     */

    GtkButton *btnRestart;
    GtkButton *btnResign;
    GtkLabel *labelStatusPlay;
    GtkLabel *labelGameSide;


    /*
     * WGameInfo
     *
     */
    GtkButton *btnCreate;
    GtkButton *btnCancelGameInfo;
    GtkEntry *entryPortGameInfo;

    /*
     * wResign
     */
    GtkLabel *labelStatusResign;
    GtkButton *btnNewGame;


    /*
     * wRestart
     */
    GtkLabel *labelStatusRestart;

    /*
     * wWait
     */
    GtkLabel *labelStatusWait;

    // map
    Square *squareMap[8][8];

    /* Insert more widgets to use */

    Loc curloc;
    GameState gameState;
    Team team;


    // effect

    EffectLoc effectLoc[MAX_CHESS_PLACE_SIZE];
    int effectLocIndex;

    // network

    int socketfd;
    struct sockaddr_in cliaddr, servaddr;
};

typedef struct appData_s AppData;

extern PlaceLoc placeLoc[64];

typedef enum iconame_e {
    BBISHOP, BPAWN, WBISTHOP, WPAWN, SPACE, BKIGHT, BQUEEN, WKIGHT, WQUEEN, BKING, BROOK, WKING, WROCK
} ImgName;

extern GdkPixbuf *imgArr[13];

void init_img();

extern AppData *appData;

#endif //PROJECTNP_UI_H
