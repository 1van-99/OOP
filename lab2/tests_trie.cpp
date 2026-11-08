#include <gtest/gtest.h>
#include "Trie.h"
#include <string>
#include <vector>

TEST(TrieLifeсycle, InitialState) {
    Trie trie;
    EXPECT_EQ(trie.size(), 0);
    EXPECT_TRUE(trie.empty());

    EXPECT_FALSE(trie.contains("smth"));
    EXPECT_FALSE(trie.contains(""));

    EXPECT_EQ(trie.prefixCount("smth"), 0);
    EXPECT_EQ(trie.prefixCount(""), 0);

    EXPECT_TRUE(trie.wordsWithPref("smth").empty());
    EXPECT_TRUE(trie.wordsWithPref("").empty());
}

TEST(TrieLifecycle, EraseOnEmptyTree) {
    Trie trie;

    EXPECT_FALSE(trie.erase("smth"));
    EXPECT_FALSE(trie.erase(""));

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieLifecycle, ClearEmptyTree) {
    Trie trie;
    trie.clear();

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains("smth"));
    EXPECT_FALSE(trie.contains(""));
}

TEST(TrieLifecycle, ClearPopulatedTree) {
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("cherry");

    EXPECT_EQ(trie.size(), 3);
    EXPECT_FALSE(trie.empty());
    EXPECT_TRUE(trie.contains("apple"));
    EXPECT_TRUE(trie.contains("banana"));
    EXPECT_TRUE(trie.contains("cherry"));

    trie.clear();

    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains("apple"));
    EXPECT_FALSE(trie.contains("banana"));
    EXPECT_FALSE(trie.contains("cherry"));
    EXPECT_FALSE(trie.contains(""));
    EXPECT_FALSE(trie.prefixCount(""));

    trie.insert("orange");
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("orange"));
}

TEST(TrieInsertSearch, SingleWord) {
    Trie trie;
    trie.insert("hello");

    EXPECT_TRUE(trie.contains("hello"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_FALSE(trie.empty());
}

TEST(TrieInsertSearch, InsertDuplicates) {
    Trie trie;
    trie.insert("apple");
    trie.insert("apple");
    trie.insert("apple");

    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("apple"));
}

TEST(TrieInsertSearch, SearchNonExistent) {
    Trie trie;
    trie.insert("hello");

    EXPECT_EQ(trie.size(), 1);
    EXPECT_FALSE(trie.contains("world"));
    EXPECT_FALSE(trie.contains("helloo"));
    std::string current("");
    for (const auto &sym: "hello") {
        if (sym != '\0') {
            EXPECT_FALSE(trie.contains(current));
            current.push_back(sym);
        }
    }
    EXPECT_TRUE(trie.contains(current));
}

TEST(TrieInsertSearch, CommonPrefixes) {
    Trie trie;
    trie.insert("car");
    trie.insert("cart");
    trie.insert("carpet");
    trie.insert("cat");

    EXPECT_EQ(trie.size(), 4);
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_TRUE(trie.contains("carpet"));
    EXPECT_TRUE(trie.contains("cat"));

    EXPECT_FALSE(trie.contains("ca"));
    EXPECT_FALSE(trie.contains("carp"));
}

TEST(TriePrefix, PrefixCount) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");

    EXPECT_EQ(trie.prefixCount("app"), 2);
    EXPECT_EQ(trie.prefixCount("ap"), 3);
    EXPECT_EQ(trie.prefixCount("a"), 3);
    EXPECT_EQ(trie.prefixCount("b"), 1);
    EXPECT_EQ(trie.prefixCount(""), 4);
    EXPECT_EQ(trie.prefixCount("bap"), 0);
    EXPECT_EQ(trie.prefixCount("Ap"), 0);
    EXPECT_EQ(trie.prefixCount("A"), 0);
}

TEST(TriePrefix, WordsWithPrefixOrder) {
    Trie trie;
    trie.insert("banana");
    trie.insert("apple");
    trie.insert("cap");
    trie.insert("app");
    trie.insert("apricot");

    std::vector<std::string> res = trie.wordsWithPref("ap");

    ASSERT_EQ(res.size(), 3);
    EXPECT_EQ(res[0], "app");
    EXPECT_EQ(res[1], "apple");
    EXPECT_EQ(res[2], "apricot");

    std::vector<std::string> all = trie.wordsWithPref("");
    ASSERT_EQ(all.size(), 5);
    EXPECT_EQ(all.size(), trie.size());
    EXPECT_EQ(all[0], "app");
    EXPECT_EQ(all[1], "apple");
    EXPECT_EQ(all[2], "apricot");
    EXPECT_EQ(all[3], "banana");
    EXPECT_EQ(all[4], "cap");
}

