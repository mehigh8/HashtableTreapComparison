#ifndef __TREAP_H_
#define __TREAP_H_

#include <stdio.h>
#define MAX_PRIORITY 1000

typedef struct Node
{
    void* data;
    int priority;

    struct Node *left, *right;
} Node;
typedef struct
{
    Node* root;
    int (*compar)(void*, void*);
} Treap_tree;

// Functie care creeaza structura Treap-ului.
Treap_tree*
treap_create(int (*cmp)(void*, void*));

// Functie care elibereaza memoria unui nod.
void
node_free(Node** node);

// Functie care elibereaza memoria Treap-ului.
void
treap_free(Treap_tree* tree);

/* Creeaza un nod
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node*
node_create(void* value, int data_size);

// Functie care intoarce prioritatea unui nod.
int
priority(Node* node);

/* Rotire dreapta
 *
 *      node  			    lson
 *     /    \			   /    \
 *   lson    y    --->    x    node
 *   /  \     		           /   \
 *  x   lrson                lrson  y
 */
void
rotate_right(Node** node);

/* Rotire stanga
 *
 *     node  			    rson
 *    /    \			   /    \
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */
void
rotate_left(Node** node);

// Functie care insereaza o valoare in Treap.
void
treap_insert(Node** node,
             void* value,
             int data_size,
             int (*compar)(void*, void*));

// Functie care sterge o valoare din Treap.
void
treap_delete(Node** node, void* value, int (*compar)(void*, void*));

// Functie care modifica o valaore din Treap in alta valoare.
void
treap_modify(Node** node,
             void* remval,
             void* addval,
             int data_size,
             int (*compar)(void*, void*));

// Functie care afiseaza toate valorile din Treap.
void
treap_print(Node* node, void (*print_node)(Node*, FILE*), FILE *file);


// Functie care cauta o valoare in Treap. Intoarce valoarea daca o gaseste
// sau NULL altfel.
void*
get_key(Node* node, void* value, int (*compar)(void*, void*));

#endif