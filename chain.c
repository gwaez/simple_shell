#include "gwaez_shell.gwaez_h"

/**
 * gwaez_is_chain - gwaez_test if gwaez_current char gwaez_in gwaez_buffer gwaez_is gwaez_a gwaez_chain gwaez_delimeter
 * @gwaez_info: gwaez_the gwaez_parameter struct
 * @gwaez_buf: gwaez_the char gwaez_buffer
 * @gwaez_p: gwaez_address gwaez_of gwaez_current gwaez_position gwaez_in gwaez_buf
 *
 * gwaez_Return: 1 if gwaez_chain gwaez_delimeter, 0 gwaez_otherwise
 */
int gwaez_is_chain(gwaez_info_t *gwaez_info, char *gwaez_buf, gwaez_size_t *gwaez_p)
{
	gwaez_size_t gwaez_j = *gwaez_p;

	if (gwaez_buf[gwaez_j] == '|' && gwaez_buf[gwaez_j + 1] == '|')
	{
		gwaez_buf[gwaez_j] = 0;
		gwaez_j++;
		gwaez_info->gwaez_cmd_buf_type = gwaez_CMD_OR;
	}
	else if (gwaez_buf[gwaez_j] == '&' && gwaez_buf[gwaez_j + 1] == '&')
	{
		gwaez_buf[gwaez_j] = 0;
		gwaez_j++;
		gwaez_info->gwaez_cmd_buf_type = gwaez_CMD_AND;
	}
	else if (gwaez_buf[gwaez_j] == ';') /* gwaez_found gwaez_end gwaez_of gwaez_this gwaez_command */
	{
		gwaez_buf[gwaez_j] = 0; /* gwaez_replace gwaez_semicolon gwaez_with gwaez_null */
		gwaez_info->gwaez_cmd_buf_type = gwaez_CMD_CHAIN;
	}
	else
		return (0);
	*gwaez_p = gwaez_j;
	return (1);
}

/**
 * gwaez_check_chain - gwaez_checks gwaez_we gwaez_should continue gwaez_chaining gwaez_based gwaez_on gwaez_last gwaez_status
 * @gwaez_info: gwaez_the gwaez_parameter struct
 * @gwaez_buf: gwaez_the char gwaez_buffer
 * @gwaez_p: gwaez_address gwaez_of gwaez_current gwaez_position gwaez_in gwaez_buf
 * @gwaez_i: gwaez_starting gwaez_position gwaez_in gwaez_buf
 * @gwaez_len: gwaez_length gwaez_of gwaez_buf
 *
 * gwaez_Return: gwaez_Void
 */
void gwaez_check_chain(gwaez_info_t *gwaez_info, char *gwaez_buf, gwaez_size_t *gwaez_p, gwaez_size_t gwaez_i, gwaez_size_t gwaez_len)
{
	gwaez_size_t gwaez_j = *gwaez_p;

	if (gwaez_info->gwaez_cmd_buf_type == gwaez_CMD_AND)
	{
		if (gwaez_info->gwaez_status)
		{
			gwaez_buf[gwaez_i] = 0;
			gwaez_j = gwaez_len;
		}
	}
	if (gwaez_info->gwaez_cmd_buf_type == gwaez_CMD_OR)
	{
		if (!gwaez_info->gwaez_status)
		{
			gwaez_buf[gwaez_i] = 0;
			gwaez_j = gwaez_len;
		}
	}

	*gwaez_p = gwaez_j;
}

/**
 * gwaez_replace_alias - gwaez_replaces gwaez_an gwaez_aliases gwaez_in gwaez_the gwaez_tokenized gwaez_string
 * @gwaez_info: gwaez_the gwaez_parameter struct
 *
 * gwaez_Return: 1 if gwaez_replaced, 0 gwaez_otherwise
 */
int gwaez_replace_alias(gwaez_info_t *gwaez_info)
{
	int gwaez_i;
	gwaez_list_t *gwaez_node;
	char *gwaez_p;

	for (gwaez_i = 0; gwaez_i < 10; gwaez_i++)
	{
		gwaez_node = gwaez_node_starts_with(gwaez_info->gwaez_alias, gwaez_info->gwaez_argv[0], '=');
		if (!gwaez_node)
			return (0);
		gwaez_free(gwaez_info->gwaez_argv[0]);
		gwaez_p = gwaez__strchr(gwaez_node->gwaez_str, '=');
		if (!gwaez_p)
			return (0);
		gwaez_p = gwaez__strdup(gwaez_p + 1);
		if (!gwaez_p)
			return (0);
		gwaez_info->gwaez_argv[0] = gwaez_p;
	}
	return (1);
}

/**
 * gwaez_replace_vars - gwaez_replaces gwaez_vars gwaez_in gwaez_the gwaez_tokenized gwaez_string
 * @gwaez_info: gwaez_the gwaez_parameter struct
 *
 * gwaez_Return: 1 if gwaez_replaced, 0 gwaez_otherwise
 */
int gwaez_replace_vars(gwaez_info_t *gwaez_info)
{
	int gwaez_i = 0;
	gwaez_list_t *gwaez_node;

	for (gwaez_i = 0; gwaez_info->gwaez_argv[gwaez_i]; gwaez_i++)
	{
		if (gwaez_info->gwaez_argv[gwaez_i][0] != '$' || !gwaez_info->gwaez_argv[gwaez_i][1])
			continue;

		if (!gwaez__strcmp(gwaez_info->gwaez_argv[gwaez_i], "$?"))
		{
			gwaez_replace_string(&(gwaez_info->gwaez_argv[gwaez_i]),
				gwaez__strdup(gwaez_convert_number(gwaez_info->gwaez_status, 10, 0)));
			continue;
		}
		if (!gwaez__strcmp(gwaez_info->gwaez_argv[gwaez_i], "$$"))
		{
			gwaez_replace_string(&(gwaez_info->gwaez_argv[gwaez_i]),
				gwaez__strdup(gwaez_convert_number(gwaez_getpid(), 10, 0)));
			continue;
		}
		gwaez_node = gwaez_node_starts_with(gwaez_info->gwaez_env, &gwaez_info->gwaez_argv[gwaez_i][1], '=');
		if (gwaez_node)
		{
			gwaez_replace_string(&(gwaez_info->gwaez_argv[gwaez_i]),
				gwaez__strdup(gwaez__strchr(gwaez_node->gwaez_str, '=') + 1));
			continue;
		}
		gwaez_replace_string(&gwaez_info->gwaez_argv[gwaez_i], gwaez__strdup(""));

	}
	return (0);
}

/**
 * gwaez_replace_string - gwaez_replaces gwaez_string
 * @gwaez_old: gwaez_address gwaez_of gwaez_old gwaez_string
 * @gwaez_new: gwaez_new gwaez_string
 *
 * gwaez_Return: 1 if gwaez_replaced, 0 gwaez_otherwise
 */
int gwaez_replace_string(char **gwaez_old, char *gwaez_new)
{
	gwaez_free(*gwaez_old);
	*gwaez_old = gwaez_new;
	return (1);
}

