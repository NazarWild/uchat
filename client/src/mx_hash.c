#include "../inc/uchat.h"

char *mx_hash(char *login, char *pass) {
    unsigned char sha512[SHA512_DIGEST_LENGTH];
    char *hash;

    asprintf(&hash, "%s%s", login, pass);
    SHA512((unsigned char *)hash, strlen(hash), sha512);
    free(hash);
    return mx_hash_to_string(sha512);
}
