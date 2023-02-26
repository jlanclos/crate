#include <gtest/gtest.h>
#include <sequencer.h>

#define GTEST_COUT std::cout

TEST(sequencerMethods, sequencerConstruction) {
  // sequencer can be instantiated without any arguments, resulting in default behavior
  // to run this test, move uint32_t value from private to public in order to make this->value available
  // for the manipulation required to run this test
  // sequencer mockSequencer;
  // ASSERT_EQ(mockSequencer.getCurrent(), 0);
  // ASSERT_EQ(mockSequencer.getStart(), 0);
  // ASSERT_EQ(mockSequencer.getEnd(), 4294967295);
  // ASSERT_EQ(mockSequencer.getStep(), 1);
  // mockSequencer.value = 4294967255;
  // for (uint32_t i = mockSequencer.getStart() + 4294967255; i < mockSequencer.getEnd(); i++) {
  //   ASSERT_EQ(mockSequencer.next(), i + 1);
  //   ASSERT_EQ(mockSequencer.getCurrent(), i + 1);
  //   GTEST_COUT << printf("current: %d\n", mockSequencer.getCurrent()) << std::endl;
  // }
  // ASSERT_EQ(mockSequencer.next(), 0);
  // mockSequencer.value = 4294967155;
  // for (uint32_t i = mockSequencer.getStart() + 4294967155; i < mockSequencer.getEnd(); i++) {
  //   ASSERT_EQ(mockSequencer.next(), i + 1);
  //   ASSERT_EQ(mockSequencer.getCurrent(), i + 1);
  //   GTEST_COUT << printf("current: %d\n", mockSequencer.getCurrent()) << std::endl;
  // }

  // sequencer can be instantiated with a start and end argument
  // if end>= start, the sequencer counts up
  sequencer mockSequencerUp(6, 345343);
  ASSERT_EQ(mockSequencerUp.getCurrent(), 6);
  ASSERT_EQ(mockSequencerUp.getStart(), 6);
  ASSERT_EQ(mockSequencerUp.getEnd(), 345343);
  ASSERT_EQ(mockSequencerUp.getStep(), 1);
  for (uint32_t i = mockSequencerUp.getStart(); i < mockSequencerUp.getEnd(); i++) {
    ASSERT_EQ(mockSequencerUp.next(), i + 1);
    ASSERT_EQ(mockSequencerUp.getCurrent(), i + 1);
    // GTEST_COUT << printf("current: %d\n", mockSequencerUp.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerUp.next(), mockSequencerUp.getStart());
  for (uint32_t i = mockSequencerUp.getStart(); i < mockSequencerUp.getEnd(); i++) {
    ASSERT_EQ(mockSequencerUp.next(), i + 1);
    ASSERT_EQ(mockSequencerUp.getCurrent(), i + 1);
    // GTEST_COUT << printf("current: %d\n", mockSequencerUp.getCurrent()) << std::endl;
  }

  // sequencer can be instantiated with a start and end argument
  // if start > end, the sequencer counts down
  sequencer mockSequencerDown(70000, 23);
  ASSERT_EQ(mockSequencerDown.getCurrent(), 70000);
  ASSERT_EQ(mockSequencerDown.getStart(), 70000);
  ASSERT_EQ(mockSequencerDown.getEnd(), 23);
  ASSERT_EQ(mockSequencerDown.getStep(), 1);
  for (uint32_t i = mockSequencerDown.getStart(); i > mockSequencerDown.getEnd(); i--) {
    ASSERT_EQ(mockSequencerDown.next(), i - 1);
    ASSERT_EQ(mockSequencerDown.getCurrent(), i - 1);
    // GTEST_COUT << printf("current: %d\n", mockSequencerDown.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerDown.next(), mockSequencerDown.getStart());
  for (uint32_t i = mockSequencerDown.getStart(); i > mockSequencerDown.getEnd(); i--) {
    ASSERT_EQ(mockSequencerDown.next(), i - 1);
    ASSERT_EQ(mockSequencerDown.getCurrent(), i - 1);
    // GTEST_COUT << printf("current: %d\n", mockSequencerDown.getCurrent()) << std::endl;
  }

  // sequencer can be instantiated with a start, end, and stop argument
  // if end >= start, the sequencer counts up
  sequencer mockSequencerUpStep(6, 90001, 1000);
  ASSERT_EQ(mockSequencerUpStep.getCurrent(), 6);
  ASSERT_EQ(mockSequencerUpStep.getStart(), 6);
  ASSERT_EQ(mockSequencerUpStep.getEnd(), 90001);
  ASSERT_EQ(mockSequencerUpStep.getStep(), 1000);
  for (uint32_t i = mockSequencerUpStep.getStart(); i < mockSequencerUpStep.getEnd();
       i += mockSequencerUpStep.getStep()) {
    ASSERT_EQ(mockSequencerUpStep.next(), i + mockSequencerUpStep.getStep());
    ASSERT_EQ(mockSequencerUpStep.getCurrent(), i + mockSequencerUpStep.getStep());
    // GTEST_COUT << printf("current: %d\n", mockSequencerUpStep.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerUpStep.next(), mockSequencerUpStep.getStart());
  for (uint32_t i = mockSequencerUpStep.getStart(); i < mockSequencerUpStep.getEnd();
       i += mockSequencerUpStep.getStep()) {
    ASSERT_EQ(mockSequencerUpStep.next(), i + mockSequencerUpStep.getStep());
    ASSERT_EQ(mockSequencerUpStep.getCurrent(), i + mockSequencerUpStep.getStep());
    // GTEST_COUT << printf("current: %d\n", mockSequencerUpStep.getCurrent()) << std::endl;
  }

  // sequencer can be instantiated with a start, end, and stop argument
  // if start > end, the sequencer counts down
  sequencer mockSequencerDownStep(145, 23, 7);
  ASSERT_EQ(mockSequencerDownStep.getCurrent(), 145);
  ASSERT_EQ(mockSequencerDownStep.getStart(), 145);
  ASSERT_EQ(mockSequencerDownStep.getEnd(), 23);
  ASSERT_EQ(mockSequencerDownStep.getStep(), 7);
  for (uint32_t i = mockSequencerDownStep.getStart(); i > mockSequencerDownStep.getEnd();
       i -= mockSequencerDownStep.getStep()) {
    ASSERT_EQ(mockSequencerDownStep.next(), i - mockSequencerDownStep.getStep());
    ASSERT_EQ(mockSequencerDownStep.getCurrent(), i - mockSequencerDownStep.getStep());
    // GTEST_COUT << printf("current: %d\n", mockSequencerDownStep.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerDownStep.next(), mockSequencerDownStep.getStart());
  for (uint32_t i = mockSequencerDownStep.getStart(); i > mockSequencerDownStep.getEnd();
       i -= mockSequencerDownStep.getStep()) {
    ASSERT_EQ(mockSequencerDownStep.next(), i - mockSequencerDownStep.getStep());
    ASSERT_EQ(mockSequencerDownStep.getCurrent(), i - mockSequencerDownStep.getStep());
    // GTEST_COUT << printf("current: %d\n", mockSequencerDownStep.getCurrent()) << std::endl;
  }

  // sequencer can be instantiated with a start, end, and step argument
  // if end >= start, the sequencer counts up, but in the case that start = end, the sequence will stagnate
  sequencer mockSequencerStag1(127, 127, 4);
  ASSERT_EQ(mockSequencerStag1.getCurrent(), 127);
  ASSERT_EQ(mockSequencerStag1.getStart(), 127);
  ASSERT_EQ(mockSequencerStag1.getEnd(), 127);
  ASSERT_EQ(mockSequencerStag1.getStep(), 4);
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag1.next(), 127);
    ASSERT_EQ(mockSequencerStag1.getCurrent(), 127);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag1.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerStag1.next(), mockSequencerStag1.getStart());
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag1.next(), 127);
    ASSERT_EQ(mockSequencerStag1.getCurrent(), 127);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag1.getCurrent()) << std::endl;
  }

  sequencer mockSequencerStag2(0, 0, 29);
  ASSERT_EQ(mockSequencerStag2.getCurrent(), 0);
  ASSERT_EQ(mockSequencerStag2.getStart(), 0);
  ASSERT_EQ(mockSequencerStag2.getEnd(), 0);
  ASSERT_EQ(mockSequencerStag2.getStep(), 29);
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag2.next(), 0);
    ASSERT_EQ(mockSequencerStag2.getCurrent(), 0);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag2.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerStag2.next(), mockSequencerStag2.getStart());
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag2.next(), 0);
    ASSERT_EQ(mockSequencerStag2.getCurrent(), 0);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag2.getCurrent()) << std::endl;
  }

  sequencer mockSequencerStag3(255, 255, 12);
  ASSERT_EQ(mockSequencerStag3.getCurrent(), 255);
  ASSERT_EQ(mockSequencerStag3.getStart(), 255);
  ASSERT_EQ(mockSequencerStag3.getEnd(), 255);
  ASSERT_EQ(mockSequencerStag3.getStep(), 12);
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag3.next(), 255);
    ASSERT_EQ(mockSequencerStag3.getCurrent(), 255);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag3.getCurrent()) << std::endl;
  }
  ASSERT_EQ(mockSequencerStag3.next(), mockSequencerStag3.getStart());
  for (uint32_t i = 0; i < 10; i++) {
    ASSERT_EQ(mockSequencerStag3.next(), 255);
    ASSERT_EQ(mockSequencerStag3.getCurrent(), 255);
    // GTEST_COUT << printf("current: %d\n", mockSequencerStag3.getCurrent()) << std::endl;
  }
}
