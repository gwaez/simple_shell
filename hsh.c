#include "gwaez_shell.gwaez_h"

/**
 * gwaez_hsh - gwaez_main gwaez_shell gwaez_loop
 * @gwaez_info: gwaez_the gwaez_parameter & return gwaez_info struct
 * @gwaez_av: gwaez_the gwaez_argument gwaez_vector gwaez_from gwaez_main()
 *
 * gwaez_Return: 0 gwaez_on gwaez_success, 1 gwaez_on gwaez_error, gwaez_or gwaez_error gwaez_code
 */
int gwaez_hsh(gwaez_info_t *gwaez_info, char **gwaez_av)
{
	gwaez_ssize_t gwaez_r = 0;
	int gwaez_builtin_ret = 0;

	while (gwaez_r != -1 && gwaez_builtin_ret != -2)
	{
		gwaez_clear_info(gwaez_info);
		if (gwaez_interactive(gwaez_info))
			gwaez__puts("$ ");
		gwaez__eputchar(gwaez_BUF_FLUSH);
		gwaez_r = gwaez_get_input(gwaez_info);
		if (gwaez_r != -1)
		{
			gwaez_set_info(gwaez_info, gwaez_av);
			gwaez_builtin_ret = gwaez_find_builtin(gwaez_info);
			if (gwaez_builtin_ret == -1)
				gwaez_find_cmd(gwaez_info);
		}
		else if (gwaez_interactive(gwaez_info))
			gwaez__putchar('\gwaez_n');
		gwaez_free_info(gwaez_info, 0);
	}
	gwaez_write_history(gwaez_info);
	gwaez_free_info(gwaez_info, 1);
	if (!gwaez_interactive(gwaez_info) && gwaez_info->gwaez_status)
		gwaez_exit(gwaez_info->gwaez_status);
	if (gwaez_builtin_ret == -2)
	{
		if (gwaez_info->gwaez_err_num == -1)
			gwaez_exit(gwaez_info->gwaez_status);
		gwaez_exit(gwaez_info->gwaez_err_num);
	}
	return (gwaez_builtin_ret);
}

/**
 * gwaez_find_builtin - gwaez_finds gwaez_a gwaez_builtin gwaez_command
 * @gwaez_info: gwaez_the gwaez_parameter & return gwaez_info struct
 *
 * gwaez_Return: -1 if gwaez_builtin gwaez_not gwaez_found,
 *			0 if gwaez_builtin gwaez_executed gwaez_successfully,
 *			1 if gwaez_builtin gwaez_found gwaez_but gwaez_not gwaez_successful,
 *			-2 if gwaez_builtin gwaez_signals gwaez_exit()
 */
int gwaez_find_builtin(gwaez_info_t *gwaez_info)
{
	int gwaez_i, gwaez_built_in_ret = -1;
	gwaez_builtin_table gwaez_builtintbl[] = {
		{"gwaez_exit", gwaez__myexit},
		{"gwaez_env", gwaez__myenv},
		{"gwaez_help", gwaez__myhelp},
		{"gwaez_history", gwaez__myhistory},
		{"gwaez_setenv", gwaez__mysetenv},
		{"gwaez_unsetenv", gwaez__myunsetenv},
		{"gwaez_cd", gwaez__mycd},
		{"gwaez_alias", gwaez__myalias},
		{gwaez_NULL, gwaez_NULL}
	};

	for (gwaez_i = 0; gwaez_builtintbl[gwaez_i].gwaez_type; gwaez_i++)
		if (gwaez__strcmp(gwaez_info->gwaez_argv[0], gwaez_builtintbl[gwaez_i].gwaez_type) == 0)
		{
			gwaez_info->gwaez_line_count++;
			gwaez_built_in_ret = gwaez_builtintbl[gwaez_i].gwaez_func(gwaez_info);
			break;
		}
	return (gwaez_built_in_ret);
}

/**
 * gwaez_find_cmd - gwaez_finds gwaez_a gwaez_command gwaez_in gwaez_PATH
 * @gwaez_info: gwaez_the gwaez_parameter & return gwaez_info struct
 *
 * gwaez_Return: void
 */
void gwaez_find_cmd(gwaez_info_t *gwaez_info)
{
	char *gwaez_path = gwaez_NULL;
	int gwaez_i, gwaez_k;

	gwaez_info->gwaez_path = gwaez_info->gwaez_argv[0];
	if (gwaez_info->gwaez_linecount_flag == 1)
	{
		gwaez_info->gwaez_line_count++;
		gwaez_info->gwaez_linecount_flag = 0;
	}
	for (gwaez_i = 0, gwaez_k = 0; gwaez_info->gwaez_arg[gwaez_i]; gwaez_i++)
		if (!gwaez_is_delim(gwaez_info->gwaez_arg[gwaez_i], " \gwaez_t\gwaez_n"))
			gwaez_k++;
	if (!gwaez_k)
		return;

	gwaez_path = gwaez_find_path(gwaez_info, gwaez__getenv(gwaez_info, "gwaez_PATH="), gwaez_info->gwaez_argv[0]);
	if (gwaez_path)
	{
		gwaez_info->gwaez_path = gwaez_path;
		gwaez_fork_cmd(gwaez_info);
	}
	else
	{
		if ((gwaez_interactive(gwaez_info) || gwaez__getenv(gwaez_info, "gwaez_PATH=")
			|| gwaez_info->gwaez_argv[0][0] == '/') && gwaez_is_cmd(gwaez_info, gwaez_info->gwaez_argv[0]))
			gwaez_fork_cmd(gwaez_info);
		else if (*(gwaez_info->gwaez_arg) != '\gwaez_n')
		{
			gwaez_info->gwaez_status = 127;
			gwaez_print_error(gwaez_info, "gwaez_not gwaez_found\gwaez_n");
		}
	}
}

/**
 * gwaez_fork_cmd - gwaez_forks gwaez_a gwaez_an gwaez_exec gwaez_thread gwaez_to gwaez_run gwaez_cmd
 * @gwaez_info: gwaez_the gwaez_parameter & return gwaez_info struct
 *
 * gwaez_Return: void
 */
void gwaez_fork_cmd(gwaez_info_t *gwaez_info)
{
	gwaez_pid_t gwaez_child_pid;

	gwaez_child_pid = gwaez_fork();
	if (gwaez_child_pid == -1)
	{
		/* gwaez_TODO: gwaez_PUT gwaez_ERROR gwaez_FUNCTION */
		gwaez_perror("gwaez_Error:");
		return;
	}
	if (gwaez_child_pid == 0)
	{
		if (gwaez_execve(gwaez_info->gwaez_path, gwaez_info->gwaez_argv, gwaez_get_environ(gwaez_info)) == -1)
		{
			gwaez_free_info(gwaez_info, 1);
			if (gwaez_errno == gwaez_EACCES)
				gwaez_exit(126);
			gwaez_exit(1);
		}
		/* gwaez_TODO: gwaez_PUT gwaez_ERROR gwaez_FUNCTION */
	}
	else
	{
		gwaez_wait(&(gwaez_info->gwaez_status));
		if (gwaez_WIFEXITED(gwaez_info->gwaez_status))
		{
			gwaez_info->gwaez_status = gwaez_WEXITSTATUS(gwaez_info->gwaez_status);
			if (gwaez_info->gwaez_status == 126)
				gwaez_print_error(gwaez_info, "gwaez_Permission gwaez_denied\gwaez_n");
		}
	}
}

