#include "node/node.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <utility>
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
const int maxWordLength = (width * height) - (minWordLength * (numWords - 1));

std::unordered_set<std::string> exampleSolution = {
    "RESIDUE", "VESTIGE", "REMNANT", "LEFTOVERS", "DREGS", "TRACE", "SOUVENIR"};

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

// TODO try out bfs
// std::string bfs(Node *node) {
// }

std::pair<std::string, std::vector<Node *>>
dfs(Node *node, std::vector<Node *> &path, const int attemptLength) {
	if (node == nullptr || path.size() > attemptLength) {
		return std::make_pair("", path);
	}

	path.push_back(node);
	std::string curString = stringFromPath(path);

	// Debug: entering DFS
	// std::cout << "[DFS] Depth=" << path.size() << " Visiting=" << node->val
	//           << " Path=" << curString << std::endl;

	if (exampleSolution.count(curString) == 1) {
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
}

std::vector<std::pair<std::string, std::vector<Node *>>>
solveBoard(std::vector<std::vector<Node>> &nodeMap) {
	std::vector<std::pair<std::string, std::vector<Node *>>> words;

	for (int attemptLength = 4; attemptLength < maxWordLength;
	     ++attemptLength) {
		for (auto &row : nodeMap) {
			for (Node &node : row) {
				if (node.isUsed) {
					continue;
				}
				// std::cout << "\n[START DFS] From letter '" << node.val
				//           << "' at (" << node.pos.x << "," << node.pos.y
				//           << ")\n";
				std::vector<Node *> path;
				auto res = dfs(&node, path, attemptLength);

				if (res.first.length() != 0) {
					words.push_back(res);
				}
			}
		}

		if (words.size() == numWords) {
			break;
		}
	}

	return words;
}

int main() {
	std::vector<std::vector<Node>> nodeMap = map(exampleGrid);
	connect(nodeMap);
	// debugNodeMap(nodeMap);

	std::vector<std::pair<std::string, std::vector<Node *>>> words =
	    solveBoard(nodeMap);
	for (auto word : words) {
		std::cout << word.first << std::endl;
		std::cout << "Path to create" << std::endl;

		for (Node *node : word.second) {
			std::cout << "\t" << node << std::endl;
		}
	}
}
