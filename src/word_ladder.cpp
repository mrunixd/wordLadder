#include "word_ladder.h"
#include <unordered_set>

#include <cstddef>
#include <fstream>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

auto word_ladder::read_lexicon(const std::string &path) -> std::unordered_set<std::string> {
	auto set = std::unordered_set<std::string>();
	auto file = std::ifstream(path);
	auto buffer = std::string();

	if (file.is_open()) {
		while (std::getline(file, buffer)) {
			set.insert(buffer);
		}
	}

	return set;
}

auto reduce_set(std::unordered_set<std::string> &lexicon, const std::string &from) {
	auto size = from.size();
	std::erase_if(lexicon, [size](auto& x) {
		return x.size() != size;
	});
}

std::vector<std::string> generate_neighbours(const std::string &word, const std::unordered_set<std::string> &lexicon) {
	auto neighbours = std::vector<std::string>();
	for (size_t i = 0; i < word.size(); i++) {
		auto temp = word;
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
        auto temp = path;
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

std::map<std::string, std::vector<std::string>> bfs(const std::string &from, const std::string &to, const std::unordered_set<std::string> copy_lexicon) {
    auto q = std::queue<std::string>();
    q.push(from);

    auto visited = std::unordered_set<std::string>();
    auto parent = std::map<std::string, std::vector<std::string>>();
    parent[from] = {};

    auto found = false;

    while (not q.empty() and !found) {
		auto level_size = q.size();
		auto level_visited = std::unordered_set<std::string>();

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

	if (not found) {
		return std::map<std::string, std::vector<std::string>>();
	}

	return parent;
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	std::vector<std::vector<std::string>> results;

    auto copy_lexicon = lexicon;
    reduce_set(copy_lexicon, from);

	auto parent = bfs(from, to, copy_lexicon);
	if (parent.size() != 0) {
		auto path = std::vector<std::string>();
		backtrack(to, from, parent, path, results);
	}

    return results;
}