#pragma once

#include <vector>
#include "../node/node.h"
#include <ftxui/screen/screen.hpp>


class Board {
public:
	Board(const std::vector<std::vector<char>>& initialGrid);

	int getWidth() const;
	int getHeight() const;

	Node* getNodeAt(int row, int col);
	const Node* getNodeAt(int row, int col) const;
	void printBoard(ftxui::Screen& screen);

private:
	std::vector<std::vector<Node>> m_nodes;
	int m_width;
	int m_height;
	void connectAllNodes();
	bool isInBounds(int row, int col);
	bool isValid(int row, int col);
	void debugNodeMap();
};
