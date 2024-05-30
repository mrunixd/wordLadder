#include "word_ladder.h"
#include <unordered_set>

#include <fstream>
#include <iostream>
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
		return x.size() == size;
	});

	// any other improvements
}

auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	(void)from;
	(void)to;
	(void)lexicon;
	// remove this line once implemented

	std::unordered_set<std::string> copy_lexicon = lexicon;
	reduce_set(copy_lexicon, from);

	std::queue<std::string> q;
	std::unordered_set<std::string> visited;

	q.push(from);
	visited.insert(from);
	
	while (!q.empty()) {
		std::string curr = q.front();
		q.pop();
		std::cout << curr << " ";

		

	}

	return {};
}