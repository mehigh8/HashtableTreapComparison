#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"

// Functie de comparare a valorilor din Treap.
int
compar(void *value1, void *value2)
{
	int *a = (int *)value1;
	int *b = (int *)value2;
	if ((*a) > (*b)) {
		return 1;
	} else if ((*a) < (*b)) {
		return -1;
	}
	return 0;
}

// Functie care afiseaza valoarea stocata intr-un nod.
void
print_node(Node* node, FILE* file)
{
	fprintf(file, "%d ", *(int *)node->data);
}

int main(void)
{
	FILE *fin = fopen("test.in", "r");
	FILE *fout = fopen("test.out", "w");

	Treap_tree *tree = treap_create(compar);
	char c;
	int value;
	while (1) {
		fscanf(fin, "%c", &c);
		if (c == 'A') {
			fscanf(fin, "%d\n", &value);
			treap_insert(&tree->root, &value, sizeof(int), tree->compar);
		} else if (c == 'R') {
			fscanf(fin, "%d\n", &value);
			treap_delete(&tree->root, &value, tree->compar);
		} else if (c == 'M') {
			int new_value;
			fscanf(fin, "%d %d\n", &value, &new_value);
			treap_modify(&tree->root, &value, &new_value, sizeof(int), tree->compar);
		} else if (c == 'F') {
			fscanf(fin, "%d\n", &value);
			if (get_key(tree->root, &value, tree->compar))
				fprintf(fout, "1\n");
			else
				fprintf(fout, "0\n");
		} else if (c == 'P') {
			treap_print(tree->root, print_node, fout);
			fprintf(fout, "\n");
		} else if (c == 'S') {
			treap_free(tree);
			break;
		}
	}
	fclose(fin);
	fclose(fout);
	return 0;
}