first:
	gcc -c -Wall -Werror -fpic huffman.c
	gcc -shared -o libhuffman.so huffman.o
	gcc -L/home/leo/Documents/CStuff/huffman -Wl,-rpath=/home/leo/Documents/CStuff/huffman -Wall main.c -l huffman

second:
	gcc -shared -o libhuffman.so huffman.o

third:
	gcc -L/home/leo/Documents/CStuff/huffman -Wl,-rpath=/home/leo/Documents/CStuff/huffman -Wall main.c -l huffman
