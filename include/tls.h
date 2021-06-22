#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "common.h"
#include "networking.h"

/* There has to be a better way to do this */
typedef struct _BC_CONNECTION* P_BC_CONNECTION;

__forceinline void BcTlsInitOpenssl(void)
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

__forceinline void BcTlsCleanupOpenssl(void)
{
    EVP_cleanup();
}

BC_STATUS BcTlsCreateContext(SSL_CTX** tls_context);

BC_STATUS BcTlsConfigureContext(SSL_CTX* tls_context);

BC_STATUS BcTlsLoadX509Certificates(SSL_CTX* tls_context, char* cert_path, char* key_path);

BC_STATUS BcTlsDebugShowClientX509Certificate(P_BC_CONNECTION conn);

BC_STATUS BcTlsInitializeConnection(SSL_CTX* tls_context, P_BC_CONNECTION conn);

BC_STATUS BcTlsSockSend(P_BC_CONNECTION conn, char* data, int data_size, int* bytes_written);

BC_STATUS BcTlsSockRecv(P_BC_CONNECTION conn, char* buffer, int buffer_size, int* bytes_received);