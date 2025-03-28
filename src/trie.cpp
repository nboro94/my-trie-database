#include "../include/trie.h"
#include <iostream>
#include <vector>

TrieNode::TrieNode() : m_isEndOfWord(false) {}

const std::unordered_map<char, std::unique_ptr<TrieNode>>& TrieNode::getChildren() const {
    return children;
}

std::unordered_map<char, std::unique_ptr<TrieNode>>::const_iterator TrieNode::begin() const {
    return children.begin();
}

std::unordered_map<char, std::unique_ptr<TrieNode>>::const_iterator TrieNode::end() const {
    return children.end();
}

void TrieNode::setEndOfWord(bool value) {
    m_isEndOfWord = value;
}

bool TrieNode::isEndOfWord() const {
    return m_isEndOfWord;
}

void TrieNode::setChild(char ch, std::unique_ptr<TrieNode> node) {
    children[ch] = std::move(node);
}

TrieNode* TrieNode::getChild(char ch) const {
    auto it = children.find(ch);
    return (it != children.end()) ? it->second.get() : nullptr;
}

void TrieNode::removeChild(char ch) {
    children.erase(ch);
}

bool TrieNode::hasChild(char ch) const {
    return children.find(ch) != children.end();
}

Trie::Trie() : root(std::make_unique<TrieNode>()) {}

void Trie::insert(const std::string& word) {
    TrieNode* node = root.get();
    for (char ch : word) {
        auto& children = node->getChildren();
        if (children.find(ch) == children.end()) {
            node->setChild(ch, std::make_unique<TrieNode>());
        }
        node = node->getChild(ch);
    }
    node->setEndOfWord(true);
}

bool Trie::search(const std::string& word) const {
    TrieNode* node = root.get();
    for (char ch : word) {
        node = node->getChild(ch);
        if (!node) {
            return false;
        }
    }
    return node->isEndOfWord();
}

bool Trie::remove(const std::string& word) {
    return removeHelper(root.get(), word, 0);
}

bool Trie::removeHelper(TrieNode* node, const std::string& word, size_t depth) {
    if (!node) {
        return false;
    }
    if (depth == word.size()) {
        if (node->isEndOfWord()) {
            node->setEndOfWord(false);
            return nodeIsEmpty(node);
        }
        return false;
    }

    char ch = word[depth];
    TrieNode* childNode = node->getChild(ch);
    if (!childNode) {
        return false;
    }

    if (removeHelper(childNode, word, depth + 1)) {
        node->removeChild(ch);
        return !node->isEndOfWord() && nodeIsEmpty(node);
    }
    return false;
}

bool Trie::nodeIsEmpty(TrieNode* node) const {
    for (auto it = node->begin(); it != node->end(); ++it) {
        if (it->second) {
            return false;
        }
    }
    return true;
}

void Trie::printWords() const {
    std::vector<std::string> words;
    collectWords(root.get(), "", words);
    std::cout << "Words in Trie:" << std::endl;
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }
}

void Trie::collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& words) const {
    if (!node) {
        return;
    }
    if (node->isEndOfWord()) {
        words.push_back(prefix);
    }
    for (const auto& [ch, childNode] : node->getChildren()) {
        collectWords(childNode.get(), prefix + ch, words);
    }
}

Trie::~Trie() = default;