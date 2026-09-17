#include "words.h"

#define FIRST_ARG_INDEX 1
#define SECOND_ARG_INDEX 2
#define OPEN_ERR "can't open file"
#define FILE_LEGEND "Word;Frequency;Frequency (%)\n"
#define INSTR_IN "Input in file: "
#define INSTR_OUT "Input out file: "

struct Word {
    std::string word;
    unsigned int count;
};

bool compare_words(const Word &a, const Word &b) {
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.word < b.word;
}

bool is_word_char(unsigned char c) {
    return std::isalnum(c) != 0;
}

void get_files(int argc, char **argv,
               std::string &in_name, std::string &out_name) {
    if (argc < SECOND_ARG_INDEX + 1) {
        std::cout << INSTR_IN;
        std::cin >> in_name;
        std::cout << INSTR_OUT;
        std::cin >> out_name;
    } else {
        in_name = argv[FIRST_ARG_INDEX];
        out_name = argv[SECOND_ARG_INDEX];
    }
}

void process_line(const std::string &line,
                  std::map<std::string, unsigned int> &word_freq,
                  int &total_words) {
    std::string current_word;

    for (size_t i = 0; i < line.size(); i++) {
        unsigned char c = line[i];
        if (is_word_char(c)) {
            current_word.push_back(c);
        } else if (!current_word.empty()) {
            word_freq[current_word]++;
            total_words++;
            current_word.clear();
        }
    }
    if (!current_word.empty()) {
        word_freq[current_word]++;
        total_words++;
        current_word.clear();
    }
}

void build_sorted_list(const std::map<std::string, unsigned int> &word_freq,
                       std::list<Word> &out) {
    for (const auto &pair: word_freq) {
        Word word;
        word.word = pair.first;
        word.count = pair.second;
        out.push_back(word);
    }
    out.sort(compare_words);
}

void write_csv(std::ofstream &out,
               const std::list<Word> &sorted_words,
               int total_words) {
    out << FILE_LEGEND << "\n";
    for (const auto &word: sorted_words) {
        auto precent = static_cast<unsigned int>(
            static_cast<double>(word.count) / total_words * 100);
        out << word.word << ";"
                << word.count << ";"
                << precent << "\n";
    }
}
