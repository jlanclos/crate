#include <entry/entry.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(entryMethods, entryCreateReadBoolean) {
  boolean booleanData(true);
  entry booleanEntry(20, booleanData);
  ASSERT_EQ(booleanEntry.getId(), 20);
  boolean readBoolean(booleanEntry.getData());
  bool booleanValue = readBoolean.getValue();
  ASSERT_EQ(booleanValue, true);
  ASSERT_EQ(booleanEntry.getType(), entryType::BOOLEAN);
}

TEST(entryMethods, entryCreateReadInteger) {
  integer integerData(53223);
  entry integerEntry(20, integerData);
  ASSERT_EQ(integerEntry.getId(), 20);
  integer readInteger(integerEntry.getData());
  uint16_t integerValue = readInteger.getValue();
  ASSERT_EQ(integerValue, 53223);
  ASSERT_EQ(integerEntry.getType(), entryType::INTEGER);
}
