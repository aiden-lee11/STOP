#include "solver.h"
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::string stringFromPath(std::vector<Node *> &path) {
	std::string res;
	res.reserve(path.size());
	for (Node *node : path) {
		res += node->val;
	}

	return res;
}

void Solver::solve(Board &board) {
	std::vector<std::pair<std::string, std::vector<Node *>>> words;
	int width = board.getWidth();
	int height = board.getHeight();

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			Node *node = board.getNodeAt(row, col);
			if (node->isUsed) {
				continue;
			}
			std::vector<Node *> path;
			auto res = dfs(node, path, [&] { board.printBoard(); });
			// auto res = bfs(node);

			if (res.first.length() != 0) {
				for (Node *node : res.second) {
					node->isUsed = true;
					board.printBoard();
				}
				words.push_back(res);
			}
		}
	}

	m_foundWords = words;
};

std::pair<std::string, std::vector<Node *>>
Solver::dfs(Node *node, std::vector<Node *> &path,
            const std::function<void()> &drawFunc) {
	if (node == nullptr || !m_trie->isPrefix(path)) {
		return std::make_pair("", path);
	}

	path.push_back(node);
	node->inPath = true;
	drawFunc();

	if (m_trie->isWord(path)) {
		return std::make_pair(stringFromPath(path), path);
	}

	for (Node *neighbor : node->neighbors) {
		// is the neighbor even valid
		if (!neighbor->isUsed &&
		    std::find(path.begin(), path.end(), neighbor) == path.end()) {
			auto resPath = dfs(neighbor, path, drawFunc);
			if (resPath.first.length() != 0) {
				return resPath;
			}
		}
	}

	Node *lastNode = path.back();
	lastNode->isUsed = false;
	path.pop_back();

	return {"", {}};
};

std::pair<std::string, std::vector<Node *>> Solver::bfs(Node *node) {
	std::deque<std::vector<Node *>> queue;
	queue.push_back({node});

	while (!queue.empty()) {
		auto path = queue.front();
		queue.pop_front();

		if (!m_trie->isPrefix(path)) {
			continue;
		}

		if (m_trie->isWord(path)) {
			return std::make_pair(stringFromPath(path), path);
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
