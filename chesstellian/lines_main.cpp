#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>

#include "structs.h"
#include "tree.h"
#include "format.h"

uint32_t DEPTH = 1;

int main() {
  std::vector<std::vector<Square>> position = get_start_position();
  
  Tree tree;
  Tree* treeptr = &tree;
  
  if (build_tree(treeptr, position, WHITE)) {
    expand_tree(treeptr, DEPTH);
    std::vector<std::vector<Move>> lines = get_lines(treeptr, DEPTH);
    
    for (std::vector<Move> line: lines) {
      std::string fline = format::f_line::stockfish(line);
      std::cout << fline << '\n';
    }
  }
  else {
    std::cerr << "Chesstellian: Error: Cannot find legal moves: Invalid position\n";
    return 1;
  }
  
  return 0;
}