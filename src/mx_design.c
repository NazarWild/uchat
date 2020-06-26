#include "../inc/uchat.h"

void mx_design(t_widget_my *widge) {
    GtkCssProvider *provider = gtk_css_provider_new ();

    gtk_css_provider_load_from_path (provider, "src/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(provider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_set_name(widge->sign_in, "sign_in");
    gtk_widget_set_name(widge->window, "window");
    gtk_widget_set_name(widge->win_sign, "win_sign");
}
