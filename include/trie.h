#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

/**
 * @class TrieNode
 * @brief Represents a single node in a Trie (prefix tree) data structure.
 * 
 * The TrieNode class provides functionality to manage children nodes,
 * mark the end of a word, and access child nodes. It is designed to
 * facilitate efficient storage and retrieval of strings in a Trie.
 */
class TrieNode {
public:
    /**
     * @brief Constructs a new TrieNode object.
     * 
     * Initializes the node with no children and marks it as not being
     * the end of a word.
     */
    TrieNode();

    /**
     * @brief Provides read-only access to the children of the node.
     * 
     * @return A constant reference to the unordered map of children nodes.
     */
    const std::unordered_map<char, std::unique_ptr<TrieNode>>& getChildren() const;

    /**
     * @brief Returns a constant iterator to the beginning of the children map.
     * 
     * @return An iterator pointing to the first child in the map.
     */
    std::unordered_map<char, std::unique_ptr<TrieNode>>::const_iterator begin() const;

    /**
     * @brief Returns a constant iterator to the end of the children map.
     * 
     * @return An iterator pointing past the last child in the map.
     */
    std::unordered_map<char, std::unique_ptr<TrieNode>>::const_iterator end() const;

    /**
     * @brief Marks the node as the end of a word or not.
     * 
     * @param value A boolean indicating whether the node is the end of a word.
     */
    void setEndOfWord(bool value);

    /**
     * @brief Checks if the node is marked as the end of a word.
     * 
     * @return True if the node is the end of a word, false otherwise.
     */
    bool isEndOfWord() const;

    /**
     * @brief Adds or updates a child node for a given character.
     * 
     * @param ch The character associated with the child node.
     * @param node A pointer to the child TrieNode.
     */
    void setChild(char ch, std::unique_ptr<TrieNode> node);

    /**
     * @brief Retrieves the child node associated with a given character.
     * 
     * @param ch The character to look for.
     * @return A pointer to the child TrieNode, or nullptr if no child exists.
     */
    TrieNode* getChild(char ch) const;

    /**
     * @brief Removes the child node associated with a given character.
     * 
     * @param ch The character whose associated child node should be removed.
     */
    void removeChild(char ch);

    /**
     * @brief Checks if the node has a child associated with a given character.
     * 
     * @param ch The character to check for.
     * @return True if a child exists for the character, false otherwise.
     */
    bool hasChild(char ch) const;

private:
    /**
     * @brief A map storing the children nodes, where each key is a character
     * and the value is a pointer to the corresponding TrieNode.
     */
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;

    /**
     * @brief A boolean flag indicating whether this node marks the end of a word.
     */
    bool m_isEndOfWord;
};

/**
 * @class Trie
 * @brief A class representing a Trie (prefix tree) data structure for storing and managing strings.
 *
 * The Trie class provides functionality to insert, search, and remove words, as well as retrieve all stored words.
 * It is implemented using a tree-like structure where each node represents a character in a word.
 */
class Trie {
private:
    /**
     * @brief Pointer to the root node of the Trie.
     */
    std::unique_ptr<TrieNode> root;

    /**
     * @brief Helper function to collect all words stored in the Trie starting from a given node.
     * 
     * @param node The current TrieNode being traversed.
     * @param prefix The prefix string formed by traversing the Trie up to the current node.
     * @param words A reference to a vector where the collected words will be stored.
     */
    void collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& words) const;

public:
    /**
     * @brief Constructs a new Trie object and initializes the root node.
     */
    Trie();

    /**
     * @brief Destroys the Trie object and deallocates memory used by the root node.
     */
    ~Trie();

    /**
     * @brief Inserts a word into the Trie.
     * 
     * @param word The word to be inserted.
     */
    void insert(const std::string& word);

    /**
     * @brief Searches for a word in the Trie.
     * 
     * @param word The word to search for.
     * @return true if the word exists in the Trie, false otherwise.
     */
    bool search(const std::string& word) const;

    /**
     * @brief Removes a word from the Trie.
     * 
     * @param word The word to be removed.
     * @return true if the word was successfully removed, false if the word was not found.
     */
    bool remove(const std::string& word);

    /**
     * @brief Prints all words stored in the Trie.
     * 
     * This function retrieves all words stored in the Trie and prints them to the standard output.
     */
    void printWords() const;

private:
    /**
     * @brief Helper function to recursively remove a word from the Trie.
     * 
     * @param node The current TrieNode being traversed.
     * @param word The word to be removed.
     * @param depth The current depth in the Trie corresponding to the character index in the word.
     * @return true if the node can be safely deleted, false otherwise.
     */
    bool removeHelper(TrieNode* node, const std::string& word, size_t depth);

    /**
     * @brief Checks if a given TrieNode has no children.
     * 
     * @param node The TrieNode to check.
     * @return true if the node has no children, false otherwise.
     */
    bool nodeIsEmpty(TrieNode* node) const;
};

#endif // TRIE_H