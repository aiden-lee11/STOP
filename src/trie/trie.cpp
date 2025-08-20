#include "trie.h"
#include <array>
#include <iostream>
#include <string>
#include <vector>

std::array<Trie::TrieNode *, 26> Trie::TrieNode::getChildren() {
	return m_children;
};

bool Trie::TrieNode::isEndOfWord() { return m_endOfWord; };
void Trie::TrieNode::enableEndOfWord() { m_endOfWord = true; };

void Trie::TrieNode::setChild(int ind) { m_children[ind] = new TrieNode(); }

bool Trie::search(std::vector<Node *> path, bool prefix) {
	TrieNode *curTrieNode = root;

	for (Node *node : path) {
		int ind = node->val - 'A';
		TrieNode *childNode = curTrieNode->getChildren()[ind];
		if (!childNode) {
			return false;
		}
		curTrieNode = childNode;
	}
	return prefix ? true : curTrieNode->isEndOfWord();
}

void Trie::insert(std::string word) {
	TrieNode *curTrieNode = root;

	for (char c : word) {
		int ind = c - 'A';
		if (!curTrieNode->getChildren()[ind]) {
			curTrieNode->setChild(ind);
		}
		curTrieNode = curTrieNode->getChildren()[ind];
	}

	curTrieNode->enableEndOfWord();
}

bool Trie::isPrefix(std::vector<Node *> &path) { return search(path, true); }

bool Trie::isWord(std::vector<Node *> &path) { return search(path); }
