CC=gcc
CFLAGS = -lm
DFLAGS =
PROGS = assignment4

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ -lm

clean:
	rm -f $f $(PROGS) *.o ~*
