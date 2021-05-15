#include "main.h"

int main(size_t argc, char** argv)
{
	BC_STATUS bcResult = 0;
	BC_CONNECTION bcConnection = { 0 };

	/*
		Default port is 3090, change with argv
	*/
	unsigned short port = 3090;

	if (argc == 2)
	{
		port = strtoul(argv[1], NULL, 0);
	}

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