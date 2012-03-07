/*
 *  Author: Paulo Roberto Urio
 *  Date: May 2, 2011 		Created
 *  Date: March 4, 2012		Converted to generic values
 *  Description: Linked list source-code.
 *  License: FreeBSD
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <features.h>
#include "list.h"

#define create_node(node,next_node) 			\
	{						\
		node = malloc(sizeof(lst_node));	\
		assert(node != NULL);	   		\
		node->value = value;			\
		node->next = next_node;	 		\
	}

static inline void free_node(list node, f_lst_callback_node ffreenode)
{
	if (node->value != NULL) {
		if (ffreenode != NULL)
			ffreenode(node->value);
		else
			free(node->value);
	}
	free(node);
}

/** TODO: Create a list release, to just free the nodes, not try to
 * free the values (no callback) */


void list_clear(list *lst, f_lst_callback_node ffreenode)
{
	list current = *lst, next;

	while (current != NULL) {
		next = current->next;
		free_node(current, ffreenode);
		current = next;
	}
	*lst = NULL;
}


bool list_isempty(const list *lst)
{
	return (lst == NULL || *lst == NULL);
}


void list_print(const list *lst, const f_lst_print_node fprintnode)
{
	list node = *lst;

	do {
		bool first = (*lst != node);

		if (fprintnode == NULL)
			printf("%s%p", (first? ", ": ""), node->value);
		else
			fprintnode(node->value, first == true);
	} while ((node = node->next) != NULL);
	putc('\n', stdout);
}


void **list_get(const list *lst, unsigned int index)
{
	list node = *lst;

	while (node != NULL && index--)
		node = node->next;
	return (node != NULL?  &node->value:  NULL);
}


list list_get_back_node(const list *lst)
{
	list node = *lst;

	while (node != NULL && node->next != NULL)
		node = node->next;
	return node;
}


// Warning: We do not check for invalid arguments.
__always_inline __nonnull ((1))
static void list_remove_node(list *front, list node, list previous,
		const f_lst_callback_node ffreenode)
{
	if (previous != NULL)
		previous->next = node->next;
	else
		*front = node->next;
	free_node(node, ffreenode);
}


size_t list_delete_if(list *lst, const f_lst_callback_node fchecknode,
		const f_lst_callback_node ffreenode)
{
	list node = *lst, next, previous = NULL;
	size_t result = 0;

	if (node == NULL)
		return 0;
	while (node != NULL) {
		next = node->next;
		if (fchecknode(node->value)) {
			list_remove_node(lst, node, previous, ffreenode);
			result++;
		} else {
			previous = node;
		}
		node = next;
	}
	return result;
}


size_t list_remove(const list *lst, const void *value,
		const f_lst_callback_node ffreenode)
{
	list prev = NULL, node = *lst;
	size_t count = 0;

	while (node != NULL) {
		list next = node->next;

		if (node->value == value) {
			list_remove_node((list *) lst, node, prev, ffreenode);
			count++;
		} else {
			prev = node;
		}
		node = next;
	}
	return count;
}


void list_remove_front(list *lst, const f_lst_callback_node ffreenode)
{
	if (*lst == NULL)
		return;
	list_remove_node(lst, *lst, NULL, ffreenode);
}


void list_remove_back(list *lst, const f_lst_callback_node ffreenode)
{
	list prev = NULL, node = *lst;

	if (node == NULL)
		return;
	while (node->next != NULL)
		node = (prev = node)->next;
	list_remove_node(lst, node, prev, ffreenode);
}


bool list_remove_pos(list *lst, unsigned int pos,
		const f_lst_callback_node ffreenode)
{
	list prev = NULL, node = *lst;

	while (pos-- && node->next != NULL)
		node = (prev = node)->next;
	if (node != NULL)
		list_remove_node(lst, node, prev, ffreenode);
	return (node != NULL);
}


__always_inline __nonnull ((1))
static inline void *list_insert_after_node(list node, void *value)
{
	list new_node;

	create_node(new_node, (node != NULL?  node->next:  NULL));
	if (node != NULL)
		node->next = new_node;
	return new_node;
}


void list_insert_pos(list *lst, unsigned int pos, void *value)
{
	list new_node, node = *lst;

	if (node != NULL)
		while (pos-- && node->next != NULL)
			node = node->next;
	new_node = list_insert_after_node(node, value);
	if (*lst == NULL)
		*lst = new_node;
}


void list_insert_front(list *lst, void *value)
{
	list new_node;

	create_node(new_node, *lst);
	*lst = new_node;
}


void list_insert_back(list *lst, void *value)
{
	list node = *lst;

	if (node == NULL) {
		list_insert_front(lst, value);
		return;
	}
	while (node->next != NULL && (node = node->next))
		; /* VOID */
	list_insert_after_node(node, value);
}


void list_insert_sorted(list *lst, void *value,
		const f_lst_compare_nodes fcompare)
{
	list node = *lst;

	if (node == NULL || fcompare(node->value, value) > 0) {
		list_insert_front(lst, value);
		return;
	}
	while (node->next != NULL) {
		if (fcompare(node->next->value, value) > 0)
			break;
		node = node->next;
	}
	list_insert_after_node(node, value);
}


void list_fill(list *lst, const unsigned int items)
{
	unsigned int i;

	for (i = 0;  i < items;  i++) {
		unsigned int *a = malloc(sizeof(unsigned int));
		*a = (items - i);
		list_insert_front(lst, a);
	}
}


size_t list_count_if(list *lst, const f_lst_callback_node fcmp)
{
	list	node = *lst;
	size_t  result = 0;

	if (node == NULL)
		return 0;
	while (node != NULL) {
		if (fcmp(node->value))
			result++;
		node = node->next;
	}
	return result;
}


size_t list_count(list *lst)
{
	list node = *lst;
	size_t result = 0;

	while (node != NULL) {
		result++;
		node = node->next;
	}
	return result;
}


bool list_sorted(list *lst, const f_lst_compare_nodes fcompare)
{
	list node = *lst;
	void *prev;

	if (node == NULL)
		return true;
	while ((prev = node->value) && (node = node->next))
		if (fcompare(prev, node->value) > 0)
			return false;
	return true;
}
