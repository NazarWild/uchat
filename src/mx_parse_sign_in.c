#include "../inc/uchat.h"

bool mx_parse_sign_in(t_widget_my *widge, char *log, char *pass, char *rpt) {
    if (strlen(log) == 0 || strlen(pass) == 0|| strlen(rpt) == 0) {
        gtk_widget_show(GTK_WIDGET(widge->name_exists));
        gtk_label_set_text(widge->name_exists, "FILL ALL THE BLANK");
        gtk_entry_set_text(GTK_ENTRY(widge->repeat_user_password), "");
        return false;
    }
    else if (strcmp(pass, rpt) != 0) {
        gtk_widget_show(GTK_WIDGET(widge->name_exists));
        gtk_label_set_text(widge->name_exists, "CONFIRM PASSWORD");
        gtk_entry_set_text(GTK_ENTRY(widge->repeat_user_password), "");
        return false;
    }
    else if (strlen(pass) < 8) {
        gtk_widget_show(GTK_WIDGET(widge->name_exists));
        gtk_label_set_text(widge->name_exists, "Password must be >= 8 symbols");
        gtk_entry_set_text(GTK_ENTRY(widge->repeat_user_password), "");
        return false;
    }
    return true;
}