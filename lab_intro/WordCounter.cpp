#include "WordCounter.h"
#include <cctype>

namespace {
    bool is_word_char(unsigned char c) {
        return std::isalnum(c) != 0;
    }
}

void WordCounter::process_line(const std::string &line) {
    std::string current_word;
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (is_word_char(static_cast<unsigned char>(c))) {
            current_word.push_back(c);
        } else if (!current_word.empty()) {
            freq_[current_word]++;
            total_words_++;
            current_word.clear();
        }
    }
    if (!current_word.empty()) {
        freq_[current_word]++;
        total_words_++;
        current_word.clear();
    }
}

std::list<Word> WordCounter::build_sorted_list() const {
    std::list<Word> sorted_list;
    for (const auto &pair: freq_) {
        sorted_list.push_back(Word{pair.first, pair.second});
    }
    sorted_list.sort([](const Word &a, const Word &b) {
        if (a.count != b.count) {
            return (a.count > b.count);
        }
        return a.word < b.word;
    });
    return sorted_list;
}
