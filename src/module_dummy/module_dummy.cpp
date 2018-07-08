#include "../module_base.h"
#include "module_dummy.h"
#include <stdio.h>
#include <stdlib.h>

module_t *module_dummy = NULL;

int module_dummy_alloc()
{
	module_dummy = (module_t *)calloc(1, sizeof(module_t));
	if (!module_dummy)
	{
		printf("%s->%d: malloc module_dummy structor was failed\n");
		return MODULE_FALSE;
	}
	return 0;
}

int module_dummy_free()
{
	if (module_dummy)
	{
		free(module_dummy);
		module_dummy = NULL;
	}
	return 0;
}