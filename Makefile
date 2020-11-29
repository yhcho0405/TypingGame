all:
	gcc main.c util.c game.c practice.c file.c list.c typing.h

clean:
	rm -rf *.o a.out typing.h.gch

re: clean all

test:
	make re && ./a.out
