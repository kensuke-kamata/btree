#include <gtest/gtest.h>
#include "btree/is_comparable.h"

struct Comparable {
  int value;
  bool operator<(const Comparable& other) const { return value < other.value; }
  bool operator>(const Comparable& other) const { return value > other.value; }
  bool operator<=(const Comparable& other) const { return value <= other.value; }
  bool operator>=(const Comparable& other) const { return value >= other.value; }
};

struct NonComparable {
  int value;
};

struct PartiallyComparable {
  int value;
  bool operator<(const PartiallyComparable& other) const { return value < other.value; }
};


TEST(IsComparable, ComparableTest) {
  EXPECT_TRUE(is_comparable<Comparable>::value);
}

TEST(IsComparable, NonComparableTest) {
  EXPECT_FALSE(is_comparable<NonComparable>::value);
}

TEST(IsComparable, PartiallyComparableTest) {
  EXPECT_FALSE(is_comparable<PartiallyComparable>::value);
}
