#include "board/board.h"
#include "solver/solver.h"
#include <fstream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

// todo put in test file or smth
// clang-format off
// std::vector<std::vector<char>> exampleGrid = {
//     {'R', 'E', 'S', 'R', 'E', 'G'},
//     {'E', 'U', 'R', 'D', 'S', 'R'},
//     {'S', 'I', 'D', 'E', 'T', 'A'},
//     {'E', 'V', 'I', 'V', 'E', 'C'},
//     {'S', 'T', 'G', 'O', 'V', 'U'},
//     {'R', 'M', 'E', 'T', 'E', 'O'},
//     {'E', 'N', 'A', 'F', 'N', 'S'},
//     {'T', 'N', 'L', 'E', 'R', 'I'}
// };
// // clang-format on

// const std::vector<std::string> exampleSolution = {
//     "RESIDUE", "VESTIGE", "REMNANT", "LEFTOVERS", "DREGS", "TRACE", "SOUVENIR"};

std::vector<std::vector<char>>
load_grid_from_json(const std::string &filename) {
	std::ifstream file(filename);
	nlohmann::json j;
	file >> j;

	std::vector<std::vector<char>> grid;
	for (const auto &row : j["startingBoard"]) {
		std::vector<char> rowVec;
		for (char c : row.get<std::string>()) {
			rowVec.push_back(c);
		}
		grid.push_back(rowVec);
	}
	return grid;
}

int main() {
	auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
	auto grid = load_grid_from_json("strands.json");
	Board board(grid, screen);
	std::ifstream file("strands.json");
	nlohmann::json j;
	file >> j;
	std::vector<std::string> themeWords = j["themeWords"];
	Solver solver(themeWords);

	solver.solve(board);
}
