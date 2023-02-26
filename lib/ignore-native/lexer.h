#pragma once

#include <map>
#include <string>
#include <vector>

enum class tolkenType : uint8_t {
  UNKNOWN,
  NUMBER,
  IDENTIFIER,
  EQUALS,
  OPEN_BRACKET,
  CLOSED_BRACKET,
  OPEN_PARENTHESIS,
  CLOSED_PARENTHESIS,
  OPEN_BRACE,
  CLOSED_BRACE,
  BINARY_OPERATOR,
  COMPARISON_OPERATOR,
  PERIOD,
  LET,
  IF,
  FOR,
  WHILE,
  SEMICOLON,
  SPACE,
};

enum class characterType : uint8_t {
  SYMBOLIC,
  NUMERIC,
  ALPHABETIC,
};

enum class sequenceType : uint8_t {
  SYMBOL,
  INTEGER_NUMBER,
  DECIMAL_NUMBER,
  ALPHANUMERIC_TEXT,
};

struct sequence {
  std::string value = "";
  sequenceType type = sequenceType::SYMBOL;
};

struct lookupSummary {
  bool matchFound = false;
  std::string value = "";
  tolkenType type = tolkenType::UNKNOWN;
};

class sequence {
 public:
  sequence(std::string value, sequenceType type);

  std::string getValue();
  sequenceType getType();

 private:
  std::string value = "";
  sequenceType type = sequenceType::SYMBOL;
};

class sequenceGenerator {
 public:
  sequenceGenerator();

  std::vector<sequence> push(char character);
  void clear();

 private:
  characterType currentCharacterType = characterType::SYMBOLIC;
  characterType firstCharacterType = characterType::SYMBOLIC;
  characterType previousCharacterType = characterType::SYMBOLIC;
  uint8_t fullStopCount = 0;
  uint8_t numberCount = 0;
  std::string currentSequenceValue = "";
  sequenceType currentSequenceType = sequenceType::SYMBOL;
};

class tolken {
 public:
  tolken(std::string value, tolkenType type);

  std::string getValue();
  tolkenType getType();

 private:
  std::string value = "";
  tolkenType type = tolkenType::UNKNOWN;
};

lookupSummary tolkenLookup(std::string subsource);

std::vector<tolken> tolkenize(std::string source);