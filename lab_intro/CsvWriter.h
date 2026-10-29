#pragma once

#include <string>
#include <list>
#include <fstream>
#include "Word.h"

class CsvWriter {
    std::ofstream file_;
public:
    explicit CsvWriter(const std::string &name) : file_(name){};
    bool isOpen() const {
        return file_.is_open();
    }
    void writeWordFreq(const std::list<Word> &list, int totalWords);
};
