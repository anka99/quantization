#include <stdlib.h>
#include <string.h>
#include "structures.h"

#define LEAVES_NUMBER 4

list_t *new_list_node() {
  list_t *list;
  if (!(list = malloc(sizeof(list_t)))) {
    return NULL;
  }
  list->energy = 0;
  list->connected = 1;
  list->rank = 2;
  list->next = NULL;
  return list;
}

tree_t *new_tree_node() {
  tree_t *root;
  if (!(root = malloc(sizeof(tree_t)))) {
    return NULL;
  }
  if (!(root->children = malloc(LEAVES_NUMBER * sizeof(tree_t *)))) {
    return NULL;
  }
  for (int i = 0 ; i < LEAVES_NUMBER; i++) {
    root->children[i] = NULL;
  }
  if (!(root->next = new_list_node())) {
    return NULL;
  }
  return root;
}

bool add_history(tree_t *root, int *history, unsigned length) {
  if (!history) {
    return false;
  }
  tree_t *node = root;
  unsigned i = 0;
  while (i < length) {
    if (history[i] > LEAVES_NUMBER - 1) {
      return false;
    }
    if (!(node->children[history[i]])) {
      if (!(node->children[history[i]] = new_tree_node())) {
        return false;
      }
    }
    node = node->children[history[i]];
    i++;
  }
  return true;
}

tree_t *find_node(tree_t *root, int *history, unsigned length) {
  if (history == NULL) {
    return NULL;
  }
  tree_t *node = root;
  unsigned i = 0;
  while (i < length) {
    if (history[i] > LEAVES_NUMBER || !node) {
      return NULL;
    }
    node = node->children[history[i]];
    i++;
  }
  return node;
}

void delete_list_node(list_t *node) {
  if (node) {
    if (node->next) {
      (node->next->connected)--;
      if (node->next->connected == 0) {
        delete_list_node(node->next);
      }
    }
    free(node);
  }
}

void delete_subtree(tree_t *node) {
  if (node) {
    if (node->next) {
      (node->next->connected)--;
      if (node->next->connected == 0) {
        delete_list_node(node->next);
        node->next = NULL;
      }
    }
    if (node->children) {
      for (int i = 0; i < LEAVES_NUMBER; i++) {
        delete_subtree(node->children[i]);
      }
      free(node->children);
    }
    free(node);
  }
}

void delete_tree_node(tree_t *root, int *history, unsigned length) {
  if (length > 0) {
    int last_one = history[length - 1];
    tree_t *previous = find_node(root, history, length - 1);

    if (previous && (previous->children) && last_one < LEAVES_NUMBER &&
        previous->children[last_one]) {
      delete_subtree(previous->children[last_one]);
      previous->children[last_one] = NULL;
    }
  }
}