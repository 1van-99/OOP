#include "WordCounter.h"
#include <cctype>

namespace {
    bool isWordChar(unsigned char c) {
        return std::isalnum(c) != 0;
    }
}

void WordCounter::processLine(const std::string &line) {
    std::string currentWord;
    for (const char C: line) {
        if (isWordChar(static_cast<unsigned char>(C))) {
            currentWord.push_back(C);
        } else if (!currentWord.empty()) {
            freq_[currentWord]++;
            total_words_++;
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        freq_[currentWord]++;
        total_words_++;
        currentWord.clear();
    }
}

std::list<Word> WordCounter::buildSortedList() const {
    std::list<Word> sortedList;
    for (const auto &pair: freq_) {
        sortedList.push_back(Word{.word = pair.first, .count = pair.second});
    }
    sortedList.sort([](const Word &a, const Word &b) {
        if (a.count != b.count) {
            return (a.count > b.count);
        }
        return a.word < b.word;
    });
    return sortedList;
}
