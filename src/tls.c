#include "tls.h"

#ifdef _WIN32
#include <openssl/applink.c>
#endif

void BcTlsInitOpenssl(void)
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void BcTlsCleanupOpenssl(void)
{
    EVP_cleanup();
}

BC_STATUS BcTlsCreateContext(SSL_CTX** tls_context)
{
	SSL_METHOD* method;
	SSL_CTX* ctx;

	if (!tls_context)
		return BC_INVALID_PARAM;
	
	method = (SSL_METHOD*)TLS_server_method();  /* create new server-method instance */
	ctx = SSL_CTX_new(method);   /* create new context from method */
	if (ctx == NULL)
	{
		ERR_print_errors_fp(stderr);
		return BC_TLS_ERROR;
	}

	*tls_context = ctx;

	return BC_SUCCESS;
}

BC_STATUS BcTlsConfigureContext(SSL_CTX* tls_context)
{
	BC_UNREFERENCED_PARAMETER(tls_context);

	return BC_UNIMPLEMENTED;
}

BC_STATUS BcTlsLoadX509Certificates(SSL_CTX* tls_context, char* cert_path, char* key_path)
{
	if (!tls_context || !cert_path || !key_path)
		return BC_INVALID_PARAM;
	
	/* 
		Set the local certificate from cert_path 
	*/
	if (SSL_CTX_use_certificate_file(tls_context, cert_path, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		return BC_TLS_ERROR;
	}
	/* 
		Set the private key from key_path (may be the same as cert_path) 
	*/
	if (SSL_CTX_use_PrivateKey_file(tls_context, key_path, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		return BC_TLS_ERROR;
	}

	/* 
		Verify private key 
	*/
	if (!SSL_CTX_check_private_key(tls_context))
	{
		BcError("Private key does not match the public certificate\n");
		return BC_TLS_KEY_MISMATCH;
	}

	return BC_SUCCESS;
}

BC_STATUS BcTlsDebugShowClientX509Certificate(P_BC_CONNECTION conn)
{
	X509* cert;
	char* line;
	
	if (!conn)
		return BC_INVALID_PARAM;

	if (!conn->ssl_state)
		return BC_TLS_NOT_CONNECTED;

	/*
		Get client certificate
	*/
	cert = SSL_get_peer_certificate(conn->ssl_state);
	if (cert != NULL)
	{
		BcLog("Server certificates:\n");
		
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("Subject: %s\n", line);
		free(line);
		
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		printf("Issuer: %s\n", line);
		free(line);
		
		X509_free(cert);
	}
	else
		BcLog("No certificates.\n");

	return BC_SUCCESS;
}

BC_STATUS BcTlsInitializeConnection(SSL_CTX* tls_context, P_BC_CONNECTION conn)
{
	SSL* ssl = NULL;

	if (!tls_context || !conn)
		return BC_INVALID_PARAM;

	if (!conn->sock)
		return BC_NOT_CONNECTED;

	conn->ssl_state = NULL;
	
	/*
		Create new ssl state
	*/
	ssl = SSL_new(tls_context);

	/*
		Set SSL file descriptor to our open connection
	*/
	SSL_set_fd(ssl, (int)conn->sock);

	/* 
		do SSL-protocol accept 
	*/
	if (SSL_accept(ssl) <= 0)
	{
		ERR_print_errors_fp(stderr);

		return BC_TLS_ERROR;
	}

	conn->ssl_state = ssl;

	return BC_SUCCESS;
}

BC_STATUS BcTlsSockSend(P_BC_CONNECTION conn, char* data, int data_size, int* bytes_written)
{
	int result = 0;
	
	if (!conn || !data)
		return BC_INVALID_PARAM;

	if (!conn->ssl_state)
		return BC_TLS_NOT_CONNECTED;

	/*
		Write data to TLS socket
	*/
	result = SSL_write(conn->ssl_state, data, data_size);
	if (result <= 0)
	{
        ERR_print_errors_fp(stderr);
		return BC_TLS_IO_ERROR;
    }

	if (bytes_written)
		*bytes_written = result;

	return BC_SUCCESS;
}

BC_STATUS BcTlsSockRecv(P_BC_CONNECTION conn, char* buffer, int buffer_size, int* bytes_received)
{
	int result = 0;
	
	if (!conn || !buffer)
		return BC_INVALID_PARAM;

	if (!conn->ssl_state)
		return BC_TLS_NOT_CONNECTED;

	result = SSL_read(conn->ssl_state, buffer, buffer_size);
	if (result <= 0)
	{
        ERR_print_errors_fp(stderr);
		return BC_TLS_IO_ERROR;
    }

	if (bytes_received)
		*bytes_received = result;

	return BC_SUCCESS;
}
