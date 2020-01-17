#include <stdbool.h>
#include "structures.h"

#ifndef QUANTIZATION_ENGINE_H
#define QUANTIZATION_ENGINE_H

/*Funkcja declare_history dodaje do drzewa historii kwatowych wierzchołek
 * odpowiadający historii danej w parametrze history. Tym samym powoduje, że
 *  każda kwantowa historia cząstki, będąca prefiksem history staje się
 *  dopuszczalna. Jeśli wystąpi błąd alokacji pamięci lub któryś z parametrów
 *  jest niepoprawny - zwraca false. W przeciwnym razie zwraca true.
 */
bool declare_history(tree_t *root, int *history, unsigned length);

/*Funkcja remove_history usuwa z drzewa historii kwantowych wierzchołek
 * odpowiadający danej w parametrze history historii kwantowej oraz poddrzewo,
 * którego wspomniany wierzchołek jest korzeniem.
 */
void remove_history(tree_t *root, int *history, unsigned length);

/*Funkcja valid_history sprawdza, czy podana w parametrze history kwantowa
 * kwantowa historia cząstki jest dopuszczalna. Jeśli nie jest lub któryś z
 * parametrów jest niepoprawny - zwraca false. W przeciwnym razie zwraca true.
 */
bool valid_history(tree_t *root, int *history, unsigned length);

/*Funkcja show_energy zwraca wartość energi przypisanej danej w parametrze
 * history kwantowej historii cząstki. Jeśli historia jest błędna,
 * niedopuszczalna lub nie ma przypisanej energii zwraca wartość 0.
 */
uint64_t show_energy(tree_t *root, int *history, unsigned length);

/*Funkcja set_energy przypisuje podanej w parametrze history historii kwantowej
 * cząstki energię energy. Jeśli historia jest niedopuszczalna lub nieprawidłowa
 * zwraca false. W przeciwnym razie zwraca true.
 */
bool set_energy(tree_t *root, int *history, unsigned length, uint64_t energy);

/*
 * Jeśli podane w parametrach history_a i history_b kwantowe historie cząstki są
 * dopuszczalne, to funkcja equal:
 * (a) jeśli chociaż jedna z nich ma przypisaną energię, zrównuje ich energie i
 * domyka relację równoważności;
 * (b) jeśli obie historie przed wykonaniem tego polecenia mają przypisane
 * energie, to po wykonaniu polecenia energia przypisana tym historiom jest
 * średnią arytmetyczną tych energii (z ewentualnym zaokrągleniem w dół);
 * (c) jeśli obie historie są identyczne lub mają już zrównane energie,
 * niczego nie zmienia.
 * Jeśli podane parametry są nieprawidłowe - zwraca false. W przeciwnym razie
 * zwraca true.
 */
bool equal(tree_t *root, int *history_a, unsigned length_a, int *history_b,
           unsigned length_b);

#endif //QUANTIZATION_ENGINE_H
