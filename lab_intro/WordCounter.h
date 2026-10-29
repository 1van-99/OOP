#pragma once

#include <list>
#include <map>
#include <string>
#include "Word.h"

class WordCounter {
    std::map<std::string, int> freq_;
    int total_words_ = 0;

public:
    void processLine(const std::string &line);

    //[[nodiscard]] - компилятор выдаст ошибку если вызвать без использования результата.
    [[nodiscard]] std::list<Word> buildSortedList() const;


    [[nodiscard]] int getTotal() const {
        return total_words_;
    }
};
