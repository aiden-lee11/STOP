#include "node/node.h"
#include <algorithm>
#include <cstdio>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <thread>   // For sleeping
#include <chrono>   // For time units

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

void debugNodeMap(std::vector<std::vector<Node>> &nodeMap) {
	for (auto row : nodeMap) {
		for (auto node : row) {
			std::cout << node << std::endl;
		}
	}
}

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

void printSolution(std::vector<std::pair<std::string, std::vector<Node *>>> &words){
	for (auto word : words) {
		std::cout << word.first << std::endl;

		for (Node *node : word.second) {
			std::cout << "\t" << node << std::endl;
		}
	}
}


std::string stringFromPath(std::vector<Node *> &path) {
	std::string res;
	res.reserve(path.size());
	for (Node *node : path) {
		res += node->val;
	}

	return res;
}

void markPathUsed(std::vector<Node *> path) {
	for (Node *node : path) {
		node->isUsed = true;
	}
}

std::pair<std::string, std::vector<Node *>>
dfs(Node *node, std::vector<Node *> &path, const size_t attemptLength) {
	if (node == nullptr || path.size() > attemptLength) {
		return std::make_pair("", path);
	}

	path.push_back(node);
	std::string curString = stringFromPath(path);

	// Debug: entering DFS
	// std::cout << "[DFS] Depth=" << path.size() << " Visiting=" << node->val
	//           << " Path=" << curString << std::endl;

	if (exampleSolution.count(curString) == 1) {
		// std::cout << "  [FOUND] Word=" << curString << std::endl;
		markPathUsed(path);
		return std::make_pair(curString, path);
	}

	for (Node *neighbor : node->neighbors) {
		// is the neighbor even valid
		if (!neighbor->isUsed &&
			std::find(path.begin(), path.end(), neighbor) == path.end()) {
			auto resPath = dfs(neighbor, path, attemptLength);
			if (resPath.first.length() != 0) {
				return resPath;
			}
		}
	}

	path.pop_back();
	return std::make_pair("", path);
}

std::vector<std::pair<std::string, std::vector<Node *>>>
solveBoard(std::vector<std::vector<Node>> &nodeMap, size_t attemptLength) {
	std::vector<std::pair<std::string, std::vector<Node *>>> words;

	for (auto &row : nodeMap) {
		for (Node &node : row) {
			if (node.isUsed) {
				continue;
			}
			std::vector<Node *> path;
			auto res = dfs(&node, path, attemptLength);

			if (res.first.length() != 0) {
				words.push_back(res);
			}
		}
	}

	return words;
} 


int main() {
	std::vector<std::vector<Node>> nodeMap =  map(exampleGrid);
	connect(nodeMap);
	// debugNodeMap(nodeMap);
	// printSolution(words);
	//
	auto screen = ftxui::Screen::Create(ftxui::Dimension::Full());

	for (size_t attemptLength = 4; attemptLength < maxWordLength;
	++attemptLength) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		auto words = solveBoard(nodeMap, attemptLength);
		printBoard(screen, nodeMap);

		if (words.size() == numWords) {
			break;
		}
	}

}
