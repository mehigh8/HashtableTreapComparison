CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

.PHONY: clean pack

build: treap hashtable

treap: main_treap.o treap.o
	$(CC) $^ -o $@
	
main_treap.o: main_treap.c
	$(CC) $(CFLAGS) $^ -c
	
treap.o: treap.c treap.h
	$(CC) $(CFLAGS) $^ -c

hashtable: main_hashtable.o hashtable.o linked_list.o
	$(CC) $^ -o $@
	
main_hashtable.o: main_hashtable.c
	$(CC) $(CFLAGS) $^ -c
	
hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) $^ -c
	
linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) $^ -c
	
run-p1: build
	./hashtable
	
run-p2: build
	./treap
	
run-best: build
	./hashtable
	
pack:
	zip -FSr mihai_cosmin.rosu.zip README Makefile *.c *.h in/* out/*
	
clean:
	rm -f *.o treap hashtable *.h.gch
