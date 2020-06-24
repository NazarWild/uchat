#include "../inc/uchat.h"

void func(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    const gchar *full = gtk_entry_get_text(GTK_ENTRY(widge->fullname_entry));
    const gchar *nick = gtk_entry_get_text(GTK_ENTRY(widge->nickname_entry));
    const gchar *birth = gtk_entry_get_text(GTK_ENTRY(widge->birth_entry));
    char *statu = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(widge->status));

    printf("fullname = %s\n", full);
    printf("nickname = %s\n", nick);
    printf("birth = %s\n", birth);
    printf("status = %s\n", statu);
    //gtk_entry_set_text(GTK_ENTRY(widge->fullname_entry), "");
    //gtk_entry_set_text(GTK_ENTRY(widge->nickname_entry), "");
    //gtk_entry_set_text(GTK_ENTRY(widge->birth_entry), "");
}

void delete(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    
}

void profile_photo(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    mx_profile_photo_box(widge);
}

void logout(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    
}

void mx_profile_gtk(t_widget_my *widge) {
    GtkWidget *window;
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
    GtkWidget *png = gtk_button_new();
    widge->profile_photo_button = png;

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

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    nick_entry = gtk_entry_new();
    full_entry = gtk_entry_new();
    birth_entry = gtk_entry_new();
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
    g_signal_connect(png, "clicked", G_CALLBACK(profile_photo), widge);
    gtk_container_add (GTK_CONTAINER (window), box);
    gtk_widget_show_all (window);
}
