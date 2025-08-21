#pragma once

#include "../node/node.h"
#include <ftxui/screen/screen.hpp>
#include <random>
#include <vector>

class Board {
  public:
	Board(const std::vector<std::vector<char>> &initialGrid,
	      ftxui::Screen &screen);

	int getWidth() const;
	int getHeight() const;

	Node *getNodeAt(int row, int col);
	const Node *getNodeAt(int row, int col) const;
	void printBoard();
	void updateBoard(std::vector<Node *> &word);

  private:
	std::vector<std::vector<Node>> m_nodes;
	std::mt19937 m_gen;
	int m_width;
	int m_height;
	ftxui::Screen &m_screen;
	void connectAllNodes();
	bool isInBounds(int row, int col);
	bool isValid(int row, int col);
	void debugNodeMap();
};
