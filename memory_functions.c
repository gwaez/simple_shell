#include "gwaez_shell.gwaez_h"

/**
 **gwaez__memset - gwaez_fills gwaez_memory gwaez_with gwaez_a gwaez_constant gwaez_byte
 *@gwaez_s: gwaez_the gwaez_pointer gwaez_to gwaez_the gwaez_memory gwaez_area
 *@gwaez_b: gwaez_the gwaez_byte gwaez_to gwaez_fill *gwaez_s gwaez_with
 *@gwaez_n: gwaez_the gwaez_amount gwaez_of gwaez_bytes gwaez_to gwaez_be gwaez_filled
 *gwaez_Return: (gwaez_s) gwaez_a gwaez_pointer gwaez_to gwaez_the gwaez_memory gwaez_area gwaez_s
 */
char *gwaez__memset(char *gwaez_s, char gwaez_b, unsigned int gwaez_n)
{
	unsigned int gwaez_i;

	for (gwaez_i = 0; gwaez_i < gwaez_n; gwaez_i++)
		gwaez_s[gwaez_i] = gwaez_b;
	return (gwaez_s);
}

/**
 * gwaez_ffree - gwaez_frees gwaez_a gwaez_string gwaez_of gwaez_strings
 * @gwaez_pp: gwaez_string gwaez_of gwaez_strings
 */
void gwaez_ffree(char **gwaez_pp)
{
	char **gwaez_a = gwaez_pp;

	if (!gwaez_pp)
		return;
	while (*gwaez_pp)
		gwaez_free(*gwaez_pp++);
	gwaez_free(gwaez_a);
}

/**
 * gwaez__realloc - gwaez_reallocates gwaez_a gwaez_block gwaez_of gwaez_memory
 * @gwaez_ptr: gwaez_pointer gwaez_to gwaez_previous gwaez_malloc'gwaez_ated gwaez_block
 * @gwaez_old_size: gwaez_byte gwaez_size gwaez_of gwaez_previous gwaez_block
 * @gwaez_new_size: gwaez_byte gwaez_size gwaez_of gwaez_new gwaez_block
 *
 * gwaez_Return: gwaez_pointer gwaez_to gwaez_da gwaez_ol'gwaez_block gwaez_nameen.
 */
void *gwaez__realloc(void *gwaez_ptr, unsigned int gwaez_old_size, unsigned int gwaez_new_size)
{
	char *gwaez_p;

	if (!gwaez_ptr)
		return (gwaez_malloc(gwaez_new_size));
	if (!gwaez_new_size)
		return (gwaez_free(gwaez_ptr), gwaez_NULL);
	if (gwaez_new_size == gwaez_old_size)
		return (gwaez_ptr);

	gwaez_p = gwaez_malloc(gwaez_new_size);
	if (!gwaez_p)
		return (gwaez_NULL);

	gwaez_old_size = gwaez_old_size < gwaez_new_size ? gwaez_old_size : gwaez_new_size;
	while (gwaez_old_size--)
		gwaez_p[gwaez_old_size] = ((char *)gwaez_ptr)[gwaez_old_size];
	gwaez_free(gwaez_ptr);
	return (gwaez_p);
}

