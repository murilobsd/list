/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define SELF ((struct list *)l)

/* typical linked list node */
typedef struct node {
	void		*data;
	struct node 	*next;
} node_t;

/* linked list */
struct list {
	node_t		*head;
	node_t		*tail;
	free_func 	 freefn;
	uint32_t	 length; 	/* number of elements */
	uint32_t 	 size;		/* size of each element */
};

static void	*xmalloc(uint32_t);
static node_t	*node_new(void);

int
list_iterator(list_t *l, iterator_func iter_fn)
{
	node_t 	*node;
	bool 	 res;

	if (l == NULL || iter_fn == NULL)
		return (-1);

	node = SELF->head;
	res = TRUE;

	while (node != NULL && res) {
		res = iter_fn(node->data);
		node = node->next;
	}

	return (0);
}

int
list_append(list_t *l, void *el)
{
	node_t *node;

	if (l == NULL)
		return (-1);

	node = node_new();
	node->data = xmalloc(SELF->size);
	node->next = NULL;
	memcpy(node->data, el, SELF->size);

	if (SELF->length == 0) {
		SELF->head = node;
		SELF->tail = node;
	} else {
		SELF->tail->next = node;
		SELF->tail = node;
	}

	SELF->length++;

	return (0);
}

int
list_prepend(list_t *l, void *el)
{
	node_t *node;

	if (l == NULL)
		return (-1);

	/* init and copy data to node */
	node = node_new();
	node->data = xmalloc(SELF->size);
	memcpy(node->data, el, SELF->size);

	node->next = SELF->head;
	SELF->head = node;

	/* is first node */
	if (SELF->tail == NULL)
		SELF->tail = SELF->head;

	SELF->length++;

	return (0);
}

static node_t *
node_new(void)
{
	node_t *n;

	n = xmalloc(sizeof(node_t));

	return n;
}

int
list_last_el(list_t *l, void *el)
{
	node_t *node;

	if (l == NULL || SELF->tail == NULL)
		return (-1);

	node = SELF->tail;
	memcpy(el, node->data, SELF->size);

	return (0);
}

int
list_first_el(list_t *l, void *el)
{
	node_t *node;

	if (l == NULL || SELF->head == NULL)
		return (-1);

	node = SELF->head;
	memcpy(el, node->data, SELF->size);

	return (0);
}

uint32_t
list_len(list_t *l)
{
	return SELF->length;
}

void
list_free(list_t *l)
{
	node_t *current;

	if (l == NULL) return;

	while (SELF->head != NULL) {
		current = SELF->head;
		SELF->head = current->next;

		if (SELF->freefn)
			SELF->freefn(current->data);

		free(current->data);
		free(current);
	}

	free(l);
}

list_t *
list_new(uint32_t el_size, free_func freefn)
{
	list_t *l;

	l = (list_t *)xmalloc(sizeof(list_t));

	SELF->head = NULL;
	SELF->tail = NULL;
	SELF->freefn = freefn;
	SELF->length = 0;
	SELF->size = el_size;

	return l;
}

static void *
xmalloc(uint32_t size)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
		err(1, "malloc");

	return p;
}
