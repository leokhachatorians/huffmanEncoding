first:
	gcc -c -Wall -Werror -fpic huffman.c
	gcc -shared -o libhuffman.so huffman.o
	gcc -L/home/leo/Documents/c_stuff/huffmanEncoding -Wl,-rpath=/home/leo/Documents/c_stuff/huffmanEncoding -g3 -Wall main.c -l huffman
