//
// Created by Sam Hoang on 3/24/17.
//

#include "protocol.h"
#include "handle.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>


#define LOCATION_ACT(i, j) \
    if (LOCATION_VALIDATE(i, j)) {\
        if (appData->squareMap[i][j]->p != NULL) {\
            if (appData->squareMap[i][j]->p->team != appData->team) {\
                high_light_place(i, j, "enemy");\
                add_to_effect_array(i, j, "enemy");\
            }\
        } else {\
            high_light_place(i, j, "space");\
            add_to_effect_array(i, j,"space");\
        }\
    }

#define LOCATION_ACT_PAWN(i, j) \
    if (LOCATION_VALIDATE(i, j)) {\
        if (appData->squareMap[i][j]->p == NULL) {\
            high_light_place(i, j, "space");\
            add_to_effect_array(i, j,"space");\
        }\
    }


/**
 *  btn click quit
 * @param btn
 */
G_MODULE_EXPORT void on_btnQuit_clicked(GtkButton *btn) {
    gtk_main_quit();
}


// click destroy
G_MODULE_EXPORT void on_main_window_destroy(GtkWidget *main_window) {
    gtk_main_quit();
}


/*
 *  wStart
 */


G_MODULE_EXPORT void on_btnJoinRoom_clicked(GtkButton *btn) {

    gtk_widget_show((GtkWidget *) appData->wJoinInfo);
    gtk_widget_hide((GtkWidget *) appData->wStart);
}


G_MODULE_EXPORT void on_btnCreateRoom_clicked(GtkButton *btn) {

    gtk_widget_show((GtkWidget *) appData->wGameInfo);
    gtk_widget_hide((GtkWidget *) appData->wStart);
}


/*
 *  wJoinInfo
 */
G_MODULE_EXPORT void on_btnCancel_clicked(GtkButton *btn) {

    gtk_widget_hide((GtkWidget *) appData->wJoinInfo);
    gtk_widget_show((GtkWidget *) appData->wStart);
}

G_MODULE_EXPORT void on_btnJoin2_clicked(GtkButton *btn) {
    appData->team = BLACK;
    change_game_status(GAMEWAIT);
    const gchar *port = gtk_entry_get_text(appData->entryPort);
    const gchar *ip = gtk_entry_get_text(appData->entryIP);

    if ((appData->socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Problem in creating the socket");
        exit(2);
    }

    appData->servaddr.sin_family = AF_INET;
    appData->servaddr.sin_addr.s_addr = inet_addr(ip);
    appData->servaddr.sin_port = htons(atoi(port));


    while (1) {
        if (connect(appData->socketfd, (struct sockaddr *) &(appData->servaddr), sizeof((appData->servaddr))) < 0) {
            perror("Problem in connecting to the server");
            exit(1);
        }

        printf("connect to another player !");
        Protocol aProtocol;
        bzero(&aProtocol, sizeof(Protocol));
        aProtocol.mode = JOIN;

        send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);
        ssize_t n = recv(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);
        if (aProtocol.mode == ACK) {
            break;
        }

        printf("connect failed !");
    }
    printf("connect success !");

    if (fcntl(appData->socketfd, F_SETFL, O_NONBLOCK | O_ASYNC)) {
        printf("Error in setting socket to async, nonblock mode");
        exit(21);
    }


    signal(SIGIO, rev_from_player);

    if (fcntl(appData->socketfd, F_SETOWN, getpid()) < 0) {
        perror("fcntl F_SETOWN");
        exit(22);
    }

    gtk_widget_show((GtkWidget *) appData->wPlay);
    gtk_widget_hide((GtkWidget *) appData->wJoinInfo);
}


/*
 *  wGameInfo
 */

G_MODULE_EXPORT void on_btnCancelGameInfo_clicked(GtkButton *btn) {
    gtk_widget_show((GtkWidget *) appData->wStart);
    gtk_widget_hide((GtkWidget *) appData->wGameInfo);
}

