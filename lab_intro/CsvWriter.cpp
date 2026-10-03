#include "CsvWriter.h"

namespace {
    const std::string CSV_HEADER = "Слово;Частота;Частота в %\n";
}

void CsvWriter::write_word_freq(const std::list<Word> &list, int total_words) {
    file_.write("\xEF\xBB\xBF", 3);
    file_ << CSV_HEADER;

    if (total_words == 0) {
        return;
    }

    for (const Word &word : list) {
        auto precent = static_cast<int>(
            static_cast<double>(word.count) / total_words * 100);
        file_ << word.word << ";"
              << word.count << ";"
              << precent << "\n";
    }
}
