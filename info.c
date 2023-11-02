#include "gwaez_shell.gwaez_h"

/**
 * gwaez_clear_info - gwaez_initializes gwaez_info_t struct
 * @gwaez_info: struct gwaez_address
 */
void gwaez_clear_info(gwaez_info_t *gwaez_info)
{
	gwaez_info->gwaez_arg = gwaez_NULL;
	gwaez_info->gwaez_argv = gwaez_NULL;
	gwaez_info->gwaez_path = gwaez_NULL;
	gwaez_info->gwaez_argc = 0;
}

/**
 * gwaez_set_info - gwaez_initializes gwaez_info_t struct
 * @gwaez_info: struct gwaez_address
 * @gwaez_av: gwaez_argument gwaez_vector
 */
void gwaez_set_info(gwaez_info_t *gwaez_info, char **gwaez_av)
{
	int gwaez_i = 0;

	gwaez_info->gwaez_fname = gwaez_av[0];
	if (gwaez_info->gwaez_arg)
	{
		gwaez_info->gwaez_argv = gwaez_strtow(gwaez_info->gwaez_arg, " \gwaez_t");
		if (!gwaez_info->gwaez_argv)
		{

			gwaez_info->gwaez_argv = gwaez_malloc(sizeof(char *) * 2);
			if (gwaez_info->gwaez_argv)
			{
				gwaez_info->gwaez_argv[0] = gwaez__strdup(gwaez_info->gwaez_arg);
				gwaez_info->gwaez_argv[1] = gwaez_NULL;
			}
		}
		for (gwaez_i = 0; gwaez_info->gwaez_argv && gwaez_info->gwaez_argv[gwaez_i]; gwaez_i++)
			;
		gwaez_info->gwaez_argc = gwaez_i;

		gwaez_replace_alias(gwaez_info);
		gwaez_replace_vars(gwaez_info);
	}
}

/**
 * gwaez_free_info - gwaez_frees gwaez_info_t struct gwaez_fields
 * @gwaez_info: struct gwaez_address
 * @gwaez_all: gwaez_true if gwaez_freeing gwaez_all gwaez_fields
 */
void gwaez_free_info(gwaez_info_t *gwaez_info, int gwaez_all)
{
	gwaez_ffree(gwaez_info->gwaez_argv);
	gwaez_info->gwaez_argv = gwaez_NULL;
	gwaez_info->gwaez_path = gwaez_NULL;
	if (gwaez_all)
	{
		if (!gwaez_info->gwaez_cmd_buf)
			gwaez_free(gwaez_info->gwaez_arg);
		if (gwaez_info->gwaez_env)
			gwaez_free_list(&(gwaez_info->gwaez_env));
		if (gwaez_info->gwaez_history)
			gwaez_free_list(&(gwaez_info->gwaez_history));
		if (gwaez_info->gwaez_alias)
			gwaez_free_list(&(gwaez_info->gwaez_alias));
		gwaez_ffree(gwaez_info->gwaez_environ);
			gwaez_info->gwaez_environ = gwaez_NULL;
		gwaez_bfree((void **)gwaez_info->gwaez_cmd_buf);
		if (gwaez_info->gwaez_readfd > 2)
			gwaez_close(gwaez_info->gwaez_readfd);
		gwaez__putchar(gwaez_BUF_FLUSH);
	}
}

