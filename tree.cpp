#include <vector>
#include <stdint.h>
#include <queue>

#include "structs.h"
#include "moves.h"
#include "tree.h"

#include <iostream> // temporary; for testing

/*
 * Returns whether or not board represents a valid position
 * aka player_to_move is not in check
 */
bool build_tree(Tree* tree, std::vector<std::vector<Square>> board, int8_t player_to_move, bool check_for_check) {
  //Tree new_tree;
  //tree = &new_tree;
  
  tree->board = board;
  tree->player_to_move = player_to_move;
  
  for (Move m: get_moves(board, tree->player_to_move)) { //, false)) {
    Node node;
    node.move = m;
    
    if (board[m.new_index.rank][m.new_index.file].piece == KING)
      return false;
    
    if (check_for_check) {
      std::vector<std::vector<Square>> subboard = move_copy_board(board, m);
      
      Tree subtree;
      node.subtree = &subtree;
      
      if (build_tree(node.subtree, subboard, enemy(player_to_move), false)){
        tree->nodes.push_back(node);
      }
    }
    else tree->nodes.push_back(node);
  }
    
  return true;
}

void expand_tree(Tree* tree, uint32_t depth) {
  std::queue<tree_internal::ExpantionTask> tasks;
  tree_internal::ExpantionTask init_task;
  init_task.tree = tree;
  init_task.depth = depth;
  init_task.player_to_move = tree->player_to_move;
  init_task.board = tree->board;
  tasks.push(init_task);
  
  tree_internal::ExpantionTask task;
  
  while (!tasks.empty()) {
    task = tasks.front();
    
    if (task.depth > 0) {
      if (task.tree == nullptr) {
        build_tree(task.tree, task.board, task.player_to_move, true); // must return true
      }
      
      for (Node node: task.tree->nodes) {
        tree_internal::ExpantionTask new_task;
        new_task.tree = node.subtree;
        new_task.depth = task.depth-1;
        new_task.player_to_move = enemy(task.player_to_move);
        
        std::vector<std::vector<Square>> board = move_copy_board(task.board, node.move);
        
        tasks.push(new_task);
      }
    }
    
    tasks.pop();
  }
}

std::vector<std::vector<Move>> get_lines(Tree* tree, uint32_t depth) {
  std::vector<std::vector<Move>> lines;
  
  std::queue<tree_internal::LinesTask> tasks;
  tree_internal::LinesTask init_task;
  init_task.tree = tree;
  tasks.push(init_task);
  
  tree_internal::LinesTask task;
  
  while (!tasks.empty()) {
    task = tasks.front();
    
    if (task.line.size() < depth) {
      for (Node node: task.tree->nodes) {
        tree_internal::LinesTask new_task;
        Tree new_tree = *node.subtree;
        new_task.tree = &new_tree;
        new_task.line = task.line;
        new_task.line.push_back(node.move);
        tasks.push(new_task);
      }
    }
    else {
      lines.push_back(task.line);
    }
    
    tasks.pop();
  }
  
  return lines;
}
