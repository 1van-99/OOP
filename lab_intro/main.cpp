#include <iostream>
#include <string>
#include "CsvWriter.h"
#include "TextReader.h"
#include "WordCounter.h"

int main(int argc, char **argv) {
    std::string input_file_name;
    std::string output_file_name;

    if (argc < 3) {
        std::cout << "Input input file name: ";
        std::cin >> input_file_name;
        std::cout << "Input output file name: ";
        std::cin >> output_file_name;
    } else {
        input_file_name = argv[1];
        output_file_name = argv[2];
    }

    TextReader text(input_file_name);
    if (!text.is_open()) {
        std::cout << "can't open input file\n";
        return 0;
    }
    std::string line;
    WordCounter counter;

    while (text.get_line(line)) {
        counter.process_line(line);
    }

    CsvWriter writer(output_file_name);
    if (!writer.is_open()) {
        std::cout << "can't open output file\n";
        return 0;
    }
    writer.write_word_freq(counter.build_sorted_list(), counter.total());

    return 0;
}
