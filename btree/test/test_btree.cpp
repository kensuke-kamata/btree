#include <gtest/gtest.h>
#include <btree/btree.h>

class BTreeTest : public ::testing::Test {
 protected:
  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(BTreeTest, SearchTest) {
  BTree<int> btree(3);
  btree.Insert(10);
  btree.Insert(20);
  btree.Insert(5);
  // btree.Insert(6);
  // btree.Insert(12);
  // btree.Insert(30);
  // btree.Insert(7);
  // btree.Insert(17);

  EXPECT_TRUE(btree.Search(10));
  EXPECT_TRUE(btree.Search(20));
  EXPECT_TRUE(btree.Search(5));
  // EXPECT_TRUE(btree.Search(6));
  // EXPECT_TRUE(btree.Search(12));
  // EXPECT_TRUE(btree.Search(30));
  // EXPECT_TRUE(btree.Search(7));
  // EXPECT_TRUE(btree.Search(17));
  // EXPECT_FALSE(btree.Search(4));
  // EXPECT_FALSE(btree.Search(21));
}
