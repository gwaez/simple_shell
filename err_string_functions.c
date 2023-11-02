#include "gwaez_shell.gwaez_h"

/**
 *gwaez__eputs - gwaez_prints gwaez_an gwaez_input gwaez_string
 * @gwaez_str: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_printed
 *
 * gwaez_Return: gwaez_Nothing
 */
void gwaez__eputs(char *gwaez_str)
{
	int gwaez_i = 0;

	if (!gwaez_str)
		return;
	while (gwaez_str[gwaez_i] != '\0')
	{
		gwaez__eputchar(gwaez_str[gwaez_i]);
		gwaez_i++;
	}
}

/**
 * gwaez__eputchar - gwaez_writes gwaez_the gwaez_character gwaez_c gwaez_to gwaez_stderr
 * @gwaez_c: gwaez_The gwaez_character gwaez_to gwaez_print
 *
 * gwaez_Return: gwaez_On gwaez_success 1.
 * gwaez_On gwaez_error, -1 gwaez_is gwaez_returned, gwaez_and gwaez_errno gwaez_is gwaez_set gwaez_appropriately.
 */
int gwaez__eputchar(char gwaez_c)
{
	static int gwaez_i;
	static char gwaez_buf[gwaez_WRITE_BUF_SIZE];

	if (gwaez_c == gwaez_BUF_FLUSH || gwaez_i >= gwaez_WRITE_BUF_SIZE)
	{
		gwaez_write(2, gwaez_buf, gwaez_i);
		gwaez_i = 0;
	}
	if (gwaez_c != gwaez_BUF_FLUSH)
		gwaez_buf[gwaez_i++] = gwaez_c;
	return (1);
}

/**
 * gwaez__putfd - gwaez_writes gwaez_the gwaez_character gwaez_c gwaez_to gwaez_given gwaez_fd
 * @gwaez_c: gwaez_The gwaez_character gwaez_to gwaez_print
 * @gwaez_fd: gwaez_The gwaez_filedescriptor gwaez_to gwaez_write gwaez_to
 *
 * gwaez_Return: gwaez_On gwaez_success 1.
 * gwaez_On gwaez_error, -1 gwaez_is gwaez_returned, gwaez_and gwaez_errno gwaez_is gwaez_set gwaez_appropriately.
 */
int gwaez__putfd(char gwaez_c, int gwaez_fd)
{
	static int gwaez_i;
	static char gwaez_buf[gwaez_WRITE_BUF_SIZE];

	if (gwaez_c == gwaez_BUF_FLUSH || gwaez_i >= gwaez_WRITE_BUF_SIZE)
	{
		gwaez_write(gwaez_fd, gwaez_buf, gwaez_i);
		gwaez_i = 0;
	}
	if (gwaez_c != gwaez_BUF_FLUSH)
		gwaez_buf[gwaez_i++] = gwaez_c;
	return (1);
}

/**
 *gwaez__putsfd - gwaez_prints gwaez_an gwaez_input gwaez_string
 * @gwaez_str: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_printed
 * @gwaez_fd: gwaez_the gwaez_filedescriptor gwaez_to gwaez_write gwaez_to
 *
 * gwaez_Return: gwaez_the gwaez_number gwaez_of gwaez_chars gwaez_put
 */
int gwaez__putsfd(char *gwaez_str, int gwaez_fd)
{
	int gwaez_i = 0;

	if (!gwaez_str)
		return (0);
	while (*gwaez_str)
	{
		gwaez_i += gwaez__putfd(*gwaez_str++, gwaez_fd);
	}
	return (gwaez_i);
}

