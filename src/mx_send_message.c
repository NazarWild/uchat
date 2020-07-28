#include "../inc/uchat.h"

void mx_send_message(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;
    char *str; //строка которую отправляем Лехе
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widge->command_line)); //считываем данные с ввода

    if (strlen(message) == 0) { //если пустая строка, ничего не делать
        printf("Are you kidding me?\n");
    }
    else {
        if (strcmp(widge->to, "PAPA_BOT") == 0)
            widge->login_list = strdup("Papa BOT");
        else
            widge->login_list = strdup(mx_find_login_by_id(widge->login_id, widge->to));
        printf("login_list == %s widge->to == %s\n", widge->login_list, widge->to);
        mx_message_to(widge, message);
        mx_set_cur_chat_id(widge);
        str = mx_create_json_mess(message, widge);
        write(1, str, strlen(str)); //отпрвляем Лехе данные
        SSL_write(widge->ssl, str, strlen(str)); //отпрвляем Лехе данные
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
    }
}
