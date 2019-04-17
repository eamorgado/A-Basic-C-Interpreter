CC = gcc

OUT = lib/project.a
IDIR = include
ODIR = obj
SDIR = src

CFLAGS = -I$(IDIR)
LIBS = -lm

_OBJS = ParserExpression.o LinkedListLabel.o LinkedListsHashVar.o \
		LinkedListProgramSequence.o HashTableLabel.o HashTableVar.o \
		CInterpreter.o ShellFile.o ShellInteractive.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))


_DEPSI = *.h
DEPSI = $(patsubst %,$(IDIR)/%,$(_DEPSI))

_DEPSC = *.c
DEPSC = $(patsubst %,$(SDIR)/%,$(_DEPSC))

_DEPSO = *.o
DEPSO = $(patsubst %,$(ODIR)/%,$(_DEPSO))


$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OUT): $(OBJS)
	ar rvs $(OUT) $^

exe: $(DEPSI) $(DEPSC) $(DEPSO)
	make
	$(CC) $(CFLAGS) $(SDIR)/Main.c -L. $(OUT) -o exe $(LIBS)


.PHONY: clean

clean:
	-rm -f $(ODIR)/*.o $(OUT) exe
