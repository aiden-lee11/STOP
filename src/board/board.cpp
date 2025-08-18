#include "board.h"
#include <vector>
#include <iostream>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <thread>
#include <chrono>



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


void Board::debugNodeMap() {
	for (auto row : m_nodes) {
		for (auto node : row) {
			std::cout << node << std::endl;
		}
	}
}

int Board::getHeight() const {
	return m_nodes.size();
};

int Board::getWidth() const {
	return m_nodes[0].size();
};


Node* Board::getNodeAt(int row, int col) {
	return &m_nodes[row][col];
};

const Node* Board::getNodeAt(int row, int col) const {
	return &m_nodes[row][col];
};


void Board::printBoard(ftxui::Screen& screen) {
	auto cell = [](const Node* t) { 
		return (
		ftxui::text(&t->val) | 
		ftxui::border | 
		ftxui::color(t->isUsed ? 
	ftxui::Color::Red : 
	       ftxui::Color::White)
	); 
	};

	std::vector<ftxui::Elements> lines;
	for (auto row : m_nodes) {
		std::vector<ftxui::Element> line;
		for (auto node : row) {
			line.push_back(cell(&node));
		}
		lines.push_back(line);
	}

	auto document = ftxui::gridbox({lines});
	Render(screen, document);
	screen.Print();
}
