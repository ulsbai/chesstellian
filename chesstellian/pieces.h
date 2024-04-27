#include <vector>
#include <map>

#include "structs.h"

// Pawn Ranks

static std::map<int8_t, uint8_t> pawn_starting_rank = {{1, 1}, {-1, 6}};
static std::map<int8_t, uint8_t> pawn_centre_rank = {{1, 3}, {-1, 4}};
static std::map<int8_t, uint8_t> pawn_promotion_rank = {{1, 7}, {-1, 0}};

std::vector<Move> piece_moves(std::vector<std::vector<Square>> board, Index index);
