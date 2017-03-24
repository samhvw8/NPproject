#include "protocol.h"
#include "ui.h"

#define  UI_FILE "chess.glade"

int main(int argc, char **argv) {

    AppData *appData;

    GtkBuilder *builder;
    GError *error = NULL;

    /* Init GTK+ */
    gtk_init(&argc, &argv);

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
        g_warning("%s", error->message);
        g_free(error);
        return 1;
    }

    /* Allocate data structure */
    appData = g_slice_new(AppData);


    CH_GET_OBJECT(builder, wPlay, GTK_WINDOW, appData);
    CH_GET_OBJECT(builder, wStart, GTK_WINDOW, appData);

    CH_GET_OBJECT(builder, wJoinInfo, GTK_DIALOG, appData);

    CH_GET_OBJECT(builder, btnCancel, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnCreateRoom, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnJoin2, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnJoinRoom, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnQuit, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnQuit2, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnResign, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnRestart, GTK_BUTTON, appData);


    CH_GET_OBJECT(builder, entryIP, GTK_ENTRY, appData);
    CH_GET_OBJECT(builder, entryPort, GTK_ENTRY, appData);




    /* Connect signals */
    gtk_builder_connect_signals(builder, appData);

    /* Destroy builder, since we don't need it anymore */
    g_object_unref(G_OBJECT(builder));


    /* Show window */
    gtk_widget_show((GtkWidget *) appData->wStart);

    /* Start main loop */
    gtk_main();

    /* Free any allocated data */
    g_slice_free(AppData, appData);


    return 0;
}

