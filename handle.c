//
// Created by Sam Hoang on 3/24/17.
//

#include "protocol.h"
#include "handle.h"

#define LOCATION_ACT(i, j) \
    if (LOCATION_VALIDATE(i, j)) {\
        if (appData->squareMap[i][j]->p != NULL) {\
            if (appData->squareMap[i][j]->p->team != appData->team) {\
                high_light_place(i, j, "enemy", appData);\
                add_to_effect_array(i, j, "enemy", appData);\
            }\
        } else {\
            high_light_place(i, j, "space", appData);\
            add_to_effect_array(i, j,"space", appData);\
        }\
    }

#define LOCATION_ACT_PAWN(i, j) \
    if (LOCATION_VALIDATE(i, j)) {\
        if (appData->squareMap[i][j]->p == NULL) {\
            high_light_place(i, j, "space", appData);\
            add_to_effect_array(i, j,"space", appData);\
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


G_MODULE_EXPORT void on_btnJoinRoom_clicked(GtkButton *btn, AppData *appData) {

    gtk_widget_show((GtkWidget *) appData->wJoinInfo);
    gtk_widget_hide((GtkWidget *) appData->wStart);
}

/*
 *  wJoinInfo
 */
G_MODULE_EXPORT void on_btnCancel_clicked(GtkButton *btn, AppData *appData) {

    gtk_widget_hide((GtkWidget *) appData->wJoinInfo);
    gtk_widget_show((GtkWidget *) appData->wStart);
}

G_MODULE_EXPORT void on_btnJoin2_clicked(GtkButton *btn, AppData *appData) {
    gtk_widget_show((GtkWidget *) appData->wPlay);
    gtk_widget_hide((GtkWidget *) appData->wJoinInfo);
}

G_MODULE_EXPORT void on_place_clicked(GtkButton *btn, AppData *appData) {
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


    printf("!!!%p\n", appData->squareMap[i][j]->p);

    if (appData->gameState == GAMEACT) {
        // GAMEACT & select space
        PieceType pieceType = appData->squareMap[appData->curloc.x][appData->curloc.y]->p->pieceType;

        switch (pieceType) {

            case KING:
                king_act(i, j, appData);
                break;
            case QUEEN:
                queen_act(i, j, appData);
                break;
            case ROOK:
                rook_act(i, j, appData);
                break;
            case KNIGHT:
                knight_act(i, j, appData);
                break;
            case BISHOP:
                bishop_act(i, j, appData);
                break;
            case PAWN:
                pawn_act(i, j, appData);
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
        return;;
    }

    appData->curloc.x = (unsigned int) i;
    appData->curloc.y = (unsigned int) j;

    switch (appData->squareMap[i][j]->p->pieceType) {

        case KING:
            king_move(i, j, appData);
            break;
        case QUEEN:
            queen_move(i, j, appData);
            break;
        case ROOK:
            rook_move(i, j, appData);
            break;
        case KNIGHT:
            knight_move(i, j, appData);
            break;
        case BISHOP:
            bishop_move(i, j, appData);
            break;
        case PAWN:
            pawn_move(i, j, appData);
            break;
    }
    appData->gameState = GAMEACT;
}

void king_move(int x, int y, AppData *appData) {

    printf("zzzzz!\n");
    int i, j;
    i = x;
    j = y + 1;

    LOCATION_ACT(i, j);

}

void queen_move(int x, int y, AppData *appData) {

}

void knight_move(int x, int y, AppData *appData) {

}

void bishop_move(int x, int y, AppData *appData) {

}

void rook_move(int x, int y, AppData *appData) {

}

void pawn_move(int x, int y, AppData *appData) {

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

    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy", appData);
        add_to_effect_array(i, j, "enemy", appData);
    }

    i = x - 1;
    j = y + direct;

    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy", appData);
        add_to_effect_array(i, j, "enemy", appData);
    }

}

void high_light_place(int x, int y, const gchar *style_name, AppData *appData) {
    gtk_style_context_add_class(gtk_widget_get_style_context((GtkWidget *) appData->squareMap[x][y]->place),
                                style_name);
}

void king_act(int x, int y, AppData *appData) {
    appData->gameState = GAMENONE;
}

void queen_act(int x, int y, AppData *appData) {
    appData->gameState = GAMENONE;
}

void knight_act(int x, int y, AppData *appData) {
    appData->gameState = GAMENONE;
}

void bishop_act(int x, int y, AppData *appData) {
    appData->gameState = GAMENONE;
}

void rook_act(int x, int y, AppData *appData) {
    appData->gameState = GAMENONE;
}

void pawn_act(int x, int y, AppData *appData) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;
    int direct = (appData->team == WHITE) ? 1 : -1;
    if (appData->squareMap[x][y]->p == NULL) {
        // space
        if (i != x) {
            return;
        }

        if ((y - j == 2 * direct)) {
            if (direct == 1 && j == 1) goto skip;
            if (direct == -1 && j == 6) goto skip;
        }

        if ((y - j != direct)) {
            return;
        }
        skip:
        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {
        if (!(i - x == 1 || i - x == -1)) {
            return;
        }

        if (y - j != direct) {
            return;
        }
        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }

    clear_all_effect(appData);
    appData->gameState = GAMENONE;

}

void place_img_update(int x, int y, AppData *appData) {

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

void add_to_effect_array(int x, int y, gchar *style_name, AppData *appData) {
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