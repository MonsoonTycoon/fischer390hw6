#include "ArrayDictionary.h"
#include "gtest/gtest.h"

#define PRINT

TEST(dict, array_dict_basic) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_TRUE(hashTable.isEmpty());

    ASSERT_TRUE(hashTable.add(1, 2));
    ASSERT_EQ(hashTable.size(), 1);
    ASSERT_FALSE(hashTable.isEmpty());

    ASSERT_TRUE(hashTable.add(8, 4));
    ASSERT_EQ(hashTable.size(), 2);

    ASSERT_TRUE(hashTable.add(11, 4));
    ASSERT_EQ(hashTable.size(), 2);
#ifdef PRINT
    hashTable.print();
#endif
}

TEST(dict, array_dict_add_overwrite) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_TRUE(hashTable.add(2, 2));
    ASSERT_TRUE(hashTable.add(2, 4));
#ifdef PRINT
    hashTable.print();
#endif

    ASSERT_EQ(hashTable.size(), 1);
}

TEST(dict, array_dict_value_set_size) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_TRUE(hashTable.add(2, 9));
    ASSERT_TRUE(hashTable.add(3, 4));
    ASSERT_TRUE(hashTable.add(12, 8));
#ifdef PRINT
    hashTable.print();
#endif

    ASSERT_EQ(hashTable.valueSetSize(5), 0);
    ASSERT_EQ(hashTable.valueSetSize(2), 2);
    ASSERT_EQ(hashTable.valueSetSize(3), 1);
}

TEST(dict, array_dict_add_get) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_TRUE(hashTable.add(2, 9));
    ASSERT_TRUE(hashTable.add(3, 4));
    ASSERT_TRUE(hashTable.add(12, 8));
#ifdef PRINT
    hashTable.print();
#endif

    int val = 0;
    ASSERT_TRUE(hashTable.get(2, val));
    ASSERT_EQ(val, 9);
    ASSERT_TRUE(hashTable.get(12, val));
    ASSERT_EQ(val, 8);
    ASSERT_TRUE(hashTable.get(3, val));
    ASSERT_EQ(val, 4);
    ASSERT_FALSE(hashTable.get(7, val));
    ASSERT_EQ(val, 4);
}

TEST(dict, containsSet1) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_FALSE(hashTable.contain(-1));
    ASSERT_FALSE(hashTable.contain(0));
    ASSERT_FALSE(hashTable.contain(1));
}

TEST(dict, containsSet2) {
    ArrayDictionary<int, int> hashTable (1);

    hashTable.add(0, 103);
    ASSERT_FALSE(hashTable.contain(2));
    ASSERT_TRUE(hashTable.contain(0));
}

TEST(dict, containsSet3) {
    ArrayDictionary<int, int> hashTable (2);

    hashTable.add(0, 103);
    hashTable.add(1, 105);
    ASSERT_TRUE(hashTable.contain(0));
    ASSERT_TRUE(hashTable.contain(1));
    ASSERT_FALSE(hashTable.contain(2));
    ASSERT_FALSE(hashTable.contain(3));
}

TEST(dict, containsSet4) {
    ArrayDictionary<int, int> hashTable (3);

    hashTable.add(0, 103);
    hashTable.add(1, 105);
    ASSERT_FALSE(hashTable.contain(3));
    hashTable.add(2, 206);
    ASSERT_TRUE(hashTable.contain(1));
}

TEST(dict, containsSet5) {
    ArrayDictionary<int, int> hashTable (3);

    hashTable.add(0, 103);
    hashTable.add(1, 105);
    hashTable.add(2, 206);
    hashTable.add(4, 407);
    ASSERT_TRUE(hashTable.contain(1));
    ASSERT_TRUE(hashTable.contain(4));
    ASSERT_FALSE(hashTable.contain(7));
    ASSERT_FALSE(hashTable.contain(8));
}

TEST(dict, removeEmpty) {
    ArrayDictionary<int, int> hashTable;

    ASSERT_FALSE(hashTable.remove(-1));
    ASSERT_FALSE(hashTable.remove(0));
    ASSERT_FALSE(hashTable.remove(1));
}

TEST(dict, removeSingleElement1Cap) {
    ArrayDictionary<int, int> hashTable (1);

    hashTable.add(0, 9);
    ASSERT_FALSE(hashTable.remove(3));
    ASSERT_TRUE(hashTable.remove(0));
}

TEST(dict, removeSingleElement5Cap) {
    ArrayDictionary<int, int> hashTable (5);

    hashTable.add(3, 9);
    ASSERT_FALSE(hashTable.remove(14));
    ASSERT_TRUE(hashTable.remove(3));
}

TEST(dict, removeSingleElement1CapCollision) {
    ArrayDictionary<int, int> hashTable (1);

    hashTable.add(1, 9);
    hashTable.add(0, 9);
    ASSERT_FALSE(hashTable.remove(3));
    ASSERT_TRUE(hashTable.remove(0));
}

TEST(dict, removeSingleElement5CapCollision) {
    ArrayDictionary<int, int> hashTable (5);

    hashTable.add(12, 9);
    hashTable.add(3, 9);
    ASSERT_FALSE(hashTable.remove(14));
    ASSERT_TRUE(hashTable.remove(3));
}

TEST(dict, removeDoesNotExist) {
    ArrayDictionary<int, int> hashTable (5);

    hashTable.add(2, 9);
    hashTable.add(3, 9);
    hashTable.add(4, 9);
    ASSERT_FALSE(hashTable.remove(1));
    ASSERT_FALSE(hashTable.remove(5));
}

TEST(dict, remove10CapCollisionTest) {
    ArrayDictionary<int, int> hashTable;

    hashTable.add(1, 9);
    hashTable.add(3, 9);
    hashTable.add(13, 9);
    hashTable.add(31, 9);
    hashTable.add(33, 9);
    hashTable.add(11, 9);
    hashTable.add(21, 9);
    hashTable.add(4, 9);
    ASSERT_FALSE(hashTable.remove(14));
    ASSERT_TRUE(hashTable.remove(11));
    ASSERT_TRUE(hashTable.remove(21));
    ASSERT_TRUE(hashTable.remove(1));
}

TEST(dict, remove10CapCollisionTestDNE) {
    ArrayDictionary<int, int> hashTable;

    hashTable.add(1, 9);
    hashTable.add(3, 9);
    hashTable.add(13, 9);
    hashTable.add(31, 9);
    hashTable.add(33, 9);
    hashTable.add(11, 9);
    hashTable.add(21, 9);
    hashTable.add(4, 9);
    ASSERT_FALSE(hashTable.remove(0));
    ASSERT_FALSE(hashTable.remove(5));
    ASSERT_FALSE(hashTable.remove(10));
    ASSERT_FALSE(hashTable.remove(2));
}
