#include "word_ladder.h"

#include <catch2/catch.hpp>

TEST_CASE("word_ladder::read_lexicon works as expected") {
	std::unordered_set<std::string> test_set = {"Hello", "My", "Name", "Is", "Manan"};
	CHECK(test_set == word_ladder::read_lexicon("/home/manan/COMP6771/ass1/src/test.txt"));
}

TEST_CASE("at -> it") {
	auto const lexicon = std::unordered_set<std::string>{
		"at",
		"it"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "it"}
	};

	auto const ladders = word_ladder::generate("at", "it", lexicon);

	CHECK(ladders == expected);
}