G_MODULE_EXPORT void on_btnCreate_clicked(GtkButton *btn) {
//     socket here

    appData->team = WHITE;
    const gchar *port = gtk_entry_get_text(appData->entryPortGameInfo);


    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    appData->servaddr.sin_family = AF_INET;
    appData->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    appData->servaddr.sin_port = htons(atoi(port));


    bind(listenfd, (struct sockaddr *) &(appData->servaddr), sizeof((appData->servaddr)));

    listen(listenfd, LISTENQ);

    socklen_t clilen = sizeof(appData->cliaddr);


    while (1) {
        printf("Wait Connect !\n");
        appData->socketfd = accept(listenfd, (struct sockaddr *) &(appData->cliaddr), &clilen);

        Protocol aProtocol;

        ssize_t n = recv(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);

        if (aProtocol.mode == JOIN) {
            break;
        }
        bzero(&aProtocol, sizeof(Protocol));
        aProtocol.mode = ERR;
        send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);
        printf("Wait JOIN !\n");
    }

    Protocol aProtocol;
    bzero(&aProtocol, sizeof(Protocol));
    aProtocol.mode = ACK;

    send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);
    printf("connect success !");
    close(listenfd);

    if (fcntl(appData->socketfd, F_SETFL, O_NONBLOCK | O_ASYNC))
        printf("Error in setting socket to async, nonblock mode");

    signal(SIGIO, rev_from_player);

    if (fcntl(appData->socketfd, F_SETOWN, getpid()) < 0) {
        perror("fcntl F_SETOWN");
        exit(1);
    }

    // socket here
    gtk_widget_show((GtkWidget *) appData->wPlay);
    gtk_widget_hide((GtkWidget *) appData->wGameInfo);
}

/*
 *  wPlay
 */


G_MODULE_EXPORT void on_place_clicked(GtkButton *btn) {
    if (appData->gameState == GAMEWAIT) {
        printf("GAMEWAIT\n");
        return;
    }

    int i = 0, j = 0;
    for (i = 0; i < MAX_CHESS_SIDE_SIZE; i++) {
        for (j = 0; j < MAX_CHESS_SIDE_SIZE; j++) {
            if ((appData->squareMap[i][j]->place) == btn) {
                goto endloop;

            }
        }
    }
    endloop:


    if (appData->gameState == GAMEACT) {
        // GAMEACT

        if ((i == appData->curloc.x) && (j == appData->curloc.y)) {
            // cancel action
            change_game_status(GAMENONE);
            clear_all_effect(appData);
            return;
        }


        if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team == appData->team) {
            change_game_status(GAMENONE);
            clear_all_effect(appData);
            return;
        }

        PieceType pieceType = appData->squareMap[appData->curloc.x][appData->curloc.y]->p->pieceType;

        switch (pieceType) {

            case KING:
                king_act(i, j);
                break;
            case QUEEN:
                queen_act(i, j);
                break;
            case ROOK:
                rook_act(i, j);
                break;
            case KNIGHT:
                knight_act(i, j);
                break;
            case BISHOP:
                bishop_act(i, j);
                break;
            case PAWN:
                pawn_act(i, j);
                break;
        }


        return;
    }

    if (appData->squareMap[i][j]->p == NULL && appData->gameState == GAMENONE) {

        // GAMENONE & select space
        return;
    }




    // GAMENONE & select piece

    if (appData->squareMap[i][j]->p->team != appData->team) {
        // can't control another player's piece;
        return;
    }

    appData->curloc.x = (unsigned int) i;
    appData->curloc.y = (unsigned int) j;


    switch (appData->squareMap[i][j]->p->pieceType) {

        case KING:
            king_move(i, j);
            break;
        case QUEEN:
            queen_move(i, j);
            break;
        case ROOK:
            rook_move(i, j);
            break;
        case KNIGHT:
            knight_move(i, j);
            break;
        case BISHOP:
            bishop_move(i, j);
            break;
        case PAWN:
            pawn_move(i, j);
            break;
    }
    change_game_status(GAMEACT);
}

