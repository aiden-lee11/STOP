#pragma once

#include <ftxui/screen/color.hpp>
#include <ostream>
#include <vector>

struct Vec2 {
	int x;
	int y;

	friend std::ostream &operator<<(std::ostream &os, Vec2 obj) {
		os << "(" << obj.x << "," << obj.y << ")";
		return os;
	};
};

namespace Directions {
constexpr Vec2 UP = {-1, 0};
constexpr Vec2 DOWN = {1, 0};
constexpr Vec2 LEFT = {0, -1};
constexpr Vec2 RIGHT = {0, 1};
constexpr Vec2 TOP_LEFT = {-1, -1};
constexpr Vec2 TOP_RIGHT = {-1, 1};
constexpr Vec2 BOTTOM_LEFT = {1, -1};
constexpr Vec2 BOTTOM_RIGHT = {1, 1};
constexpr std::array<Vec2, 8> ALL = {
    UP, DOWN, LEFT, RIGHT, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
}; // namespace Directions

class Node {
  public:
	char val;
	Vec2 pos;
	std::vector<Node *> neighbors;
	bool isUsed;
	bool inPath;
	ftxui::Color color;

	Node(char val, Vec2 pos) : val(val), pos(pos) {}

	friend std::ostream &operator<<(std::ostream &os, const Node &obj) {
		os << "Node '" << obj.val << "' at " << obj.pos << " has ";

		if (obj.neighbors.empty()) {
			os << "no neighbors" << std::endl;
		} else {
			os << obj.neighbors.size() << " neighbors" << std::endl;
			for (const Node *neighbor : obj.neighbors) {
				os << "\t - Node '" << neighbor->val << "' at " << neighbor->pos
				   << std::endl;
			}
		}
		return os;
	};
	// overload with no neighbors
	friend std::ostream &operator<<(std::ostream &os, const Node *node) {
		os << "Node(val='" << node->val << "', pos={" << node->pos.x << ","
		   << node->pos.y << "})";
		return os;
	}
};
