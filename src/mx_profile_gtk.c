#include "../inc/uchat.h"

void profile_exit(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    widge->on_profile = 0;
}

static bool parsing_profile_data(t_widget_my *widge, char *birth) {
    int i = 0;
    int day;
    int month;
    int year;

    if (strlen(birth) == 10) {
        day = (birth[0] - 48) * 10 + (birth[1] - 48);
        month = (birth[3] - 48) * 10 + (birth[4] - 48);
        year = atoi(&birth[6]);
        if (birth[2] != '.' || birth[5] != '.') {
            gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widge->birth_entry), "[dd.mm.year]");
            return false;
        }
        if (day > 31 || day <= 0) {
            gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widge->birth_entry), "INVALID NUMBER OF DAY");
            return false;
        }
        if (month > 12 || month <= 0) {
            gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widge->birth_entry), "INVALID NUMBER OF MONTH");
            return false;
        }
        if (year > 2020 || year <= 0) {
            gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widge->birth_entry), "INVALID NUMBER OF YEAR");
            return false;
        }
        printf("day = %d month = %d year = %d\n", day, month, year);
    }
    else
        return false;
    return true;
}

void func(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    const gchar *full = gtk_entry_get_text(GTK_ENTRY(widge->fullname_entry));
    const gchar *nick = gtk_entry_get_text(GTK_ENTRY(widge->nickname_entry));
    const gchar *birth = gtk_entry_get_text(GTK_ENTRY(widge->birth_entry));
    char *statu = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widge->status));

    //printf("fullname = %s\n", full);
    //printf("nickname = %s\n", nick);
    if (parsing_profile_data(widge, (char *) birth))
        printf("birth = %s\n", birth);
    //printf("status = %s\n", statu);
    //printf("res = %s\n", widge->res_png);
    //gtk_entry_set_text(GTK_ENTRY(widge->fullname_entry), "");
    //gtk_entry_set_text(GTK_ENTRY(widge->nickname_entry), "");
    //gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
}

void set_photo(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    
    mx_photo_set(widge);
}

void delete(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

}

void logout(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
   
}

void mx_profile_gtk(t_widget_my *widge) {
    GtkWidget *save;
    GtkWidget *delete_b;//button
    GtkWidget *logout_b;//button
    GtkWidget *status;//combo box text
    GtkWidget *label;//label
    GtkWidget *lbl;//label
    GtkWidget *full;//label
    GtkWidget *nick;//label
    GtkWidget *birth;//label
    GtkWidget *birth_entry;//entry
    GtkWidget *nick_entry;//entry
    GtkWidget *full_entry;//entry
    GdkPixbuf *anon_pix;
    GtkWidget *png = gtk_button_new();

    GtkWidget *photo;

    anon_pix = gdk_pixbuf_new_from_file("img_chat/anonym.png", NULL);
    anon_pix = gdk_pixbuf_scale_simple(anon_pix, 200, 200, GDK_INTERP_BILINEAR);
    photo = gtk_image_new_from_pixbuf(anon_pix);
    gtk_button_set_image (GTK_BUTTON(png), photo);

    widge->profile_photo_button = png;
    widge->res_png = "img_chat/anonym.png";
    GtkWidget *sep_h1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_h2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_h3 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_h4 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_h5 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *sep_v = gtk_separator_new(GTK_ORIENTATION_VERTICAL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    widge->window_profile = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(widge->window_profile), 600, 400);
    gtk_window_get_position(GTK_WINDOW(widge->chat), &widge->window_x, &widge->window_y);
    gtk_window_move(GTK_WINDOW(widge->window_profile), widge->window_x + 100, widge->window_y + 72);
    // gtk_widget_hide(widge->chat);

    // gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    nick_entry = gtk_entry_new();
    full_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(birth_entry), "[dd.mm.year]");
    label = gtk_label_new("STATUS");
    full = gtk_label_new("FULLNAME");
    nick = gtk_label_new("NICKNAME");
    birth = gtk_label_new("DATE OF BIRTH");
    status = gtk_combo_box_text_new();
    gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(status), "1", "SINGLE");
    gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(status), "2", "IN LOVE");
    gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(status), "3", "MARRIED");
    gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(status), "4", "IT'S COMPLICATED");
    gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT(status), "5", "IN LOVE WITH GOD");
    lbl = gtk_label_new("PERSONAL DATA");
    save = gtk_button_new_with_label("SAVE");
    delete_b = gtk_button_new_with_label ("DELETE ACCOUNT");
    logout_b = gtk_button_new_with_label ("LOG OUT");

    //box2
    gtk_box_pack_start(GTK_BOX(box2), label, 1, 0, 5);
    gtk_box_pack_start(GTK_BOX(box2), status, 1, 0, 5);
    gtk_box_pack_start(GTK_BOX(box2), nick, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), sep_h1, 1, 0, 5);//sep
    gtk_box_pack_start(GTK_BOX(box2), nick_entry, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), full, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), sep_h2, 1, 0, 5);//sep
    gtk_box_pack_start(GTK_BOX(box2), full_entry, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), birth, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), sep_h5, 1, 0, 5);//sep
    gtk_box_pack_start(GTK_BOX(box2), birth_entry, 0, 0, 1);
    gtk_box_pack_start(GTK_BOX(box2), save, 1, 0, 10);
    //box3
    gtk_box_pack_start(GTK_BOX(box3), GTK_WIDGET(png), 0, 0, 1);
    gtk_box_pack_end(GTK_BOX(box3), delete_b, 0, 0, 1);
    gtk_box_pack_end(GTK_BOX(box3), logout_b, 0, 0, 1);
    //box1
    gtk_box_pack_start(GTK_BOX(box1), box3, 1, 0, 1);
    gtk_box_pack_start(GTK_BOX(box1), sep_v, 0, 0, 1);//sep-v
    gtk_box_pack_end(GTK_BOX(box1), box2, 1, 0, 1);
    //box
    gtk_box_pack_start(GTK_BOX(box), lbl, 1, 0, 1);
    gtk_box_pack_start(GTK_BOX(box), sep_h4, 0, 0, 1);//sep-h
    gtk_box_pack_start(GTK_BOX(box), box1, 1, 0, 1);

    widge->nickname_entry = nick_entry;
    widge->fullname_entry = full_entry;
    widge->birth_entry = birth_entry;
    widge->nickname = GTK_LABEL(nick);
    widge->birth = GTK_LABEL(birth);
    widge->fullname = GTK_LABEL(full);
    widge->status = status;
    g_signal_connect(save, "clicked", G_CALLBACK(func), widge);
    g_signal_connect(delete_b, "clicked", G_CALLBACK(delete), widge);
    g_signal_connect(logout_b, "clicked", G_CALLBACK(logout), widge);
    g_signal_connect(png, "clicked", G_CALLBACK(set_photo), widge);
    g_signal_connect(widge->window_profile, "destroy", G_CALLBACK(profile_exit), widge);
    gtk_container_add (GTK_CONTAINER (widge->window_profile), box);
    gtk_widget_show_all (widge->window_profile);
}
