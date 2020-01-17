#include "input.h"
#include "engine.h"
#include "defines.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

static void report_error() {
  fprintf(stderr, "ERROR\n");
}

static void report_yes() {
  printf("YES\n");
}

static void report_no() {
  printf("NO\n");
}

static void report_correct() {
  printf("OK\n");
}

static void print_energy(uint64_t energy) {
  printf("%" PRIu64 "\n", energy);
}

int execute_commands(tree_t *root) {
  Command *command = read_line();
  if (command == NULL) {
    return MEMORY_ERROR;
  }
  uint64_t energy = 0;
  switch (command->type) {
    case IGNORE :
      free_command(command);
      return DONE;
    case ERROR :
      free_command(command);
      report_error();
      return DONE;
    case END :
      free_command(command);
      return END;
    case DECLARE :
      if (!declare_history(root, command->int_history_a, command->length_a)) {
        free_command(command);
        return MEMORY_ERROR;
      }
      free_command(command);
      report_correct();
      return DONE;
    case REMOVE :
      remove_history(root, command->int_history_a, command->length_a);
      report_correct();
      free_command(command);
      return DONE;
    case VALID :
      if (valid_history(root, command->int_history_a, command->length_a)) {
        report_yes();
      } else {
        report_no();
      }
      free_command(command);
      return DONE;
    case ENERGY_H :
      energy = show_energy(root, command->int_history_a, command->length_a);
      if (energy == 0) {
        report_error();
      }
      else {
        print_energy(energy);
      }
      free_command(command);
      return DONE;
    case ENERGY_H_N :
      if (set_energy(root, command->int_history_a, command->length_a,
              command->energy)) {
        report_correct();
      }
      else {
        report_error();
      }
      free_command(command);
      return DONE;
    case EQUAL :
      if (!equal(root, command->int_history_a, command->length_a,
                 command->int_history_b, command->length_b)) {
        report_error();
      }
      else {
        report_correct();
      }
      free_command(command);
      return DONE;
    default:
      free_command(command);
      return DONE;
  }
}
