#include "gwaez_shell.gwaez_h"

/**
 * gwaez__erratoi - gwaez_converts gwaez_a gwaez_string gwaez_to gwaez_an gwaez_integer
 * @gwaez_s: gwaez_the gwaez_string gwaez_to gwaez_be gwaez_converted
 * gwaez_Return: 0 if gwaez_no gwaez_numbers gwaez_in gwaez_string, gwaez_converted gwaez_number gwaez_otherwise
 *       -1 gwaez_on gwaez_error
 */
int gwaez__erratoi(char *gwaez_s)
{
	int gwaez_i = 0;
	unsigned long int gwaez_result = 0;

	if (*gwaez_s == '+')
		gwaez_s++;  /* gwaez_TODO: gwaez_why gwaez_does gwaez_this gwaez_make gwaez_main return 255? */
	for (gwaez_i = 0;  gwaez_s[gwaez_i] != '\0'; gwaez_i++)
	{
		if (gwaez_s[gwaez_i] >= '0' && gwaez_s[gwaez_i] <= '9')
		{
			gwaez_result *= 10;
			gwaez_result += (gwaez_s[gwaez_i] - '0');
			if (gwaez_result > gwaez_INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (gwaez_result);
}

/**
 * gwaez_print_error - gwaez_prints gwaez_an gwaez_error gwaez_message
 * @gwaez_info: gwaez_the gwaez_parameter & return gwaez_info struct
 * @gwaez_estr: gwaez_string gwaez_containing gwaez_specified gwaez_error gwaez_type
 * gwaez_Return: 0 if gwaez_no gwaez_numbers gwaez_in gwaez_string, gwaez_converted gwaez_number gwaez_otherwise
 *        -1 gwaez_on gwaez_error
 */
void gwaez_print_error(gwaez_info_t *gwaez_info, char *gwaez_estr)
{
	gwaez__eputs(gwaez_info->gwaez_fname);
	gwaez__eputs(": ");
	gwaez_print_d(gwaez_info->gwaez_line_count, gwaez_STDERR_FILENO);
	gwaez__eputs(": ");
	gwaez__eputs(gwaez_info->gwaez_argv[0]);
	gwaez__eputs(": ");
	gwaez__eputs(gwaez_estr);
}

/**
 * gwaez_print_d - gwaez_function gwaez_prints gwaez_a gwaez_decimal (gwaez_integer) gwaez_number (gwaez_base 10)
 * @gwaez_input: gwaez_the gwaez_input
 * @gwaez_fd: gwaez_the gwaez_filedescriptor gwaez_to gwaez_write gwaez_to
 *
 * gwaez_Return: gwaez_number gwaez_of gwaez_characters gwaez_printed
 */
int gwaez_print_d(int gwaez_input, int gwaez_fd)
{
	int (*gwaez___putchar)(char) = gwaez__putchar;
	int gwaez_i, gwaez_count = 0;
	unsigned int gwaez__abs_, gwaez_current;

	if (gwaez_fd == gwaez_STDERR_FILENO)
		gwaez___putchar = gwaez__eputchar;
	if (gwaez_input < 0)
	{
		gwaez__abs_ = -gwaez_input;
		gwaez___putchar('-');
		gwaez_count++;
	}
	else
		gwaez__abs_ = gwaez_input;
	gwaez_current = gwaez__abs_;
	for (gwaez_i = 1000000000; gwaez_i > 1; gwaez_i /= 10)
	{
		if (gwaez__abs_ / gwaez_i)
		{
			gwaez___putchar('0' + gwaez_current / gwaez_i);
			gwaez_count++;
		}
		gwaez_current %= gwaez_i;
	}
	gwaez___putchar('0' + gwaez_current);
	gwaez_count++;

	return (gwaez_count);
}

/**
 * gwaez_convert_number - gwaez_converter gwaez_function, gwaez_a gwaez_clone gwaez_of gwaez_itoa
 * @gwaez_num: gwaez_number
 * @gwaez_base: gwaez_base
 * @gwaez_flags: gwaez_argument gwaez_flags
 *
 * gwaez_Return: gwaez_string
 */
char *gwaez_convert_number(long int gwaez_num, int gwaez_base, int gwaez_flags)
{
	static char *gwaez_array;
	static char gwaez_buffer[50];
	char gwaez_sign = 0;
	char *gwaez_ptr;
	unsigned long gwaez_n = gwaez_num;

	if (!(gwaez_flags & gwaez_CONVERT_UNSIGNED) && gwaez_num < 0)
	{
		gwaez_n = -gwaez_num;
		gwaez_sign = '-';

	}
	gwaez_array = gwaez_flags & gwaez_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	gwaez_ptr = &gwaez_buffer[49];
	*gwaez_ptr = '\0';

	do	{
		*--gwaez_ptr = gwaez_array[gwaez_n % gwaez_base];
		gwaez_n /= gwaez_base;
	} while (gwaez_n != 0);

	if (gwaez_sign)
		*--gwaez_ptr = gwaez_sign;
	return (gwaez_ptr);
}

/**
 * gwaez_remove_comments - gwaez_function gwaez_replaces gwaez_first gwaez_instance gwaez_of '#' gwaez_with '\0'
 * @gwaez_buf: gwaez_address gwaez_of gwaez_the gwaez_string gwaez_to gwaez_modify
 *
 * gwaez_Return: gwaez_Always 0;
 */
void gwaez_remove_comments(char *gwaez_buf)
{
	int gwaez_i;

	for (gwaez_i = 0; gwaez_buf[gwaez_i] != '\0'; gwaez_i++)
		if (gwaez_buf[gwaez_i] == '#' && (!gwaez_i || gwaez_buf[gwaez_i - 1] == ' '))
		{
			gwaez_buf[gwaez_i] = '\0';
			break;
		}
}

