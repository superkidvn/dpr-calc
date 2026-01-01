CC=gcc
DESTDIR=build

all: dpr-calc

dpr-calc: main.o dpr-calc.o
	mkdir -p $(DESTDIR)/bin
	$(CC) -o $(DESTDIR)/bin/dpr-calc $(DESTDIR)/main.o $(DESTDIR)/dpr-calc.o

main.o: main.c dpr-calc.h
	$(CC) -c -o $(DESTDIR)/main.o src/main.c

dpr-calc.o: dpr-calc.c dpr-calc.h
	$(CC) -c -o $(DESTDIR)/dpr-calc.o src/dpr-calc.c

cleanup:
	rm -f $(DESTDIR)/*.o

cleanall:
	rm -rf $(DESTDIR)

.PHONY: cleanup cleanall
