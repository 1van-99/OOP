#pragma once
#include <map>
#include <memory>

struct Node {
    std::map<unsigned char, std::unique_ptr<Node>> children;
    std::size_t subtree_words_count = 0;
    bool is_end_of_word = false;

    void swap(Node& other) noexcept {
        std::swap(children, other.children);
        std::swap(subtree_words_count, other.subtree_words_count);
        std::swap(is_end_of_word, other.is_end_of_word);
    }

    Node() = default;

    Node(const Node& other) : subtree_words_count(other.subtree_words_count),
    is_end_of_word(other.is_end_of_word)
    {
        for (const auto& [c, child] : other.children) {
            children.emplace(c, std::make_unique<Node>(*child));
        }
    }

    Node(Node&& other) noexcept : children(std::move(other.children)), subtree_words_count(other.subtree_words_count),
    is_end_of_word(other.is_end_of_word){
        other.subtree_words_count = 0;
        other.is_end_of_word = false;
    }

    Node& operator= (const Node& other) {
        if (this != &other) {
            Node temp(other);
            swap(temp);
        }
        return *this;
    }

    Node& operator= (Node&& other) noexcept {
        if (this != &other) {
            children = std::move(other.children);
            subtree_words_count = other.subtree_words_count;
            is_end_of_word = other.is_end_of_word;

            other.subtree_words_count = 0;
            other.is_end_of_word = false;
        }
        return *this;
    }

    ~Node() = default;
};
