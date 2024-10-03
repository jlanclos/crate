#include <gtest/gtest.h>
#include <sequencer.h>
#include <toggle/toggle.h>

#define GTEST_COUT std::cout

TEST(toggleMethods, toggleCreateRead) {
  // toggle can be instantiated with a true/false value
  toggle mockToggleTrue(true);
  ASSERT_EQ(mockToggleTrue.getValue(), true);
  toggle mockToggleFalse(false);
  ASSERT_EQ(mockToggleFalse.getValue(), false);

  // toggle can be instatiated with a serializedToggle vector
  byteString_t serializedToggleTrue = {(uint8_t)entryType::TOGGLE, true};
  toggle mockToggleSerializedTrue(serializedToggleTrue);
  ASSERT_EQ(mockToggleSerializedTrue.getValue(), true);
  byteString_t serializedToggleFalse = {(uint8_t)entryType::TOGGLE, false};
  toggle mockToggleSerializedFalse(serializedToggleFalse);
  ASSERT_EQ(mockToggleSerializedFalse.getValue(), false);
}

TEST(toggleMethods, toggleSerialization) {
  toggle mockToggleSerialization(true);
  ASSERT_EQ(mockToggleSerialization.getValue(), true);

  byteString_t serializationToggleTrue = {(uint8_t)entryType::TOGGLE, true};
  ASSERT_EQ(mockToggleSerialization.encode(), serializationToggleTrue);
  toggle mockToggleSerializationPrevious(true);
  toggle mockToggleSerializationNew(mockToggleSerialization.encode());
  ASSERT_EQ(mockToggleSerializationNew.getValue(), mockToggleSerializationPrevious.getValue());
}