#include "board.h"
#include <vector>


Board::Board(const std::vector<std::vector<char>> &initialGrid){
	if (initialGrid.empty() || initialGrid[0].empty()) {
		throw std::invalid_argument("empty grid");
	}
	std::vector<std::vector<Node>> nodeGrid;

	m_height = initialGrid.size();
	m_width = initialGrid[0].size(); 

	for (int r = 0; r < m_height; r++) {
		std::vector<Node> row;
		for (int c = 0; c < m_width; c++) {
			row.emplace_back(initialGrid[r][c], Vec2{r, c});
		}
		m_nodes.push_back(std::move(row));
	}

	connectAllNodes();
}

void Board::connectAllNodes() {
	for (auto &row : m_nodes) {
		for (Node &curNode : row) {
			for (Vec2 dir : Directions::ALL) {
				int newRow = curNode.pos.x + dir.x;
				int newCol = curNode.pos.y + dir.y;
				if (isInBounds(newRow, newCol)) {
					curNode.neighbors.push_back(&m_nodes[newRow][newCol]);
				}
			}
		}
	}
}

bool Board::isInBounds(int row, int col) {
	return row >= 0 && col >= 0 && row < m_height && col < m_width;
}

bool Board::isValid(int row, int col) {
	return isInBounds(row, col) && !m_nodes[row][col].isUsed;
}
