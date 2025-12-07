#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "trie.h"

#ifdef _WIN32
#include <io.h>
#define IS_TTY _isatty(_fileno(stdin))
#else
#include <unistd.h>
#define IS_TTY isatty(fileno(stdin))
#endif

int main() {
    Trie trie;
    std::string line, command, word;
    bool interactive = IS_TTY;

    if (interactive) {
        std::cout << "Welcome to the Trie Database!" << std::endl;
        std::cout << "Available commands: insert, search, remove, print, visualize, exit" << std::endl;
        std::cout << "You can provide multiple words for 'insert' and 'remove', e.g., 'insert apple banana cherry'" << std::endl;
    }

    while (true) {
        if (interactive) {
            std::cout << "> ";
        }
        
        if (!std::getline(std::cin, line)) {
            break; // End of input
        }
        
        std::stringstream ss(line);
        ss >> command;

        if (command == "insert") {
            int count = 0;
            while (ss >> word) {
                trie.insert(word);
                if (interactive) {
                    std::cout << "Inserted: " << word << std::endl;
                }
                count++;
            }
            if (count == 0 && interactive) {
                std::cout << "Enter word(s) to insert: ";
                std::getline(std::cin, line);
                std::stringstream inner_ss(line);
                while (inner_ss >> word) {
                    trie.insert(word);
                    std::cout << "Inserted: " << word << std::endl;
                }
            }
        } else if (command == "search") {
            ss >> word;
            if (word.empty() && interactive) {
                std::cout << "Enter word to search: ";
                std::cin >> word;
                std::cin.ignore(); // consume newline
            }
            if (trie.search(word)) {
                if (interactive) {
                    std::cout << "Found: " << word << std::endl;
                }
            } else {
                if (interactive) {
                    std::cout << "Not found: " << word << std::endl;
                }
            }
        } else if (command == "remove") {
            int count = 0;
            while (ss >> word) {
                if (trie.remove(word)) {
                    if (interactive) {
                        std::cout << "Removed: " << word << std::endl;
                    }
                } else {
                    if (interactive) {
                        std::cout << "Word not found: " << word << std::endl;
                    }
                }
                count++;
            }
            if (count == 0 && interactive) {
                std::cout << "Enter word(s) to remove: ";
                std::getline(std::cin, line);
                std::stringstream inner_ss(line);
                while (inner_ss >> word) {
                    if (trie.remove(word)) {
                        std::cout << "Removed: " << word << std::endl;
                    } else {
                        std::cout << "Word not found: " << word << std::endl;
                    }
                }
            }
        } else if (command == "print") {
            trie.printWords();
        } else if (command == "visualize") {
            ss >> word;
             if (word.empty() && interactive) {
                std::cout << "Enter filename for visualization (e.g., trie.dot): ";
                std::cin >> word;
                std::cin.ignore(); // consume newline
            }
            trie.visualize(word);
            if (interactive) {
                std::cout << "Trie visualization saved to " << word << std::endl;
            }
        } else if (command == "exit") {
            break;
        } else if (!command.empty() && interactive) {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}