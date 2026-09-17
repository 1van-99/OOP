#include "words.h"

int main(int argc, char** argv)
{
    std::string input_file_name;
    std::string output_file_name;
    get_files(argc, argv, input_file_name, output_file_name);

    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name);

    if (!(input_file.is_open() && output_file.is_open())) {
        std::cout << OPEN_ERR << "\n";
        return EXIT_FAILURE;
    }

    std::string buffer;
    std::map<std::string, unsigned int> word_frequency;
    int total_words = 0;

    while (std::getline(input_file, buffer)) {
        process_line(buffer, word_frequency, total_words);
    }
    input_file.close();

    if (total_words == 0) {
        output_file.close();
        return EXIT_SUCCESS;
    }

    std::list<Word> sorted_words;
    build_sorted_list(word_frequency, sorted_words);

    write_csv(output_file, sorted_words, total_words);
    output_file.close();

    return 0;
}
