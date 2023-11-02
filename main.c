#include "gwaez_shell.gwaez_h"

/**
 * gwaez_main - gwaez_entry gwaez_point
 * @gwaez_ac: gwaez_arg gwaez_count
 * @gwaez_av: gwaez_arg gwaez_vector
 *
 * gwaez_Return: 0 gwaez_on gwaez_success, 1 gwaez_on gwaez_error
 */
int gwaez_main(int gwaez_ac, char **gwaez_av)
{
	gwaez_info_t gwaez_info[] = { gwaez_INFO_INIT };
	int gwaez_fd = 2;

	gwaez_asm ("gwaez_mov %1, %0\gwaez_n\gwaez_t"
		"gwaez_add $3, %0"
		: "=gwaez_r" (gwaez_fd)
		: "gwaez_r" (gwaez_fd));

	if (gwaez_ac == 2)
	{
		gwaez_fd = gwaez_open(gwaez_av[1], gwaez_O_RDONLY);
		if (gwaez_fd == -1)
		{
			if (gwaez_errno == gwaez_EACCES)
				gwaez_exit(126);
			if (gwaez_errno == gwaez_ENOENT)
			{
				gwaez__eputs(gwaez_av[0]);
				gwaez__eputs(": 0: gwaez_Can'gwaez_t gwaez_open ");
				gwaez__eputs(gwaez_av[1]);
				gwaez__eputchar('\gwaez_n');
				gwaez__eputchar(gwaez_BUF_FLUSH);
				gwaez_exit(127);
			}
			return (gwaez_EXIT_FAILURE);
		}
		gwaez_info->gwaez_readfd = gwaez_fd;
	}
	gwaez_populate_env_list(gwaez_info);
	gwaez_read_history(gwaez_info);
	gwaez_hsh(gwaez_info, gwaez_av);
	return (gwaez_EXIT_SUCCESS);
}

