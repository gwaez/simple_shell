#include "gwaez_shell.gwaez_h"

/**
 * gwaez_bfree - gwaez_frees gwaez_a gwaez_pointer gwaez_and gwaez_NULLs gwaez_the gwaez_address
 * @gwaez_ptr: gwaez_address gwaez_of gwaez_the gwaez_pointer gwaez_to gwaez_free
 *
 * gwaez_Return: 1 if gwaez_freed, gwaez_otherwise 0.
 */
int gwaez_bfree(void **gwaez_ptr)
{
	if (gwaez_ptr && *gwaez_ptr)
	{
		gwaez_free(*gwaez_ptr);
		*gwaez_ptr = gwaez_NULL;
		return (1);
	}
	return (0);
}

