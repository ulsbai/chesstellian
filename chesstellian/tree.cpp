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
    Node* node = new Node;
    node->move = m;
    
    if (board[m.new_index.rank][m.new_index.file].piece == KING)
      return false;
    
    if (check_for_check) {
      std::vector<std::vector<Square>> subboard = board;
      move_board(subboard, m);
      
      Tree* subtree = new Tree;
      
      if (build_tree(subtree, subboard, enemy(player_to_move), false)){
        node->subtree = subtree;
        tree->nodes.push_back(*node);
      }
    }
    else tree->nodes.push_back(*node);
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
    
    /*
    if (tree->nodes[0].subtree->nodes[0].subtree != nullptr)
      std::cout << "tree.cpp:expand_tree:Tree looks more than 2 moves ahead!\n";
    else
      std::cout << "tree.cpp:expand_tree:Tree does not look more than 2 moves ahead!\n";
    */
    
    if (task.depth > 0) {
      if (task.tree->player_to_move == 0) {
        std::cout << "tree.cpp:expand_tree:task.tree->player_to_move=0\n";
                
        if (!build_tree(task.tree, task.board, task.player_to_move, true)) { // must return true
          std::cerr << "Chesstellian: Error: Function 'build_tree' returned false for a board position already varified to be valid.\n";
          abort();
        }
        
        if (task.tree->nodes[0].subtree != nullptr)
          std::cout << "tree.cpp:expand_tree:task.tree looks more than 2 moves ahead!\n";
        else
          std::cout << "tree.cpp:expand_tree:task.tree does not look more than 2 moves ahead!\n";
      }
      //else std::cout << "tree.cpp:expand_tree:task.tree->player_to_move!=0\n";
      
      for (Node node: task.tree->nodes) {
        //std::cout << "tree.cpp:expand_tree:node.move.new_index.rank=" << (int) node.move.new_index.rank << '\n';
        tree_internal::ExpantionTask* new_task = new tree_internal::ExpantionTask;
        
        std::cout << "tree.cpp:expand_tree:task.depth=" << (int) task.depth << '\n';
        
        if (node.subtree == nullptr) {
          std::cout << "tree.cpp:expand_tree:node.subtree=nullptr\n";
          node.subtree = new Tree;
        }
        
        new_task->tree = node.subtree;
        new_task->depth = task.depth-1;
        new_task->player_to_move = enemy(task.player_to_move);
        
        new_task->board = task.board;
        move_board(new_task->board, node.move);
        
        tasks.push(*new_task);
      }
    }
    
    tasks.pop();
  }
}

std::vector<std::vector<Move>> get_lines(Tree* tree) {
  std::vector<std::vector<Move>> lines;
  
  std::queue<tree_internal::LinesTask> tasks;
  tree_internal::LinesTask init_task;
  init_task.tree = tree;
  tasks.push(init_task);
  
  tree_internal::LinesTask task;
  
  while (!tasks.empty()) {
    task = tasks.front();
    
    //std::cout << "__________get_lines:New task:task.tree->board.size()=" << task.tree->board.size() << '\n';
    
    if (task.tree != nullptr) {
      for (Node& node: task.tree->nodes) {
        //std::cout << "get_lines:before:task.tree->board.size()=" << task.tree->board.size() << '\n';
        tree_internal::LinesTask* new_task = new tree_internal::LinesTask;
        new_task->tree = node.subtree;
        new_task->line = task.line;
        new_task->line.push_back(node.move);
        tasks.push(*new_task);
        //std::cout << "get_lines:after:task.tree->board.size()=" << task.tree->board.size() << '\n';
        //std::cout << "get_lines:new_task.tree->board.size()=" << new_task.tree->board.size() << '\n';
      }
    }
    else
      lines.push_back(task.line);
    
    tasks.pop();
  }
  
  return lines;
}
