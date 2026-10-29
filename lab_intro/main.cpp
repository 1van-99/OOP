#include <iostream>
#include <string>
#include "CsvWriter.h"
#include "TextReader.h"
#include "WordCounter.h"

int main(int argc, char **argv) {
    std::string inputFileName;
    std::string outputFileName;

    if (argc < 3) {
        std::cout << "Input input file name: ";
        std::cin >> inputFileName;
        std::cout << "Input output file name: ";
        std::cin >> outputFileName;
    } else {
        inputFileName = argv[1];
        outputFileName = argv[2];
    }

    TextReader text(inputFileName);
    if (!text.isOpen()) {
        std::cout << "can't open input file\n";
        return 0;
    }
    std::string line;
    WordCounter counter;

    while (text.getLine(line)) {
        counter.processLine(line);
    }

    CsvWriter writer(outputFileName);
    if (!writer.isOpen()) {
        std::cout << "can't open output file\n";
        return 0;
    }
    writer.writeWordFreq(counter.buildSortedList(), counter.getTotal());

    return 0;
}
