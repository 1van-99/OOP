#pragma once

#include <list>
#include <map>
#include <string>
#include "Word.h"

class WordCounter {
    std::map<std::string, int> freq_;
    int total_words_ = 0;
public:
    void process_line(const std::string &line);
    std::list<Word> build_sorted_list() const;
    int get_total() const {
        return total_words_;
    }
};
