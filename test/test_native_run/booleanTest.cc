#include <boolean/boolean.h>
#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(booleanMethods, booleanCreateRead) {
  // boolean can be instantiated without arguments, resulting in a false value
  boolean mockBoolean;
  ASSERT_EQ(mockBoolean.getValue(), false);

  // boolean can be instantiated with a true/false value
  boolean mockBooleanTrue(true);
  ASSERT_EQ(mockBooleanTrue.getValue(), true);
  boolean mockBooleanFalse(false);
  ASSERT_EQ(mockBooleanFalse.getValue(), false);

  // boolean can be instatiated with a serializedBoolean vector
  std::vector<uint8_t> serializedBooleanTrue = {(uint8_t)entryType::BOOLEAN, 1, true};
  boolean mockBooleanSerializedTrue(serializedBooleanTrue);
  ASSERT_EQ(isValidBoolean(serializedBooleanTrue), true);
  ASSERT_EQ(mockBooleanSerializedTrue.getValue(), true);
  std::vector<uint8_t> serializedBooleanFalse = {(uint8_t)entryType::BOOLEAN, 1, false};
  boolean mockBooleanSerializedFalse(serializedBooleanFalse);
  ASSERT_EQ(isValidBoolean(serializedBooleanFalse), true);
  ASSERT_EQ(mockBooleanSerializedFalse.getValue(), false);
}

TEST(booleanMethods, booleanSerialization) {
  boolean mockBooleanSerialization(true);
  ASSERT_EQ(mockBooleanSerialization.getValue(), true);

  std::vector<uint8_t> serializationBooleanTrue = {(uint8_t)entryType::BOOLEAN, 1, true};
  ASSERT_EQ(mockBooleanSerialization.serialize(), serializationBooleanTrue);
  boolean mockBooleanSerializationPrevious(true);
  mockBooleanSerialization.deserialize(mockBooleanSerialization.serialize());
  ASSERT_EQ(mockBooleanSerialization.getValue(), mockBooleanSerializationPrevious.getValue());
}