#include "word_ladder.h"

#include <catch2/catch.hpp>
#include <unordered_set>
#include <cerrno>

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

TEST_CASE("fold -> mole") {
	auto const lexicon = std::unordered_set<std::string>{
		"fold",
		"mold",
		"told",
		"mole"
	};

	auto const expected = std::vector<std::vector<std::string>>{
		{"fold", "mold", "mole"}
	};
	auto const ladders = word_ladder::generate("fold", "mole", lexicon);

	CHECK(ladders == expected);
}