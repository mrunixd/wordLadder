#include "word_ladder.h"

#include <catch2/catch.hpp>

TEST_CASE("read_lexicon works as expected") {
	CHECK(127142 == word_ladder::read_lexicon("./english.txt").size());
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
