/*
 * 
 */

#include <string>
#include <vector>
#include <stdint.h>

#include "structs.h"
#include "format.h"

#include <iostream>

namespace format
{
  namespace f_position {
    std::string repr(std::vector<std::vector<Square>> position) {
      std::string result;
      
      result.append(" +---+---+---+---+---+---+---+---+\n");
      
      for (uint8_t r = 7; r <= 7; r--){
        for (uint8_t f = 0; f < 8; f++){
          Square s = position[r][f];
          result.append(" | ");
          result += pieces[s.colour][s.piece];
          //std::cout << "repr:" << pieces[s.colour][s.piece];
        }
        
        result.append(" | ");
        result.append(std::to_string((int)(r+1)));
        result.append("\n +---+---+---+---+---+---+---+---+\n");;
      }
      
      return result;
    }
  }
  
  namespace f_move
  {
    std::string stockfish(Move m) {
      std::string result;
      result.push_back(files[m.old_index.file]);
      result.push_back('1' + m.old_index.rank);
      result.push_back(files[m.new_index.file]);
      result.push_back('1' + m.new_index.rank);
      return result;
    }
  }
  
  namespace f_line {
    std::string stockfish(std::vector<Move> line) {
      std::string result;
      
      for (Move m: line) {
        result.append(f_move::stockfish(m));
        result.push_back(' ');
      }
      
      return result;
    }
  }
}
