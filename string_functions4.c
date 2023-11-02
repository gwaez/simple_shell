#include "gwaez_shell.gwaez_h"

/**
 * **gwaez_strtow - gwaez_splits gwaez_a gwaez_string gwaez_into gwaez_words. gwaez_Repeat gwaez_delimiters gwaez_are gwaez_ignored
 * @gwaez_str: gwaez_the gwaez_input gwaez_string
 * @gwaez_d: gwaez_the gwaez_delimeter gwaez_string
 * gwaez_Return: gwaez_a gwaez_pointer gwaez_to gwaez_an gwaez_array gwaez_of gwaez_strings, gwaez_or gwaez_NULL gwaez_on gwaez_failure
 */

char **gwaez_strtow(char *gwaez_str, char *gwaez_d)
{
	int gwaez_i, gwaez_j, gwaez_k, gwaez_m, gwaez_numwords = 0;
	char **gwaez_s;

	if (gwaez_str == gwaez_NULL || gwaez_str[0] == 0)
		return (gwaez_NULL);
	if (!gwaez_d)
		gwaez_d = " ";
	for (gwaez_i = 0; gwaez_str[gwaez_i] != '\0'; gwaez_i++)
		if (!gwaez_is_delim(gwaez_str[gwaez_i], gwaez_d) && (gwaez_is_delim(gwaez_str[gwaez_i + 1], gwaez_d) || !gwaez_str[gwaez_i + 1]))
			gwaez_numwords++;

	if (gwaez_numwords == 0)
		return (gwaez_NULL);
	gwaez_s = gwaez_malloc((1 + gwaez_numwords) * sizeof(char *));
	if (!gwaez_s)
		return (gwaez_NULL);
	for (gwaez_i = 0, gwaez_j = 0; gwaez_j < gwaez_numwords; gwaez_j++)
	{
		while (gwaez_is_delim(gwaez_str[gwaez_i], gwaez_d))
			gwaez_i++;
		gwaez_k = 0;
		while (!gwaez_is_delim(gwaez_str[gwaez_i + gwaez_k], gwaez_d) && gwaez_str[gwaez_i + gwaez_k])
			gwaez_k++;
		gwaez_s[gwaez_j] = gwaez_malloc((gwaez_k + 1) * sizeof(char));
		if (!gwaez_s[gwaez_j])
		{
			for (gwaez_k = 0; gwaez_k < gwaez_j; gwaez_k++)
				gwaez_free(gwaez_s[gwaez_k]);
			gwaez_free(gwaez_s);
			return (gwaez_NULL);
		}
		for (gwaez_m = 0; gwaez_m < gwaez_k; gwaez_m++)
			gwaez_s[gwaez_j][gwaez_m] = gwaez_str[gwaez_i++];
		gwaez_s[gwaez_j][gwaez_m] = 0;
	}
	gwaez_s[gwaez_j] = gwaez_NULL;
	return (gwaez_s);
}

/**
 * **gwaez_strtow2 - gwaez_splits gwaez_a gwaez_string gwaez_into gwaez_words
 * @gwaez_str: gwaez_the gwaez_input gwaez_string
 * @gwaez_d: gwaez_the gwaez_delimeter
 * gwaez_Return: gwaez_a gwaez_pointer gwaez_to gwaez_an gwaez_array gwaez_of gwaez_strings, gwaez_or gwaez_NULL gwaez_on gwaez_failure
 */
char **gwaez_strtow2(char *gwaez_str, char gwaez_d)
{
	int gwaez_i, gwaez_j, gwaez_k, gwaez_m, gwaez_numwords = 0;
	char **gwaez_s;

	if (gwaez_str == gwaez_NULL || gwaez_str[0] == 0)
		return (gwaez_NULL);
	for (gwaez_i = 0; gwaez_str[gwaez_i] != '\0'; gwaez_i++)
		if ((gwaez_str[gwaez_i] != gwaez_d && gwaez_str[gwaez_i + 1] == gwaez_d) ||
		    (gwaez_str[gwaez_i] != gwaez_d && !gwaez_str[gwaez_i + 1]) || gwaez_str[gwaez_i + 1] == gwaez_d)
			gwaez_numwords++;
	if (gwaez_numwords == 0)
		return (gwaez_NULL);
	gwaez_s = gwaez_malloc((1 + gwaez_numwords) * sizeof(char *));
	if (!gwaez_s)
		return (gwaez_NULL);
	for (gwaez_i = 0, gwaez_j = 0; gwaez_j < gwaez_numwords; gwaez_j++)
	{
		while (gwaez_str[gwaez_i] == gwaez_d && gwaez_str[gwaez_i] != gwaez_d)
			gwaez_i++;
		gwaez_k = 0;
		while (gwaez_str[gwaez_i + gwaez_k] != gwaez_d && gwaez_str[gwaez_i + gwaez_k] && gwaez_str[gwaez_i + gwaez_k] != gwaez_d)
			gwaez_k++;
		gwaez_s[gwaez_j] = gwaez_malloc((gwaez_k + 1) * sizeof(char));
		if (!gwaez_s[gwaez_j])
		{
			for (gwaez_k = 0; gwaez_k < gwaez_j; gwaez_k++)
				gwaez_free(gwaez_s[gwaez_k]);
			gwaez_free(gwaez_s);
			return (gwaez_NULL);
		}
		for (gwaez_m = 0; gwaez_m < gwaez_k; gwaez_m++)
			gwaez_s[gwaez_j][gwaez_m] = gwaez_str[gwaez_i++];
		gwaez_s[gwaez_j][gwaez_m] = 0;
	}
	gwaez_s[gwaez_j] = gwaez_NULL;
	return (gwaez_s);
}

