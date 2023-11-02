#include "gwaez_shell.gwaez_h"

/**
 * gwaez_interactive - gwaez_returns gwaez_true if gwaez_shell gwaez_is gwaez_interactive gwaez_mode
 * @gwaez_info: struct gwaez_address
 *
 * gwaez_Return: 1 if gwaez_interactive gwaez_mode, 0 gwaez_otherwise
 */
int gwaez_interactive(gwaez_info_t *gwaez_info)
{
	return (gwaez_isatty(gwaez_STDIN_FILENO) && gwaez_info->gwaez_readfd <= 2);
}

/**
 * gwaez_is_delim - gwaez_checks if gwaez_character gwaez_is gwaez_a gwaez_delimeter
 * @gwaez_c: gwaez_the char gwaez_to gwaez_check
 * @gwaez_delim: gwaez_the gwaez_delimeter gwaez_string
 * gwaez_Return: 1 if gwaez_true, 0 if gwaez_false
 */
int gwaez_is_delim(char gwaez_c, char *gwaez_delim)
{
	while (*gwaez_delim)
		if (*gwaez_delim++ == gwaez_c)
			return (1);
	return (0);
}

/**
 *gwaez__isalpha - gwaez_checks for gwaez_alphabetic gwaez_character
 *@gwaez_c: gwaez_The gwaez_character gwaez_to gwaez_input
 *gwaez_Return: 1 if gwaez_c gwaez_is gwaez_alphabetic, 0 gwaez_otherwise
 */

int gwaez__isalpha(int gwaez_c)
{
	if ((gwaez_c >= 'gwaez_a' && gwaez_c <= 'gwaez_z') || (gwaez_c >= 'gwaez_A' && gwaez_c <= 'gwaez_Z'))
		return (1);
	else
		return (0);
}

/**
 *gwaez__atoi - gwaez_converts gwaez_a gwaez_string gwaez_to gwaez_an gwaez_integer
 *@gwaez_s: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_converted
 *gwaez_Return: 0 if gwaez_no gwaez_numbers gwaez_in gwaez_string, gwaez_converted gwaez_number gwaez_otherwise
 */

int gwaez__atoi(char *gwaez_s)
{
	int gwaez_i, gwaez_sign = 1, gwaez_flag = 0, gwaez_output;
	unsigned int gwaez_result = 0;

	for (gwaez_i = 0;  gwaez_s[gwaez_i] != '\0' && gwaez_flag != 2; gwaez_i++)
	{
		if (gwaez_s[gwaez_i] == '-')
			gwaez_sign *= -1;

		if (gwaez_s[gwaez_i] >= '0' && gwaez_s[gwaez_i] <= '9')
		{
			gwaez_flag = 1;
			gwaez_result *= 10;
			gwaez_result += (gwaez_s[gwaez_i] - '0');
		}
		else if (gwaez_flag == 1)
			gwaez_flag = 2;
	}

	if (gwaez_sign == -1)
		gwaez_output = -gwaez_result;
	else
		gwaez_output = gwaez_result;

	return (gwaez_output);
}

