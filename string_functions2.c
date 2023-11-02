#include "gwaez_shell.gwaez_h"

/**
 * gwaez__strcpy - gwaez_copies gwaez_a gwaez_string
 * @gwaez_dest: gwaez_the gwaez_destination
 * @gwaez_src: gwaez_the gwaez_source
 *
 * gwaez_Return: gwaez_pointer gwaez_to gwaez_destination
 */
char *gwaez__strcpy(char *gwaez_dest, char *gwaez_src)
{
	int gwaez_i = 0;

	if (gwaez_dest == gwaez_src || gwaez_src == 0)
		return (gwaez_dest);
	while (gwaez_src[gwaez_i])
	{
		gwaez_dest[gwaez_i] = gwaez_src[gwaez_i];
		gwaez_i++;
	}
	gwaez_dest[gwaez_i] = 0;
	return (gwaez_dest);
}

/**
 * gwaez__strdup - gwaez_duplicates gwaez_a gwaez_string
 * @gwaez_str: gwaez_the gwaez_string gwaez_to gwaez_duplicate
 *
 * gwaez_Return: gwaez_pointer gwaez_to gwaez_the gwaez_duplicated gwaez_string
 */
char *gwaez__strdup(const char *gwaez_str)
{
	int gwaez_length = 0;
	char *gwaez_ret;

	if (gwaez_str == gwaez_NULL)
		return (gwaez_NULL);
	while (*gwaez_str++)
		gwaez_length++;
	gwaez_ret = gwaez_malloc(sizeof(char) * (gwaez_length + 1));
	if (!gwaez_ret)
		return (gwaez_NULL);
	for (gwaez_length++; gwaez_length--;)
		gwaez_ret[gwaez_length] = *--gwaez_str;
	return (gwaez_ret);
}

/**
 *gwaez__puts - gwaez_prints gwaez_an gwaez_input gwaez_string
 *@gwaez_str: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_printed
 *
 * gwaez_Return: gwaez_Nothing
 */
void gwaez__puts(char *gwaez_str)
{
	int gwaez_i = 0;

	if (!gwaez_str)
		return;
	while (gwaez_str[gwaez_i] != '\0')
	{
		gwaez__putchar(gwaez_str[gwaez_i]);
		gwaez_i++;
	}
}

/**
 * gwaez__putchar - gwaez_writes gwaez_the gwaez_character gwaez_c gwaez_to gwaez_stdout
 * @gwaez_c: gwaez_The gwaez_character gwaez_to gwaez_print
 *
 * gwaez_Return: gwaez_On gwaez_success 1.
 * gwaez_On gwaez_error, -1 gwaez_is gwaez_returned, gwaez_and gwaez_errno gwaez_is gwaez_set gwaez_appropriately.
 */
int gwaez__putchar(char gwaez_c)
{
	static int gwaez_i;
	static char gwaez_buf[gwaez_WRITE_BUF_SIZE];

	if (gwaez_c == gwaez_BUF_FLUSH || gwaez_i >= gwaez_WRITE_BUF_SIZE)
	{
		gwaez_write(1, gwaez_buf, gwaez_i);
		gwaez_i = 0;
	}
	if (gwaez_c != gwaez_BUF_FLUSH)
		gwaez_buf[gwaez_i++] = gwaez_c;
	return (1);
}

