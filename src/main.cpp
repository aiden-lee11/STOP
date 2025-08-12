#include "node/node.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>



std::vector<std::vector<Node>> map(std::vector<std::vector<char>> grid) {
	size_t height = grid.size(); 
	size_t width = grid[0].size();

	std::vector<std::vector<Node>> node_grid;

	for (int r = 0; r < height; r++) {
		std::vector<Node> row;
		for (int c = 0; c < width; c++) {
			row.emplace_back(grid[r][c], Vec2{r,c});
		}
		node_grid.push_back(std::move(row));
	} 

	return node_grid;
};

int main() {
	Node n = Node('c', {0,0});
	std::cout << n.val << std::endl; 
}
