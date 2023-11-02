#include "gwaez_shell.gwaez_h"

/**
 **gwaez__strncpy - gwaez_copies gwaez_a gwaez_string
 *@gwaez_dest: gwaez_the gwaez_destination gwaez_string gwaez_to gwaez_be gwaez_copied gwaez_to
 *@gwaez_src: gwaez_the gwaez_source gwaez_string
 *@gwaez_n: gwaez_the gwaez_amount gwaez_of gwaez_characters gwaez_to gwaez_be gwaez_copied
 *gwaez_Return: gwaez_the gwaez_concatenated gwaez_string
 */
char *gwaez__strncpy(char *gwaez_dest, char *gwaez_src, int gwaez_n)
{
	int gwaez_i, gwaez_j;
	char *gwaez_s = gwaez_dest;

	gwaez_i = 0;
	while (gwaez_src[gwaez_i] != '\0' && gwaez_i < gwaez_n - 1)
	{
		gwaez_dest[gwaez_i] = gwaez_src[gwaez_i];
		gwaez_i++;
	}
	if (gwaez_i < gwaez_n)
	{
		gwaez_j = gwaez_i;
		while (gwaez_j < gwaez_n)
		{
			gwaez_dest[gwaez_j] = '\0';
			gwaez_j++;
		}
	}
	return (gwaez_s);
}

/**
 **gwaez__strncat - gwaez_concatenates gwaez_two gwaez_strings
 *@gwaez_dest: gwaez_the gwaez_first gwaez_string
 *@gwaez_src: gwaez_the gwaez_second gwaez_string
 *@gwaez_n: gwaez_the gwaez_amount gwaez_of gwaez_bytes gwaez_to gwaez_be gwaez_maximally gwaez_used
 *gwaez_Return: gwaez_the gwaez_concatenated gwaez_string
 */
char *gwaez__strncat(char *gwaez_dest, char *gwaez_src, int gwaez_n)
{
	int gwaez_i, gwaez_j;
	char *gwaez_s = gwaez_dest;

	gwaez_i = 0;
	gwaez_j = 0;
	while (gwaez_dest[gwaez_i] != '\0')
		gwaez_i++;
	while (gwaez_src[gwaez_j] != '\0' && gwaez_j < gwaez_n)
	{
		gwaez_dest[gwaez_i] = gwaez_src[gwaez_j];
		gwaez_i++;
		gwaez_j++;
	}
	if (gwaez_j < gwaez_n)
		gwaez_dest[gwaez_i] = '\0';
	return (gwaez_s);
}

/**
 **gwaez__strchr - gwaez_locates gwaez_a gwaez_character gwaez_in gwaez_a gwaez_string
 *@gwaez_s: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_parsed
 *@gwaez_c: gwaez_the gwaez_character gwaez_to gwaez_look for
 *gwaez_Return: (gwaez_s) gwaez_a gwaez_pointer gwaez_to gwaez_the gwaez_memory gwaez_area gwaez_s
 */
char *gwaez__strchr(char *gwaez_s, char gwaez_c)
{
	do {
		if (*gwaez_s == gwaez_c)
			return (gwaez_s);
	} while (*gwaez_s++ != '\0');

	return (gwaez_NULL);
}