TEST(TriePrefix, WordsWithPrefixLimit) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");

    std::vector<std::string> res = trie.wordsWithPref("ap", 2);
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "app");
    EXPECT_EQ(res[1], "apple");

    std::vector<std::string> resMore = trie.wordsWithPref("ap", 10);
    EXPECT_EQ(resMore.size(), 3);

    std::vector<std::string> resZero = trie.wordsWithPref("ap", 0);
    EXPECT_EQ(resZero.size(), 3);
}

TEST(TriePrefix, WordsWithPrefixNonExistent) {
    Trie trie;
    trie.insert("apple");

    EXPECT_TRUE(trie.wordsWithPref("b").empty());
    EXPECT_TRUE(trie.wordsWithPref("apples").empty());
    EXPECT_TRUE(trie.wordsWithPref("cap").empty());
}

TEST(TrieErase, BasicErase) {
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("365!");

    EXPECT_TRUE(trie.erase("hello"));
    EXPECT_EQ(trie.size(), 2);
    EXPECT_FALSE(trie.contains("hello"));
    EXPECT_TRUE(trie.contains("world"));
    EXPECT_TRUE(trie.contains("365!"));

    EXPECT_TRUE(trie.erase("365!"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_FALSE(trie.contains("hello"));
    EXPECT_TRUE(trie.contains("world"));
    EXPECT_FALSE(trie.contains("365!"));

    EXPECT_TRUE(trie.erase("world"));
    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieErase, EraseNonExisting) {
    Trie trie;
    trie.insert("hello");

    EXPECT_FALSE(trie.erase("world"));
    EXPECT_FALSE(trie.erase("hell"));

    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("hello"));
}

TEST(TrieErase, EraseWordThatIsPrefix) {
    Trie trie;
    trie.insert("car");
    trie.insert("cart");
    trie.insert("cartoon");

    EXPECT_TRUE(trie.erase("car"));
    EXPECT_FALSE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_TRUE(trie.contains("cartoon"));
    EXPECT_EQ(trie.size(), 2);
    EXPECT_TRUE(trie.erase("cart"));
    EXPECT_FALSE(trie.contains("cart"));
    EXPECT_TRUE(trie.contains("cartoon"));
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.erase("cartoon"));
    EXPECT_TRUE(trie.empty());
    EXPECT_EQ(trie.size(), 0);
}

TEST(TrieErase, EraseWordWithPrefix) {
    Trie trie;
    trie.insert("car");
    trie.insert("cart");
    trie.insert("cartoon");

    EXPECT_TRUE(trie.erase("cartoon"));
    EXPECT_FALSE(trie.contains("cartoon"));
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_TRUE(trie.contains("cart"));
    EXPECT_EQ(trie.size(), 2);

    EXPECT_TRUE(trie.erase("cart"));
    EXPECT_FALSE(trie.contains("cart"));
    EXPECT_TRUE(trie.contains("car"));
    EXPECT_EQ(trie.size(), 1);

    EXPECT_TRUE(trie.erase("car"));
    EXPECT_FALSE(trie.contains("car"));
    EXPECT_EQ(trie.size(), 0);
    EXPECT_TRUE(trie.empty());
}

TEST(TrieErase, EraseAllAndReinsert) {
    Trie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("cherry");

    EXPECT_TRUE(trie.erase("apple"));
    EXPECT_TRUE(trie.erase("banana"));
    EXPECT_TRUE(trie.erase("cherry"));

    // Дерево должно быть полностью пустым
    EXPECT_EQ(trie.size(), 0);
    EXPECT_TRUE(trie.empty());
    EXPECT_TRUE(trie.wordsWithPref("").empty());

    // Проверяем, что после полного удаления дерево готово к работе
    trie.insert("apple");
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains("apple"));
}

TEST(TrieErase, PrefixCountAfterErase) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");

    EXPECT_EQ(trie.prefixCount("ap"), 3);
    EXPECT_EQ(trie.prefixCount("app"), 2);
    trie.erase("apple");
    EXPECT_EQ(trie.prefixCount("ap"), 2);
    EXPECT_EQ(trie.prefixCount("app"), 1);
}

