#include "structures.h"
#include "execute.h"
#include "defines.h"

int main(void) {
  tree_t *root;
  if (!(root = new_tree_node())) {
    return 1;
  }
  int result = execute_commands(root);
  while (result != END && result != MEMORY_ERROR) {
    result = execute_commands(root);
  }
  delete_subtree(root);
  if (result == END) {
    return 0;
  }
  return 1;
}
