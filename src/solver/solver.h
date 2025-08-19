#pragma once

#include "../board/board.h"
#include "../node/node.h"
#include "../trie/trie.h"
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

class Solver {
  public:
	Solver(Trie *trie) : m_trie(trie) {};
	void solve(Board &board, const std::function<void()> &drawFunc);

	void printSolution();

  private:
	Trie *m_trie;

	std::vector<std::pair<std::string, std::vector<Node *>>> m_foundWords;

	std::pair<std::string, std::vector<Node *>> dfs(Node *node,
	                                                std::vector<Node *> &path);

	std::pair<std::string, std::vector<Node *>> bfs(Node *node);
};
