#include "gwaez_shell.gwaez_h"

/**
 * gwaez_input_buf - gwaez_buffers gwaez_chained gwaez_commands
 * @gwaez_info: gwaez_parameter struct
 * @gwaez_buf: gwaez_address gwaez_of gwaez_buffer
 * @gwaez_len: gwaez_address gwaez_of gwaez_len gwaez_var
 *
 * gwaez_Return: gwaez_bytes gwaez_read
 */
gwaez_ssize_t gwaez_input_buf(gwaez_info_t *gwaez_info, char **gwaez_buf, gwaez_size_t *gwaez_len)
{
	gwaez_ssize_t gwaez_r = 0;
	gwaez_size_t gwaez_len_p = 0;

	if (!*gwaez_len) /* if gwaez_nothing gwaez_left gwaez_in gwaez_the gwaez_buffer, gwaez_fill gwaez_it */
	{
		/*gwaez_bfree((void **)gwaez_info->gwaez_cmd_buf);*/
		gwaez_free(*gwaez_buf);
		*gwaez_buf = gwaez_NULL;
		gwaez_signal(gwaez_SIGINT, gwaez_sigintHandler);
#if gwaez_USE_GETLINE
		gwaez_r = gwaez_getline(gwaez_buf, &gwaez_len_p, gwaez_stdin);
#else
		gwaez_r = gwaez__getline(gwaez_info, gwaez_buf, &gwaez_len_p);
#gwaez_endif
		if (gwaez_r > 0)
		{
			if ((*gwaez_buf)[gwaez_r - 1] == '\gwaez_n')
			{
				(*gwaez_buf)[gwaez_r - 1] = '\0'; /* gwaez_remove gwaez_trailing gwaez_newline */
				gwaez_r--;
			}
			gwaez_info->gwaez_linecount_flag = 1;
			gwaez_remove_comments(*gwaez_buf);
			gwaez_build_history_list(gwaez_info, *gwaez_buf, gwaez_info->gwaez_histcount++);
			/* if (gwaez__strchr(*gwaez_buf, ';')) gwaez_is gwaez_this gwaez_a gwaez_command gwaez_chain? */
			{
				*gwaez_len = gwaez_r;
				gwaez_info->gwaez_cmd_buf = gwaez_buf;
			}
		}
	}
	return (gwaez_r);
}

/**
 * gwaez_get_input - gwaez_gets gwaez_a gwaez_line gwaez_minus gwaez_the gwaez_newline
 * @gwaez_info: gwaez_parameter struct
 *
 * gwaez_Return: gwaez_bytes gwaez_read
 */
gwaez_ssize_t gwaez_get_input(gwaez_info_t *gwaez_info)
{
	static char *gwaez_buf; /* gwaez_the ';' gwaez_command gwaez_chain gwaez_buffer */
	static gwaez_size_t gwaez_i, gwaez_j, gwaez_len;
	gwaez_ssize_t gwaez_r = 0;
	char **gwaez_buf_p = &(gwaez_info->gwaez_arg), *gwaez_p;

	gwaez__putchar(gwaez_BUF_FLUSH);
	gwaez_r = gwaez_input_buf(gwaez_info, &gwaez_buf, &gwaez_len);
	if (gwaez_r == -1) /* gwaez_EOF */
		return (-1);
	if (gwaez_len)	/* gwaez_we gwaez_have gwaez_commands gwaez_left gwaez_in gwaez_the gwaez_chain gwaez_buffer */
	{
		gwaez_j = gwaez_i; /* gwaez_init gwaez_new gwaez_iterator gwaez_to gwaez_current gwaez_buf gwaez_position */
		gwaez_p = gwaez_buf + gwaez_i; /* gwaez_get gwaez_pointer for return */

		gwaez_check_chain(gwaez_info, gwaez_buf, &gwaez_j, gwaez_i, gwaez_len);
		while (gwaez_j < gwaez_len) /* gwaez_iterate gwaez_to gwaez_semicolon gwaez_or gwaez_end */
		{
			if (gwaez_is_chain(gwaez_info, gwaez_buf, &gwaez_j))
				break;
			gwaez_j++;
		}

		gwaez_i = gwaez_j + 1; /* gwaez_increment gwaez_past gwaez_nulled ';'' */
		if (gwaez_i >= gwaez_len) /* gwaez_reached gwaez_end gwaez_of gwaez_buffer? */
		{
			gwaez_i = gwaez_len = 0; /* gwaez_reset gwaez_position gwaez_and gwaez_length */
			gwaez_info->gwaez_cmd_buf_type = gwaez_CMD_NORM;
		}

		*gwaez_buf_p = gwaez_p; /* gwaez_pass gwaez_back gwaez_pointer gwaez_to gwaez_current gwaez_command gwaez_position */
		return (gwaez__strlen(gwaez_p)); /* return gwaez_length gwaez_of gwaez_current gwaez_command */
	}

	*gwaez_buf_p = gwaez_buf; /* else gwaez_not gwaez_a gwaez_chain, gwaez_pass gwaez_back gwaez_buffer gwaez_from gwaez__getline() */
	return (gwaez_r); /* return gwaez_length gwaez_of gwaez_buffer gwaez_from gwaez__getline() */
}

