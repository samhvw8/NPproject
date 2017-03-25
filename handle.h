//
// Created by Sam Hoang on 3/25/17.
//

#ifndef PROJECTNP_HANDLE_H
#define PROJECTNP_HANDLE_H

#include "ui.h"

G_MODULE_EXPORT void on_btnQuit_clicked(GtkButton *btn) ;


// click destroy
G_MODULE_EXPORT void on_main_window_destroy(GtkWidget *main_window) ;


/*
 *  wStart
 */


G_MODULE_EXPORT void on_btnJoinRoom_clicked(GtkButton *btn, AppData *appData) ;

/*
 *  wJoinInfo
 */
G_MODULE_EXPORT void on_btnCancel_clicked(GtkButton *btn, AppData *appData) ;

G_MODULE_EXPORT void on_btnJoin2_clicked(GtkButton *btn, AppData *appData) ;

G_MODULE_EXPORT void on_place_clicked(GtkButton *btn, AppData *appData) ;

#endif //PROJECTNP_HANDLE_H
