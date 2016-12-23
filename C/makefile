first:
	gcc -c -Wall -Werror -fpic huffman.c
	gcc -shared -o libhuffman.so huffman.o
	gcc -L$(CURDIR) -Wl,-rpath=$(CURDIR) -g3 -Wall main.c -l huffman
