#include "protocol.h"
#include "handle.h"

#define  UI_FILE "chess.glade"
#define  CSS_FILE "myCSS.css"

int main(int argc, char **argv) {

    AppData *appData;

    GtkBuilder *builder;
    GError *error = NULL;
    GtkCssProvider *cssProvider;

    /* Init GTK+ */
    gtk_init(&argc, &argv);

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, UI_FILE, &error)) {
        g_warning("%s", error->message);
        g_free(error);
        return 1;
    }

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, CSS_FILE, &error);


    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    /* Allocate data structure */
    appData = g_slice_new(AppData);


    CH_GET_OBJECT(builder, wPlay, GTK_WINDOW, appData);
    CH_GET_OBJECT(builder, wStart, GTK_WINDOW, appData);
    CH_GET_OBJECT(builder, wWait, GTK_WINDOW, appData);

    CH_GET_OBJECT(builder, wJoinInfo, GTK_DIALOG, appData);

    CH_GET_OBJECT(builder, btnCancel, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnCreateRoom, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnJoin2, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnJoinRoom, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnResign, GTK_BUTTON, appData);
    CH_GET_OBJECT(builder, btnRestart, GTK_BUTTON, appData);

    CH_GET_OBJECT(builder, entryIP, GTK_ENTRY, appData);
    CH_GET_OBJECT(builder, entryPort, GTK_ENTRY, appData);

    CH_GET_OBJECT(builder, labelStatusPlay, GTK_LABEL, appData);
    CH_GET_OBJECT(builder, labelStatusWait, GTK_LABEL, appData);

    int i;

    init_img();

    for (i = 0; i < MAX_CHESS_PLACE_SIZE; i++) {
        int x = placeLoc[i].loc.x;
        int y = placeLoc[i].loc.y;

        appData->squareMap[x][y] = g_slice_new(Square);


        char *placeId = placeLoc[i].placeId;
        char *imgId = placeLoc[i].imgId;

        appData->squareMap[x][y]->img = GTK_IMAGE(gtk_builder_get_object(builder, imgId));
        appData->squareMap[x][y]->place = GTK_BUTTON(gtk_builder_get_object(builder, placeId));

        appData->squareMap[x][y]->p = NULL;
        gtk_image_set_from_pixbuf(appData->squareMap[x][y]->img, imgArr[SPACE]);
        g_signal_connect (G_OBJECT(appData->squareMap[x][y]->place), "clicked", G_CALLBACK(on_place_clicked), appData);
        gtk_style_context_add_class(gtk_widget_get_style_context((GtkWidget *) appData->squareMap[x][y]->place),
                                    "place");
    }

    init_game();
    for (i = 0; i < 32; i++) {
        int x = piece[i].currentLoc.x;
        int y = piece[i].currentLoc.y;
        appData->squareMap[x][y]->p = &piece[i];
        switch (piece[i].team) {

            case BLACK:
                switch (piece[i].pieceType) {

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
                switch (piece[i].pieceType) {

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


    change_game_status(GAMENONE, appData);

    appData->team = WHITE;
    appData->effectLocIndex = -1;

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

