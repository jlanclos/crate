#include <entry/entry.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(entryMethods, entryCreateReadToggle) {
  toggle toggleData(true);
  entry toggleEntry(20, toggleData);
  ASSERT_EQ(toggleEntry.getId(), 20);
  toggle readToggle(toggleEntry.getData());
  bool toggleValue = readToggle.getValue();
  ASSERT_EQ(toggleValue, true);
  ASSERT_EQ(toggleEntry.getType(), entryType::TOGGLE);
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
