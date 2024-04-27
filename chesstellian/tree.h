#include <vector>
#include <stdint.h>

#include "structs.h"

struct Node;

struct Tree {
  std::vector<std::vector<Square>> board;
  std::vector<Node> nodes;
  int8_t player_to_move;
};

struct Node {
  Move move;
  Tree* subtree = nullptr;
};

namespace tree_internal {
  struct ExpantionTask {
    Tree* tree;
    uint32_t depth;
    int8_t player_to_move;
    std::vector<std::vector<Square>> board;
  };
  
  struct LinesTask {
    std::vector<Move> line;
    Tree* tree;
  };
}

bool build_tree(Tree* tree, std::vector<std::vector<Square>> board, int8_t player_to_move); //, bool check_for_check);

void expand_tree(Tree* tree, uint32_t depth);

std::vector<std::vector<Move>> get_lines(Tree* tree, uint32_t depth);