void king_move(int x, int y) {
    int i, j;
    i = x;
    j = y + 1;

    LOCATION_ACT(i, j);

    i = x + 1;
    j = y + 1;

    LOCATION_ACT(i, j);

    i = x + 1;
    j = y;
    LOCATION_ACT(i, j);

    i = x + 1;
    j = y - 1;
    LOCATION_ACT(i, j);

    i = x;
    j = y - 1;

    LOCATION_ACT(i, j);

    i = x - 1;
    j = y - 1;
    LOCATION_ACT(i, j);
    i = x - 1;
    j = y;
    LOCATION_ACT(i, j);
    i = x - 1;
    j = y + 1;
    LOCATION_ACT(i, j);

}

void queen_move(int x, int y) {
    int i, j;
    i = x;

    // like rook
    for (j = y + 1; j < MAX_CHESS_SIDE_SIZE; j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }
    for (j = y - 1; j >= 0; j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    j = y;

    for (i = x + 1; i < MAX_CHESS_SIDE_SIZE; i++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1; i >= 0; i--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    // -- like bishop
    for (i = x + 1, j = y + 1;
         i < MAX_CHESS_SIDE_SIZE && j < MAX_CHESS_SIDE_SIZE;
         i++, j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x + 1, j = y - 1; i < MAX_CHESS_SIDE_SIZE && j >= 0; i++, j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1, j = y + 1;
         i >= 0 && j < MAX_CHESS_SIDE_SIZE;
         i--, j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }


}

void knight_move(int x, int y) {
    int i, j;
    i = x + 1;
    j = y + 2;
    LOCATION_ACT(i, j);

    i = x + 2;
    j = y + 1;
    LOCATION_ACT(i, j);

    i = x + 2;
    j = y + 1;
    LOCATION_ACT(i, j);

    i = x + 2;
    j = y - 1;
    LOCATION_ACT(i, j);

    i = x + 1;
    j = y - 2;
    LOCATION_ACT(i, j);

    i = x - 1;
    j = y - 2;
    LOCATION_ACT(i, j);

    i = x - 2;
    j = y - 1;
    LOCATION_ACT(i, j);

    i = x - 2;
    j = y + 1;
    LOCATION_ACT(i, j);

    i = x - 1;
    j = y + 2;
    LOCATION_ACT(i, j);
}

void bishop_move(int x, int y) {
    int i, j;
    for (i = x + 1, j = y + 1;
         i < MAX_CHESS_SIDE_SIZE && j < MAX_CHESS_SIDE_SIZE;
         i++, j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x + 1, j = y - 1; i < MAX_CHESS_SIDE_SIZE && j >= 0; i++, j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1, j = y + 1;
         i >= 0 && j < MAX_CHESS_SIDE_SIZE;
         i--, j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }
}

void rook_move(int x, int y) {
    int i, j;
    i = x;

    for (j = y + 1; j < MAX_CHESS_SIDE_SIZE; j++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }
    for (j = y - 1; j >= 0; j--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    j = y;

    for (i = x + 1; i < MAX_CHESS_SIDE_SIZE; i++) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }

    for (i = x - 1; i >= 0; i--) {
        LOCATION_ACT(i, j);
        if (appData->squareMap[i][j]->p != NULL) {
            break;
        }
    }
}

void pawn_move(int x, int y) {

    int i, j, direct = (appData->team == WHITE) ? 1 : -1;
    i = x;
    j = y + direct;

    LOCATION_ACT_PAWN(i, j);

    if ((appData->team == WHITE && y == 1) || (appData->team == BLACK && y == 6)) {
        j = y + direct * 2;
        LOCATION_ACT_PAWN(i, j);
    }

    i = x + 1;
    j = y + direct;

    if (!LOCATION_VALIDATE(i, j)) {
        return;
    }


    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy");
        add_to_effect_array(i, j, "enemy");
    }


    if (appData->squareMap[i][j - direct]->p != NULL) {
        // // En passant
        if (appData->squareMap[i][j - direct]->p->team != appData->team &&
            appData->squareMap[i][j - direct]->p->pieceType == PAWN) {
            high_light_place(i, j, "enemy");
            add_to_effect_array(i, j, "enemy");
        }

    }

    i = x - 1;
    j = y + direct;
    if (!LOCATION_VALIDATE(i, j)) {
        return;
    }

    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy");
        add_to_effect_array(i, j, "enemy");
    }

    if (appData->squareMap[i][j - direct]->p != NULL) {
        // En passant
        if (appData->squareMap[i][j - direct]->p->team != appData->team &&
            appData->squareMap[i][j - direct]->p->pieceType == PAWN) {
            high_light_place(i, j, "enemy");
            add_to_effect_array(i, j, "enemy");
        }

    }


}

