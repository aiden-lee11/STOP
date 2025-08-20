#include "board/board.h"
#include "node/node.h"
#include "solver/solver.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <vector>

// todo put in test file or smth
// clang-format off
std::vector<std::vector<char>> exampleGrid = {
    {'R', 'E', 'S', 'R', 'E', 'G'},
    {'E', 'U', 'R', 'D', 'S', 'R'},
    {'S', 'I', 'D', 'E', 'T', 'A'},
    {'E', 'V', 'I', 'V', 'E', 'C'},
    {'S', 'T', 'G', 'O', 'V', 'U'},
    {'R', 'M', 'E', 'T', 'E', 'O'},
    {'E', 'N', 'A', 'F', 'N', 'S'},
    {'T', 'N', 'L', 'E', 'R', 'I'}
};
// clang-format on

const std::vector<std::string> exampleSolution = {
    "RESIDUE", "VESTIGE", "REMNANT", "LEFTOVERS", "DREGS", "TRACE", "SOUVENIR"};

int main() {
	auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());
	Board board(exampleGrid, screen);
	Solver solver(exampleSolution);

	solver.solve(board);
}
