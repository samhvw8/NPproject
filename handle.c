//
// Created by Sam Hoang on 3/24/17.
//

#include "protocol.h"
#include "handle.h"



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

}
