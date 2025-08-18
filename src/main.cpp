#include "node/node.h"
#include "board/board.h"
#include "solver/solver.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <ftxui/screen/color.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

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
//
const int numWords = 7;
const int minWordLength = 4;
const int width = 6;
const int height = 8;
const int maxWordLength = (width * height) - (minWordLength * (numWords - 1));

std::unordered_set<std::string> exampleSolution = {
	"RESIDUE", "VESTIGE", "REMNANT", "LEFTOVERS", "DREGS", "TRACE", "SOUVENIR"};


void printBoard(ftxui::Screen& screen, std::vector<std::vector<Node>> &nodeMap) {
	// auto cell = [](const char* t) { return text(t) | border; };
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
	for (auto row : nodeMap) {
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

int main() {
	Board board(exampleGrid);
	Solver solver(exampleSolution);
	auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());

	solver.solve(board, [&]{
		board.printBoard(screen);
	});
	// solver.printSolution();
}
