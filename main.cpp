#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>

#define FIRST_ARG_INDEX 1
#define SECOND_ARG_INDEX 2
#define OPEN_ERR "can't open file"
#define FILE_LEGEND "Word;Freaquency;Freacuency (%)\n"

struct Word {
    std::string word;
    unsigned int count;
};

bool compare_words(const Word& a, const Word& b)
{
    if (a.count != b.count) {
        return a.count > b.count;
    }
    return a.word < b.word;
}

int main(int argc, char** argv)
{
    std::string input_file_name;
    std::string output_file_name;

    if (argc < SECOND_ARG_INDEX + 1) {
        std::cin >> input_file_name;
        std::cin >> output_file_name;
    } else {
        input_file_name = argv[FIRST_ARG_INDEX];
        output_file_name = argv[SECOND_ARG_INDEX];
    }

    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name);

    if (!(input_file.is_open() && output_file.is_open())) {
        std::cout << OPEN_ERR << std::endl;
        return EXIT_FAILURE;
    }

    std::string buffer;
    std::map<std::string, unsigned int> word_frequency;
    std::string current_word;
    int total_words = 0;

    while (std::getline(input_file, buffer)) {
        for (size_t i = 0; i < buffer.size(); i++) {
            unsigned char c = buffer[i];
            if (std::isalnum(c)) {
                current_word.push_back(c);
            } else if (!current_word.empty()) {
                word_frequency[current_word]++;
                total_words++;
                current_word.clear();
            }
        }
        if (!current_word.empty()) {
            word_frequency[current_word]++;
            total_words++;
            current_word.clear();
        }
    }
    input_file.close();

    if (total_words == 0) {
        output_file.close();
        return EXIT_SUCCESS;
    }

    std::list<Word> sorted_words;
    for (const auto& pair : word_frequency) {
        Word word;
        word.word = pair.first;
        word.count = pair.second;
        sorted_words.push_back(word);
    }

    sorted_words.sort(compare_words);

    output_file << FILE_LEGEND << std::endl;
    for (const auto& word : sorted_words) {
        unsigned int precent = (((double)word.count / total_words) * 100);
        output_file << word.word << ";"
                    << word.count << ";"
                    << precent << "\n";
    }

    return 0;
}
