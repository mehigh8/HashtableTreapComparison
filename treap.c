#include "treap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRIORITY 1000

Treap_tree*
treap_create(int (*cmp)(void*, void*))
{
    srand(time(NULL));
    Treap_tree* tree = malloc(sizeof(Treap_tree));
    tree->compar = cmp;
    if (tree == NULL) {
        return NULL;
    }
    tree->root = NULL;
    return tree;
}
void
node_free(Node** node)
{

    if (!(*node)) {
        return;
    }
    node_free(&(*node)->left);
    node_free(&(*node)->right);

    free((*node)->data);
    free(*node);
}

void
treap_free(Treap_tree* tree)
{
    if (tree->root != NULL) {
        node_free(&tree->root);
    }
    free(tree);
}

Node*
node_create(void* value, int data_size)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(data_size);

    // Copiere octet cu octet din value, in nodul curent.
    for (int i = 0; i < data_size; ++i) {
        *(char*)(node->data + i) = *(char*)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
    node->priority = rand() % MAX_PRIORITY;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int
priority(Node* node)
{
    if (node == NULL) {
        return -1;
    }
    return node->priority;
}

void
rotate_right(Node** node)
{
    // Retin intr-o variabila auxiliara fiul drept (lrson) al fiului stang
    // al nodului.
    Node *aux = (*node)->left->right;
    // Fiul drept al fiului stang devine nodul initial.
    (*node)->left->right = *node;
    // Valoarea de la adresa nodului initial devine fiul stang.
    *node = (*node)->left;
    // Fiul stang al fiului drept (vechiul nod initial) devine noul retinut
    // in variabila auxiliara.
    (*node)->right->left = aux;
}

void
rotate_left(Node** node)
{
    // Analog rotate_right, dar se schimba left cu right.
    Node *aux = (*node)->right->left;
    (*node)->right->left = *node;
    *node = (*node)->right;
    (*node)->left->right = aux;
}

void
treap_insert(Node** node,
             void* value,
             int data_size,
             int (*compar)(void*, void*))
{
    // Daca nodul este NULL, inseamna ca am ajuns la frunza ce trebuie creata.
    if (!(*node)) {
        *node = node_create(value, data_size);
        return;
    } else if (compar(value, (*node)->data) < 0) {
        // Daca valoarea ce trebuie adaugata este mai mica decat cea a nodului
        // curent, reapelez functia pentru fiul stang.
        treap_insert(&(*node)->left, value, data_size, compar);
        // Dupa apel, verific daca este necesara rotirea la dreapta pentru a
        // mentine proprietatile de Heap.
        if (priority((*node)->left) > priority(*node))
            rotate_right(node);
    } else {
        // Daca valoarea nu era mai mica, se considera ca este mai mare (chiar daca
        // ar putea fi si egala), deoarece nodul nou trebuie adaugat pe o frunza.
        // Apoi, reapelez functia pentru fiul drept.
        treap_insert(&(*node)->right, value, data_size, compar);
        // Si verific daca este necesara rotirea la stanga.
        if (priority((*node)->right) > priority(*node))
            rotate_left(node);
    }
}

void
treap_delete(Node** node, void* value, int (*compar)(void*, void*))
{
    // Daca nodul nu este gasit se iese din functie.
    if (!(*node)) {
        return;
    } else if (compar(value, (*node)->data) < 0) {
        // Daca exista nodul verific daca valoarea cautata este mai mica, caz
        // in care reapelez functie pentru fiul stang.
        treap_delete(&(*node)->left, value, compar);
    } else if (compar(value, (*node)->data) > 0) {
        // Cazul in care este mai mare.
        treap_delete(&(*node)->right, value, compar);
    } else if ((*node)->left == NULL && (*node)->right == NULL) {
        // Daca nu este niciunul din cazuri, inseamna ca am gasit nodul ce
        // trebuie eliminat. In cazul in care este frunza poate fi eliminat
        // direct.
        free((*node)->data);
        free(*node);
        *node = NULL;
    } else if (priority((*node)->left) > priority((*node)->right)) {
        // Daca nu este frunza, in functie de valorile prioritatilor fiilor
        // aplic o rotire la dreapta sau la stanga, iar apoi reapelez functia
        // de delete, intrucat acum nodul nu mai este corect.
        rotate_right(node);
        treap_delete(node, value, compar);
    } else {
        rotate_left(node);
        treap_delete(node, value, compar);
    }

}

void
treap_modify(Node** node,
             void* remval,
             void* addval,
             int data_size,
             int (*compar)(void*, void*))
{
    treap_delete(node, remval, compar);
    treap_insert(node, addval, data_size, compar);
}

void
treap_print(Node* node, void (*print_node)(Node*, FILE*), FILE *file)
{
    if (node == NULL) {
        return;
    }
    treap_print(node->left, print_node, file);
    print_node(node, file);
    treap_print(node->right, print_node, file);
}

void*
get_key(Node* node, void* value, int (*compar)(void*, void*))
{
    // Daca nu este gasit nodul, functia returneaza NULL.
    if (!node)
        return NULL;
    // Caut nodul dupa valoarea primita. Daca este mai mica reapelez functia
    // pentru fiul stang.
    if (compar(value, node->data) < 0)
        return get_key(node->left, value, compar);
    // Daca este mai mare o reapelez pentru fiul drept.
    else if (compar(value, node->data) > 0)
        return get_key(node->right, value, compar);
    // Altfel, inseamna ca am gasit nodul si returnez data-ul nodului.
    else
        return node->data;
}
