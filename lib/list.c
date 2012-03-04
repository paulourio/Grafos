/*
 *  Author: Paulo Roberto Urio
 *  Date: 2 de Maio de 2011
 *  Description: Linked list source-code.
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


__always_inline __nonnull ((1))
inline void list_test(const list *lst)
{
	assert(*lst != NULL);
}


void list_clear(register list *lst)
{
	list current = *lst, next;

	while (current) {
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}


bool list_isempty(const list *lst)
{
	return (lst == NULL || *lst == NULL);
}


void list_print(const list *lst)
{
	list node = *lst;

	do {
		if (*lst != node)
			printf(", ");
		printf("%i", node->value);
	} while ((node = node->next) != NULL);
	putc('\n', stdout);
}


int *list_get(register list *lst, register int index)
{
	list node = *lst;

	while (node != NULL && index--)
		node = node->next;
	return node != NULL?  &node->value:  NULL;
}


list list_get_back_node(const list *lst)
{
	list node = *lst;

	if (node == NULL)
		return NULL;
	while (node->next)
		node = node->next;
	return node;
}


// Warning: We do not check for invalid arguments.
__always_inline __nonnull ((1))
static void list_remove_node(list *front, list node, list previous)
{
	if (previous != NULL)
		previous->next = node->next;
	else
		*front = node->next;
	free(node);
}


size_t list_delete_if(list *lst, const f_lst_cmp_node fcmp)
{
	list node = *lst, next, previous = NULL;
	size_t result = 0;

	if (node == NULL)
		return 0;
	while (node != NULL) {
		next = node->next;
		if (fcmp(node->value)) {
			list_remove_node(lst, node, previous);
			result++;
		} else {
			previous = node;
		}
		node = next;
	}
	return result;
}


size_t list_remove(const list *lst, const int value)
{
	list prev = NULL, node = *lst;
	size_t count = 0;

	while (node != NULL) {
		list next = node->next;

		if (node->value == value) {
			list_remove_node((list *) lst, node, prev);
			count++;
		} else {
			prev = node;
		}
		node = next;
	}
	return count;
}


void list_remove_front(register list *lst)
{
	if (*lst == NULL)
		return;
	list_remove_node(lst, *lst, NULL);
}


void list_remove_back(register list *lst)
{
	list prev = NULL, node = *lst;

	if (node == NULL)
		return;
	while (node->next && (node = (prev = node)->next))
		; /* VOID */
	list_remove_node(lst, node, prev);
}


void list_remove_pos(register list *lst, size_t pos)
{
	list prev = NULL, node = *lst;

	while (pos-- && node->next && (node = (prev = node)->next))
		; /* VOID */
	list_remove_node(lst, node, prev);
}


__always_inline __nonnull ((1))
static inline void *list_insert_after_node(list node, const int value)
{
	list new_node;

	create_node(new_node, (node != NULL?  node->next:  NULL));
	if (node != NULL)
		node->next = new_node;
	return new_node;
}


void list_insert_pos(list *lst, size_t pos, const int value)
{
	list new_node, node = *lst;

	while (pos != 0 && --pos && (node = node->next))
		; /* VOID */
	new_node = list_insert_after_node(node, value);
	if (*lst == NULL)
		*lst = new_node;
}


void list_insert_front(list *lst, const int value)
{
	list new_node;

	create_node(new_node,*lst);
	*lst = new_node;
}


void list_insert_back(list *lst, const int value)
{
	list node = *lst;

	if (node == NULL) {
		list_insert_front(lst, value);
		return;
	}
	while (node->next && (node = node->next))
		if (node->next == NULL)
			break;
	if (node != NULL)
		list_insert_after_node(node, value);
}


void list_insert_sorted(list *lst, const int value)
{
	list node = *lst;

	if (node == NULL || node->value >= value) {
		list_insert_front(lst, value);
		return;
	}
	while (node->next != NULL) {
		if (node->next->value >= value)
			break;
		node = node->next;
	}
	list_insert_after_node(node, value);
}


void list_fill(list *lst, const size_t items)
{
	size_t i;

	for (i=0; i<items; i++)
		list_insert_front(lst, (int) (items - i));
}


size_t list_count_if(list *lst, const f_lst_cmp_node fcmp)
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


bool list_sorted(list *lst)
{
	list node = *lst;
	int prev;

	if (node == NULL)
		return true;
	while ((prev = node->value) && (node = node->next))
		if (prev >= node->value)
			return false;
	return true;
}
