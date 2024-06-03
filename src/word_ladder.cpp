#include "word_ladder.h"
#include <unordered_set>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

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

void backtrack(const std::string &node, const std::string &start,
               const std::map<std::string, std::vector<std::string>> &parent,
               std::vector<std::string> &path, std::vector<std::vector<std::string>> &results) {
    if (node == start) {
        std::vector<std::string> temp = path;
        temp.push_back(start);
        std::reverse(temp.begin(), temp.end());
        results.push_back(temp);
        return;
    }
    path.push_back(node);
    for (const auto &p : parent.at(node)) {
        backtrack(p, start, parent, path, results);
    }
    path.pop_back();
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
    std::map<std::string, std::vector<std::string>> parent; // To track multiple parents
    parent[from] = {};

    bool found = false;

    while (!q.empty() && !found) {
		auto level_size = q.size();
		std::unordered_set<std::string> level_visited;

		for (size_t i = 0; i < level_size; i++) {
        	auto curr = q.front();
        	q.pop();

			if (curr == to) {
				found = true;
			}

	        auto neighbours = generate_neighbours(curr, copy_lexicon);
			for (auto neighbour : neighbours) {
				if (!visited.contains(neighbour)) {
                    if (!level_visited.contains(neighbour)) {
                        q.push(neighbour);
                        level_visited.insert(neighbour);
                        parent[neighbour] = {curr};
                    } else {
                        parent[neighbour].push_back(curr);
                    }
                }
			}
		}
		visited.insert(level_visited.begin(), level_visited.end());
    }

	if (found) {
		std::vector<std::string> path;
		backtrack(to, from, parent, path, results);
	}

    return results;
}