void high_light_place(int x, int y, const gchar *style_name) {
    gtk_style_context_add_class(gtk_widget_get_style_context((GtkWidget *) appData->squareMap[x][y]->place),
                                style_name);
}

void king_act(int x, int y) {

    int i = appData->curloc.x;
    int j = appData->curloc.y;

    if (x - i > 1 || y - j > 1) {
        goto end;
    }


    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }
    change_game_status(GAMEWAIT);

    send_to_player(appData->curloc.x, appData->curloc.y, x, y);

    end:
    clear_all_effect(appData);
}

void queen_act(int x, int y) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;

    int absX = (x - i > 0) ? x - i : i - x;
    int absY = (y - j > 0) ? y - j : j - y;

    if (!((absX == absY) || (x == i) || (j == y))) {
        goto end;
    }

    if (absX == absY) {
        if (x - i > 0 && y - j > 0) {
            int idx, idy;
            for (idx = i + 1, idy = j + 1;
                 idx < x && idy < y;
                 idx++, idy++) {

                if (appData->squareMap[idx][idy]->p != NULL) {
                    goto end;
                }
            }
        }


        if (x - i < 0 && y - j < 0) {
            int idx, idy;
            for (idx = i - 1, idy = j - 1;
                 idx > x && idy > y;
                 idx--, idy--) {

                if (appData->squareMap[idx][idy]->p != NULL) {
                    goto end;
                }
            }
        }

        if (x - i > 0 && y - j < 0) {
            int idx, idy;
            for (idx = i + 1, idy = j - 1;
                 idx < x && idy > y;
                 idx++, idy--) {

                if (appData->squareMap[idx][idy]->p != NULL) {
                    goto end;
                }
            }
        }

        if (x - i < 0 && y - j > 0) {
            int idx, idy;
            for (idx = i - 1, idy = j + 1;
                 idx > x && idy < y;
                 idx--, idy++) {
                if (appData->squareMap[idx][idy]->p != NULL) {
                    goto end;
                }
            }
        }
    }

    if (x == i) {
        if (j != y) {
            int idy;
            if (y - j > 0) {

                for (idy = j + 1; idy < y; idy++) {
                    if (appData->squareMap[i][idy]->p != NULL) {
                        goto end;
                    }
                }
            } else {

                for (idy = j - 1; idy > y; idy--) {
                    if (appData->squareMap[i][idy]->p != NULL) {
                        goto end;
                    }
                }
            }
        }
    }

    if (j == y) {
        if (i != x) {
            int idx;
            if (x - i > 0) {
                for (idx = i + 1; idx < x; idx++) {
                    if (appData->squareMap[idx][j]->p != NULL) {
                        goto end;
                    }
                }
            } else {
                for (idx = i - 1; idx > x; idx--) {
                    if (appData->squareMap[idx][j]->p != NULL) {
                        goto end;
                    }
                }
            }
        }
    }


    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }

    change_game_status(GAMEWAIT);

    send_to_player(appData->curloc.x, appData->curloc.y, x, y);
    end:
    clear_all_effect(appData);
}

