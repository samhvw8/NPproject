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


G_MODULE_EXPORT void on_btnJoinRoom_clicked(GtkButton *btn);

G_MODULE_EXPORT void on_btnCreateRoom_clicked(GtkButton *btn);


/*
 *  wPlay
 */


G_MODULE_EXPORT void on_btnRestart_clicked(GtkButton *btn);

G_MODULE_EXPORT void on_btnResign_clicked(GtkButton *btn);


/*
 *  wJoinInfo
 */
G_MODULE_EXPORT void on_btnCancel_clicked(GtkButton *btn);

G_MODULE_EXPORT void on_btnJoin2_clicked(GtkButton *btn);


/*
 *  wGameInfo
 */

G_MODULE_EXPORT void on_btnCancelGameInfo_clicked(GtkButton *btn);

G_MODULE_EXPORT void on_btnCreate_clicked(GtkButton *btn);

/*
 *  wResign
 */
//G_MODULE_EXPORT void on_btnNewGame_clicked(GtkButton *btn);


/*
 * wPlay
 */
G_MODULE_EXPORT void on_place_clicked(GtkButton *btn);

// Helper
void king_move(int x, int y);

void queen_move(int x, int y);

void knight_move(int x, int y);

void bishop_move(int x, int y);

void rook_move(int x, int y);

void pawn_move(int x, int y);

void king_act(int x, int y);

void queen_act(int x, int y);

void knight_act(int x, int y);

void bishop_act(int x, int y);

void rook_act(int x, int y);

void pawn_act(int x, int y);

void high_light_place(int x, int y, const gchar *style_name);

void place_img_update(int x, int y);

void add_to_effect_array(int x, int y, gchar *style_name);

void clear_all_effect(AppData *appData);

void change_game_status(GameState gameState);

void send_to_player(Mode mode,int x, int y, int i, int j);

void rev_from_player(int signo);

void change_team(Team team);

void check_game_end();

void fn_timeout();
#endif //PROJECTNP_HANDLE_H
