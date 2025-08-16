#include "solver.h"
#include <unordered_set>
#include <iostream>


Solver::Solver(std::unordered_set<std::string> &solutionWords) {
	m_solutionWords = solutionWords;
};

void Solver::solve(Board& board){
	std::vector<std::pair<std::string, std::vector<Node *>>> words;
	int width = board.getWidth();
	int height = board.getHeight();


	for (size_t attemptLength = 4; attemptLength < 9; ++attemptLength) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			Node* node = board.getNodeAt(row, col);
			if (node->isUsed) {
				continue;
			}
			std::vector<Node *> path;
			auto res = dfs(node, path, attemptLength);

			if (res.first.length() != 0) {
				words.push_back(res);
			}
		}
	}
	}

	m_foundWords = words;
};

std::string Solver::stringFromPath(std::vector<Node *> &path) {
	std::string res;
	res.reserve(path.size());
	for (Node *node : path) {
		res += node->val;
	}

	return res;
}

void Solver::markPathUsed(std::vector<Node *> path) {
	for (Node *node : path) {
		node->isUsed = true;
	}
}


std::pair<std::string, std::vector<Node *>>
Solver::dfs(Node *node, std::vector<Node *> &path, const size_t attemptLength){
	if (node == nullptr || path.size() > attemptLength) {
		return std::make_pair("", path);
	}

	path.push_back(node);
	std::string curString = stringFromPath(path);

	// Debug: entering DFS
	// std::cout << "[DFS] Depth=" << path.size() << " Visiting=" << node->val
	//           << " Path=" << curString << std::endl;

	if (m_solutionWords.count(curString) == 1) {
		// std::cout << "  [FOUND] Word=" << curString << std::endl;
		markPathUsed(path);
		return std::make_pair(curString, path);
	}

	for (Node *neighbor : node->neighbors) {
		// is the neighbor even valid
		if (!neighbor->isUsed &&
			std::find(path.begin(), path.end(), neighbor) == path.end()) {
			auto resPath = dfs(neighbor, path, attemptLength);
			if (resPath.first.length() != 0) {
				return resPath;
			}
		}
	}

	path.pop_back();
	return std::make_pair("", path);
};


void Solver::printSolution(){
	for (auto word : m_foundWords) {
		std::cout << word.first << std::endl;

		for (Node *node : word.second) {
			std::cout << "\t" << node << std::endl;
		}
	}
}

