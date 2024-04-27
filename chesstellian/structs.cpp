#include <array>
#include <vector>
#include <stdint.h>
#include <utility>

#include "structs.h"

Square create_square(int8_t colour, uint8_t piece) {
  Square result;
  result.colour = colour;
  result.piece = piece;
  return result;
}

std::vector<std::vector<Square>> get_start_position() {
  std::vector<std::vector<Square>> start_position;
  
  std::vector<std::vector<std::pair<int8_t, uint8_t>>> start_position_builder {
  {{WHITE, ROOK}, {WHITE, KNIGHT}, {WHITE, BISHOP}, {WHITE, QUEEN}, {WHITE, KING}, {WHITE, BISHOP}, {WHITE, KNIGHT}, {WHITE, ROOK}},
  {{WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}, {WHITE, PAWN}},
  {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
  {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
  {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
  {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
  {{BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}, {BLACK, PAWN}},
  {{BLACK, ROOK}, {BLACK, KNIGHT}, {BLACK, BISHOP}, {BLACK, QUEEN}, {BLACK, KING}, {BLACK, BISHOP}, {BLACK, KNIGHT}, {BLACK, ROOK}}
  };
  
  if (start_position.size() == 0){
    for (int r = 0; r < 8; r++) {
      std::vector<Square> rank_pos;
      
      for (int f = 0; f < 8; f++) {
        std::pair<int8_t, uint8_t> Square_builder = start_position_builder[r][f];
        
        if (Square_builder.first == 0){
          rank_pos.push_back(create_square(EMPTY, 0));
        } else {
          rank_pos.push_back(create_square(Square_builder.first, Square_builder.second));
        }
      }
      
      start_position.push_back(rank_pos);
    }
  }
  
  return start_position;
}

Index create_index(uint8_t rank, uint8_t file) {
  Index result;
  result.rank = rank;
  result.file = file;
  return result;
}

bool index_eq(Index index1, Index index2) {
  return ((index1.rank == index2.rank) && (index1.file == index2.file));
}

int8_t enemy(int8_t colour) {
  return -colour;
}

Move create_move(int8_t colour, uint8_t old_piece, Index old_index, Index new_index, uint8_t new_piece) {
  Move result;
  result.colour = colour;
  result.old_piece = old_piece;
  result.old_index = old_index;
  result.new_index = new_index;
  result.new_piece = new_piece;
  return result;
}

/*
 * Depricated
std::vector<std::vector<Square*>> copy_board(std::vector<std::vector<Square*>>* board) {
  std::vector<std::vector<Square*>> result;
  
  for (uint8_t rank = 0; rank < 8; rank++) {
    std::vector<Square*> rank_pos;
    
    for (uint8_t file = 0; file < 8; file++) {
      rank_pos.push_back(board[rank][file]);
    }
    
    result.push_back(rank_pos);
  }
  
  return result;
}
*/
