#include "node/node.h"
#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
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

std::string exampleSolution[7] = {"residue", "vestige", "remnant", "leftovers",
                                  "dregs",   "trace",   "souvenir"};

std::vector<std::vector<Node>> map(std::vector<std::vector<char>> grid) {
	size_t height = grid.size();
	size_t width = grid[0].size();

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

bool isInBounds(int row, int col, int height, int width) {
	return row >= 0 && col >= 0 && row < height && col < width;
}

bool isValid(int r, int c, int height, int width,
             std::vector<std::vector<Node>> nodeMap) {
	return isInBounds(r, c, width, height) && !nodeMap[r][c].isUsed;
}

void debugNodeMap(std::vector<std::vector<Node>> &nodeMap) {
	for (auto row : nodeMap) {
		for (auto node : row) {
			std::cout << node << std::endl;
		}
	}
}

void connect(std::vector<std::vector<Node>> &nodeMap) {
	size_t height = nodeMap.size();
	size_t width = nodeMap[0].size();

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Node &curNode = nodeMap[r][c];
			for (Vec2 dir : Directions::ALL) {
				int newRow = curNode.pos.x + dir.x;
				int newCol = curNode.pos.y + dir.y;
				if (isInBounds(newRow, newCol, height, width)) {
					curNode.neighbors.push_back(&nodeMap[newRow][newCol]);
				}
			}
		}
	}
}

int main() {
	std::vector<std::vector<Node>> nodeMap = map(exampleGrid);
	connect(nodeMap);
	debugNodeMap(nodeMap);

	return 0;
}
