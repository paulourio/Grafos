/*
 *  Author: Paulo Roberto Urio
 *  Date: May 2, 2011
 *  Description: Linked list header.
 */
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <features.h>

struct lst_node {
    void *value;
    struct lst_node *next;
};

typedef struct lst_node lst_node;
typedef lst_node *list;


/* Callback functions for linked list
 * Used for print, free and comparaison.
 * Example:
 *      bool cmp(const void *a) { return ((*(int *)a) % 2); }
 */
typedef bool (*f_lst_callback_node)(const void *);
typedef void (*f_lst_print_node)(const void *, const int);
typedef int (*f_lst_compare_nodes)(const void *, const void *);

/* Test if the list is valid (assert will fail when list is empty) */
extern void list_clear(list *, f_lst_callback_node) __nonnull ((1));
extern bool list_isempty(const list *);

/* Print all items in the format [0, 1, 2, ...] */
extern void list_print(const list *, const f_lst_print_node) __nonnull ((1));

extern void **list_get(const list *, unsigned int) __nonnull ((1)) __wur;
    
extern list list_get_back_node(const list *) __nonnull ((1)) __wur;

/* Remove methods */
extern size_t list_remove(const list *, const void *,
		const f_lst_callback_node) __nonnull ((1));
extern size_t list_delete_if(list *, const f_lst_callback_node,
		const f_lst_callback_node) __nonnull ((1));
extern void list_remove_front(list *,
		const f_lst_callback_node) __nonnull ((1));
extern void list_remove_back(list *,
		const f_lst_callback_node) __nonnull ((1));
extern bool list_remove_pos(list *, unsigned int,
		const f_lst_callback_node) __nonnull ((1));

/* Insert methods */
extern void list_insert_pos(list *, unsigned int, void *)
	__nonnull ((1));
extern void list_insert_front(list *, void *) __nonnull ((1));
extern void list_insert_back(list *, void *) __nonnull ((1));
extern void list_insert_sorted(list *, void *,
		const f_lst_compare_nodes) __nonnull ((1));

/* Populate a list with items, starting at 1. */
extern void list_fill(list *, const unsigned int) __nonnull ((1));

/* Count how many elements are in the list (It uses the compare function */
extern size_t list_count_if(list *, const f_lst_callback_node)
	__nonnull ((1,2)) __wur;
extern size_t list_count(list *) __nonnull ((1)) __wur;

extern bool list_sorted(list *, const f_lst_compare_nodes) __nonnull ((1));

#endif
