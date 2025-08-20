#pragma once

#include "../node/node.h"
#include <ftxui/screen/screen.hpp>
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

  private:
	std::vector<std::vector<Node>> m_nodes;
	int m_width;
	int m_height;
	ftxui::Screen &m_screen;
	void connectAllNodes();
	bool isInBounds(int row, int col);
	bool isValid(int row, int col);
	void debugNodeMap();
};
