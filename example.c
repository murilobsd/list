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

#include <stdio.h>

#include "list.h"

bool print_int(void *);

int
main(void)
{
	int		 i;
	int		 n_max;
	int		 first;
	int		 last;
	uint32_t	 el_size;
	list_t 		*list = NULL;

	i = 0;
	n_max = 10;
	el_size = sizeof(int);
	list = list_new(el_size, NULL);

	for (i = 1; i <= n_max; i++)
		list_append(list, &i);

	if (list_first_el(list, &first) == 0)
		printf("first value: %d\n", first);

	if (list_last_el(list, &last) == 0)
		printf("last value: %d\n", last);

	/* append number 1 to last position */
	list_append(list, &first);

	if (list_last_el(list, &last) == 0)
		printf("new last value: %d\n", last);

	/* prepend number 10 to last position */
	list_prepend(list, &n_max);

	if (list_first_el(list, &first) == 0)
		printf("new first value: %d\n", first);

	printf("List size: %u elements\n", list_size(list));

	list_iterator(list, print_int);

	list_free(list);

	return (0);
}

bool
print_int(void *el)
{
	printf("Value: %d\n", *(int *)el);
	return TRUE;
}
