#include "word_ladder.h"

#include <fstream>
#include <iostream>
#include <string>

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


auto word_ladder::generate(
	const std::string &from,
	const std::string &to,
	const std::unordered_set<std::string> &lexicon
) -> std::vector<std::vector<std::string>> {
	(void)from;
	(void)to;
	(void)lexicon;
	// remove this line once implemented

	return {};
}