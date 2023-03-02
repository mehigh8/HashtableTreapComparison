#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include <stdio.h>
#include "linked_list.h"

struct info {
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t {
	linked_list_t **buckets; /* Array de liste simplu-inlantuite. */
	/* Nr. total de noduri existente curent in toate bucket-urile. */
	unsigned int size;
	unsigned int hmax; /* Nr. de bucket-uri. */
	/* (Pointer la) Functie pentru a calcula valoarea hash asociata cheilor. */
	unsigned int (*hash_function)(void*);
	/* (Pointer la) Functie pentru a compara doua chei. */
	int (*compare_function)(void*, void*);
};

// Functie care creeaza un Hashtable.
hashtable_t *
ht_create(unsigned int hmax,
		  unsigned int (*hash_function)(void*),
		  int (*compare_function)(void*, void*));

// Functie care adauga o pereche (cheie, valoare) in Hashtable. Daca numarul de
// elemente curente atinge valoarea maxima, se redimensioneaza Hashtable-ul.
void
ht_put(hashtable_t **ht,
	   void *key,
	   unsigned int key_size,
	   void *value,
	   unsigned int value_size);

// Functie care verifica daca exista cheia primita ca parametru in Hashtable.
int
ht_has_key(hashtable_t *ht, void *key);

// Functie care sterge din Hashtable o cheie si valoarea care ii corespunde.
void
ht_remove_entry(hashtable_t *ht, void *key);

// Functie care modifica o cheie din Hashtable in alta.
void
ht_modify(hashtable_t **ht,
		  void *remkey,
		  void *addkey,
		  unsigned int key_size,
		  void *addval,
		  unsigned int value_size);

// Functie care elibereaza memoria Hashtable-ului.
void
ht_free(hashtable_t *ht);

// Functie care redimensioneaza Hashtable-ul, dublandu-i dimensiunea maxima.
hashtable_t
*ht_resize(hashtable_t *ht);

// Functie care afiseaza toate valorile din Hashtable.
void
ht_print(hashtable_t *ht, void (*print_node)(ll_node_t*, FILE*), FILE *file);

int
compare_function_ints(void *a, void *b);

unsigned int
hash_function_int(void *a);

#endif
