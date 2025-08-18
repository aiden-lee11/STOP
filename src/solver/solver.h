#pragma once

#include "../board/board.h"
#include "../node/node.h"
#include <functional>
#include <string>
#include <unordered_set>
#include <vector>

class Solver {
  public:
	Solver(std::unordered_set<std::string> &solutionWords);
	void solve(Board &board, const std::function<void()> &drawFunc);

	void printSolution();

  private:
	std::unordered_set<std::string> m_solutionWords;

	std::vector<std::pair<std::string, std::vector<Node *>>> m_foundWords;

	std::pair<std::string, std::vector<Node *>>
	dfs(Node *node, std::vector<Node *> &path, const size_t attemptLength);

	std::pair<std::string, std::vector<Node *>> bfs(Node *node,
	                                                const size_t attemptLength);

	std::string stringFromPath(std::vector<Node *> &path);

	void markPathUsed(std::vector<Node *> path);
};
