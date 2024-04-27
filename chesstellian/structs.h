/*
 * The chess board is represented by a std::vector<std::vector<Square>> object,
 * where Square is the struct defined below, containing attributes
 * colour and piece.
 * The Square object is null if the Square on the chessboard that it represents is empty.
 * 
 * The index coordinates (rank, file) of a Square on the chessboard is represented by
 * an instance of the struct Index defined below.
 * The coordinates of an Index can be referenced by i.rank and i.file.
 * 
 * A Move is reprented by an instance of the struct Move.
 * It has attributes Move.new_index, Move.new_piece
 */ 

#ifndef STRUCTSH
#define STRUCTSH

//#include <array>
#include <vector>
#include <stdint.h>

// Pieces
#define ROOK 0
#define KNIGHT 1
#define BISHOP 2
#define QUEEN 3
#define KING 4
#define PAWN 5

// Colours
#define EMPTY 0
#define WHITE 1
#define BLACK -1

struct Square {
  int8_t colour;
  uint8_t piece;
};

struct Index {
  uint8_t rank;
  uint8_t file;
};

struct Move {
  int8_t colour;
  uint8_t old_piece;
  Index old_index;
  Index new_index;
  uint8_t new_piece;
};

std::vector<std::vector<Square>> get_start_position();

Square create_square(int8_t colour, uint8_t piece);

Index create_index(uint8_t rank, uint8_t file);

bool index_eq(Index index1, Index index2);

int8_t enemy(int8_t colour);

Move create_move(int8_t colour, uint8_t old_piece, Index old_index, Index new_index, uint8_t new_piece);

#endif
