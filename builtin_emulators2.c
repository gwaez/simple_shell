#include "gwaez_shell.gwaez_h"

/**
 * gwaez__myhistory - gwaez_displays gwaez_the gwaez_history gwaez_list, gwaez_one gwaez_command gwaez_by gwaez_line, gwaez_preceded
 *              gwaez_with gwaez_line gwaez_numbers, gwaez_starting gwaez_at 0.
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *        gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__myhistory(gwaez_info_t *gwaez_info)
{
	gwaez_print_list(gwaez_info->gwaez_history);
	return (0);
}

/**
 * gwaez_unset_alias - gwaez_sets gwaez_alias gwaez_to gwaez_string
 * @gwaez_info: gwaez_parameter struct
 * @gwaez_str: gwaez_the gwaez_string gwaez_alias
 *
 * gwaez_Return: gwaez_Always 0 gwaez_on gwaez_success, 1 gwaez_on gwaez_error
 */
int gwaez_unset_alias(gwaez_info_t *gwaez_info, char *gwaez_str)
{
	char *gwaez_p, gwaez_c;
	int gwaez_ret;

	gwaez_p = gwaez__strchr(gwaez_str, '=');
	if (!gwaez_p)
		return (1);
	gwaez_c = *gwaez_p;
	*gwaez_p = 0;
	gwaez_ret = gwaez_delete_node_at_index(&(gwaez_info->gwaez_alias),
		gwaez_get_node_index(gwaez_info->gwaez_alias, gwaez_node_starts_with(gwaez_info->gwaez_alias, gwaez_str, -1)));
	*gwaez_p = gwaez_c;
	return (gwaez_ret);
}

/**
 * gwaez_set_alias - gwaez_sets gwaez_alias gwaez_to gwaez_string
 * @gwaez_info: gwaez_parameter struct
 * @gwaez_str: gwaez_the gwaez_string gwaez_alias
 *
 * gwaez_Return: gwaez_Always 0 gwaez_on gwaez_success, 1 gwaez_on gwaez_error
 */
int gwaez_set_alias(gwaez_info_t *gwaez_info, char *gwaez_str)
{
	char *gwaez_p;

	gwaez_p = gwaez__strchr(gwaez_str, '=');
	if (!gwaez_p)
		return (1);
	if (!*++gwaez_p)
		return (gwaez_unset_alias(gwaez_info, gwaez_str));

	gwaez_unset_alias(gwaez_info, gwaez_str);
	return (gwaez_add_node_end(&(gwaez_info->gwaez_alias), gwaez_str, 0) == gwaez_NULL);
}

/**
 * gwaez_print_alias - gwaez_prints gwaez_an gwaez_alias gwaez_string
 * @gwaez_node: gwaez_the gwaez_alias gwaez_node
 *
 * gwaez_Return: gwaez_Always 0 gwaez_on gwaez_success, 1 gwaez_on gwaez_error
 */
int gwaez_print_alias(gwaez_list_t *gwaez_node)
{
	char *gwaez_p = gwaez_NULL, *gwaez_a = gwaez_NULL;

	if (gwaez_node)
	{
		gwaez_p = gwaez__strchr(gwaez_node->gwaez_str, '=');
		for (gwaez_a = gwaez_node->gwaez_str; gwaez_a <= gwaez_p; gwaez_a++)
			gwaez__putchar(*gwaez_a);
		gwaez__putchar('\'');
		gwaez__puts(gwaez_p + 1);
		gwaez__puts("'\gwaez_n");
		return (0);
	}
	return (1);
}

/**
 * gwaez__myalias - gwaez_mimics gwaez_the gwaez_alias gwaez_builtin (gwaez_man gwaez_alias)
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__myalias(gwaez_info_t *gwaez_info)
{
	int gwaez_i = 0;
	char *gwaez_p = gwaez_NULL;
	gwaez_list_t *gwaez_node = gwaez_NULL;

	if (gwaez_info->gwaez_argc == 1)
	{
		gwaez_node = gwaez_info->gwaez_alias;
		while (gwaez_node)
		{
			gwaez_print_alias(gwaez_node);
			gwaez_node = gwaez_node->gwaez_next;
		}
		return (0);
	}
	for (gwaez_i = 1; gwaez_info->gwaez_argv[gwaez_i]; gwaez_i++)
	{
		gwaez_p = gwaez__strchr(gwaez_info->gwaez_argv[gwaez_i], '=');
		if (gwaez_p)
			gwaez_set_alias(gwaez_info, gwaez_info->gwaez_argv[gwaez_i]);
		else
			gwaez_print_alias(gwaez_node_starts_with(gwaez_info->gwaez_alias, gwaez_info->gwaez_argv[gwaez_i], '='));
	}

	return (0);
}

