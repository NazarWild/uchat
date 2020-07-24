#include "../inc/uchat.h"

void mx_send_message(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;
    char *str; //строка которую отправляем Лехе
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widge->command_line)); //считываем данные с ввода

    if (strlen(message) == 0) { //если пустая строка, ничего не делать
        printf("Are you kidding me?\n");
    }
    else {
        mx_message_to(widge, message);
        asprintf(&str, "{\"IF_MESS\":true,\"TO\":\"%s\",\"MESS\":\"%s\",\"TYPE\":\"text\",\"CHAT_ID\":\"1\"}\n", widge->to, message);
        //write(1, str, strlen(str));
        write(widge->sockfd, str, strlen(str)); //отпрвляем Лехе данные
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
        free(str);
    }
}
