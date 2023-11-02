#include "gwaez_shell.gwaez_h"

/**
 * gwaez_is_cmd - gwaez_determines if gwaez_a gwaez_file gwaez_is gwaez_an gwaez_executable gwaez_command
 * @gwaez_info: gwaez_the gwaez_info struct
 * @gwaez_path: gwaez_path gwaez_to gwaez_the gwaez_file
 *
 * gwaez_Return: 1 if gwaez_true, 0 gwaez_otherwise
 */
int gwaez_is_cmd(gwaez_info_t *gwaez_info, char *gwaez_path)
{
	struct gwaez_stat gwaez_st;

	(void)gwaez_info;
	if (!gwaez_path || gwaez_stat(gwaez_path, &gwaez_st))
		return (0);

	if (gwaez_st.gwaez_st_mode & gwaez_S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * gwaez_dup_chars - gwaez_duplicates gwaez_characters
 * @gwaez_pathstr: gwaez_the gwaez_PATH gwaez_string
 * @gwaez_start: gwaez_starting gwaez_index
 * @gwaez_stop: gwaez_stopping gwaez_index
 *
 * gwaez_Return: gwaez_pointer gwaez_to gwaez_new gwaez_buffer
 */
char *gwaez_dup_chars(char *gwaez_pathstr, int gwaez_start, int gwaez_stop)
{
	static char gwaez_buf[1024];
	int gwaez_i = 0, gwaez_k = 0;

	for (gwaez_k = 0, gwaez_i = gwaez_start; gwaez_i < gwaez_stop; gwaez_i++)
		if (gwaez_pathstr[gwaez_i] != ':')
			gwaez_buf[gwaez_k++] = gwaez_pathstr[gwaez_i];
	gwaez_buf[gwaez_k] = 0;
	return (gwaez_buf);
}

/**
 * gwaez_find_path - gwaez_finds gwaez_this gwaez_cmd gwaez_in gwaez_the gwaez_PATH gwaez_string
 * @gwaez_info: gwaez_the gwaez_info struct
 * @gwaez_pathstr: gwaez_the gwaez_PATH gwaez_string
 * @gwaez_cmd: gwaez_the gwaez_cmd gwaez_to gwaez_find
 *
 * gwaez_Return: gwaez_full gwaez_path gwaez_of gwaez_cmd if gwaez_found gwaez_or gwaez_NULL
 */
char *gwaez_find_path(gwaez_info_t *gwaez_info, char *gwaez_pathstr, char *gwaez_cmd)
{
	int gwaez_i = 0, gwaez_curr_pos = 0;
	char *gwaez_path;

	if (!gwaez_pathstr)
		return (gwaez_NULL);
	if ((gwaez__strlen(gwaez_cmd) > 2) && gwaez_starts_with(gwaez_cmd, "./"))
	{
		if (gwaez_is_cmd(gwaez_info, gwaez_cmd))
			return (gwaez_cmd);
	}
	while (1)
	{
		if (!gwaez_pathstr[gwaez_i] || gwaez_pathstr[gwaez_i] == ':')
		{
			gwaez_path = gwaez_dup_chars(gwaez_pathstr, gwaez_curr_pos, gwaez_i);
			if (!*gwaez_path)
				gwaez__strcat(gwaez_path, gwaez_cmd);
			else
			{
				gwaez__strcat(gwaez_path, "/");
				gwaez__strcat(gwaez_path, gwaez_cmd);
			}
			if (gwaez_is_cmd(gwaez_info, gwaez_path))
				return (gwaez_path);
			if (!gwaez_pathstr[gwaez_i])
				break;
			gwaez_curr_pos = gwaez_i;
		}
		gwaez_i++;
	}
	return (gwaez_NULL);
}

