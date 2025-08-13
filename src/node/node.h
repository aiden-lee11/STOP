#include <vector>

struct Vec2 {
	int x;
	int y;
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

	Node(char val, Vec2 pos) : val(val), pos(pos) {}
};
