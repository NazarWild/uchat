#include "../inc/uchat.h"

static void change_pos(GtkWidget *widget, void *data) {
    static gdouble uper = 0;

    if (uper != gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget))) {
        gtk_adjustment_set_value(GTK_ADJUSTMENT(widget), gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget)));
        uper = gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget));
    }
}

void mx_pop_front_gtk(t_list_gtk **head) {
    t_list_gtk *cur = *head;

    if (cur->next == NULL) {
        free(*head);
        *head = NULL;
    }
    cur = cur->next;
    free(*head);
    *head = cur;
    cur = NULL;
}

t_list_gtk *mx_create_node_gtk(void *data) {
    t_list_gtk *head = NULL;

    head = malloc(sizeof(t_list_gtk));
    if (head == NULL)
        return 0;
    head->data = data;
    head->next = NULL;
    return head;
}

void mx_push_front_gtk(t_list_gtk **list, void *data) {
    t_list_gtk *tmp = *list;

    if (*list == 0) {
        *list = mx_create_node_gtk(data);
        return;
    }
    *list = mx_create_node_gtk(data);
    (*list)->next = tmp;
}


void mx_create_chat(t_page *page, t_widget_my *widge, const gchar *text) {
    widge->page_label = gtk_button_new();

    page->scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(page->scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

    page->list_box = gtk_list_box_new();

    gtk_widget_set_name(page->list_box, "list_box");
    gtk_widget_set_name(page->scroll, "scroll");

    gtk_notebook_insert_page(GTK_NOTEBOOK(widge->notebook), page->scroll, widge->page_label, -1);
    gtk_container_add(GTK_CONTAINER(page->scroll), page->list_box);
    page->slider_adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(page->scroll));

    char *str = strdup(text);
    g_object_set_data(G_OBJECT(page->list_box), "id", (gpointer)(str));

    printf("{%s}; id = [%s]\n", text, (char*)g_object_get_data(G_OBJECT(page->list_box), "id"));

    g_signal_connect(page->slider_adj, "changed", G_CALLBACK(change_pos), NULL);

    gtk_widget_show_all(widge->notebook);
}
