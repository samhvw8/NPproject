//
// Created by Sam Hoang on 3/24/17.
//

#include "ui.h"
#include "protocol.h"


/**
 *  btn click quit
 * @param btn
 */
G_MODULE_EXPORT void onBtnQuitClicked(GtkButton *btn) {
    gtk_main_quit();
}


// click destroy
G_MODULE_EXPORT void on_main_window_destroy(GtkWidget *main_window) {
    gtk_main_quit();
}


/*
 *  wStart
 */


G_MODULE_EXPORT void onBtnJoinRoomClicked(GtkButton *btn, AppData *appData) {

    gtk_widget_show((GtkWidget *) appData->wJoinInfo);
    gtk_widget_hide((GtkWidget* ) appData->wStart);
}