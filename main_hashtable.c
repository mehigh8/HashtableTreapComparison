#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#define HMAX 1

// Functie care afiseaza cheia stocata intr-un nod.
void print_node(ll_node_t *node, FILE *file)
{
	fprintf(file, "%d ", *(int *)((struct info *)(node->data))->key);
}

int main(void)
{
	FILE *fin = fopen("test.in", "r");
	FILE *fout = fopen("test.out", "w");

	hashtable_t *ht = ht_create(HMAX, hash_function_int, compare_function_ints);
	char c;
	int value;
	while (1) {
		fscanf(fin, "%c", &c);
		if (c == 'A') {
			fscanf(fin, "%d\n", &value);
			ht_put(&ht, &value, sizeof(int), &value, sizeof(int));
		} else if (c == 'R') {
			fscanf(fin, "%d\n", &value);
			ht_remove_entry(ht, &value);
		} else if (c == 'M') {
			int new_value;
			fscanf(fin, "%d %d\n", &value, &new_value);
			ht_modify(&ht, &value, &new_value, sizeof(int), &new_value, sizeof(int));
		} else if (c == 'F') {
			fscanf(fin, "%d\n", &value);
			fprintf(fout, "%d\n", ht_has_key(ht, &value));
		} else if (c == 'P') {
			ht_print(ht, print_node, fout);
			fprintf(fout, "\n");
		} else if (c == 'S') {
			ht_free(ht);
			break;
		}
	}
	fclose(fin);
	fclose(fout);
	return 0;
}