void knight_act(int x, int y) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;

    int absX = (x - i > 0) ? x - i : i - x;
    int absY = (y - j > 0) ? y - j : j - y;

    if (!((absX == 1 && absY == 2) || (absY == 1 && absX == 2))) {
        goto end;
    }


    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }
    change_game_status(GAMEWAIT);
    send_to_player(appData->curloc.x, appData->curloc.y, x, y);
    end:
    clear_all_effect(appData);
}

void bishop_act(int x, int y) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;


    int absX = (x - i > 0) ? x - i : i - x;
    int absY = (y - j > 0) ? y - j : j - y;

    if (absX != absY) {
        goto end;
    }

    if (x - i > 0 && y - j > 0) {
        int idx, idy;
        for (idx = i + 1, idy = j + 1;
             idx < x && idy < y;
             idx++, idy++) {

            if (appData->squareMap[idx][idy]->p != NULL) {
                goto end;
            }
        }
    }


    if (x - i < 0 && y - j < 0) {
        int idx, idy;
        for (idx = i - 1, idy = j - 1;
             idx > x && idy > y;
             idx--, idy--) {

            if (appData->squareMap[idx][idy]->p != NULL) {
                goto end;
            }
        }
    }

    if (x - i > 0 && y - j < 0) {
        int idx, idy;
        for (idx = i + 1, idy = j - 1;
             idx < x && idy > y;
             idx++, idy--) {

            if (appData->squareMap[idx][idy]->p != NULL) {
                goto end;
            }
        }
    }

    if (x - i < 0 && y - j > 0) {
        int idx, idy;
        for (idx = i - 1, idy = j + 1;
             idx > x && idy < y;
             idx--, idy++) {
            if (appData->squareMap[idx][idy]->p != NULL) {
                goto end;
            }
        }
    }

    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }
    change_game_status(GAMEWAIT);
    send_to_player(appData->curloc.x, appData->curloc.y, x, y);
    end:
    clear_all_effect(appData);

}

void rook_act(int x, int y) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;


    if (i != x && j != y) {
        goto end;
    }

    if (i != x) {
        int idx;
        if (x - i > 0) {
            for (idx = i + 1; idx < x; idx++) {
                if (appData->squareMap[idx][j]->p != NULL) {
                    goto end;
                }
            }
        } else {
            for (idx = i - 1; idx > x; idx--) {
                if (appData->squareMap[idx][j]->p != NULL) {
                    goto end;
                }
            }
        }
    }

    if (j != y) {
        int idy;
        if (y - j > 0) {

            for (idy = j + 1; idy < y; idy++) {
                if (appData->squareMap[i][idy]->p != NULL) {
                    goto end;
                }
            }
        } else {

            for (idy = j - 1; idy > y; idy--) {
                if (appData->squareMap[i][idy]->p != NULL) {
                    goto end;
                }
            }
        }
    }


    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }
    change_game_status(GAMEWAIT);
    send_to_player(appData->curloc.x, appData->curloc.y, x, y);
    end:
    clear_all_effect(appData);


}

void pawn_act(int x, int y) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;
    int direct = (appData->team == WHITE) ? 1 : -1;
    if (appData->squareMap[x][y]->p == NULL) {
        // space
        if (i != x) {
            if (appData->squareMap[x][j]->p != NULL &&
                appData->squareMap[x][j]->p->team != appData->squareMap[i][j]->p->team) {
                appData->squareMap[x][j]->p->status = DEAD;
                appData->squareMap[x][j]->p = NULL;
                place_img_update(x, j);
                goto skip;
            }


            goto end;
        }

        if ((y - j == 2 * direct)) {
            if (direct == 1 && j == 1) goto skip;
            if (direct == -1 && j == 6) goto skip;
        }

        if ((y - j != direct)) {
            goto end;
        }
        skip:
        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);
    } else {
        if (!(i - x == 1 || i - x == -1)) {
            goto end;
        }

        if (y - j != direct) {
            goto end;
        }
        if (appData->squareMap[x][y]->p->team != appData->squareMap[i][j]->p->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);
        }
    }

    if (appData->squareMap[x][y]->p->team == WHITE && y == 7) {
        appData->squareMap[x][y]->p->pieceType = QUEEN;
        place_img_update(x, y);
    }

    if (appData->squareMap[x][y]->p->team == BLACK && y == 0) {
        appData->squareMap[x][y]->p->pieceType = QUEEN;
        place_img_update(x, y);
    }

    change_game_status(GAMEWAIT);
    send_to_player(appData->curloc.x, appData->curloc.y, x, y);
    end:
    clear_all_effect(appData);


}

