#include "linked_list.h"

BC_STATUS BcLinkedListInit(P_BC_LINKED_LIST linked_list)
{
	if (!linked_list)
		return BC_INVALID_PARAM;

	linked_list = malloc(sizeof(*linked_list));
	if (!linked_list)
		BcFatalError("Failed to malloc");

	linked_list->data = NULL;
	linked_list->next = NULL;

	return BC_SUCCESS;
}

BC_STATUS BcLinkedListAppend(P_BC_LINKED_LIST linked_list, void* data)
{
	BC_UNREFERENCED_PARAMETER(linked_list);
	BC_UNREFERENCED_PARAMETER(data);

	/* Unimplemented for now */

	return BC_UNIMPLEMENTED;
}