#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "common.h"
#include "networking.h"

__forceinline void BcTlsInitOpenssl()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

__forceinline void BcTlsCleanupOpenssl()
{
    EVP_cleanup();
}

BC_STATUS BcTlsCreateContext(SSL_CTX** tls_context);

BC_STATUS BcTlsConfigureContext(SSL_CTX* tls_context);

BC_STATUS BcTlsLoadX509Certificates(SSL_CTX* tls_context, char* cert_path, char* key_path);

BC_STATUS BcTlsDebugShowClientX509Certificate(P_BC_CONNECTION conn);

BC_STATUS BcTlsInitializeConnection(SSL_CTX* tls_context, P_BC_CONNECTION conn);

BC_STATUS BcTlsSockSend(P_BC_CONNECTION conn, char* data, size_t data_size, int* bytes_written);

BC_STATUS BcTlsSockRecv(P_BC_CONNECTION conn, char* buffer, size_t buffer_size, int* bytes_received);