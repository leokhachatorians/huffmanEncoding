first:
	gcc -c -Wall -Werror -fpic huffman.c
	gcc -shared -o libhuffman.so huffman.o
	gcc -L/home/leo/Documents/CStuff/huffman -Wl,-rpath=/home/leo/Documents/CStuff/huffman -g3 -Wall main.c -l huffman
