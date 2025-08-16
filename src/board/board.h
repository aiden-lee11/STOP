#include <vector>
#include "../node/node.h"


class Board {
public:
	Board(const std::vector<std::vector<char>>& initialGrid);

	int getWidth() const;
	int getHeight() const;

	Node* getNodeAt(int row, int col);
	const Node* getNodeAt(int row, int col) const;
private:
	std::vector<std::vector<Node>> m_nodes;
	int m_width;
	int m_height;
	void connectAllNodes();
	bool isInBounds(int row, int col);
	bool isValid(int row, int col);
};
