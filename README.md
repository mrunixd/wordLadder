# Word Ladder Program

## Description

The Word Ladder program finds the shortest transformation sequence from a start word to an end word, such that only one letter can be changed at a time and each transformed word must exist in the given dictionary of words. This implementation uses breadth-first search (BFS) to ensure the shortest path is found.

## Features

- Finds the shortest transformation sequence from the start word to the end word.
- Uses BFS for efficient pathfinding.
- Validates that each intermediate word is in the given dictionary.

## Requirements

- C++11 or higher
- Standard Template Library (STL)

## Usage
   ```bash 
    git clone https://github.com/yourusername/word-ladder.git
    cd word-ladder
    g++ -std=c++11 -o word_ladder word_ladder.cpp
    ./word_ladder
    
