#pragma once

#include <string>
#include <fstream>

class TextReader {
    std::ifstream file_;
public:
    explicit TextReader(const std::string &name) : file_(name){}
    bool is_open() const {
        return file_.is_open();
    }
    bool get_line(std::string &line) {
        return static_cast<bool>(std::getline(file_, line));
    }
};
