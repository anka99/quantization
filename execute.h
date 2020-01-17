#ifndef QUANTIZATION_EXECUTE_H
#define QUANTIZATION_EXECUTE_H
#include "input.h"
#include "engine.h"
#include "structures.h"

/*Funkcja execute_commands wczytuje polecenie, rozpoznaje jego typ i wywołuje
 * odpowiednią funkcję. Zwraca wartość:
 * 1) MEMORY_ERROR - jeśli wystąpił błąd alokacji pamięci;
 * 2) END - jeśli nastąpił koniec czytanego pliku;
 * 3) DONE - w przeciwnym wypadku.
 * */
int execute_commands(tree_t *root);

#endif //QUANTIZATION_EXECUTE_H
