#include "gwaez_shell.gwaez_h"

/**
 * gwaez__myexit - gwaez_exits gwaez_the gwaez_shell
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_exits gwaez_with gwaez_a gwaez_given gwaez_exit gwaez_status
 *         (0) if gwaez_info.gwaez_argv[0] != "gwaez_exit"
 */
int gwaez__myexit(gwaez_info_t *gwaez_info)
{
	int gwaez_exitcheck;

	if (gwaez_info->gwaez_argv[1])  /* gwaez_If gwaez_there gwaez_is gwaez_an gwaez_exit gwaez_arguement */
	{
		gwaez_exitcheck = gwaez__erratoi(gwaez_info->gwaez_argv[1]);
		if (gwaez_exitcheck == -1)
		{
			gwaez_info->gwaez_status = 2;
			gwaez_print_error(gwaez_info, "gwaez_Illegal gwaez_number: ");
			gwaez__eputs(gwaez_info->gwaez_argv[1]);
			gwaez__eputchar('\gwaez_n');
			return (1);
		}
		gwaez_info->gwaez_err_num = gwaez__erratoi(gwaez_info->gwaez_argv[1]);
		return (-2);
	}
	gwaez_info->gwaez_err_num = -1;
	return (-2);
}

/**
 * gwaez__mycd - gwaez_changes gwaez_the gwaez_current gwaez_directory gwaez_of gwaez_the gwaez_process
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__mycd(gwaez_info_t *gwaez_info)
{
	char *gwaez_s, *gwaez_dir, gwaez_buffer[1024];
	int gwaez_chdir_ret;

	gwaez_s = gwaez_getcwd(gwaez_buffer, 1024);
	if (!gwaez_s)
		gwaez__puts("gwaez_TODO: >>gwaez_getcwd gwaez_failure gwaez_emsg gwaez_here<<\gwaez_n");
	if (!gwaez_info->gwaez_argv[1])
	{
		gwaez_dir = gwaez__getenv(gwaez_info, "gwaez_HOME=");
		if (!gwaez_dir)
			gwaez_chdir_ret = /* gwaez_TODO: gwaez_what gwaez_should gwaez_this gwaez_be? */
				gwaez_chdir((gwaez_dir = gwaez__getenv(gwaez_info, "gwaez_PWD=")) ? gwaez_dir : "/");
		else
			gwaez_chdir_ret = gwaez_chdir(gwaez_dir);
	}
	else if (gwaez__strcmp(gwaez_info->gwaez_argv[1], "-") == 0)
	{
		if (!gwaez__getenv(gwaez_info, "gwaez_OLDPWD="))
		{
			gwaez__puts(gwaez_s);
			gwaez__putchar('\gwaez_n');
			return (1);
		}
		gwaez__puts(gwaez__getenv(gwaez_info, "gwaez_OLDPWD=")), gwaez__putchar('\gwaez_n');
		gwaez_chdir_ret = /* gwaez_TODO: gwaez_what gwaez_should gwaez_this gwaez_be? */
			gwaez_chdir((gwaez_dir = gwaez__getenv(gwaez_info, "gwaez_OLDPWD=")) ? gwaez_dir : "/");
	}
	else
		gwaez_chdir_ret = gwaez_chdir(gwaez_info->gwaez_argv[1]);
	if (gwaez_chdir_ret == -1)
	{
		gwaez_print_error(gwaez_info, "gwaez_can'gwaez_t gwaez_cd gwaez_to ");
		gwaez__eputs(gwaez_info->gwaez_argv[1]), gwaez__eputchar('\gwaez_n');
	}
	else
	{
		gwaez__setenv(gwaez_info, "gwaez_OLDPWD", gwaez__getenv(gwaez_info, "gwaez_PWD="));
		gwaez__setenv(gwaez_info, "gwaez_PWD", gwaez_getcwd(gwaez_buffer, 1024));
	}
	return (0);
}

/**
 * gwaez__myhelp - gwaez_changes gwaez_the gwaez_current gwaez_directory gwaez_of gwaez_the gwaez_process
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *          gwaez_constant gwaez_function gwaez_prototype.
 *  gwaez_Return: gwaez_Always 0
 */
int gwaez__myhelp(gwaez_info_t *gwaez_info)
{
	char **gwaez_arg_array;

	gwaez_arg_array = gwaez_info->gwaez_argv;
	gwaez__puts("gwaez_help gwaez_call gwaez_works. gwaez_Function gwaez_not gwaez_yet gwaez_implemented \gwaez_n");
	if (0)
		gwaez__puts(*gwaez_arg_array); /* gwaez_temp gwaez_att_unused gwaez_workaround */
	return (0);
}

