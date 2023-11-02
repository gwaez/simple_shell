#include "gwaez_shell.gwaez_h"

/**
 * gwaez__strlen - gwaez_returns gwaez_the gwaez_length gwaez_of gwaez_a gwaez_string
 * @gwaez_s: gwaez_the gwaez_string gwaez_whose gwaez_length gwaez_to gwaez_check
 *
 * gwaez_Return: gwaez_integer gwaez_length gwaez_of gwaez_string
 */
int gwaez__strlen(char *gwaez_s)
{
	int gwaez_i = 0;

	if (!gwaez_s)
		return (0);

	while (*gwaez_s++)
		gwaez_i++;
	return (gwaez_i);
}

/**
 * gwaez__strcmp - gwaez_performs gwaez_lexicogarphic gwaez_comparison gwaez_of gwaez_two gwaez_strangs.
 * @gwaez_s1: gwaez_the gwaez_first gwaez_strang
 * @gwaez_s2: gwaez_the gwaez_second gwaez_strang
 *
 * gwaez_Return: gwaez_negative if gwaez_s1 < gwaez_s2, gwaez_positive if gwaez_s1 > gwaez_s2, gwaez_zero if gwaez_s1 == gwaez_s2
 */
int gwaez__strcmp(char *gwaez_s1, char *gwaez_s2)
{
	while (*gwaez_s1 && *gwaez_s2)
	{
		if (*gwaez_s1 != *gwaez_s2)
			return (*gwaez_s1 - *gwaez_s2);
		gwaez_s1++;
		gwaez_s2++;
	}
	if (*gwaez_s1 == *gwaez_s2)
		return (0);
	else
		return (*gwaez_s1 < *gwaez_s2 ? -1 : 1);
}

/**
 * gwaez_starts_with - gwaez_checks if gwaez_needle gwaez_starts gwaez_with gwaez_haystack
 * @gwaez_haystack: gwaez_string gwaez_to gwaez_search
 * @gwaez_needle: gwaez_the gwaez_substring gwaez_to gwaez_find
 *
 * gwaez_Return: gwaez_address gwaez_of gwaez_next char gwaez_of gwaez_haystack gwaez_or gwaez_NULL
 */
char *gwaez_starts_with(const char *gwaez_haystack, const char *gwaez_needle)
{
	while (*gwaez_needle)
		if (*gwaez_needle++ != *gwaez_haystack++)
			return (gwaez_NULL);
	return ((char *)gwaez_haystack);
}

/**
 * gwaez__strcat - gwaez_concatenates gwaez_two gwaez_strings
 * @gwaez_dest: gwaez_the gwaez_destination gwaez_buffer
 * @gwaez_src: gwaez_the gwaez_source gwaez_buffer
 *
 * gwaez_Return: gwaez_pointer gwaez_to gwaez_destination gwaez_buffer
 */
char *gwaez__strcat(char *gwaez_dest, char *gwaez_src)
{
	char *gwaez_ret = gwaez_dest;

	while (*gwaez_dest)
		gwaez_dest++;
	while (*gwaez_src)
		*gwaez_dest++ = *gwaez_src++;
	*gwaez_dest = *gwaez_src;
	return (gwaez_ret);
}

