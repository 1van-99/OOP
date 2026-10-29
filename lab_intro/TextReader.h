#pragma once

#include <string>
#include <fstream>

class TextReader {
    std::ifstream file_;
public:
    explicit TextReader(const std::string &name) : file_(name){}
    bool isOpen() const {
        return file_.is_open();
    }
    bool getLine(std::string &line) {
        return static_cast<bool>(std::getline(file_, line));
    }
};