void place_img_update(int x, int y) {


    printf("!zzzz! %d %d\n", x, y);

    Piece *p = appData->squareMap[x][y]->p;

    if (p == NULL) {
        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[SPACE]);
        return;
    }

    switch (p->team) {

        case BLACK:
            switch (p->pieceType) {

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
            switch (p->pieceType) {

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

void add_to_effect_array(int x, int y, gchar *style_name) {
    appData->effectLocIndex = appData->effectLocIndex + 1;
    appData->effectLoc[appData->effectLocIndex].x = x;
    appData->effectLoc[appData->effectLocIndex].y = y;
    appData->effectLoc[appData->effectLocIndex].style_name = style_name;
}

void clear_all_effect(AppData *appData) {
    int i, x, y;
    for (i = 0; i <= appData->effectLocIndex; i++) {
        x = appData->effectLoc[i].x;
        y = appData->effectLoc[i].y;
        gchar *style_name = appData->effectLoc[i].style_name;
        gtk_style_context_remove_class(gtk_widget_get_style_context((GtkWidget *) appData->squareMap[x][y]->place),
                                       style_name);

    }
    appData->effectLocIndex = -1;
}

void change_game_status(GameState gameState) {
    switch (gameState) {

        case GAMEWAIT:
            gtk_label_set_text(appData->labelStatusPlay, "Wait Another Player !!");
            appData->gameState = GAMEWAIT;
            break;
        case GAMEACT:
            gtk_label_set_text(appData->labelStatusPlay, "Choose Location");
            appData->gameState = GAMEACT;
            break;
        case GAMENONE:
            gtk_label_set_text(appData->labelStatusPlay, "Choose Piece");
            appData->gameState = GAMENONE;
            break;
    }
}

void send_to_player(int x, int y, int i, int j) {
    Protocol aProtocol;
    bzero(&aProtocol, sizeof(Protocol));
    aProtocol.from.x = (unsigned int) x;
    aProtocol.from.y = (unsigned int) y;


    aProtocol.to.x = (unsigned int) i;
    aProtocol.to.y = (unsigned int) j;


    aProtocol.mode = MOVE;

    send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);

    printf("send: %d %d %d %d %d\n", aProtocol.mode, aProtocol.from.x, aProtocol.from.y, aProtocol.to.x,
           aProtocol.to.y);
}

void another_player_move(int i, int j, int x, int y) {
    if (appData->squareMap[x][y]->p == NULL) {

        if (appData->squareMap[i][j]->p->pieceType == PAWN) {
            if (appData->squareMap[x][j]->p != NULL &&
                appData->squareMap[x][j]->p->team != appData->squareMap[i][j]->p->team) {
                appData->squareMap[x][j]->p->status = DEAD;
                appData->squareMap[x][j]->p = NULL;
                place_img_update(x, j);
            }
        }


        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y);
        place_img_update(i, j);


    } else {

        if (appData->squareMap[x][y]->p->team != appData->squareMap[i][j]->p->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y);
            place_img_update(i, j);


        } else {
            Protocol aProtocol;
            bzero(&aProtocol, sizeof(Protocol));
            aProtocol.mode = ERR;

            send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);
            goto end;
        }
    }
    if (appData->squareMap[x][y]->p->pieceType == PAWN) {

        if (appData->squareMap[x][y]->p->team == WHITE && y == 7) {
            appData->squareMap[x][y]->p->pieceType = QUEEN;
            place_img_update(x, y);
        }

        if (appData->squareMap[x][y]->p->team == BLACK && y == 0) {
            appData->squareMap[x][y]->p->pieceType = QUEEN;
            place_img_update(x, y);
        }

    }


    Protocol aProtocol;
    bzero(&aProtocol, sizeof(Protocol));
    aProtocol.mode = ACK;

    send(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);

    end:;
}

