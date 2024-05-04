/*
 * 
 */

#include <vector>
#include <stdint.h>

#include "structs.h"
#include "pieces.h"
#include "moves.h"

#include <iostream> // temporary, for testing

/*
 * Section Depricated
 * 

// Check for check

bool is_piece_attacked(std::vector<std::vector<Square>> board, Square piece){
  
  for (Move m: get_moves(board, enemy(piece.colour), false)) {
    if (board[m.new_index.rank][m.new_index.file].piece == piece.piece){
      return true;
    }
  }
  
  return false;
}

Index find_king(std::vector<std::vector<Square>> board, int8_t colour){
  for (uint8_t rank = 0; rank < 8; rank++) {
    for (uint8_t file = 0; file < 8; file++) {
      Square s = board[rank][file];
      
      if ((s.colour == colour) && (s.piece == KING)){
        return create_index(rank, file);
      }
    }
  }
  
  return create_index(0, 0);
}

bool is_in_check(std::vector<std::vector<Square>> board, int8_t colour){
  Index king = find_king(board, colour);
  return is_attacked(board, king);
}
*/


//

/*
 * Depricated
std::vector<std::vector<Square>> move_copy_board(std::vector<std::vector<Square>> board, Move m) {
  std::vector<std::vector<Square>> result;
  
  for (uint8_t rank = 0; rank < 8; rank++) {
    std::vector<Square> rank_pos;
    
    for (uint8_t file = 0; file < 8; file++) {
      if ((rank == m.old_index.rank) && (file == m.old_index.file)){
        rank_pos.push_back(create_square(EMPTY, 0));
      }
      else if ((rank == m.new_index.rank) && (file == m.new_index.file)){
        rank_pos.push_back(create_square(m.colour, m.new_piece));
      }
      else {
        rank_pos.push_back(board[rank][file]);
      }
    }
    
    result.push_back(rank_pos);
  }
  
  return result;
}
*/

void move_board(std::vector<std::vector<Square>> board, Move m) {
  //std::cout << "move_board:" << std::flush << (int) board.size() << std::flush << ' ' << (int) board[0].size() << std::flush << ' ' << (int) m.old_index.rank << ' ' << (int) m.old_index.file << '\n';
  int8_t colour = board[m.old_index.rank][m.old_index.file].colour;
  board[m.old_index.rank][m.old_index.file].colour = EMPTY;
  board[m.new_index.rank][m.new_index.file] = create_square(m.colour, m.new_piece);
}

std::vector<Move> get_moves(std::vector<std::vector<Square>> board, int8_t colour) { //, bool count_check) {
  std::vector<Move> result = {};
  std::vector<Move> ms;
  
  for (uint8_t rank = 0; rank < 8; rank++){
    for (uint8_t file = 0; file < 8; file++){
      Square s = board[rank][file];
      
      if (s.colour == colour){
        ms = piece_moves(board, create_index(rank, file));
        
        /*
        if (count_check){
          for (Move m: ms) {
            std::vector<std::vector<Square>> b = move_copy_board(board, m);
            
            if (!is_piece_attacked(b, create_square(colour, KING))){
              result.push_back(m);
            }
          }
        
        }
        else
        */
        
        result.insert(result.end(), ms.begin(), ms.end());
      }
    }
  }
  
  return result;
}
