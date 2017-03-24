//
// Created by Sam Hoang on 3/24/17.
//

#ifndef PROJECTNP_UI_H
#define PROJECTNP_UI_H

#include <gtk/gtk.h>

/* Macros for obtaining objects from UI file */
#define CH_GET_OBJECT(builder, name, type, data) \
data->name = type ( gtk_builder_get_object(builder, #name ))

#define CH_GET_WIDGET(builder, name, data)                    \
CH_GET_OBJECT( builder, name, GTK_WIDGET, data )

struct _AppData {
    /* Windows */
    GtkWindow *wPlay;
    GtkWindow *wStart;

    /*
     *  Dialog
     */

    GtkDialog *wJoinInfo;

    /*
     *  GtkWindow wStart
     */

    GtkButton *btnCreateRoom;
    GtkButton *btnJoinRoom;
    GtkButton *btnQuit;
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
    GtkButton *btnQuit2;

    // map
    GtkImage *map[8][8];

    /* Insert more widgets to use */
};

typedef struct _AppData AppData;

#endif //PROJECTNP_UI_H
