#include <gtest/gtest.h>
#include <lexer.h>

#define GTEST_COUT std::cout

TEST(lexerMethods, tolkenCreateRead) {
  // create tolkens
  tolken mockTolken1 = tolken("let", tolkenType::LET);
  tolken mockTolken2 = tolken("325", tolkenType::NUMBER);
  // read tolkens
  ASSERT_EQ(mockTolken1.getValue(), "let");
  ASSERT_EQ(mockTolken1.getType(), tolkenType::LET);
  ASSERT_EQ(mockTolken2.getValue(), "325");
  ASSERT_EQ(mockTolken2.getType(), tolkenType::NUMBER);

  GTEST_COUT << printf("tolken 1: %s\n", mockTolken1.getValue().c_str());
}

TEST(lexerMethods, tolkenizeFunction) {
  std::string mockSource = "for(i=20;i<113.234;i++){};";
  std::vector<tolken> tolkens = tolkenize(mockSource);

  for (uint8_t i = 0; i < tolkens.size(); i++) {
    GTEST_COUT << printf(
        "   tolken: value:"
        "%s"
        " , type: %d\n",
        tolkens[i].getValue().c_str(), tolkens[i].getType());
  }
}