TEST(TrieBoundaryCases, EmptyStringBehavior) {
    Trie trie;

    EXPECT_THROW(trie.insert(""), std::invalid_argument);
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains(""));
    EXPECT_FALSE(trie.erase(""));
    EXPECT_EQ(trie.prefixCount(""), 0);
    EXPECT_TRUE(trie.wordsWithPref("").empty());
}

TEST(TrieBoundaryCases, InvalidUtf8Behavior) {
    Trie trie;
    std::string invalidUtf8 = "\xC3\x28";

    EXPECT_THROW(trie.insert(invalidUtf8), std::invalid_argument);
    EXPECT_EQ(trie.size(), 0);
    EXPECT_FALSE(trie.contains(invalidUtf8));
    EXPECT_FALSE(trie.erase(invalidUtf8));
    EXPECT_EQ(trie.prefixCount(invalidUtf8), 0);
    EXPECT_TRUE(trie.wordsWithPref(invalidUtf8).empty());
}

TEST(TrieBoundaryCases, SingleCharacterStrings) {
    Trie trie;
    trie.insert("a");
    trie.insert("b");

    EXPECT_EQ(trie.size(), 2);
    EXPECT_TRUE(trie.contains("a"));
    EXPECT_TRUE(trie.contains("b"));
    EXPECT_EQ(trie.prefixCount("a"), 1);

    trie.erase("a");
    EXPECT_FALSE(trie.contains("a"));
    EXPECT_TRUE(trie.contains("b"));
}

TEST(TrieBoundaryCases, ValidUtf8) {
    Trie trie;
    trie.insert("Привет");
    trie.insert("Пока");
    trie.insert("Пиво");
    trie.insert("Пролог");
    trie.insert("Привет");

    EXPECT_EQ(trie.size(), 4);
    EXPECT_TRUE(trie.contains("Привет"));
    EXPECT_TRUE(trie.contains("Пока"));
    EXPECT_FALSE(trie.contains("Прив"));

    EXPECT_EQ(trie.prefixCount("П"), 4);
    EXPECT_EQ(trie.prefixCount("Пр"), 2);
    EXPECT_EQ(trie.prefixCount("При"), 1);

    std::vector<std::string> res = trie.wordsWithPref("П");
    ASSERT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], "Пиво");
    EXPECT_EQ(res[1], "Пока");
    EXPECT_EQ(res[2], "Привет");
    EXPECT_EQ(res[3], "Пролог");
}

TEST(TrieBoundaryCases, VeryLongString) {
    Trie trie;
    std::string longString(10000, 'a');

    trie.insert(longString);
    EXPECT_EQ(trie.size(), 1);
    EXPECT_TRUE(trie.contains(longString));
    EXPECT_TRUE(trie.erase(longString));
    EXPECT_EQ(trie.size(), 0);
    EXPECT_TRUE(trie.empty());
}

TEST(TrieSemantics, CopyConstructorDeepCopy) {
    Trie original;
    original.insert("apple");
    original.insert("app");
    original.insert("banana");

    Trie copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_TRUE(copy.contains("apple"));
    EXPECT_TRUE(copy.contains("app"));
    EXPECT_TRUE(copy.contains("banana"));

    copy.insert("cherry");
    copy.erase("apple");

    EXPECT_EQ(original.size(), 3);
    EXPECT_TRUE(original.contains("apple"));
    EXPECT_FALSE(original.contains("cherry"));

    EXPECT_EQ(copy.size(), 3);
    EXPECT_FALSE(copy.contains("apple"));
    EXPECT_TRUE(copy.contains("cherry"));
}

TEST(TrieSemantics, CopyAssignmentDeepCopy) {
    Trie a;
    a.insert("apple");
    a.insert("app");

    Trie b;
    b.insert("banana");
    b.insert("cherry");

    b = a;

    EXPECT_EQ(b.size(), 2);
    EXPECT_TRUE(b.contains("apple"));
    EXPECT_TRUE(b.contains("app"));
    EXPECT_FALSE(b.contains("banana"));
    EXPECT_FALSE(b.contains("cherry"));

    b.insert("orange");
    EXPECT_EQ(a.size(), 2);
    EXPECT_FALSE(a.contains("orange"));
}

