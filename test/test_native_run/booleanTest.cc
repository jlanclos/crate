#include <boolean/boolean.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(booleanMethods, booleanCreateRead) {
  // boolean can be instantiated with a true/false value
  boolean mockBooleanTrue(true);
  ASSERT_EQ(mockBooleanTrue.getValue(), true);
  boolean mockBooleanFalse(false);
  ASSERT_EQ(mockBooleanFalse.getValue(), false);

  // boolean can be instatiated with a serializedBoolean vector
  std::vector<uint8_t> serializedBooleanTrue = {(uint8_t)entryType::BOOLEAN, true};
  boolean mockBooleanSerializedTrue(serializedBooleanTrue);
  ASSERT_EQ(mockBooleanSerializedTrue.getValue(), true);
  std::vector<uint8_t> serializedBooleanFalse = {(uint8_t)entryType::BOOLEAN, false};
  boolean mockBooleanSerializedFalse(serializedBooleanFalse);
  ASSERT_EQ(mockBooleanSerializedFalse.getValue(), false);
}

TEST(booleanMethods, booleanSerialization) {
  boolean mockBooleanSerialization(true);
  ASSERT_EQ(mockBooleanSerialization.getValue(), true);

  std::vector<uint8_t> serializationBooleanTrue = {(uint8_t)entryType::BOOLEAN, true};
  ASSERT_EQ(mockBooleanSerialization.getBytes(), serializationBooleanTrue);
  boolean mockBooleanSerializationPrevious(true);
  boolean mockBooleanSerializationNew(mockBooleanSerialization.getBytes());
  ASSERT_EQ(mockBooleanSerializationNew.getValue(), mockBooleanSerializationPrevious.getValue());
}