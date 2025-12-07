#include "../include/trie.h"
#include <iostream>
#include <vector>
#include <fstream>

TrieNode::TrieNode() : m_isEndOfWord(false) {}

TrieNode::TrieNode(const TrieNode& other) : m_isEndOfWord(other.m_isEndOfWord) {
    for (const auto& [key, value] : other.children) {
        children[key] = std::make_unique<TrieNode>(*value);
    }
}

TrieNode& TrieNode::operator=(const TrieNode& other) {
    if (this != &other) {
        m_isEndOfWord = other.m_isEndOfWord;
        children.clear();
        for (const auto& [key, value] : other.children) {
            children[key] = std::make_unique<TrieNode>(*value);
        }
    }
    return *this;
}

TrieNode::TrieNode(TrieNode&& other) noexcept = default;

TrieNode& TrieNode::operator=(TrieNode&& other) noexcept = default;

const TrieMap<char, std::unique_ptr<TrieNode>>& TrieNode::getChildren() const {
    return children;
}

TrieMap<char, std::unique_ptr<TrieNode>>::const_iterator TrieNode::begin() const {
    return children.begin();
}

TrieMap<char, std::unique_ptr<TrieNode>>::const_iterator TrieNode::end() const {
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

Trie::Trie(const Trie& other) : root(std::make_unique<TrieNode>(*other.root)) {}

Trie& Trie::operator=(const Trie& other) {
    if (this != &other) {
        root = std::make_unique<TrieNode>(*other.root);
    }
    return *this;
}

Trie::Trie(Trie&& other) noexcept = default;

Trie& Trie::operator=(Trie&& other) noexcept = default;

void Trie::insert(const std::string& word) {
    if (word.empty()) {
        return;
    }

    TrieNode* current = root.get();
    for (const char ch : word) {
        TrieNode* child = current->getChild(ch);
        if (!child) {
            auto newNode = std::make_unique<TrieNode>();
            child = newNode.get();
            current->setChild(ch, std::move(newNode));
        }
        current = child;
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
    if (word.empty()) {
        return false;
    }

    bool removed = false;
    removeHelper(root.get(), word, 0, removed);
    return removed;
}

bool Trie::removeHelper(TrieNode* node, const std::string& word, size_t depth, bool& removed) {
    if (!node || depth > word.size()) {
        return false;
    }

    if (depth == word.size()) {
        if (!node->isEndOfWord()) {
            return node->getChildren().empty();
        }
        node->setEndOfWord(false);
        removed = true;
        return node->getChildren().empty();
    }

    const char ch = word[depth];
    TrieNode* child = node->getChild(ch);
    if (!child) {
        return false;
    }

    const bool shouldDeleteChild = removeHelper(child, word, depth + 1, removed);
    if (shouldDeleteChild) {
        node->removeChild(ch);
    }

    return !node->isEndOfWord() && node->getChildren().empty();
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

void Trie::visualize(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error opening file for visualization: " << filename << std::endl;
        return;
    }

    out << "digraph Trie {" << std::endl;
    out << "node [shape=circle];" << std::endl;
    int nodeCount = 0;
    std::string rootName = "node" + std::to_string(nodeCount++);
    out << rootName << " [label=\"ROOT\"];" << std::endl;
    visualizeHelper(out, root.get(), rootName, nodeCount);
    out << "}" << std::endl;
}

void Trie::visualizeHelper(std::ostream& out, const TrieNode* node, const std::string& parentName, int& nodeCount) const {
    if (!node) {
        return;
    }

    for (const auto& [ch, childNode] : node->getChildren()) {
        std::string childName = "node" + std::to_string(nodeCount++);
        out << childName << " [label=\"" << ch << "\"";
        if (childNode->isEndOfWord()) {
            out << ", shape=doublecircle";
        }
        out << "];" << std::endl;
        out << parentName << " -> " << childName << ";" << std::endl;
        visualizeHelper(out, childNode.get(), childName, nodeCount);
    }
}

Trie::~Trie() = default;