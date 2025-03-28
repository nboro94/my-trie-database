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
    if (word.empty()) {
        return;
    }

    TrieNode* current = root.get();
    for (const char ch : word) {
        if (!current->hasChild(ch)) {
            current->setChild(ch, std::make_unique<TrieNode>());
        }
        current = current->getChild(ch);
    }
    current->setEndOfWord(true);
}

bool Trie::search(const std::string& word) const {
    // Handle empty string case
    if (word.empty()) {
        return false;
    }

    // Start from the root node
    TrieNode* current = root.get();

    // Traverse the trie for each character in the word
    for (const char ch : word) {
        // If current character doesn't exist in trie, word is not found
        if (!current->hasChild(ch)) {
            return false;
        }
        // Move to the next node in the path
        current = current->getChild(ch);
    }

    // Word exists only if the last node is marked as end of word
    return current->isEndOfWord();
}

bool Trie::remove(const std::string& word) {
    return removeHelper(root.get(), word, 0);
}

bool Trie::removeHelper(TrieNode* node, const std::string& word, size_t depth) {
    // Early return for invalid cases
    if (!node || depth > word.size()) {
        return false;
    }

    // Word found - handle deletion
    if (depth == word.size()) {
        if (!node->isEndOfWord()) {
            return false;  // Word not marked as complete
        }
        node->setEndOfWord(false);
        return node->getChildren().empty();  // Return true if no children
    }

    // Continue searching
    const char ch = word[depth];
    TrieNode* child = node->getChild(ch);
    
    if (!child || !removeHelper(child, word, depth + 1)) {
        return false;
    }

    // Remove child if it should be deleted
    node->removeChild(ch);
    
    // Return true if this node should also be deleted
    return !node->isEndOfWord() && node->getChildren().empty();
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