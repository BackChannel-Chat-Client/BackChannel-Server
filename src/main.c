#include "main.h"

int main(size_t argc, char** argv)
{
	BC_STATUS bcResult = 0;
	P_BC_CONTEXT context = NULL;
	P_BC_CHANNEL chan = NULL;

	/*
		Default port is 3090, change with argv
	*/
	unsigned short port = 3090;

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
	bcResult = BcCtxInit(&context, 10);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to initialize context");

	/*
		Register example channel
		TODO: Register channels based on config file
	*/
	bcResult = BcChanRegisterChannel(context, "ExampleChannel", 500, &chan);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to register channel");

	/*
		Initialize network library
	*/
	bcResult = BcInitializeNet();
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to initialize network");

	/*
		Begin handling new connections
	*/
	bcResult = BcHandleNewConnections(port);
	if (bcResult != BC_SUCCESS)
		BcFatalError("Failed to handle connections");

	return 0;
}