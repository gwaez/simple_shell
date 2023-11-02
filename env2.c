#include "gwaez_shell.gwaez_h"

/**
 * gwaez_get_environ - gwaez_returns gwaez_the gwaez_string gwaez_array gwaez_copy gwaez_of gwaez_our gwaez_environ
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 * gwaez_Return: gwaez_Always 0
 */
char **gwaez_get_environ(gwaez_info_t *gwaez_info)
{
	if (!gwaez_info->gwaez_environ || gwaez_info->gwaez_env_changed)
	{
		gwaez_info->gwaez_environ = gwaez_list_to_strings(gwaez_info->gwaez_env);
		gwaez_info->gwaez_env_changed = 0;
	}

	return (gwaez_info->gwaez_environ);
}

/**
 * gwaez__unsetenv - gwaez_Remove gwaez_an gwaez_environment gwaez_variable
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *        gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: 1 gwaez_on gwaez_delete, 0 gwaez_otherwise
 * @gwaez_var: gwaez_the gwaez_string gwaez_env gwaez_var gwaez_property
 */
int gwaez__unsetenv(gwaez_info_t *gwaez_info, char *gwaez_var)
{
	gwaez_list_t *gwaez_node = gwaez_info->gwaez_env;
	gwaez_size_t gwaez_i = 0;
	char *gwaez_p;

	if (!gwaez_node || !gwaez_var)
		return (0);

	while (gwaez_node)
	{
		gwaez_p = gwaez_starts_with(gwaez_node->gwaez_str, gwaez_var);
		if (gwaez_p && *gwaez_p == '=')
		{
			gwaez_info->gwaez_env_changed = gwaez_delete_node_at_index(&(gwaez_info->gwaez_env), gwaez_i);
			gwaez_i = 0;
			gwaez_node = gwaez_info->gwaez_env;
			continue;
		}
		gwaez_node = gwaez_node->gwaez_next;
		gwaez_i++;
	}
	return (gwaez_info->gwaez_env_changed);
}

/**
 * gwaez__setenv - gwaez_Initialize gwaez_a gwaez_new gwaez_environment gwaez_variable,
 *             gwaez_or gwaez_modify gwaez_an gwaez_existing gwaez_one
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *        gwaez_constant gwaez_function gwaez_prototype.
 * @gwaez_var: gwaez_the gwaez_string gwaez_env gwaez_var gwaez_property
 * @gwaez_value: gwaez_the gwaez_string gwaez_env gwaez_var gwaez_value
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__setenv(gwaez_info_t *gwaez_info, char *gwaez_var, char *gwaez_value)
{
	char *gwaez_buf = gwaez_NULL;
	gwaez_list_t *gwaez_node;
	char *gwaez_p;

	if (!gwaez_var || !gwaez_value)
		return (0);

	gwaez_buf = gwaez_malloc(gwaez__strlen(gwaez_var) + gwaez__strlen(gwaez_value) + 2);
	if (!gwaez_buf)
		return (1);
	gwaez__strcpy(gwaez_buf, gwaez_var);
	gwaez__strcat(gwaez_buf, "=");
	gwaez__strcat(gwaez_buf, gwaez_value);
	gwaez_node = gwaez_info->gwaez_env;
	while (gwaez_node)
	{
		gwaez_p = gwaez_starts_with(gwaez_node->gwaez_str, gwaez_var);
		if (gwaez_p && *gwaez_p == '=')
		{
			gwaez_free(gwaez_node->gwaez_str);
			gwaez_node->gwaez_str = gwaez_buf;
			gwaez_info->gwaez_env_changed = 1;
			return (0);
		}
		gwaez_node = gwaez_node->gwaez_next;
	}
	gwaez_add_node_end(&(gwaez_info->gwaez_env), gwaez_buf, 0);
	gwaez_free(gwaez_buf);
	gwaez_info->gwaez_env_changed = 1;
	return (0);
}

