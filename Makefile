all:
	gcc -o start main.c util.c game.c file.c list.c

clean:
	rm -rf *.o start

re: clean all

test:
	make re && ./start
