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


    if (appData->gameState == GAMEACT) {
        // GAMEACT

        if ((i == appData->curloc.x) && (j == appData->curloc.y)) {
            // cancel action
            printf("cancel action !!\n");
            appData->gameState = GAMENONE;
            clear_all_effect(appData);
            return;
        }


        if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team == appData->team) {
            printf("!cancel action !!\n");
            appData->gameState = GAMENONE;
            clear_all_effect(appData);
            return;
        }

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
        return;
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

void queen_move(int x, int y, AppData *appData) {
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

void knight_move(int x, int y, AppData *appData) {
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

void bishop_move(int x, int y, AppData *appData) {
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

void rook_move(int x, int y, AppData *appData) {
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

    if (!LOCATION_VALIDATE(i, j)) {
        return;
    }


    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy", appData);
        add_to_effect_array(i, j, "enemy", appData);
    }


    if (appData->squareMap[i][j - direct]->p != NULL) {
        // // En passant
        if (appData->squareMap[i][j - direct]->p->team != appData->team &&
            appData->squareMap[i][j - direct]->p->pieceType == PAWN) {
            high_light_place(i, j, "enemy", appData);
            add_to_effect_array(i, j, "enemy", appData);
        }

    }

    i = x - 1;
    j = y + direct;
    if (!LOCATION_VALIDATE(i, j)) {
        return;
    }

    if (appData->squareMap[i][j]->p != NULL && appData->squareMap[i][j]->p->team != appData->team) {
        high_light_place(i, j, "enemy", appData);
        add_to_effect_array(i, j, "enemy", appData);
    }

    if (appData->squareMap[i][j - direct]->p != NULL) {
        // En passant
        if (appData->squareMap[i][j - direct]->p->team != appData->team &&
            appData->squareMap[i][j - direct]->p->pieceType == PAWN) {
            high_light_place(i, j, "enemy", appData);
            add_to_effect_array(i, j, "enemy", appData);
        }

    }


}

void high_light_place(int x, int y, const gchar *style_name, AppData *appData) {
    gtk_style_context_add_class(gtk_widget_get_style_context((GtkWidget *) appData->squareMap[x][y]->place),
                                style_name);
}

void king_act(int x, int y, AppData *appData) {

    int i = appData->curloc.x;
    int j = appData->curloc.y;

    if (x - i > 1 || y - j > 1) {
        goto end;
    }


    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }
    end:
    clear_all_effect(appData);

    appData->gameState = GAMENONE;

}

void queen_act(int x, int y, AppData *appData) {
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
                        printf("1!!\n");
                        goto end;
                    }
                }
            } else {

                for (idy = j - 1; idy > y; idy--) {
                    if (appData->squareMap[i][idy]->p != NULL) {
                        printf("2!! %d - %d\n", i, idy);
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
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }
    end:
    clear_all_effect(appData);

    appData->gameState = GAMENONE;
}

void knight_act(int x, int y, AppData *appData) {
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
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }
    end:
    clear_all_effect(appData);

    appData->gameState = GAMENONE;
}

void bishop_act(int x, int y, AppData *appData) {
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
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }
    end:
    clear_all_effect(appData);

    appData->gameState = GAMENONE;
}

void rook_act(int x, int y, AppData *appData) {
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
                    printf("1!!\n");
                    goto end;
                }
            }
        } else {

            for (idy = j - 1; idy > y; idy--) {
                if (appData->squareMap[i][idy]->p != NULL) {
                    printf("2!! %d - %d\n", i, idy);
                    goto end;
                }
            }
        }
    }

    printf("!!\n");

    if (appData->squareMap[x][y]->p == NULL) {

        appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
        appData->squareMap[i][j]->p = NULL;
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
    } else {

        if (appData->squareMap[x][y]->p->team != appData->team) {

            appData->squareMap[x][y]->p->status = DEAD;
            appData->squareMap[x][y]->p = appData->squareMap[i][j]->p;
            appData->squareMap[i][j]->p = NULL;
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }

    end:
    clear_all_effect(appData);


    appData->gameState = GAMENONE;


}

void pawn_act(int x, int y, AppData *appData) {
    int i = appData->curloc.x;
    int j = appData->curloc.y;
    int direct = (appData->team == WHITE) ? 1 : -1;
    if (appData->squareMap[x][y]->p == NULL) {
        // space
        if (i != x) {
            if (appData->squareMap[x][j]->p != NULL && appData->squareMap[x][j]->p->team != appData->squareMap[i][j]->p->team) {
                appData->squareMap[x][j]->p->status = DEAD;
                appData->squareMap[x][j]->p = NULL;
                place_img_update(x, j, appData);
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
        place_img_update(x, y, appData);
        place_img_update(i, j, appData);
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
            place_img_update(x, y, appData);
            place_img_update(i, j, appData);
        }
    }

    if (appData->squareMap[x][y]->p->team == WHITE && y == 7) {
        appData->squareMap[x][y]->p->pieceType = QUEEN;
        place_img_update(x, y, appData);
    }

    if (appData->squareMap[x][y]->p->team == BLACK && y == 0) {
        appData->squareMap[x][y]->p->pieceType = QUEEN;
        place_img_update(x, y, appData);
    }

    end:
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