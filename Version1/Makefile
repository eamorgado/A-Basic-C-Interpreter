CC = gcc
DEPS = *.h *.c

EXE: $(DEPS)
	$(CC) -c *.c
	ar -rc project.a *.o
	ranlib project.a
	$(CC) Main.c -L. project.a -o exe -lm

clean:
	-rm -f *.o *.a exe
