#include "WordCounter.h"

bool WordCounter::compare_words(const Word &a, const Word &b) {
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.word < b.word;
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
        Word word;
        word.word = pair.first;
        word.count = pair.second;
        sorted_list.push_back(word);
    }
    sorted_list.sort(compare_words);
    return sorted_list;
}
