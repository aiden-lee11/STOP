#include "solver.h"
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

Solver::Solver(std::unordered_set<std::string> &solutionWords) {
	m_solutionWords = solutionWords;
};

void Solver::solve(Board &board, const std::function<void()> &drawFunc) {
	std::vector<std::pair<std::string, std::vector<Node *>>> words;
	int width = board.getWidth();
	int height = board.getHeight();

	for (size_t attemptLength = 4; attemptLength < 9; ++attemptLength) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				Node *node = board.getNodeAt(row, col);
				if (node->isUsed) {
					continue;
				}
				std::vector<Node *> path;
				// auto res = dfs(node, path, attemptLength);
				auto res = bfs(node, attemptLength);

				if (res.first.length() != 0) {
					for (Node *node : res.second) {
						node->isUsed = true;
						drawFunc();
					}
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

std::pair<std::string, std::vector<Node *>>
Solver::dfs(Node *node, std::vector<Node *> &path, const size_t attemptLength) {
	if (node == nullptr || path.size() > attemptLength) {
		return std::make_pair("", path);
	}

	path.push_back(node);
	std::string curString = stringFromPath(path);

	if (m_solutionWords.count(curString) == 1) {
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
	return {"", {}};
};

std::pair<std::string, std::vector<Node *>>
Solver::bfs(Node *node, const size_t attemptLength) {
	std::deque<std::vector<Node *>> queue;
	queue.push_back({node});

	while (!queue.empty()) {
		auto path = queue.front();
		queue.pop_front();

		std::string curString = stringFromPath(path);

		if (m_solutionWords.contains(curString)) {
			return {curString, path};
		}

		if (path.size() > attemptLength) {
			return {"", {}};
		}

		Node *lastNode = path.back();

		for (Node *neighbor : lastNode->neighbors) {
			if (!neighbor->isUsed &&
			    std::find(path.begin(), path.end(), neighbor) == path.end()) {
				std::vector<Node *> neighborPath = path;
				neighborPath.push_back(neighbor);
				queue.push_back(neighborPath);
			}
		}
	};
	return {"", {}};
};

void Solver::printSolution() {
	for (auto word : m_foundWords) {
		std::cout << word.first << std::endl;

		for (Node *node : word.second) {
			std::cout << "\t" << node << std::endl;
		}
	}
}
