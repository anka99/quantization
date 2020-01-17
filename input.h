#ifndef QUANTIZATION_INPUT_H
#define QUANTIZATION_INPUT_H

#include <stdint.h>

#define NONE 0
#define ERROR -2
#define DECLARE 1
#define REMOVE 2
#define VALID 3
#define ENERGY_H 4
#define ENERGY_H_N 5
#define EQUAL 6

typedef struct Command Command;

struct Command {

  //Jeden z: DECLARE, REMOVE, VALID, EQUAL, ENERGY
  int type;

  //Możliwe znaki w history_a i history_b: 0, 1, 2, 3
  char *history_a;
  char *history_b;
  int *int_history_a;
  unsigned length_a;
  int *int_history_b;
  unsigned length_b;
  uint64_t energy;

  //Wskaźnik na odczytaną linię polecenia. Potrzebny, żeby zwolnić pamięć.
  char *line;
};

/*
 * Funkcja wczytuje pojedynczą linię polecenia i zwraca utworzoną strukturę
 * komendy.
 */
Command *read_line();

/*
 * Funkcja usuwa strukturę komendy zwalniając zaalokowaną pamięć.
 */
void free_command(Command *command);

#endif //QUANTIZATION_INPUT_H
