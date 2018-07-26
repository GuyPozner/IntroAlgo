cli: src/cli.o src/threaded_bst.o
	gcc -g -pedantic -Wall src/cli.o src/threaded_bst.o -o cli

cli.o: src/cli.c
	gcc -c -pedantic -Wall src/cli.c -o src/cli.o

threaded_bst.o: src/threaded_bst.c
	gcc -c -pedantic -Wall src/threaded_bst.c -o src/threaded_bst.o