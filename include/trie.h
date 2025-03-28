#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>

class TrieNode {
public:
    TrieNode() : m_isEndOfWord(false) {}

    // Provide access to children
    const std::unordered_map<char, TrieNode*>& getChildren() const {
        return children;
    }

    // Iterator for children
    std::unordered_map<char, TrieNode*>::const_iterator begin() const {
        return children.begin();
    }

    std::unordered_map<char, TrieNode*>::const_iterator end() const {
        return children.end();
    }

    void setEndOfWord(bool value) {
        m_isEndOfWord = value;
    }

    bool isEndOfWord() const {
        return m_isEndOfWord;
    }

    void setChild(char ch, TrieNode* node) {
        children[ch] = node;
    }

    TrieNode* getChild(char ch) const {
        auto it = children.find(ch);
        return (it != children.end()) ? it->second : nullptr;
    }

    void removeChild(char ch) {
        children.erase(ch);
    }

    bool hasChild(char ch) const {
        return children.find(ch) != children.end();
    }

private:
    std::unordered_map<char, TrieNode*> children;
    bool m_isEndOfWord;
};

class Trie {
private:
    TrieNode* root;

    void collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& words) const;

public:
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        delete root;
    }

    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool remove(const std::string& word);
    void printWords() const; // New function declaration

private:
    bool removeHelper(TrieNode* node, const std::string& word, size_t depth);
    bool nodeIsEmpty(TrieNode* node) const;
};

#endif // TRIE_H