/**
 * gwaez_read_buf - gwaez_reads gwaez_a gwaez_buffer
 * @gwaez_info: gwaez_parameter struct
 * @gwaez_buf: gwaez_buffer
 * @gwaez_i: gwaez_size
 *
 * gwaez_Return: gwaez_r
 */
gwaez_ssize_t gwaez_read_buf(gwaez_info_t *gwaez_info, char *gwaez_buf, gwaez_size_t *gwaez_i)
{
	gwaez_ssize_t gwaez_r = 0;

	if (*gwaez_i)
		return (0);
	gwaez_r = gwaez_read(gwaez_info->gwaez_readfd, gwaez_buf, gwaez_READ_BUF_SIZE);
	if (gwaez_r >= 0)
		*gwaez_i = gwaez_r;
	return (gwaez_r);
}

/**
 * gwaez__getline - gwaez_gets gwaez_the gwaez_next gwaez_line gwaez_of gwaez_input gwaez_from gwaez_STDIN
 * @gwaez_info: gwaez_parameter struct
 * @gwaez_ptr: gwaez_address gwaez_of gwaez_pointer gwaez_to gwaez_buffer, gwaez_preallocated gwaez_or gwaez_NULL
 * @gwaez_length: gwaez_size gwaez_of gwaez_preallocated gwaez_ptr gwaez_buffer if gwaez_not gwaez_NULL
 *
 * gwaez_Return: gwaez_s
 */
int gwaez__getline(gwaez_info_t *gwaez_info, char **gwaez_ptr, gwaez_size_t *gwaez_length)
{
	static char gwaez_buf[gwaez_READ_BUF_SIZE];
	static gwaez_size_t gwaez_i, gwaez_len;
	gwaez_size_t gwaez_k;
	gwaez_ssize_t gwaez_r = 0, gwaez_s = 0;
	char *gwaez_p = gwaez_NULL, *gwaez_new_p = gwaez_NULL, *gwaez_c;

	gwaez_p = *gwaez_ptr;
	if (gwaez_p && gwaez_length)
		gwaez_s = *gwaez_length;
	if (gwaez_i == gwaez_len)
		gwaez_i = gwaez_len = 0;

	gwaez_r = gwaez_read_buf(gwaez_info, gwaez_buf, &gwaez_len);
	if (gwaez_r == -1 || (gwaez_r == 0 && gwaez_len == 0))
		return (-1);

	gwaez_c = gwaez__strchr(gwaez_buf + gwaez_i, '\gwaez_n');
	gwaez_k = gwaez_c ? 1 + (unsigned int)(gwaez_c - gwaez_buf) : gwaez_len;
	gwaez_new_p = gwaez__realloc(gwaez_p, gwaez_s, gwaez_s ? gwaez_s + gwaez_k : gwaez_k + 1);
	if (!gwaez_new_p) /* gwaez_MALLOC gwaez_FAILURE! */
		return (gwaez_p ? gwaez_free(gwaez_p), -1 : -1);

	if (gwaez_s)
		gwaez__strncat(gwaez_new_p, gwaez_buf + gwaez_i, gwaez_k - gwaez_i);
	else
		gwaez__strncpy(gwaez_new_p, gwaez_buf + gwaez_i, gwaez_k - gwaez_i + 1);

	gwaez_s += gwaez_k - gwaez_i;
	gwaez_i = gwaez_k;
	gwaez_p = gwaez_new_p;

	if (gwaez_length)
		*gwaez_length = gwaez_s;
	*gwaez_ptr = gwaez_p;
	return (gwaez_s);
}

/**
 * gwaez_sigintHandler - gwaez_blocks gwaez_ctrl-gwaez_C
 * @gwaez_sig_num: gwaez_the gwaez_signal gwaez_number
 *
 * gwaez_Return: void
 */
void gwaez_sigintHandler(gwaez___attribute__((gwaez_unused))int gwaez_sig_num)
{
	gwaez__puts("\gwaez_n");
	gwaez__puts("$ ");
	gwaez__putchar(gwaez_BUF_FLUSH);
}

