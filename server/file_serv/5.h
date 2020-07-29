#ifndef LIBMX_H
#define LIBMX_H

#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <malloc/malloc.h>

void mx_printint(int n);
void mx_del_intarr(int ***arr, int size);
void mx_print_unicode(wchar_t c);
void mx_print_strarr(char **arr, const char *delim);
void mx_printchar(char c);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
void mx_str_reverse(char *s);
void mx_printstr(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_foreach(int *arr, int size, void (*f)(int));
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len);
void *mx_realloc(void *ptr, size_t size);
void mx_printerr(const char *s);
void mx_del_intarr(int ***arr, int size);
int mx_memcmp(const void *s1, const void *s2, size_t n);
int mx_strlen(const char *s);
int mx_strcmp(const char *s1, const char *s2);
int mx_sqrt(int x);
int mx_arrlen(char **str);
int mx_is_alpha(char c);
int mx_isdigit(char c);
int mx_is_space(char c);
int mx_get_char_index(const char *str, char c);
int mx_bubble_sort(char **arr, int size);
int mx_strncmp(const char *s1, const char *s2, int n);
int mx_is_space(char c);
int mx_atoi(const char *str);
int mx_isdigit(char c);
int mx_is_space(char c);
int mx_count_words(const char *str, char c);
int mx_get_substr_index(const char *str, const char *sub);
int mx_skip_substr_index(const char *str, const char *sub, int counter);
int mx_count_substr(const char *str, const char *sub);
int mx_binary_search(char **arr, int size, const char *s, int *count);
double mx_pow(double n, unsigned int pow);
char *mx_itoa(int number);
char *mx_file_to_str(const char *file);
char *mx_strstr(const char *haystack, const char *needle);
char *mx_nbr_to_hex(unsigned long nbr);
char *mx_strnew(const int size);
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strtrim(const char *str);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);
char *mx_ultra_strtrim(const char *str, char c);
char *mx_del_extra_spaces(const char *str);
char *mx_ultra_del_extra_spaces(const char *str, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_replace_substr(const char *str, const char *sub, const char *replace);
char **mx_strsplit(const char *s, char c);
unsigned long   mx_hex_to_nbr(const char *hex);

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

t_list *mx_create_node(void *data);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));
int mx_list_size(t_list *list);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);

#endif
