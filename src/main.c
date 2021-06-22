#include "main.h"

int main(size_t argc, char** argv)
{
	BC_STATUS bcResult = 0;
	P_BC_CONTEXT bc_context = NULL;
	P_BC_CHANNEL chan = NULL;
	SSL_CTX* tls_context = NULL;

	/*
		Default port is 3090, change with argv
	*/
	unsigned short port = 3090;

	/*
		Set port number if specified
		TODO: Make this also read from a config file
	*/
	if (argc == 2)
	{
		/* This is probably fine and not at all dangerous */
		port = (unsigned short)strtoul(argv[1], NULL, 0);

		if (port == 0 || port == ULONG_MAX)
		{
			BcError("Port number invalid, defaulting to 3090");
			port = 3090;
		}
	}

	/*
		Initialize context
	*/
	bcResult = BcCtxInit(&bc_context, 10);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to initialize context");

	/*
		Register example channel
		TODO: Register channels based on config file
	*/
	bcResult = BcChanRegisterChannel(bc_context, "ExampleChannel1", 500, &chan);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to register channel");

	bcResult = BcChanRegisterChannel(bc_context, "ExampleChannel2", 500, &chan);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to register channel");

	bcResult = BcChanRegisterChannel(bc_context, "ExampleChannel3", 500, &chan);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to register channel");

	/*
		Initialize network library
	*/
	bcResult = BcInitializeNet();
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to initialize network");

	/*
		Initialize TLS/OpenSSL library and context
	*/
	BcTlsInitOpenssl();
	bcResult = BcTlsCreateContext(&tls_context);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to initialize TLS context");

	/*
		Load X509 Certificates
	*/
	bcResult = BcTlsLoadX509Certificates(tls_context, "temp_cert.pem", "temp_key.pem");
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to load X509 certificates");

	/*
		Begin handling new connections
	*/
	bcResult = BcHandleNewConnections(bc_context, tls_context, port);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to handle connections");

	return 0;
}