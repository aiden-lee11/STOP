#pragma once

#include "../board/board.h"
#include "../node/node.h"
#include "../trie/trie.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Solver {
  public:
	Solver(const std::vector<std::string> &solutionWords)
	    : m_trie(std::make_unique<Trie>(solutionWords)) {};
	void solve(Board &board);

	void printSolution();
	int numWordsFound();
	void incrementWordsFound();

  private:
	std::unique_ptr<Trie> m_trie;
	int m_wordsFound = 0;

	std::vector<std::pair<std::string, std::vector<Node *>>> m_foundWords;

	std::pair<std::string, std::vector<Node *>>
	dfs(Node *node, std::vector<Node *> &path,
	    const std::function<void()> &drawFunc);

	std::pair<std::string, std::vector<Node *>> bfs(Node *node);
};
