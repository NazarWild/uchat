#include "../inc/uchat.h"

void mx_pop_front_listbox(t_list_box **head) {
    t_list_box *first = *head;
    *head = (*head)->next;
}

void free_list_listbox(t_list_box **head) {
    while(*head)
        mx_pop_front_listbox(head);
}

t_list_box *mx_create_node_listbox(int chat_id, int listbox_id, int user_id) {
    t_list_box *node = (t_list_box *) malloc(sizeof(t_list_box));

    node->user_id = user_id;
    node->chat_id = chat_id;
    node->listbox_id = listbox_id;
    node->next = NULL;  
    return node;
}

void mx_push_back_listbox(t_list_box **list, int chat_id, int listbox_id, int user_id){
    if(*list == NULL) {
        *list = mx_create_node_listbox(chat_id, listbox_id, user_id);
        return;
    }
    t_list_box *copy = *list;

    while(copy->next != NULL) {
        copy = copy->next;
    }
    copy->next = mx_create_node_listbox(chat_id, listbox_id, user_id);
    copy = copy->next;
}