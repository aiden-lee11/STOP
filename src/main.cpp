#include "node/node.h"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

// todo put in test file or smth
// clang-format off
std::vector<std::vector<char>> exampleGrid = {
    {'R', 'E', 'S', 'R', 'E', 'G'},
    {'E', 'U', 'R', 'D', 'S', 'R'},
    {'S', 'I', 'D', 'E', 'T', 'A'},
    {'E', 'V', 'I', 'V', 'E', 'C'},
    {'S', 'T', 'G', 'O', 'V', 'U'},
    {'R', 'M', 'E', 'T', 'E', 'O'},
    {'E', 'N', 'A', 'F', 'N', 'S'},
    {'T', 'N', 'L', 'E', 'R', 'I'}
};
// clang-format on
//
const int numWords = 7;
const int minWordLength = 4;
const int width = 6;
const int height = 8;
// const int maxWordLength = (width * height) - (minWordLength * (numWords -
// 1));
const int maxWordLength = 9;

std::unordered_set<std::string> exampleSolution = {
    "residue", "vestige", "remnant", "leftovers", "dregs", "trace", "souvenir"};

std::vector<std::vector<Node>> map(std::vector<std::vector<char>> grid) {
	std::vector<std::vector<Node>> nodeGrid;

	for (int r = 0; r < height; r++) {
		std::vector<Node> row;
		for (int c = 0; c < width; c++) {
			row.emplace_back(grid[r][c], Vec2{r, c});
		}
		nodeGrid.push_back(std::move(row));
	}

	return nodeGrid;
};

bool isInBounds(int row, int col) {
	return row >= 0 && col >= 0 && row < height && col < width;
}

bool isValid(int r, int c, std::vector<std::vector<Node>> nodeMap) {
	return isInBounds(r, c) && !nodeMap[r][c].isUsed;
}

void debugNodeMap(std::vector<std::vector<Node>> &nodeMap) {
	for (auto row : nodeMap) {
		for (auto node : row) {
			std::cout << node << std::endl;
		}
	}
}

void connect(std::vector<std::vector<Node>> &nodeMap) {
	for (auto &row : nodeMap) {
		for (Node &curNode : row) {
			for (Vec2 dir : Directions::ALL) {
				int newRow = curNode.pos.x + dir.x;
				int newCol = curNode.pos.y + dir.y;
				if (isInBounds(newRow, newCol)) {
					curNode.neighbors.push_back(&nodeMap[newRow][newCol]);
				}
			}
		}
	}
}

std::string stringFromPath(std::vector<Node *> &path) {
	std::string res;
	res.reserve(path.size());
	for (Node *node : path) {
		res += node->val;
	}

	return res;
}

void markPathUsed(std::vector<Node *> path) {
	for (Node *node : path) {
		node->isUsed = true;
	}
}

std::string dfs(Node *node, std::vector<Node *> &path) {
	if (node == nullptr || path.size() > maxWordLength) {
		return "";
	}

	path.push_back(node);
	std::string curString = stringFromPath(path);

	// Debug: entering DFS
	// std::cout << "[DFS] Depth=" << path.size() << " Visiting=" << node->val
	//           << " Path=" << curString << std::endl;

	if (exampleSolution.count(curString) == 1) {
		std::cout << "  [FOUND] Word=" << curString << std::endl;
		markPathUsed(path);
		return curString;
	}

	for (Node *neighbor : node->neighbors) {
		// is the neighbor even valid
		if (!neighbor->isUsed &&
		    std::find(path.begin(), path.end(), neighbor) == path.end()) {
			std::string resPath = dfs(neighbor, path);
			if (resPath.length() != 0) {
				return resPath;
			}
		}
	}

	path.pop_back();
	return "";
}

std::vector<std::string> solveBoard(std::vector<std::vector<Node>> &nodeMap) {
	std::vector<std::string> words;

	for (auto &row : nodeMap) {
		for (Node &node : row) {
			if (node.isUsed) {
				continue;
			}
			std::cout << "\n[START DFS] From letter '" << node.val << "' at ("
			          << node.pos.x << "," << node.pos.y << ")\n";
			std::vector<Node *> path;
			std::string word = dfs(&node, path);

			if (word.length() != 0) {
				words.push_back(word);
			}
		}
	}

	return words;
}

int main() {
	std::vector<std::vector<Node>> nodeMap = map(exampleGrid);
	connect(nodeMap);
	// debugNodeMap(nodeMap);
	std::vector<std::string> words = solveBoard(nodeMap);
	for (std::string word : words) {
		std::cout << word << std::endl;
	}
}
