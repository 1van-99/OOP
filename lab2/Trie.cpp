#include "Trie.h"
#include "core.h" // Для UTF-8
#include <stdexcept>
#include <ostream>

bool Trie::insertImpl(Node &node, std::string_view str, size_type depth) {
    if (depth == str.size()) {
        if (node.is_end_of_word) {
            return false;
        }
        node.is_end_of_word = true;
        node.subtree_words_count += 1;
        return true;
    }

    auto currentSymbol = static_cast<unsigned char>(str[depth]);
    auto nextEdge = node.children.find(currentSymbol);

    if (nextEdge == node.children.end()) {
        auto newNode = std::make_unique<Node>();
        // возвращает std::pair<iterator, bool>
        auto insertResult = node.children.emplace(currentSymbol, std::move(newNode));
        // Берем только iterator
        nextEdge = insertResult.first;
    }

    const bool ADDED = insertImpl(*(nextEdge->second), str, depth + 1);
    if (ADDED) {
        node.subtree_words_count += 1;
    }
    return ADDED;
}

bool Trie::eraseImpl(Node &node, std::string_view str, size_type depth) {
    if (depth == str.size()) {
        if (node.is_end_of_word) {
            node.is_end_of_word = false;
            node.subtree_words_count -= 1;
            return true;
        }
        return false;
    }

    auto currentSymbol = static_cast<unsigned char>(str[depth]);
    auto nextEdge = node.children.find(currentSymbol);
    if (nextEdge == node.children.end()) {
        return false;
    }

    const bool REMOVED = eraseImpl(*(nextEdge->second), str, depth + 1);
    if (REMOVED) {
        node.subtree_words_count -= 1;
        if (!nextEdge->second->is_end_of_word && nextEdge->second->children.empty()) {
            node.children.erase(nextEdge);
        }
    }
    return REMOVED;
}

void Trie::collectWordsInSubtree(const Node &node, std::string &currentStr,
                                 std::vector<std::string> &words, size_type limit) {
    if (limit > 0 && words.size() >= limit) {
        return;
    }

    if (node.is_end_of_word) {
        words.push_back(currentStr);
        if (limit > 0 && words.size() >= limit) {
            return;
        }
    }

    for (const auto &[c, child]: node.children) {
        currentStr.push_back(static_cast<char>(c));
        collectWordsInSubtree(*child, currentStr, words, limit);
        currentStr.pop_back();
        if (limit > 0 && words.size() >= limit) {
            return;
        }
    }
}

bool Trie::nodesEqual(const Node &a, const Node &b) {
    if (a.is_end_of_word != b.is_end_of_word) {
        return false;
    }

    if (a.subtree_words_count != b.subtree_words_count) {
        return false;
    }

    if (a.children.size() != b.children.size()) {
        return false;
    }

    auto nextEdgeA = a.children.begin();
    auto nextEdgeB = b.children.begin();
    while (nextEdgeA != a.children.end()) {
        if (nextEdgeA->first != nextEdgeB->first) {
            return false;
        }
        if (!nodesEqual(*(nextEdgeA->second), *(nextEdgeB->second))) {
            return false;
        }
        ++nextEdgeA;
        ++nextEdgeB;
    }
    return true;
}

void Trie::insert(std::string_view str) {
    if (str.empty()) {
        throw std::invalid_argument("Empty string cannot be a key");
    }
    if (!utf8::is_valid(str.begin(), str.end())) {
        throw std::invalid_argument("String is not valid UTF-8");
    }

    insertImpl(root_, str, 0);
}

bool Trie::contains(std::string_view str) const {
    if (!utf8::is_valid(str.begin(), str.end())) {
        return false;
    }

    const Node *current = &root_;
    for (size_type i = 0; i < str.size(); ++i) {
        auto currentSymbol = static_cast<unsigned char>(str[i]);
        auto nextEdge = current->children.find(currentSymbol);
        if (nextEdge == current->children.end()) {
            return false;
        }
        current = nextEdge->second.get();
    }
    return current->is_end_of_word;
}

bool Trie::erase(std::string_view str) {
    if (!utf8::is_valid(str.begin(), str.end())) {
        return false;
    }

    return eraseImpl(root_, str, 0);
}

Trie::size_type Trie::prefixCount(std::string_view pref) const {
    if (!utf8::is_valid(pref.begin(), pref.end())) {
        return 0;
    }

    const Node *current = &root_;
    for (size_type i = 0; i < pref.size(); ++i) {
        auto currentSymbol = static_cast<unsigned char>(pref[i]);
        auto nextEdge = current->children.find(currentSymbol);
        if (nextEdge == current->children.end()) {
            return 0;
        }
        current = nextEdge->second.get();
    }
    return current->subtree_words_count;
}

std::vector<std::string> Trie::wordsWithPref(std::string_view pref, size_type limit) const {
    if (!utf8::is_valid(pref.begin(), pref.end())) {
        return {};
    }

    const Node *current = &root_;
    for (size_type i = 0; i < pref.size(); ++i) {
        auto currentSymbol = static_cast<unsigned char>(pref[i]);
        auto nextEdge = current->children.find(currentSymbol);
        if (nextEdge == current->children.end()) {
            return {}; // Нет такого префикса
        }
        current = nextEdge->second.get();
    }

    std::vector<std::string> words;
    std::string currentStr(pref);
    collectWordsInSubtree((*current), currentStr, words, limit);
    return words;
}

void Trie::clear() {
    root_ = Node();
}

bool Trie::empty() const noexcept{
    return root_.subtree_words_count == 0;
}

Trie::size_type Trie::size() const noexcept {
    return root_.subtree_words_count;
}

bool Trie::operator==(const Trie &other) const {
    if (this->size() != other.size()) {
        return false;
    }

    return nodesEqual(root_, other.root_);
}

bool Trie::operator!=(const Trie &other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream &os, const Trie &trie) {
    std::vector<std::string> allWords = trie.wordsWithPref("");
    for (const auto &word: allWords) {
        os << word << "\n";
    }
    return os;
}
