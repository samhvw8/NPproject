//
// Created by Sam Hoang on 3/25/17.
//

#ifndef PROJECTNP_HANDLE_H
#define PROJECTNP_HANDLE_H

#include "ui.h"

G_MODULE_EXPORT void on_btnQuit_clicked(GtkButton *btn);


// click destroy
G_MODULE_EXPORT void on_main_window_destroy(GtkWidget *main_window);


/*
 *  wStart
 */


G_MODULE_EXPORT void on_btnJoinRoom_clicked(GtkButton *btn, AppData *appData);

/*
 *  wJoinInfo
 */
G_MODULE_EXPORT void on_btnCancel_clicked(GtkButton *btn, AppData *appData);

G_MODULE_EXPORT void on_btnJoin2_clicked(GtkButton *btn, AppData *appData);

G_MODULE_EXPORT void on_place_clicked(GtkButton *btn, AppData *appData);


// Helper
void king_move(int x, int y, AppData *appData);

void queen_move(int x, int y, AppData *appData);

void knight_move(int x, int y, AppData *appData);

void bishop_move(int x, int y, AppData *appData);

void rook_move(int x, int y, AppData *appData);

void pawn_move(int x, int y, AppData *appData);

void king_act(int x, int y, AppData *appData);

void queen_act(int x, int y, AppData *appData);

void knight_act(int x, int y, AppData *appData);

void bishop_act(int x, int y, AppData *appData);

void rook_act(int x, int y, AppData *appData);

void pawn_act(int x, int y, AppData *appData);

void high_light_place(int x, int y, const gchar *style_name, AppData *appData);

void place_img_update(int x, int y, AppData *appData);

void add_to_effect_array(int x, int y, gchar *style_name, AppData *appData);

void clear_all_effect(AppData *appData);

#endif //PROJECTNP_HANDLE_H
