parrotsay : parrotsay.o
		cc -o parrotsay parrotsay.o

parrotsay.o : parrotsay.c
		cc -c parrotsay.c

clean :
		rm parrotsay parrotsay.o
