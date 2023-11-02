#include "gwaez_shell.gwaez_h"

/**
 * gwaez_add_node - gwaez_adds gwaez_a gwaez_node gwaez_to gwaez_the gwaez_start gwaez_of gwaez_the gwaez_list
 * @gwaez_head: gwaez_address gwaez_of gwaez_pointer gwaez_to gwaez_head gwaez_node
 * @gwaez_str: gwaez_str gwaez_field gwaez_of gwaez_node
 * @gwaez_num: gwaez_node gwaez_index gwaez_used gwaez_by gwaez_history
 *
 * gwaez_Return: gwaez_size gwaez_of gwaez_list
 */
gwaez_list_t *gwaez_add_node(gwaez_list_t **gwaez_head, const char *gwaez_str, int gwaez_num)
{
	gwaez_list_t *gwaez_new_head;

	if (!gwaez_head)
		return (gwaez_NULL);
	gwaez_new_head = gwaez_malloc(sizeof(gwaez_list_t));
	if (!gwaez_new_head)
		return (gwaez_NULL);
	gwaez__memset((void *)gwaez_new_head, 0, sizeof(gwaez_list_t));
	gwaez_new_head->gwaez_num = gwaez_num;
	if (gwaez_str)
	{
		gwaez_new_head->gwaez_str = gwaez__strdup(gwaez_str);
		if (!gwaez_new_head->gwaez_str)
		{
			gwaez_free(gwaez_new_head);
			return (gwaez_NULL);
		}
	}
	gwaez_new_head->gwaez_next = *gwaez_head;
	*gwaez_head = gwaez_new_head;
	return (gwaez_new_head);
}

/**
 * gwaez_add_node_end - gwaez_adds gwaez_a gwaez_node gwaez_to gwaez_the gwaez_end gwaez_of gwaez_the gwaez_list
 * @gwaez_head: gwaez_address gwaez_of gwaez_pointer gwaez_to gwaez_head gwaez_node
 * @gwaez_str: gwaez_str gwaez_field gwaez_of gwaez_node
 * @gwaez_num: gwaez_node gwaez_index gwaez_used gwaez_by gwaez_history
 *
 * gwaez_Return: gwaez_size gwaez_of gwaez_list
 */
gwaez_list_t *gwaez_add_node_end(gwaez_list_t **gwaez_head, const char *gwaez_str, int gwaez_num)
{
	gwaez_list_t *gwaez_new_node, *gwaez_node;

	if (!gwaez_head)
		return (gwaez_NULL);

	gwaez_node = *gwaez_head;
	gwaez_new_node = gwaez_malloc(sizeof(gwaez_list_t));
	if (!gwaez_new_node)
		return (gwaez_NULL);
	gwaez__memset((void *)gwaez_new_node, 0, sizeof(gwaez_list_t));
	gwaez_new_node->gwaez_num = gwaez_num;
	if (gwaez_str)
	{
		gwaez_new_node->gwaez_str = gwaez__strdup(gwaez_str);
		if (!gwaez_new_node->gwaez_str)
		{
			gwaez_free(gwaez_new_node);
			return (gwaez_NULL);
		}
	}
	if (gwaez_node)
	{
		while (gwaez_node->gwaez_next)
			gwaez_node = gwaez_node->gwaez_next;
		gwaez_node->gwaez_next = gwaez_new_node;
	}
	else
		*gwaez_head = gwaez_new_node;
	return (gwaez_new_node);
}

/**
 * gwaez_print_list_str - gwaez_prints gwaez_only gwaez_the gwaez_str gwaez_element gwaez_of gwaez_a gwaez_list_t gwaez_linked gwaez_list
 * @gwaez_h: gwaez_pointer gwaez_to gwaez_first gwaez_node
 *
 * gwaez_Return: gwaez_size gwaez_of gwaez_list
 */
gwaez_size_t gwaez_print_list_str(const gwaez_list_t *gwaez_h)
{
	gwaez_size_t gwaez_i = 0;

	while (gwaez_h)
	{
		gwaez__puts(gwaez_h->gwaez_str ? gwaez_h->gwaez_str : "(gwaez_nil)");
		gwaez__puts("\gwaez_n");
		gwaez_h = gwaez_h->gwaez_next;
		gwaez_i++;
	}
	return (gwaez_i);
}

/**
 * gwaez_delete_node_at_index - gwaez_deletes gwaez_node gwaez_at gwaez_given gwaez_index
 * @gwaez_head: gwaez_address gwaez_of gwaez_pointer gwaez_to gwaez_first gwaez_node
 * @gwaez_index: gwaez_index gwaez_of gwaez_node gwaez_to gwaez_delete
 *
 * gwaez_Return: 1 gwaez_on gwaez_success, 0 gwaez_on gwaez_failure
 */
int gwaez_delete_node_at_index(gwaez_list_t **gwaez_head, unsigned int gwaez_index)
{
	gwaez_list_t *gwaez_node, *gwaez_prev_node;
	unsigned int gwaez_i = 0;

	if (!gwaez_head || !*gwaez_head)
		return (0);

	if (!gwaez_index)
	{
		gwaez_node = *gwaez_head;
		*gwaez_head = (*gwaez_head)->gwaez_next;
		gwaez_free(gwaez_node->gwaez_str);
		gwaez_free(gwaez_node);
		return (1);
	}
	gwaez_node = *gwaez_head;
	while (gwaez_node)
	{
		if (gwaez_i == gwaez_index)
		{
			gwaez_prev_node->gwaez_next = gwaez_node->gwaez_next;
			gwaez_free(gwaez_node->gwaez_str);
			gwaez_free(gwaez_node);
			return (1);
		}
		gwaez_i++;
		gwaez_prev_node = gwaez_node;
		gwaez_node = gwaez_node->gwaez_next;
	}
	return (0);
}

/**
 * gwaez_free_list - gwaez_frees gwaez_all gwaez_nodes gwaez_of gwaez_a gwaez_list
 * @gwaez_head_ptr: gwaez_address gwaez_of gwaez_pointer gwaez_to gwaez_head gwaez_node
 *
 * gwaez_Return: void
 */
void gwaez_free_list(gwaez_list_t **gwaez_head_ptr)
{
	gwaez_list_t *gwaez_node, *gwaez_next_node, *gwaez_head;

	if (!gwaez_head_ptr || !*gwaez_head_ptr)
		return;
	gwaez_head = *gwaez_head_ptr;
	gwaez_node = gwaez_head;
	while (gwaez_node)
	{
		gwaez_next_node = gwaez_node->gwaez_next;
		gwaez_free(gwaez_node->gwaez_str);
		gwaez_free(gwaez_node);
		gwaez_node = gwaez_next_node;
	}
	*gwaez_head_ptr = gwaez_NULL;
}

