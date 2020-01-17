#ifdef _STDC_ALLOC_LIB_
#define _STDC_WANT_LIB_EXT2_ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "input.h"
#include "defines.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DECLARE_STR "DECLARE"
#define REMOVE_STR "REMOVE"
#define VALID_STR "VALID"
#define ENERGY_STR "ENERGY"
#define EQUAL_STR "EQUAL"

/*Funkcja new_command tworzy nową strukturę command. Jeśli nie udało się
 * zaalokować pamięci zwraca NULL.
 */
static Command *new_command() {
  Command *new;
  if (!(new = malloc(sizeof(Command)))) {
    return NULL;
  }
  new->type = NONE;
  new->history_a = NULL;
  new->int_history_a = NULL;
  new->length_a = 0;
  new->history_b = NULL;
  new->int_history_b = NULL;
  new->length_a = 0;
  new->energy = 0;
  new->line = NULL;
  return new;
}

void free_command(Command *command) {
  if (command) {
    if (command->line) {
      free(command->line);
    }
    if (command->int_history_a) {
      free(command->int_history_a);
    }
    if (command->int_history_b) {
      free(command->int_history_b);
    }
    free(command);
  }
}

/*Funkcja split_line dzieli wczytaną linię wejścia na pojedyncze wyrazy,
 * zastępując każdą spacje znakiem \0.
 */
static void split_line(char *line, uint64_t length) {
  if (line) {
    for (uint64_t i = 0; i < length; i++) {
      if (line[i] == ' ') {
        line[i] = '\0';
      }
    }
  }
}

/*Funkcja valid_command sprawdza, czy pierwszy wyraz lini to jeden z : DECLARE,
 * REMOVE, VALID, ENERGY, EQUAL. Jeśli tak, to wypełnia w strukturze command
 * pole type odpowiednią wartością i zwraca true. W przeciwnym razie zwraca
 * false.
 * */
static bool valid_command(char *line, Command *command) {
  if (strcmp(line, DECLARE_STR) == 0) {
    command->type = DECLARE;
    return true;
  }
  if (strcmp(line, REMOVE_STR) == 0) {
    command->type = REMOVE;
    return true;
  }
  if (strcmp(line, VALID_STR) == 0) {
    command->type = VALID;
    return true;
  }
  if (strcmp(line, EQUAL_STR) == 0) {
    command->type = EQUAL;
    return true;
  }
  if (strcmp(line, ENERGY_STR) == 0) {
    return true;
  }
  return false;
}

/*
 * Funkcja sprawdza poprawność kwantowej historii cząstki.
 */
static bool valid_history(char *line, uint64_t *pointer, uint64_t length) {
  while ((*pointer) < length && line[*pointer] != '\0' &&
         line[*pointer] != '\n') {
    if (line[*pointer] != '0' && line[*pointer] != '1' &&
        line[*pointer] != '2' && line[*pointer] != '3') {
      return false;
    }
    (*pointer)++;
  }
  return true;
}
/*Funkcja read_history sprawdza czy ciąg znaków linii począwszy od znaku
 * wskazywanego przez pointer jest poprawną historią cząstki. Jeśli tak, zwraca
 * wskaźnik na tę historię. W przeciwnym razie zwraca NULL.
 */
static char *read_history(char *line, uint64_t *pointer, uint64_t length) {
  uint64_t local_pointer = *pointer;
  if (valid_history(line, pointer, length)) {
    return line + local_pointer;
  }
  return NULL;
}
/*Funkcja move_to_history przesuwa pointer do miejsca w linii, gdzie zaczyna się
 * potencjalna historia kwantowa cząstki. Zwraca false, jeśli natrafiła na
 * koniec linii. W przeciwnym razie zwraca true.
 */
static bool move_to_history(char *line, uint64_t *pointer, uint64_t length) {
  while (*pointer < length && line[*pointer] != '\0') {
    if (line[*pointer] == '\n' || line[*pointer] == EOF) {
      return false;
    }
    (*pointer)++;
  }
  (*pointer)++;
  return (*pointer < length - 1);
}

/*
 * Funkcja przekształca napis od podanego momentu w liczbę całkowitą i ją
 * zwraca.
 */
