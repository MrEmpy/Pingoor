CC = gcc
all:
	mv src/pingoor.h src/pingoor.h.bak
	sed -e "s/127.0.0.1/$(HOST)/" -e "s/1234/$(PORT)/" src/pingoor.h.bak > src/pingoor.h
	$(CC) -o pingoor src/pingoor.c -static
	rm src/pingoor.h
	mv src/pingoor.h.bak src/pingoor.h

clean:
	rm pingoor
