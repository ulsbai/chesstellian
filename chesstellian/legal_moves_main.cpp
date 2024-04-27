/*
 * Write to std::cout each legal move from the start position,
 * each on a seperate line.
 */

/*
#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>

#include "structs.h"
#include "tree.h"
#include "format.h"

int main() {
  std::vector<std::vector<Square>> start_position = get_start_position();
  
  Tree tree;
  
  if (build_tree(&tree, start_position, WHITE, true)) {
    for (Node node: tree.nodes) {
      std::string fm = format::f_move::stockfish(node.move);
      std::cout << fm << '\n';
    }
    
    return 0;
  }
  else {
    std::cerr << "Chesstellian: Error: Cannot find legal moves: Invalid position" << '\n';
    return 1;
  }
}
*/
