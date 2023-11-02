#include "gwaez_shell.gwaez_h"

/**
 * gwaez__myenv - gwaez_prints gwaez_the gwaez_current gwaez_environment
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 * gwaez_Return: gwaez_Always 0
 */
int gwaez__myenv(gwaez_info_t *gwaez_info)
{
	gwaez_print_list_str(gwaez_info->gwaez_env);
	return (0);
}

/**
 * gwaez__getenv - gwaez_gets gwaez_the gwaez_value gwaez_of gwaez_an gwaez_environ gwaez_variable
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 * @gwaez_name: gwaez_env gwaez_var gwaez_name
 *
 * gwaez_Return: gwaez_the gwaez_value
 */
char *gwaez__getenv(gwaez_info_t *gwaez_info, const char *gwaez_name)
{
	gwaez_list_t *gwaez_node = gwaez_info->gwaez_env;
	char *gwaez_p;

	while (gwaez_node)
	{
		gwaez_p = gwaez_starts_with(gwaez_node->gwaez_str, gwaez_name);
		if (gwaez_p && *gwaez_p)
			return (gwaez_p);
		gwaez_node = gwaez_node->gwaez_next;
	}
	return (gwaez_NULL);
}

/**
 * gwaez__mysetenv - gwaez_Initialize gwaez_a gwaez_new gwaez_environment gwaez_variable,
 *             gwaez_or gwaez_modify gwaez_an gwaez_existing gwaez_one
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *        gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__mysetenv(gwaez_info_t *gwaez_info)
{
	if (gwaez_info->gwaez_argc != 3)
	{
		gwaez__eputs("gwaez_Incorrect gwaez_number gwaez_of gwaez_arguements\gwaez_n");
		return (1);
	}
	if (gwaez__setenv(gwaez_info, gwaez_info->gwaez_argv[1], gwaez_info->gwaez_argv[2]))
		return (0);
	return (1);
}

/**
 * gwaez__myunsetenv - gwaez_Remove gwaez_an gwaez_environment gwaez_variable
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *        gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__myunsetenv(gwaez_info_t *gwaez_info)
{
	int gwaez_i;

	if (gwaez_info->gwaez_argc == 1)
	{
		gwaez__eputs("gwaez_Too gwaez_few gwaez_arguements.\gwaez_n");
		return (1);
	}
	for (gwaez_i = 1; gwaez_i <= gwaez_info->gwaez_argc; gwaez_i++)
		gwaez__unsetenv(gwaez_info, gwaez_info->gwaez_argv[gwaez_i]);

	return (0);
}

/**
 * gwaez_populate_env_list - gwaez_populates gwaez_env gwaez_linked gwaez_list
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 * gwaez_Return: gwaez_Always 0
 */
int gwaez_populate_env_list(gwaez_info_t *gwaez_info)
{
	gwaez_list_t *gwaez_node = gwaez_NULL;
	gwaez_size_t gwaez_i;

	for (gwaez_i = 0; gwaez_environ[gwaez_i]; gwaez_i++)
		gwaez_add_node_end(&gwaez_node, gwaez_environ[gwaez_i], 0);
	gwaez_info->gwaez_env = gwaez_node;
	return (0);
}

