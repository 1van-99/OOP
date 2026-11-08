#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <ostream>
#include "Node.h"

class Trie {
private:
    Node root_;

    static bool insertImpl(Node& node, std::string_view str, std::size_t depth);
    static bool eraseImpl(Node& node, std::string_view str, std::size_t depth);
    static void collectWordsInSubtree(const Node& node, std::string& currentStr,
        std::vector<std::string>& words, std::size_t limit);
    static bool nodesEqual(const Node& a, const Node& b);

public:
    using size_type = std::size_t;
    Trie() = default;
    Trie(const Trie& other) = default;
    Trie(Trie&& other) noexcept = default;
    Trie& operator= (const Trie& other) = default;
    Trie& operator= (Trie&& other) noexcept = default;
    ~Trie() = default;

    // ---Базовые методы---
    void insert(std::string_view str);
    bool contains(std::string_view str) const;
    bool erase(std::string_view str);
    size_type prefixCount(std::string_view pref) const;
    std::vector<std::string> wordsWithPref(std::string_view pref, size_type limit = 0) const;

    // ---Служебные методы---
    void clear();
    bool empty() const noexcept;
    size_type size() const noexcept;

    // ---Перегрузка операторов---
    bool operator== (const Trie& other) const; //По множеству строк
    bool operator!= (const Trie& other) const;

    friend std::ostream& operator<< (std::ostream& os, const Trie& trie); //Вывод всех слов в алфавитном порядке
};
