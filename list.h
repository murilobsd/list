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

#ifndef _LIST_H
#define _LIST_H

#include <stdint.h>

typedef enum {
	FALSE,
	TRUE
} bool;

/* function free data */
typedef void (*free_func)(void *);

/* function iterator */
typedef bool (*iterator_func)(void *);

/* linked list */
typedef struct list list_t;

list_t		*list_new(uint32_t, free_func);
void		 list_free(list_t *);
uint32_t	 list_size(list_t *);
int		 list_first_el(list_t *, void *);
int		 list_last_el(list_t *, void *);
int		 list_prepend(list_t *, void *);
int		 list_append(list_t *, void *);
int		 list_iterator(list_t *, iterator_func);

#endif /* _LIST_H */
