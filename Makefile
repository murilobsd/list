list.o: list.c
	${CC} -std=c89 -O2 -g -c list.c

example: list.o
	${CC} -std=c89 -O2 -g -Wall -I. -Werror example.c list.o -o example

check: example
	valgrind --leak-check=yes ./example
clean:
	rm -f *.o *.core *.out
