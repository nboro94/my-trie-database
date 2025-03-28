# Trie Database

This project implements a Trie data structure, which is a type of search tree used to store a dynamic set of strings, where the keys are usually strings. The Trie allows for efficient insertion, search, and deletion operations.

## Project Structure

```
my-trie-database
├── src
│   ├── main.cpp        # Entry point of the application
│   └── trie.cpp        # Implementation of the Trie class
├── include
│   └── trie.h          # Public header for the Trie class
├── CMakeLists.txt      # CMake configuration file
└── README.md           # Project documentation
```

## Building the Project

To build the project, you need to have CMake installed. Follow these steps:

1. Clone the repository or download the project files.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make -j
   ```

## Running the Application

After building the project, you can run the application using the following command:
```
./TrieDatabase
```

## Usage

The application allows you to interact with the Trie database by inserting, searching, and deleting words. Follow the prompts in the console to use the application.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.