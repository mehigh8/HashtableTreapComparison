#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_

typedef struct ll_node_t ll_node_t;
struct ll_node_t {
    void* data;
    ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t {
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

// Functie care creeaza o lista.
linked_list_t*
ll_create(unsigned int data_size);

// Functie care adauga o valoare in lista la pozitia primita ca parametru.
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* data);

// Functie care sterge din lista valoarea de la pozitia primita ca parametru.
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n);

// Functie care intoarce dimensiunea listei.
unsigned int
ll_get_size(linked_list_t* list);

// Functie care elibereaza memoria listei.
void
ll_free(linked_list_t** pp_list);

#endif /* __LINKED_LIST_H_ */
