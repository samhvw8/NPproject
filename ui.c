//
// Created by Sam Hoang on 3/25/17.
//

#include "ui.h"

PlaceLoc placeLoc[64] = {
        {{0, 0}, "00", "img00"},
        {{0, 1}, "01", "img01"},
        {{0, 2}, "02", "img02"},
        {{0, 3}, "03", "img03"},
        {{0, 4}, "04", "img04"},
        {{0, 5}, "05", "img05"},
        {{0, 6}, "06", "img06"},
        {{0, 7}, "07", "img07"},
        {{1, 0}, "10", "img10"},
        {{1, 1}, "11", "img11"},
        {{1, 2}, "12", "img12"},
        {{1, 3}, "13", "img13"},
        {{1, 4}, "14", "img14"},
        {{1, 5}, "15", "img15"},
        {{1, 6}, "16", "img16"},
        {{1, 7}, "17", "img17"},
        {{2, 0}, "20", "img20"},
        {{2, 1}, "21", "img21"},
        {{2, 2}, "22", "img22"},
        {{2, 3}, "23", "img23"},
        {{2, 4}, "24", "img24"},
        {{2, 5}, "25", "img25"},
        {{2, 6}, "26", "img26"},
        {{2, 7}, "27", "img27"},
        {{3, 0}, "30", "img30"},
        {{3, 1}, "31", "img31"},
        {{3, 2}, "32", "img32"},
        {{3, 3}, "33", "img33"},
        {{3, 4}, "34", "img34"},
        {{3, 5}, "35", "img35"},
        {{3, 6}, "36", "img36"},
        {{3, 7}, "37", "img37"},
        {{4, 0}, "40", "img40"},
        {{4, 1}, "41", "img41"},
        {{4, 2}, "42", "img42"},
        {{4, 3}, "43", "img43"},
        {{4, 4}, "44", "img44"},
        {{4, 5}, "45", "img45"},
        {{4, 6}, "46", "img46"},
        {{4, 7}, "47", "img47"},
        {{5, 0}, "50", "img50"},
        {{5, 1}, "51", "img51"},
        {{5, 2}, "52", "img52"},
        {{5, 3}, "53", "img53"},
        {{5, 4}, "54", "img54"},
        {{5, 5}, "55", "img55"},
        {{5, 6}, "56", "img56"},
        {{5, 7}, "57", "img57"},
        {{6, 0}, "60", "img60"},
        {{6, 1}, "61", "img61"},
        {{6, 2}, "62", "img62"},
        {{6, 3}, "63", "img63"},
        {{6, 4}, "64", "img64"},
        {{6, 5}, "65", "img65"},
        {{6, 6}, "66", "img66"},
        {{6, 7}, "67", "img67"},
        {{7, 0}, "70", "img70"},
        {{7, 1}, "71", "img71"},
        {{7, 2}, "72", "img72"},
        {{7, 3}, "73", "img73"},
        {{7, 4}, "74", "img74"},
        {{7, 5}, "75", "img75"},
        {{7, 6}, "76", "img76"},
        {{7, 7}, "77", "img77"},
};
GdkPixbuf *imgArr[13];
void init_img() {
    GError *error = NULL;
    imgArr[BBISHOP]= gdk_pixbuf_new_from_file ("./img/Bbishop.png", &error);
    imgArr[BPAWN] = gdk_pixbuf_new_from_file ("./img/Bpawn.png", &error);
    imgArr[WBISTHOP] = gdk_pixbuf_new_from_file ("./img/Wbisthop.png", &error);
    imgArr[WPAWN] = gdk_pixbuf_new_from_file ("./img/Wpawn.png", &error);
    imgArr[SPACE] = gdk_pixbuf_new_from_file ("./img/space.png", &error);
    imgArr[BKIGHT] = gdk_pixbuf_new_from_file ("./img/Bkight.png", &error);
    imgArr[BQUEEN] = gdk_pixbuf_new_from_file ("./img/Bqueen.png", &error);
    imgArr[WKIGHT] = gdk_pixbuf_new_from_file ("./img/Wkight.png", &error);
    imgArr[WQUEEN] = gdk_pixbuf_new_from_file ("./img/Wqueen.png", &error);
    imgArr[BKING] = gdk_pixbuf_new_from_file ("./img/Bking.png", &error);
    imgArr[BROOK] = gdk_pixbuf_new_from_file ("./img/Brook.png", &error);
    imgArr[WKING] = gdk_pixbuf_new_from_file ("./img/Wking.png", &error);
    imgArr[WROCK] = gdk_pixbuf_new_from_file ("./img/Wrock.png", &error);
}