#ifndef QUANTIZATION_STRUCTURES_H
#define QUANTIZATION_STRUCTURES_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Struktura listy budującej relacje równoważności między wierzchołkami drzewa.
 */
typedef struct linked_list list_t;

/*
 * Struktura drzewa, w którym każdy wierzchołek ma co najwyżej czwórkę dzieci.
 */
typedef struct four_leaves_tree tree_t;

struct linked_list {
  uint64_t energy;
  unsigned connected;
  unsigned rank;
  struct linked_list *next;
};

struct four_leaves_tree {
  struct four_leaves_tree **children;
  list_t *next;
};

/*Funkcja add_history dodaje nową historię kwantową. Jeśli historia jest
 * niepoprawna lub wystąpi błąd alokacji pamięci, zwraca false. W przeciwnym
 * wypadku zwraca true.
 */
bool add_history(tree_t *root, int *history, unsigned length);

/*
 * Alokuje pamięć i tworzy nowy wierzchołek drzewa. Zwraca wskaźnik na utworzoną
 * strukturę lub NULL jeśli wystąpi błąd alokacji pamięci.
 */
tree_t *new_tree_node();

/*
 * Usuwa podane w parametrze poddrzewo zwalniając zaalokowaną pamięć.
 */
void delete_subtree(tree_t *node);

/*Funkcja delete_tree_node usuwa wierzchołek drzewa odpowiadający podanej
 * historii kwantowej (jeśli taki istnieje i jeśli historia jest poprawna).
 * Usuwa również poddrzewo, którego wspomniany wierchołek jest korzeniem.
 */
void delete_tree_node(tree_t *root, int *history, unsigned length);

/*Funkcja find_node wyszukuje wierzchołek drzewa odpowiadający podanej historii
 * kwantowej. Jeśli wierzchołek istnieje, zwraca wskaźnik na niego. W przeciwnym
 * razie zwraca NULL (również gdy któryś z parametrów jest niepoprawny).
 */
tree_t *find_node(tree_t *root, int *history, unsigned length);

/*
 * Funkcja usuwa wierzchołek listy zwalniając zaalokowaną pamięć. Zmniejsza
 * wartość connected w następnym (wskazywanym przez niego) wierzchołku. Jeśli
 * wartość connected wynosi 0, usuwa wierzchołek i wszystkie kolejne, dopóki
 * wartość connected napotkanego wierzchołka nie będzie dodatnia.
 */
void delete_list_node(list_t *node);

#endif //QUANTIZATION_STRUCTURES_H
