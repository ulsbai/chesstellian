#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>

#include "structs.h"
#include "tree.h"
#include "format.h"

#define DEPTH 3

int main() {
  std::vector<std::vector<Square>> position = get_start_position();
  
  Tree tree;
  Tree* treeptr = &tree;
  
  if (build_tree(treeptr, position, WHITE, true)) {
    expand_tree(treeptr, DEPTH);
    std::vector<std::vector<Move>> lines = get_lines(treeptr);
    
    std::cout << "lines.size()=" << (int) lines.size() << '\n';
    
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
