#include "../inc/uchat.h"

void *mx_realloc(void *ptr, size_t size, ssize_t from) {
    void *new_ptr= malloc(size);
    if (new_ptr && ptr)
    {
        memcpy(new_ptr, ptr, from);
        free(ptr);
    }

    return new_ptr;
}
