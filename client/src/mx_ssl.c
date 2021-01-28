#include "../inc/uchat.h"

// void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile) {
//     /* set the local certificate from CertFile */
//     if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0) {
//         ERR_print_errors_fp(stderr);
//     }
//     /* set the private key from KeyFile (may be the same as CertFile) */
//     if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0) {
//         ERR_print_errors_fp(stderr);
//     }
//     /* verify private key */
//     if (!SSL_CTX_check_private_key(ctx)) {
//         fprintf(stderr, "Private key does not match the public certificate\n");
//     }
// }
void ShowCerts(SSL* ssl) {
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if (cert != NULL) {
        // printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        // printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        // printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("Info: No client certificates configured.\n");
}

SSL_CTX* InitCTX(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */
    SSL_load_error_strings(); /* Bring in and register error messages */
    method = TLS_client_method();/* Create new client-method instance */
    ctx = SSL_CTX_new(method); /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

SSL *mx_ssl(int fd) {
    SSL_CTX *ctx;
    SSL *ssl;

    SSL_library_init();
    ctx = InitCTX();
    // LoadCertificates(ctx, "keys/client/client_cert.pem", "keys/client/private/client_key.pem");
    ssl = SSL_new(ctx); /* create new SSL connection state */
    SSL_set_fd(ssl, fd); /* attach the socket descriptor */
    if (SSL_connect(ssl) == -1) {/* perform the connection */
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    ShowCerts(ssl);
    return ssl;
}
