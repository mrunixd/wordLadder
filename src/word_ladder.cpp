#include "word_ladder.h"
#include <unordered_set>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <queue>

auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	std::unordered_set<std::string> set;
	std::ifstream file (path);
	std::string buffer;

	if (file.is_open()) {
		while (std::getline(file, buffer)) {
			set.insert(buffer);
		}
	}

	return set;
}

auto reduce_set(std::unordered_set<std::string> &lexicon, const std::string &from) {
	size_t size = from.size();
	std::erase_if(lexicon, [size](auto& x) {
		return x.size() != size;
	});

	// any other improvements
}

std::vector<std::string> generate_neighbours(const std::string &word, const std::unordered_set<std::string> &lexicon) {
	std::vector<std::string> neighbours;
	for (size_t i = 0; i < word.size(); i++) {
		std::string temp = word;
		for (char c = 'a'; c <= 'z'; ++c) {
			temp[i] = c;
			if (lexicon.find(temp) != lexicon.end()) {
				neighbours.push_back(temp);
			}
		}
	}
	return neighbours;
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	std::vector<std::vector<std::string>> results;

    std::unordered_set<std::string> copy_lexicon = lexicon;
    reduce_set(copy_lexicon, from);

    std::queue<std::string> q;
    q.push(from);

    std::unordered_set<std::string> visited;
    std::map<std::string, std::string> parent; // To track multiple parents
    parent[from] = " ";

    bool found = false;

    while (!q.empty() && !found) {
        auto curr = q.front();
        q.pop();

        if (curr == to) {
            // do smth
        }

        auto neighbours = generate_neighbours(curr, copy_lexicon);
        for (auto neighbour : neighbours) {
            if (!visited.contains(neighbour)) {
                q.push(neighbour);
                visited.insert(neighbour);
                parent[neighbour] = curr;
            }
        }
    }

    // include backtracking


    return results;
}