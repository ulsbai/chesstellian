#include <vector>
#include <stdint.h>

#include "structs.h"

std::vector<Move> get_moves(std::vector<std::vector<Square>> board, int8_t colour); //, bool count_check);

std::vector<std::vector<Square>> move_copy_board(std::vector<std::vector<Square>> board, Move m);