TEST(TrieSemantics, MoveConstructor) {
    Trie original;
    original.insert("apple");
    original.insert("app");
    original.insert("banana");

    Trie moved = std::move(original);

    EXPECT_EQ(moved.size(), 3);
    EXPECT_TRUE(moved.contains("apple"));
    EXPECT_TRUE(moved.contains("app"));
    EXPECT_TRUE(moved.contains("banana"));

    EXPECT_TRUE(original.empty());
    EXPECT_EQ(original.size(), 0);
    EXPECT_FALSE(original.contains("apple"));
    EXPECT_FALSE(original.contains("app"));
    EXPECT_FALSE(original.contains("banana"));

    std::vector<std::string> words = original.wordsWithPref("");
    EXPECT_TRUE(words.empty());
    EXPECT_EQ(original.prefixCount("a"), 0);
    EXPECT_EQ(original.prefixCount(""), 0);

    original.insert("orange");
    EXPECT_EQ(original.size(), 1);
    EXPECT_EQ(moved.size(), 3);
    EXPECT_TRUE(original.contains("orange"));
    EXPECT_FALSE(moved.contains("orange"));
}

TEST(TrieSemantics, MoveAssignment) {
    Trie a;
    a.insert("apple");
    a.insert("app");
    a.insert("apricot");

    Trie b;
    b.insert("banana");

    b = std::move(a);

    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(b.contains("apple"));
    EXPECT_TRUE(b.contains("app"));
    EXPECT_TRUE(b.contains("apricot"));
    EXPECT_FALSE(b.contains("banana"));

    std::vector<std::string> bWords = b.wordsWithPref("");
    EXPECT_EQ(bWords.size(), 3);

    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.size(), 0);
    EXPECT_FALSE(a.contains("apple"));
    EXPECT_FALSE(a.contains("banana"));
    EXPECT_EQ(a.prefixCount("a"), 0);
    std::vector<std::string> aWords = a.wordsWithPref("");
    EXPECT_EQ(aWords.size(), 0);

    a.insert("kiwi");
    EXPECT_EQ(a.size(), 1);
    EXPECT_TRUE(a.contains("kiwi"));
    EXPECT_FALSE(b.contains("kiwi"));
}

TEST(TrieSemantics, SelfAssignment) {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    Trie& ref = trie;
    trie = ref;

    EXPECT_EQ(trie.size(), 3);
    EXPECT_TRUE(trie.contains("apple"));
    EXPECT_TRUE(trie.contains("app"));
    EXPECT_TRUE(trie.contains("banana"));

    trie = std::move(trie);
    EXPECT_EQ(trie.size(), 3);
    EXPECT_TRUE(trie.contains("apple"));
    EXPECT_TRUE(trie.contains("app"));
    EXPECT_TRUE(trie.contains("banana"));
}

TEST(TrieOperators, EqualityEmptyAndBasic) {
    Trie empty1;
    Trie empty2;
    Trie non_empty;
    non_empty.insert("apple");

    EXPECT_TRUE(empty1 == empty2);
    EXPECT_FALSE(empty1 != empty2);

    EXPECT_FALSE(empty1 == non_empty);
    EXPECT_TRUE(empty1 != non_empty);
}

TEST(TrieOperators, EqualitySameWordsDifferentInsertionOrder) {
    Trie a;
    a.insert("banana");
    a.insert("apple");
    a.insert("cherry");

    Trie b;
    b.insert("cherry");
    b.insert("banana");
    b.insert("apple");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TrieOperators, EqualitySharedPrefixes) {
    Trie a;
    a.insert("car");
    a.insert("cart");
    a.insert("cat");

    Trie b;
    b.insert("cat");
    b.insert("cart");
    b.insert("car");

    EXPECT_TRUE(a == b);

    Trie c;
    c.insert("cap");
    c.insert("car");
    c.insert("cat");

    EXPECT_FALSE(a == c);
    EXPECT_TRUE(c != b);

    Trie d;
    d.insert("car");
    d.insert("cart");
    d.insert("cat");
    d.insert("caterpillar");

    EXPECT_FALSE(a == d);
}

TEST(TrieOperators, OutputEmpty) {
    Trie trie;
    std::stringstream ss;
    ss << trie;
    EXPECT_EQ(ss.str(), "");
}

TEST(TrieOperators, OutputAlphabeticalOrder) {
    Trie trie;
    trie.insert("банан");
    trie.insert("яблоко");
    trie.insert("вишня");
    trie.insert("абрикос");
    trie.insert("арбуз");

    std::stringstream ss;
    ss << trie;

    EXPECT_EQ(ss.str(), "абрикос\nарбуз\nбанан\nвишня\nяблоко\n");
}

TEST(TrieOperators, OutputChaining) {
    Trie trie1;
    trie1.insert("first");

    Trie trie2;
    trie2.insert("second");

    std::stringstream ss;
    ss << trie1 << trie2;

    EXPECT_EQ(ss.str(), "first\nsecond\n");
}
