#pragma once

#include <stdlib.h>

#include "common.h"
#include "log.h"

typedef struct _BC_LINKED_LIST
{
	void* data;
	struct _BC_LINKED_LIST *next;
} BC_LINKED_LIST, *P_BC_LINKED_LIST;

BC_STATUS BcLinkedListInit(P_BC_LINKED_LIST linked_list);

BC_STATUS BcLinkedListAppend(P_BC_LINKED_LIST linked_list, void* data);