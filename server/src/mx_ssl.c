#include "../inc/uchat.h"

SSL_CTX* mx_initserverctx(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    method = TLS_server_method();  /* create new server-method instance */
    ctx = SSL_CTX_new(method);   /* create new context from method */
    if ( ctx == NULL ) {
        ERR_print_errors_fp(stderr);
    }
    return ctx;
}

void mx_loadcertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile) {
    /* set the local certificate from CertFile */
    if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
        ERR_print_errors_fp(stderr);
    /* set the private key from KeyFile (may be the same as CertFile) */
    if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
        ERR_print_errors_fp(stderr);
    /* verify private key */
    if (!SSL_CTX_check_private_key(ctx) )
        fprintf(stderr, "Private key does not match the public certificate\n");
}

