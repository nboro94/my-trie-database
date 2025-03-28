#include <iostream>
#include "trie.h"

int main() {
    Trie trie;
    std::string command, word;

    std::cout << "Welcome to the Trie Database!" << std::endl;
    std::cout << "Available commands: insert, search, remove, print, exit" << std::endl;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "insert") {
            std::cout << "Enter word to insert: ";
            std::cin >> word;
            trie.insert(word);
            std::cout << "Inserted: " << word << std::endl;
        } else if (command == "search") {
            std::cout << "Enter word to search: ";
            std::cin >> word;
            if (trie.search(word)) {
                std::cout << "Found: " << word << std::endl;
            } else {
                std::cout << "Not found: " << word << std::endl;
            }
        } else if (command == "remove") {
            std::cout << "Enter word to remove: ";
            std::cin >> word;
            trie.remove(word);
            std::cout << "Removed: " << word << std::endl;
        } else if (command == "print") {
            trie.printWords();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}