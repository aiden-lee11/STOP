#pragma once

#include "../node/node.h"
#include <array>
#include <string>
#include <unordered_set>

class Trie {
  public:
	class TrieNode {
	  public:
		TrieNode() {
			for (auto &child : m_children) {
				child = nullptr;
			}

			m_endOfWord = false;
		}

		std::array<TrieNode *, 26> getChildren();
		bool isEndOfWord();
		void enableEndOfWord();
		void setChild(int ind);

	  private:
		bool m_endOfWord;
		std::array<TrieNode *, 26> m_children;
	};

	Trie(const std::vector<std::string> &solutionWords) {
		for (std::string word : solutionWords) {
			insert(word);
		}
	};
	TrieNode *root = new TrieNode();
	bool isPrefix(std::vector<Node *> &path);
	bool isWord(std::vector<Node *> &path);

  private:
	void insert(std::string word);
	bool search(std::vector<Node *> path, bool prefix = false);
};
