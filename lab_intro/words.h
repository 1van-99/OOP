#ifndef LAB_INTRO_WORDS_H
#define LAB_INTRO_WORDS_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <cctype> //std::isalnum
#include <cstdlib> //EXIT_SUCCESS

#define OPEN_ERR "can't open file"

struct Word;

void get_files(int argc, char **argv,
               std::string &in_name, std::string &out_name);

void process_line(const std::string &line,
                  std::map<std::string, unsigned int> &word_freq,
                  int &total_words);

void build_sorted_list(const std::map<std::string, unsigned int> &word_freq,
                       std::list<Word> &out);

void write_csv(std::ofstream &out,
               const std::list<Word> &sorted_words,
               int total_words);

#endif //LAB_INTRO_WORDS_H
