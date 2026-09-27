#ifndef LAB_INTRO_WORDCOUNTER_H
#define LAB_INTRO_WORDCOUNTER_H

#include <list>
#include <map>
#include <string>
#include <cctype>
#include "Word.h"

class WordCounter {
    std::map<std::string, int> freq_;
    int total_words_ = 0;
    static bool compare_words(const Word& a, const Word &b);
    static bool is_word_char(unsigned char c) {
        return std::isalnum(c) != 0;
    }
public:
    void process_line(const std::string &line);
    std::list<Word> build_sorted_list() const;
    int total() const {
        return total_words_;
    }
};

#endif //LAB_INTRO_WORDCOUNTER_H
