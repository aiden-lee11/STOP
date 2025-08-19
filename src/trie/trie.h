#pragma once

#include "../node/node.h"
#include <array>
#include <string>
#include <unordered_set>

class Trie {
  public:
	class TrieNode {
	  public:
		TrieNode(char value) : m_value(value) {
			for (auto &child : m_children) {
				child = nullptr;
			}

			m_endOfWord = false;
		}

		std::array<TrieNode *, 26> getChildren();
		bool isEndOfWord();
		void enableEndOfWord();
		void setChild(TrieNode *node);

	  private:
		bool m_endOfWord;
		char m_value;
		std::array<TrieNode *, 26> m_children;
	};

	Trie(std::unordered_set<std::string> &solutionWords) {
		for (std::string word : solutionWords) {
			insert(word);
		}
	};
	TrieNode *root = new TrieNode('a');
	bool isPrefix(std::vector<Node *> &path);
	bool isWord(std::vector<Node *> &path);

  private:
	void insert(std::string word);
	bool search(std::vector<Node *> path, bool prefix = false);
};
