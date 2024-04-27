/*
 * Ranks and files range inclusively from 0 to 7, not 1 to 8
 * index are represented by a std::pair<int, int> index(rank, file);
 */

#include <vector>
#include <stdint.h>

#include "structs.h"
#include "pieces.h"

#include <iostream>

// Piece Move fns

namespace {
  std::vector<Move> rook_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> moves = {};
        
    int8_t colour = board[index.rank][index.file].colour;

    // whiteward
    for (uint8_t r = index.rank - 1; r < index.rank; r--) {
      int8_t c = board[r][index.file].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, ROOK, index, create_index(r, index.file), ROOK));
        }
        break;
      }
      moves.push_back(create_move(colour, ROOK, index, create_index(r, index.file), ROOK));
    }

    // blackward
    for (uint8_t r = index.rank + 1; r < 8; r++) {
      int8_t c = board[r][index.file].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, ROOK, index, create_index(r, index.file), ROOK));
        }
        break;
      }
      moves.push_back(create_move(colour, ROOK, index, create_index(r, index.file), ROOK));
    }

    // kingsideward
    for (uint8_t f = index.file + 1; f < 8; f++) {
      int8_t c = board[index.rank][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, ROOK, index, create_index(index.rank, f), ROOK));
        }
        break;
      }
      moves.push_back(create_move(colour, ROOK, index, create_index(index.rank, f), ROOK));
    }

    // queensideward
    for (uint8_t f = index.file - 1; f < index.file; f--) {
      int8_t c = board[index.rank][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, ROOK, index, create_index(index.rank, f), ROOK));
        }
        break;
      }
      moves.push_back(create_move(colour, ROOK, index, create_index(index.rank, f), ROOK));
    }
    
    return moves;
  }

  std::vector<Move> knight_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> moves = {};
    
    int8_t colour = board[index.rank][index.file].colour;
    
    std::vector<std::pair<int8_t, int8_t>> directions {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    
    for (std::pair<int8_t, int8_t> dir: directions) {
      uint8_t dr = dir.first;
      uint8_t df = dir.second;
      uint8_t r = index.rank + dr;
      uint8_t f = index.file + df;
      if (r >= 0 && r < 8 && f >= 0 && f < 8) {
        int8_t c = board[r][f].colour;
        if (!c || c == enemy(colour)) {
          moves.push_back(create_move(colour, KNIGHT, index, create_index(r, f), KNIGHT));
        }
      }
    }
    
    return moves;
  }

  std::vector<Move> bishop_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> moves = {};
    
    int8_t colour = board[index.rank][index.file].colour;
    
    uint8_t r, f;
    
    // up-right
    r = index.rank + 1;
    f = index.file + 1;
    while (r < 8 && f < 8) {
      int8_t c = board[r][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
        }
        break;
      }
      moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
      r++;
      f++;
    }

    // down-right
    r = index.rank - 1;
    f = index.file + 1;
    while (r < index.rank && f < 8) {
      int8_t c = board[r][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
        }
        break;
      }
      moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
      r--;
      f++;
    }

    // down-left
    r = index.rank - 1;
    f = index.file - 1;
    while (r < index.rank && f < index.file) {
      int8_t c = board[r][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
        }
        break;
      }
      moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
      r--;
      f--;
    }

    // up-left
    r = index.rank + 1;
    f = index.file - 1;
    while (r < 8 && f < index.file) {
      int8_t c = board[r][f].colour;
      if (c != EMPTY) {
        if (c == enemy(colour)) {
          moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
        }
        break;
      }
      moves.push_back(create_move(colour, BISHOP, index, create_index(r, f), BISHOP));
      r++;
      f--;
    }
    
    return moves;
  }

  std::vector<Move> queen_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> rm = rook_moves(board, index);
    std::vector<Move> bm = bishop_moves(board, index);
    
    std::vector<Move> moves = {};
    
    for (Move m : rm) {
      moves.push_back(create_move(m.colour, QUEEN, m.old_index, m.new_index, QUEEN));
    }
    
    for (Move m : bm) {
      moves.push_back(create_move(m.colour, QUEEN, m.old_index, m.new_index, QUEEN));
    }
    
    return moves;
  }

  std::vector<Move> king_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> moves = {};
    
    int8_t colour = board[index.rank][index.file].colour;
    
    std::vector<std::pair<int8_t, int8_t>> directions {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    
    for (std::pair<int8_t, int8_t> dir: directions) {
      uint8_t dr = dir.first;
      uint8_t df = dir.second;
      uint8_t r = index.rank + dr;
      uint8_t f = index.file + df;
      if (r >= 0 && r < 8 && f >= 0 && f < 8) {
        int8_t c = board[r][f].colour;
        if (!c || c == enemy(colour)) {
          moves.push_back(create_move(colour, KING, index, create_index(r, f), KING));
        }
      }
    }
    
    return moves;
  }

  std::vector<Move> pawn_moves(std::vector<std::vector<Square>> board, Index index) {
    std::vector<Move> moves = {};
    
    int8_t colour = board[index.rank][index.file].colour;
    //std::cout << "pieces.cpp:" << "pawn_moves:" << "colour=" << (int) colour << '\n';
    
    int8_t c;
    
    uint8_t r = index.rank + colour;
      
    if (board[r][index.file].colour == EMPTY){
      // promotion
      if (r == pawn_promotion_rank[colour]) {
        moves.push_back(create_move(colour, PAWN, index, create_index(r, index.file), ROOK));
        moves.push_back(create_move(colour, PAWN, index, create_index(r, index.file), KNIGHT));
        moves.push_back(create_move(colour, PAWN, index, create_index(r, index.file), BISHOP));
        moves.push_back(create_move(colour, PAWN, index, create_index(r, index.file), QUEEN));
      } else {
        moves.push_back(create_move(colour, PAWN, index, create_index(r, index.file), PAWN));
      }
      
      // double push
      uint8_t d = pawn_centre_rank[colour];
      if (index.rank == pawn_starting_rank[colour] && (board[d][index.file].colour == EMPTY)) {
        moves.push_back(create_move(colour, PAWN, index, create_index(d, index.file), PAWN));
      }
    }
    
    // capture
    int8_t e = enemy(colour);
    uint8_t f;
    
    if (index.file < 7) {
      f = index.file + 1;
      c = board[r][f].colour;
      if (c == e) {
        // promotion
        if (r == pawn_promotion_rank[colour]) {
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), ROOK));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), KNIGHT));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), BISHOP));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), QUEEN));
        } else {
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), PAWN));
        }
      }
    }
    
    if (index.file > 0) {
      f = index.file - 1;
      c = board[r][f].colour;
      if (c == e) {
        // promotion
        if (r == pawn_promotion_rank[colour]) {
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), ROOK));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), KNIGHT));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), BISHOP));
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), QUEEN));
        } else {
          moves.push_back(create_move(colour, PAWN, index, create_index(r, f), PAWN));
        }
      }
    }
    return moves;
  }
}

std::vector<Move> piece_moves(std::vector<std::vector<Square>> board, Index index) {
  uint8_t piece = board[index.rank][index.file].piece;
  
  switch (piece) {
    case ROOK: return rook_moves(board, index); break;
    case KNIGHT: return knight_moves(board, index); break;
    case BISHOP: return bishop_moves(board, index); break;
    case QUEEN: return queen_moves(board, index); break;
    case KING: return king_moves(board, index); break;
    case PAWN: return pawn_moves(board, index);
  }
  
  std::vector<Move> result;
  return result;
}