static uint64_t read_big_number(char *line, uint64_t *pointer) {
  uint64_t energy = 0;
  uint64_t ten = 1;
  uint64_t temp = *pointer;
  while(line[temp] != '\n') {
    if (line[temp] < '0' || line[temp] > '9') {
      return energy;
    }
    temp++;
  }
  uint64_t temp2 = temp;
  temp--;
  while(temp >= *pointer) {
    if (energy > UINT64_MAX - (int)(line[temp] - '0') * ten) {
      return 0;
    }
    energy = energy + ((int)(line[temp] - '0') * ten);
    ten = ten * 10;
    temp--;
  }
  *pointer = temp2;
  return energy;
}

/*
 * Funkcja sprawdza poprawność i wczytuje wartość energii cząstki.
 */
static uint64_t read_energy(char *line, uint64_t *pointer) {
  uint64_t energy = 0;
  if (line[*pointer] < '1' || line[*pointer] > '9') {
    return energy;
  }
  energy = read_big_number(line, pointer);
  return energy;
}

/*Funkcja str_to_int przekształca podany w parametrze history napis o długości
 * podanej w parametrze length na tablicę liczb całkowitych. W przypadku błędu
 * (błąd alokacji pamięci, history wskazuje na NULL) zwraca NULL.
 */
static int *str_to_int(char *history, unsigned length) {
  if (!history) {
    return NULL;
  }
  int *int_history;
  if (!(int_history = malloc(length * sizeof(int)))) {
    return NULL;
  }
  unsigned i = 0;
  while (i < length) {
    int_history[i] = (int)(history[i] - '0');
    i++;
  }
  return int_history;
}

/*
 * Funkcja odpowiada za przekształcenie napisu reprezentującego historię
 * kwantową cząstki w tablicę liczb całkowitych i zapisanie danych w strukturze
 * komendy.
 */
static Command *convert_histories(Command *command) {
  if (command->type == ERROR) {
    return command;
  }
  if (command->history_a) {
    command->length_a = strlen(command->history_a);
    if (!(command->int_history_a = str_to_int(command->history_a,
            command->length_a))) {
      free_command(command);
      return NULL;
    }
  }
  if (command->history_b) {
    if (command->history_b) {
      command->length_b = strlen(command->history_b);
      if (!(command->int_history_b = str_to_int(command->history_b,
              command->length_b))) {
        free_command(command);
        return NULL;
      }
    }
  }
  return command;
}

/*Funkcja read_line czyta pojedynczą linię wejścia. Jeśli polecenie jest
 * poprawne, zwraca wskaźnik na odpowiednio wypełnioną strukturę Command. Jeśli
 * nastąpił błąd alokacji pamięci, zwalnia zaalokowaną pamięć i zwraca NULL.
 * Jeśli polecenie było niepoprawne zwraca wskaźnik na strukturę command z
 * wartością ERROR w polu type.
 */
Command *read_line() {
  Command *command;
  if (!(command = new_command())) {
    return NULL;
  }
  size_t size = 0;
  char *line = NULL;
  if (getline(&line, &size, stdin) == -1) {
    command->line = line;
    command->type = END;
    return command;
  } //dodać memory error przy getline
  command->line = line;
  if (line == NULL || strcmp(line, "") == 0) {
    command->type = ERROR;
    return command;
  }
  if (line[0] == '#' || line[0] == '\n') {
    command->type = IGNORE;
    return command;
  }
  uint64_t length = strlen(line);
  split_line(line, length);
  if (!valid_command(line, command)) {
    command->type = ERROR;
    return command;
  }

  uint64_t pointer = 0;
  if (!move_to_history(line, &pointer, length)) {
    command->type = ERROR;
    return command;
  }
  if (!(command->history_a = read_history(line, &pointer, length))) {
    command->type = ERROR;
    return command;
  }
  if (command->type == EQUAL) {
    pointer++;
    if (pointer == length ||
    !(command->history_b = read_history(line, &pointer, length))) {
      command->type = ERROR;
      return command;
    }
  }
  if (command->type == NONE) {
    pointer++;
    if (pointer >= length - 1) {
      pointer--;
      command->type = ENERGY_H;
    }
    else {
      command->energy = read_energy(line, &pointer);
      if (command->energy == 0) {
        command->type = ERROR;
        return command;
      }
      command->type = ENERGY_H_N;
    }
  }
  if (line[pointer] != '\n') {
    command->type = ERROR;
    return command;
  }
  line[length - 1] = '\0';
  return convert_histories(command);
}