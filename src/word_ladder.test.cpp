#include "word_ladder.h"

#include <catch2/catch.hpp>
#include <unordered_set>
#include <cstddef>
#include <cstring>

TEST_CASE("read_lexicon works as expected") {
	char file_name[] = "/tmp/mytempfileXXXXXX";
	auto fileDescriptor = mkstemp(file_name);
	REQUIRE(fileDescriptor != -1);

	std::string words[] = {"Hello", "My", "Name", "Is", "Manan"};
	auto len = sizeof(words) / sizeof(words[0]);

	for (size_t i = 0; i < len; i++) {
		write(fileDescriptor, words[i].c_str(), words[i].length());
		write(fileDescriptor, "\n", 1);
	}

	close(fileDescriptor);

	auto const lexicon = word_ladder::read_lexicon(file_name);
	for (auto word : words) {
		CHECK(lexicon.contains(word));
	}

	remove(file_name);
}

TEST_CASE("at -> it") {
	auto const lexicon = std::unordered_set<std::string>{"at", "it"};

	const auto expected = std::vector<std::vector<std::string>>{{"at", "it"}};

	auto const ladders = word_ladder::generate("at", "it", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("fold -> mole") {
	auto const lexicon = std::unordered_set<std::string>{"fold", "mold", "told", "mole"};

	auto const expected = std::vector<std::vector<std::string>>{{"fold", "mold", "mole"}};
	auto const ladders = word_ladder::generate("fold", "mole", lexicon);

	CHECK(ladders == expected);
}

TEST_CASE("work -> play") {
	auto const lexicon = std::unordered_set<std::string>{"work", "fork", "form", "foam", "flam", "flay", "play", "pork",
	                                                     "perk", "peak", "pean", "plan", "worm", "peat", "plat", "porn",
	                                                     "pirn", "pert", "pian", "port", "word", "wood", "pood", "plod",
	                                                     "ploy", "wort", "bort", "boat", "blat", "wert", "worn"};

	auto const expected =
	    std::vector<std::vector<std::string>>{{"work", "fork", "form", "foam", "flam", "flay", "play"},
	                                          {"work", "pork", "perk", "peak", "pean", "plan", "play"},
	                                          {"work", "pork", "perk", "peak", "peat", "plat", "play"},
	                                          {"work", "pork", "perk", "pert", "peat", "plat", "play"},
	                                          {"work", "pork", "porn", "pirn", "pian", "plan", "play"},
	                                          {"work", "pork", "port", "pert", "peat", "plat", "play"},
	                                          {"work", "word", "wood", "pood", "plod", "ploy", "play"},
	                                          {"work", "worm", "form", "foam", "flam", "flay", "play"},
	                                          {"work", "worn", "porn", "pirn", "pian", "plan", "play"},
	                                          {"work", "wort", "bort", "boat", "blat", "plat", "play"},
	                                          {"work", "wort", "port", "pert", "peat", "plat", "play"},
	                                          {"work", "wort", "wert", "pert", "peat", "plat", "play"}};

	auto const ladder = word_ladder::generate("work", "play", lexicon);
	CHECK(ladder == expected);
}

TEST_CASE("cut -> try, no result and different word length") {
	auto const lexicon = std::unordered_set<std::string>{
	    "cut",
	    "try",
	    "told",
	};

	auto const expected = std::vector<std::vector<std::string>>{};

	auto const ladders = word_ladder::generate("cut", "try", lexicon);

	CHECK(ladders == expected);
}