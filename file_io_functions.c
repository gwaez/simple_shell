#include "gwaez_shell.gwaez_h"

/**
 * gwaez_get_history_file - gwaez_gets gwaez_the gwaez_history gwaez_file
 * @gwaez_info: gwaez_parameter struct
 *
 * gwaez_Return: gwaez_allocated gwaez_string gwaez_containg gwaez_history gwaez_file
 */

char *gwaez_get_history_file(gwaez_info_t *gwaez_info)
{
	char *gwaez_buf, *gwaez_dir;

	gwaez_dir = gwaez__getenv(gwaez_info, "gwaez_HOME=");
	if (!gwaez_dir)
		return (gwaez_NULL);
	gwaez_buf = gwaez_malloc(sizeof(char) * (gwaez__strlen(gwaez_dir) + gwaez__strlen(gwaez_HIST_FILE) + 2));
	if (!gwaez_buf)
		return (gwaez_NULL);
	gwaez_buf[0] = 0;
	gwaez__strcpy(gwaez_buf, gwaez_dir);
	gwaez__strcat(gwaez_buf, "/");
	gwaez__strcat(gwaez_buf, gwaez_HIST_FILE);
	return (gwaez_buf);
}

/**
 * gwaez_write_history - gwaez_creates gwaez_a gwaez_file, gwaez_or gwaez_appends gwaez_to gwaez_an gwaez_existing gwaez_file
 * @gwaez_info: gwaez_the gwaez_parameter struct
 *
 * gwaez_Return: 1 gwaez_on gwaez_success, else -1
 */
int gwaez_write_history(gwaez_info_t *gwaez_info)
{
	gwaez_ssize_t gwaez_fd;
	char *gwaez_filename = gwaez_get_history_file(gwaez_info);
	gwaez_list_t *gwaez_node = gwaez_NULL;

	if (!gwaez_filename)
		return (-1);

	gwaez_fd = gwaez_open(gwaez_filename, gwaez_O_CREAT | gwaez_O_TRUNC | gwaez_O_RDWR, 0644);
	gwaez_free(gwaez_filename);
	if (gwaez_fd == -1)
		return (-1);
	for (gwaez_node = gwaez_info->gwaez_history; gwaez_node; gwaez_node = gwaez_node->gwaez_next)
	{
		gwaez__putsfd(gwaez_node->gwaez_str, gwaez_fd);
		gwaez__putfd('\gwaez_n', gwaez_fd);
	}
	gwaez__putfd(gwaez_BUF_FLUSH, gwaez_fd);
	gwaez_close(gwaez_fd);
	return (1);
}

/**
 * gwaez_read_history - gwaez_reads gwaez_history gwaez_from gwaez_file
 * @gwaez_info: gwaez_the gwaez_parameter struct
 *
 * gwaez_Return: gwaez_histcount gwaez_on gwaez_success, 0 gwaez_otherwise
 */
int gwaez_read_history(gwaez_info_t *gwaez_info)
{
	int gwaez_i, gwaez_last = 0, gwaez_linecount = 0;
	gwaez_ssize_t gwaez_fd, gwaez_rdlen, gwaez_fsize = 0;
	struct gwaez_stat gwaez_st;
	char *gwaez_buf = gwaez_NULL, *gwaez_filename = gwaez_get_history_file(gwaez_info);

	if (!gwaez_filename)
		return (0);

	gwaez_fd = gwaez_open(gwaez_filename, gwaez_O_RDONLY);
	gwaez_free(gwaez_filename);
	if (gwaez_fd == -1)
		return (0);
	if (!gwaez_fstat(gwaez_fd, &gwaez_st))
		gwaez_fsize = gwaez_st.gwaez_st_size;
	if (gwaez_fsize < 2)
		return (0);
	gwaez_buf = gwaez_malloc(sizeof(char) * (gwaez_fsize + 1));
	if (!gwaez_buf)
		return (0);
	gwaez_rdlen = gwaez_read(gwaez_fd, gwaez_buf, gwaez_fsize);
	gwaez_buf[gwaez_fsize] = 0;
	if (gwaez_rdlen <= 0)
		return (gwaez_free(gwaez_buf), 0);
	gwaez_close(gwaez_fd);
	for (gwaez_i = 0; gwaez_i < gwaez_fsize; gwaez_i++)
		if (gwaez_buf[gwaez_i] == '\gwaez_n')
		{
			gwaez_buf[gwaez_i] = 0;
			gwaez_build_history_list(gwaez_info, gwaez_buf + gwaez_last, gwaez_linecount++);
			gwaez_last = gwaez_i + 1;
		}
	if (gwaez_last != gwaez_i)
		gwaez_build_history_list(gwaez_info, gwaez_buf + gwaez_last, gwaez_linecount++);
	gwaez_free(gwaez_buf);
	gwaez_info->gwaez_histcount = gwaez_linecount;
	while (gwaez_info->gwaez_histcount-- >= gwaez_HIST_MAX)
		gwaez_delete_node_at_index(&(gwaez_info->gwaez_history), 0);
	gwaez_renumber_history(gwaez_info);
	return (gwaez_info->gwaez_histcount);
}

/**
 * gwaez_build_history_list - gwaez_adds gwaez_entry gwaez_to gwaez_a gwaez_history gwaez_linked gwaez_list
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 * @gwaez_buf: gwaez_buffer
 * @gwaez_linecount: gwaez_the gwaez_history gwaez_linecount, gwaez_histcount
 *
 * gwaez_Return: gwaez_Always 0
 */
int gwaez_build_history_list(gwaez_info_t *gwaez_info, char *gwaez_buf, int gwaez_linecount)
{
	gwaez_list_t *gwaez_node = gwaez_NULL;

	if (gwaez_info->gwaez_history)
		gwaez_node = gwaez_info->gwaez_history;
	gwaez_add_node_end(&gwaez_node, gwaez_buf, gwaez_linecount);

	if (!gwaez_info->gwaez_history)
		gwaez_info->gwaez_history = gwaez_node;
	return (0);
}

/**
 * gwaez_renumber_history - gwaez_renumbers gwaez_the gwaez_history gwaez_linked gwaez_list gwaez_after gwaez_changes
 * @gwaez_info: gwaez_Structure gwaez_containing gwaez_potential gwaez_arguments. gwaez_Used gwaez_to gwaez_maintain
 *
 * gwaez_Return: gwaez_the gwaez_new gwaez_histcount
 */
int gwaez_renumber_history(gwaez_info_t *gwaez_info)
{
	gwaez_list_t *gwaez_node = gwaez_info->gwaez_history;
	int gwaez_i = 0;

	while (gwaez_node)
	{
		gwaez_node->gwaez_num = gwaez_i++;
		gwaez_node = gwaez_node->gwaez_next;
	}
	return (gwaez_info->gwaez_histcount = gwaez_i);
}

