#include <map>

#include "structs.h"

namespace format {
  namespace f_position {
    static std::map<int8_t, std::string> pieces = {{WHITE, "RNBQKP"}, {BLACK, "rnbqkp"}, {EMPTY, "      "}};
    
    std::string repr(std::vector<std::vector<Square>> position);
  }
  
  namespace f_move {
    static char files[9] = "abcdefgh";
    
    std::string stockfish(Move m);
  }
  
  namespace f_line {
    std::string stockfish(std::vector<Move> m);
  }
}
