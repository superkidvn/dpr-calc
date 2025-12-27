CC=gcc
DESTDIR=build

all: dpr-calc

dpr-calc: main.c dpr-calc.c
	mkdir -p $(DESTDIR)/bin
	$(CC) -lm -o $(DESTDIR)/bin/dpr-calc $(DESTDIR)/main.o $(DESTDIR)/dpr-calc.o

main.c:
	$(CC) -c -o $(DESTDIR)/main.o src/main.c

dpr-calc.c:
	$(CC) -c -o $(DESTDIR)/dpr-calc.o src/dpr-calc.c

cleanup:
	rm -f $(DESTDIR)/*.o

cleanall:
	rm -rf $(DESTDIR)

.PHONY: cleanup cleanall
