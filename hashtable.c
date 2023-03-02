#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "hashtable.h"

#define MAX_BUCKET_SIZE 64

int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

// Credits: https://stackoverflow.com/a/12996028/7883884
unsigned int
hash_function_int(void *a)
{
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

hashtable_t *
ht_create(unsigned int hmax,
		  unsigned int (*hash_function)(void*),
		  int (*compare_function)(void*, void*))
{
	// Aloc memoria pentru un hashtable si ii setez size-ul si hmax-ul.
	hashtable_t *ht = malloc(sizeof(hashtable_t));
	DIE(!ht, "Malloc failed\n");
	ht->size = 0;
	ht->hmax = hmax;
	// Aloc vectorul de liste, iar pentru fiecare pozitie din vector creez lista.
	ht->buckets = malloc(ht->hmax * sizeof(linked_list_t *));
	for (unsigned int i = 0; i < hmax; i++)
		ht->buckets[i] = ll_create(sizeof(struct info));
	// Setez functiile de comparare.
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;
	return ht;
}

hashtable_t
*ht_resize(hashtable_t *ht);

void
ht_put(hashtable_t **ht,
	   void *key,
	   unsigned int key_size,
	   void *value,
	   unsigned int value_size)
{
	if ((*ht)->size == (*ht)->hmax) {
		*ht = ht_resize(*ht);
	}

	int index = (*ht)->hash_function(key) % (*ht)->hmax;
	ll_node_t *node = (*ht)->buckets[index]->head;
	int ok = 0;
	// Parcurg nod cu nod lista de pe pozitia index si daca gasesc cheia specificata, doar modific valoarea.
	for (unsigned int i = 0; i < (*ht)->buckets[index]->size; i++) {
		if (!(*ht)->compare_function(key, ((struct info *)(node->data))->key)) {
			memcpy(((struct info *)(node->data))->value, value, value_size);
			ok = 1;
		}
		node = node->next;
	}
	// Daca nu gasesc cheia, adaug un nod nou care retine perechea cheie-valoare primita.
	if (!ok) {
		struct info aux;
		aux.key = malloc(key_size);
		DIE(!aux.key, "Malloc failed\n");
		aux.value = malloc(value_size);
		DIE(!aux.value, "Malloc failed\n");
		memcpy(aux.key, key, key_size);
		memcpy(aux.value, value, value_size);
		ll_add_nth_node((*ht)->buckets[index], (*ht)->buckets[index]->size, &aux);
		(*ht)->size++;
	}
}

int
ht_has_key(hashtable_t *ht, void *key)
{
	int index = ht->hash_function(key) % ht->hmax;
	ll_node_t *node = ht->buckets[index]->head;
	// Parcurg lista de pe pozitia index nod cu nod si daca gasesc cheia returnez 1, altfel 0.
	for (unsigned int i = 0; i < ht->buckets[index]->size; i++) {
		if (!ht->compare_function(key, ((struct info *)(node->data))->key))
			return 1;
		node = node->next;
	}
	return 0;
}

void
ht_remove_entry(hashtable_t *ht, void *key)
{
	int index = ht->hash_function(key) % ht->hmax;
	ll_node_t *node = ht->buckets[index]->head;
	unsigned int pos = 0;
	// Parcurg lista de pe pozitia index nod cu nod si cand gasesc cheia ies din for si, in cazul in care nodul nu este
	// nul, il elimin din lista si eliberez memoria din struct info, din data si din nod.
	for (unsigned int i = 0; i < ht->buckets[index]->size; i++) {
		if (!ht->compare_function(key, ((struct info *)(node->data))->key)) {
			pos = i;
			break;
		}
		node = node->next;
	}
	if (node != NULL) {
		node = ll_remove_nth_node(ht->buckets[index], pos);
		free(((struct info *)(node->data))->value);
		free(((struct info *)(node->data))->key);
		free(node->data);
		free(node);
		ht->size--;
	}
}

void
ht_modify(hashtable_t **ht,
		  void *remkey,
		  void *addkey,
		  unsigned int key_size,
		  void *addval,
		  unsigned int value_size)
{
	ht_remove_entry(*ht, remkey);
	ht_put(ht, addkey, key_size, addval, value_size);
}

void
ht_free(hashtable_t *ht)
{
	// Pentru fiecare lista din vectorul de liste, eliberez memoria din fiecare struct info retinut in data, iar apoi
	// eliberez memoria listei prin functia ll_free.
	for (unsigned int i = 0; i < ht->hmax; i++) {
		ll_node_t *node = ht->buckets[i]->head;
		while (node) {
			free(((struct info *)(node->data))->value);
			free(((struct info *)(node->data))->key);
			node = node->next;
		}
		ll_free(&ht->buckets[i]);
	}
	// Eliberez memoria vectorului de liste si a hashtable-ului.
	free(ht->buckets);
	free(ht);
}

hashtable_t
*ht_resize(hashtable_t *ht)
{
	// Creez un hashtable nou, cu hmax dublu.
	hashtable_t *ht_new = ht_create(ht->hmax * 2, ht->hash_function, ht->compare_function);
	// Pornesc cu un nod de la head-ul primului bucket din hashtable-ul initial.
	ll_node_t *node = ht->buckets[0]->head;
	unsigned int i = 0, j = 1;
	while (i < ht->size) {
		// Daca nodul este nul trec la urmatorul bucket.
		if (node == NULL) {
			node = ht->buckets[j++]->head;
		// Altfel adaug in hashtable-ul nou perechea de la nodul respectiv, si trec la nodul urmator.
		} else {
			struct info *aux = (struct info *)(node->data);
			ht_put(&ht_new, aux->key, sizeof(aux->key), aux->value, sizeof(aux->value));
			i++;
			node = node->next;
		}
	}
	// Eliberez memoria hashtable-ului initial si returnez noul hashtable.
	ht_free(ht);
	return ht_new;
}

void
ht_print(hashtable_t *ht, void (*print_node)(ll_node_t*, FILE*), FILE *file)
{
	ll_node_t *node = ht->buckets[0]->head;
	unsigned int i = 0, j = 1;
	while (i < ht->size) {
		if (node == NULL) {
			node = ht->buckets[j++]->head;
		} else {
			print_node(node, file);
			i++;
			node = node->next;
		}
	}

}
