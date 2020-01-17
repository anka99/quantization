#include "engine.h"
#include "structures.h"

bool declare_history(tree_t *root, int *history, unsigned length) {
  return add_history(root, history, length);
}

void remove_history(tree_t *root, int *history, unsigned length) {
  if (history) {
    delete_tree_node(root, history, length);
  }
}

bool valid_history(tree_t *root, int *history, unsigned length) {
  if (find_node(root, history, length)) {
    return true;
  }
  return false;
}

static void optimize(tree_t *node, list_t *representation) {
  if (node) {
    (node->next->connected)--;

    list_t *temp = node->next;

    node->next = representation;
    (representation->connected)++;

    if (temp->connected == 0) {
      delete_list_node(temp);
    }
  }
}

uint64_t show_energy(tree_t *root, int *history, unsigned length) {
  tree_t *node = find_node(root, history, length);
  if (node) {
    list_t *temp = node->next;
    if (!temp) {
      return 0;
    }
    while (temp->next) {
      temp = temp->next;
    }
    optimize(node, temp);
    return temp->energy;
  }
  return 0;
}

bool set_energy(tree_t *root, int *history, unsigned length, uint64_t energy) {
  tree_t *node = find_node(root, history, length);
  if (!node) {
    return false;
  }
  list_t *temp = node->next;
  if (!temp) {
    return false;
  }
  while (temp->next) {
    temp = temp->next;
  }
  temp->energy = energy;
  optimize(node, temp);
  return true;
}

static uint64_t max(uint64_t a, uint64_t b) {
  if (a > b) {
    return a;
  }
  return b;
}

static uint64_t min(uint64_t a, uint64_t b) {
  if (a > b) {
    return b;
  }
  return a;
}

static uint64_t average(uint64_t a, uint64_t b) {
  return (max(a, b) - min(a, b))/2 + min(a, b);
}

static void connect(list_t *node_a, list_t *node_b, uint64_t energy) {
  if (node_a->rank < node_b->rank) {
    node_a->next = node_b;
    node_b->rank = max(node_b->rank, node_a->rank + 1);
    (node_b->connected)++;
    node_b->energy = energy;
  }
  else {
    node_b->next = node_a;
    node_a->rank = max(node_b->rank + 1, node_a->rank);
    (node_a->connected)++;
    node_a->energy = energy;
  }
}

bool equal(tree_t *root, int *history_a, unsigned length_a, int *history_b,
           unsigned length_b) {
  tree_t *node_a = find_node(root, history_a, length_a);
  tree_t *node_b = find_node(root, history_b, length_b);
  if (!node_a || !node_b) {
    return false;
  }
  if (node_a == node_b) {
    return true;
  }
  list_t *temp_a = node_a->next;
  list_t *temp_b = node_b->next;
  if (!temp_a || !temp_b) {
    return false;
  }
  while (temp_a->next) {
    temp_a = temp_a->next;
  }
  while (temp_b->next) {
    temp_b = temp_b->next;
  }
  optimize(node_a, temp_a);
  optimize(node_b, temp_b);
  if (temp_a == temp_b) {
    return true;
  }
  if (temp_a->energy == 0 && temp_b->energy == 0) {
    return false;
  }
  if (temp_a->energy == 0) {
    connect (temp_a, temp_b, temp_b->energy);
    return true;
  }
  if (temp_b->energy == 0) {
    connect (temp_a, temp_b, temp_a->energy);
    return true;
  }
  connect (temp_a, temp_b, average(temp_a->energy, temp_b->energy));
  return true;
}

