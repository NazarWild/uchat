#include "../inc/uchat.h"

void mx_theme_6(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/themes/theme_6.css", NULL);
}
