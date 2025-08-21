#include "board/board.h"
#include "solver/solver.h"
#include <fstream>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

struct StrandsData {
	std::vector<std::vector<char>> grid;
	std::vector<std::string> solutions;
};

StrandsData load_strands_from_json(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filename);
	}

	nlohmann::json j;
	file >> j;

	StrandsData data;

	// Load the grid
	for (const auto &row : j["startingBoard"]) {
		std::vector<char> rowVec;
		for (char c : row.get<std::string>()) {
			rowVec.push_back(c);
		}
		data.grid.push_back(rowVec);
	}

	// Load theme words and spangram
	data.solutions = j["themeWords"];
	data.solutions.push_back(j["spangram"]);

	return data;
}

int main() {
	StrandsData strandsData = load_strands_from_json("strands.json");

	auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());

	Board board(strandsData.grid, screen);

	Solver solver(strandsData.solutions);
	solver.solve(board);
}
