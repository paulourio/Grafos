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
    int             value;
    struct lst_node *next;
};

typedef struct lst_node lst_node;
typedef lst_node *list;


/*  Compare function for linked list
 *  Example:
 *      bool cmp(int a) { return (a % 2); }
 */
typedef bool (*f_lst_cmp_node)(const int);

/* Test if the list is valid (assert will fail when list is empty) */
extern void list_test(const list *lst) __nonnull ((1));
extern void list_clear(register list *lst) __nonnull ((1));
extern bool list_isempty(const list *lst) __attribute_pure__ __wur;

/* Print all items in the format [0, 1, 2, ...] */
extern void list_print(const list *lst) __nonnull ((1));

extern int *list_get(register list *lst, register int index) __nonnull ((1))
    __wur;
    
extern list list_get_back_node(const list *lst) __nonnull ((1)) __wur;

/* Remove methods */
extern size_t list_remove(const list *lst, const int value) __nonnull ((1));
extern size_t list_delete_if(list *lst, const f_lst_cmp_node fcmp) 
		__nonnull ((1, 2));
extern void list_remove_front(register list *lst) __nonnull ((1));
extern void list_remove_back(register list *lst) __nonnull ((1));
extern void list_remove_pos(register list *lst, size_t pos) __nonnull ((1));

/* Insert methods */
extern void list_insert_pos(list *lst, size_t pos, const int value) 
	__nonnull ((1));
extern void list_insert_front(list *lst, const int value) __nonnull ((1));
extern void list_insert_back(list *lst, const int value) __nonnull ((1));
extern void list_insert_sorted(list *lst, const int value) __nonnull ((1));

/* Populate a list with items, starting at 1. */
extern void list_fill(list *lst, const size_t items) __nonnull ((1));

/* Count how many elements are in the list (It uses the compare function */
extern size_t list_count_if(list *lst, const f_lst_cmp_node fcmp) 
	__nonnull ((1,2)) __wur;

extern bool list_sorted(list *lst) __nonnull((1));

#endif
