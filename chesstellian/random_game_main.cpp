/*
 * Note:
 * Make so as to switch the player to move each half-move
 */

/*
#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <random>

#include "structs.h"
#include "tree.h"
#include "format.h"

int main() {
  std::vector<std::vector<Square>> position = get_start_position();
  int8_t player_to_move = WHITE;
  
  std::string fms;
  
  uint32_t n_moves = 0;
  
  while (true) {
    Tree tree;
    
    std::cout << format::f_position::repr(position);
    
    if (build_tree(&tree, position, player_to_move, true)) {
      // Obtain a random number between 1 and tree.nodes.size()-1
      std::random_device rd;
      std::mt19937 eng(rd());
      std::uniform_int_distribution<> distr(0, tree.nodes.size()-1);
      int x = distr(eng);
      
      Move m = tree.nodes[x].move;
      
      std::string fm = format::f_move::stockfish(m);
      std::cout << fm << '\n';
      
      fms += fm + ' ';
      
      position = move_copy_board(position, m);
      player_to_move = enemy(player_to_move);
      
      n_moves++;
      
      if (n_moves > 100) {
        std::cout << fms << '\n';
        return 0;
      }
    }
    else {
      std::cout << fms << '\n';
      std::cerr << "Chesstellian: Error: Cannot find legal moves: Invalid position" << '\n';
      return 1;
    }
  }
  
  std::cout << fms << '\n';
  
  return 0;
}
*/
