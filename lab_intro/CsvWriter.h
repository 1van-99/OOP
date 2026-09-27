#ifndef LAB_INTRO_CSVWRITER_H
#define LAB_INTRO_CSVWRITER_H

#include <string>
#include <list>
#include <fstream>
#include "Word.h"

class CsvWriter {
    std::ofstream file_;
public:
    explicit CsvWriter(const std::string &name) : file_(name){};
    bool is_open() const {
        return file_.is_open();
    }
    void write_word_freq(const std::list<Word> &list, int total_words);
};

#endif //LAB_INTRO_CSVWRITER_H
