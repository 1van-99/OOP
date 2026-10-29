#include "CsvWriter.h"

namespace {
    const std::string CSV_HEADER = "Слово;Частота;Частота в %\n";
}

void CsvWriter::writeWordFreq(const std::list<Word> &list, int totalWords) {
    file_.write("\xEF\xBB\xBF", 3);
    file_ << CSV_HEADER;

    if (totalWords == 0) {
        return;
    }

    for (const Word &word : list) {
        auto precent = static_cast<int>(
            static_cast<double>(word.count) / totalWords * 100);
        file_ << word.word << ";"
              << word.count << ";"
              << precent << "\n";
    }
}