void rev_from_player(int signo) {
    Protocol aProtocol;

    ssize_t n = recv(appData->socketfd, &aProtocol, sizeof(aProtocol), 0);

    if (n > 0) {
        printf("rev %d %d %d %d %d\n", aProtocol.mode, aProtocol.from.x, aProtocol.from.y, aProtocol.to.x,
               aProtocol.to.y);
    } else {
        return;
    }


    switch (aProtocol.mode) {

        case JOIN:
            break;
        case MOVE:
            if (appData->squareMap[aProtocol.from.x][aProtocol.from.y]->p != NULL) {
//                another_player_move(aProtocol.from.x, aProtocol.from.y, aProtocol.to.x, aProtocol.to.y);

                {
                    int i = aProtocol.from.x;
                    int j = aProtocol.from.y;
                    int x = aProtocol.to.x;
                    int y = aProtocol.to.y;
                    if (appData->squareMap[x][y]->p == NULL) {

                        if (appData->squareMap[i][j]->p->pieceType == PAWN) {
                            if (appData->squareMap[x][j]->p != NULL) {
                                if (appData->squareMap[x][j]->p->team != appData->squareMap[i][j]->p->team) {
                                    appData->squareMap[x][j]->p->status = DEAD;
                                    appData->squareMap[x][j]->p = NULL;
                                    place_img_update(x, j);
                                }
                            }

                        }

                        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
                        appData->squareMap[i][j]->p = NULL;
                        place_img_update(x, y);
                        place_img_update(i, j);
                        gtk_main_iteration_do (FALSE);

                    } else {

                        if (appData->squareMap[x][y]->p->team != appData->squareMap[i][j]->p->team) {

                            appData->squareMap[x][y]->p->status = DEAD;
                            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
                            appData->squareMap[i][j]->p = NULL;
                            place_img_update(x, y);
                            place_img_update(i, j);
                            gtk_main_iteration_do (FALSE);

                        } else {
                            Protocol protocol;
                            bzero(&protocol, sizeof(Protocol));
                            protocol.mode = ERR;

                            send(appData->socketfd, &protocol, sizeof(protocol), 0);
                            goto end;
                        }
                    }
                    if (appData->squareMap[x][y]->p->pieceType == PAWN) {

                        if (appData->squareMap[x][y]->p->team == WHITE && y == 7) {
                            appData->squareMap[x][y]->p->pieceType = QUEEN;
                            place_img_update(x, y);
                            gtk_main_iteration_do (FALSE);
                        }

                        if (appData->squareMap[x][y]->p->team == BLACK && y == 0) {
                            appData->squareMap[x][y]->p->pieceType = QUEEN;
                            place_img_update(x, y);
                            gtk_main_iteration_do (FALSE);
                        }

                    }


                    Protocol protocol;
                    bzero(&protocol, sizeof(Protocol));
                    aProtocol.mode = ACK;

                    send(appData->socketfd, &protocol, sizeof(protocol), 0);

                    end:;
                }


                change_game_status(GAMENONE);
            }
//            else {
//                place_img_update(aProtocol.from.x, aProtocol.from.y);
//                place_img_update(aProtocol.to.x, aProtocol.to.y);
//            }
            break;
        case RESIGN:
            printf("Player disconnect !!");
            gtk_main_quit();
            break;
        case RESTART:
            break;
        case ACK:
            break;
        case ERR:
            break;

        default:
            break;
    }

}