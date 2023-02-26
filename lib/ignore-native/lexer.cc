#include <lexer.h>

// base tolkens map
std::map<std::string, tolkenType> keywords = {
    {"{", tolkenType::OPEN_BRACE},
    {"}", tolkenType::CLOSED_BRACE},
    {"[", tolkenType::OPEN_BRACKET},
    {"]", tolkenType::CLOSED_BRACKET},
    {"=", tolkenType::EQUALS},
    {";", tolkenType::SEMICOLON},
    {"+", tolkenType::BINARY_OPERATOR},
    {"-", tolkenType::BINARY_OPERATOR},
    {"*", tolkenType::BINARY_OPERATOR},
    {"/", tolkenType::BINARY_OPERATOR},
    {"^", tolkenType::BINARY_OPERATOR},
    {"(", tolkenType::OPEN_PARENTHESIS},
    {")", tolkenType::CLOSED_PARENTHESIS},
    {".", tolkenType::PERIOD},
    {" ", tolkenType::SPACE},
    {"if", tolkenType::IF},
    {"or", tolkenType::BINARY_OPERATOR},
    {"and", tolkenType::BINARY_OPERATOR},
    {"not", tolkenType::COMPARISON_OPERATOR},
    {"equals", tolkenType::COMPARISON_OPERATOR},
    {"modulo", tolkenType::COMPARISON_OPERATOR},
    {"equalOrGreaterThan", tolkenType::COMPARISON_OPERATOR},
    {"equalOrLessThan", tolkenType::COMPARISON_OPERATOR},
    {"greaterThan", tolkenType::COMPARISON_OPERATOR},
    {"lessThan", tolkenType::COMPARISON_OPERATOR},
    {"while", tolkenType::WHILE},
    {"for", tolkenType::FOR},
    {"var", tolkenType::LET},
};

// tolken class
tolken::tolken(std::string value, tolkenType type) {
  this->value = value;
  this->type = type;
};

std::string tolken::getValue() { return this->value; }

tolkenType tolken::getType() { return this->type; }

// tolken lookup function
lookupSummary tolkenLookup(std::map<std::string, tolkenType> lookupTable, std::string subsource) {
  lookupSummary summary;
  if (lookupTable.count(subsource) != 0) {
    summary.matchFound = true;
    summary.value = subsource;
    summary.type = lookupTable[subsource];
  }
  return summary;
}

// sequence class
sequence::sequence(std::string value, sequenceType type) {
  this->value = value;
  this->type = type;
}

std::string sequence::getValue() { return this->value; }

sequenceType sequence::getType() { return this->type; }

// sequenceGenerator class
sequenceGenerator::sequenceGenerator() {};

std::vector<sequence> sequenceGenerator::push(char character) {
  std::vector<sequence> newSequences;

  // evaluate the incoming character and the current accumulated sequence
  bool charIsAlphabetic = isalpha(character);
  bool charIsAlphanumeric = isalnum(character);
  bool charIsFullStop = character == '.';
  uint8_t currentSequenceLength = this->currentSequenceValue.length();
  sequenceType currentSequenceType = this->currentSequenceType;

  // determine what character type the current character is
  if (charIsAlphabetic) {
    this->currentCharacterType = characterType::ALPHABETIC;
  } else if (charIsAlphanumeric and not charIsAlphabetic) {
    this->currentCharacterType = characterType::NUMERIC;
  } else {
    this->currentCharacterType = characterType::SYMBOLIC;
  }

  // determine what character type the first character is
  if (currentSequenceLength == 0) {
    this->firstCharacterType = currentCharacterType;
  }

  // determine
  if (currentCharacterType == characterType::NUMERIC) {
    this->numberCount += 1;
  } else if (currentCharacterType == characterType::SYMBOLIC and charIsFullStop) {
    this->fullStopCount += 1;
  }

  characterType currentCharacterType = this->currentCharacterType;
  characterType firstCharacterType = this->firstCharacterType;
  uint8_t numberCount = this->numberCount;
  uint8_t fullStopCount = this->fullStopCount;

  if (currentCharacterType == characterType::SYMBOLIC and
      not(firstCharacterType == characterType::NUMERIC and fullStopCount <= 1)) {
    if (currentSequenceLength > 0) {
      newSequences.push_back(sequence(currentSequenceValue, currentSequenceType));
    }
    this->currentSequenceValue.push_back(character);
    this->currentSequenceType = sequenceType::SYMBOL;
    currentSequenceValue = this->currentSequenceValue;
    currentSequenceType = this->currentSequenceType;
    newSequences.push_back(sequence(currentSequenceValue, currentSequenceType));
    this->clear();
  } else if (firstCharacterType == characterType::NUMERIC) {
    if (numberCount == currentSequenceLength and currentCharacterType == characterType::NUMERIC) {
      this->currentSequenceValue.push_back(character);
      this->currentSequenceType = sequenceType::INTEGER_NUMBER;
    } else if ((numberCount == currentSequenceLength - 1 and fullStopCount <= 1) and
               (currentCharacterType == characterType::NUMERIC or
                (currentCharacterType == characterType::SYMBOLIC and charIsFullStop))) {
      this->currentSequenceValue.push_back(character);
      this->currentSequenceType = sequenceType::DECIMAL_NUMBER;
    } else {
      newSequences.push_back(sequence(currentSequenceValue, currentSequenceType));
      this->currentCharacterType = characterType::SYMBOLIC;
      this->firstCharacterType = currentCharacterType;
      this->previousCharacterType = characterType::SYMBOLIC;
      this->fullStopCount = 0;
      this->numberCount = 0;
      this->currentSequenceValue.clear();
      this->currentSequenceValue.push_back(character);
      this->currentSequenceType = sequenceType::ALPHANUMERIC_TEXT;
    }
  } else if (firstCharacterType == characterType::ALPHABETIC) {
    this->currentSequenceValue.push_back(character);
    this->currentSequenceType = sequenceType::ALPHANUMERIC_TEXT;
  } else {
    this->clear();
  }

  return newSequences;
}

void sequenceGenerator::clear() {
  this->currentCharacterType = characterType::SYMBOLIC;
  this->firstCharacterType = characterType::SYMBOLIC;
  this->previousCharacterType = characterType::SYMBOLIC;
  this->fullStopCount = 0;
  this->numberCount = 0;
  this->currentSequenceValue = "";
  this->currentSequenceType = sequenceType::SYMBOL;
}

// tolkenize function
std::vector<tolken> tolkenize(std::string source) {
  std::vector<tolken> tolkens;
  uint64_t sourceLength = source.length();
  sequenceGenerator sequencer;
  char currentChar;

  for (uint32_t i = 0; i < sourceLength; i++) {
    currentChar = source[i];
    std::vector<sequence> newSequences = sequencer.push(currentChar);

    for (uint8_t j = 0; j < newSequences.size(); j++) {
      sequence currentSequence = newSequences[j];
      std::string currentSequenceValue = currentSequence.getValue();
      sequenceType currentSequenceType = currentSequence.getType();
      lookupSummary lookupResult = tolkenLookup(keywords, currentSequenceValue);
      if (lookupResult.matchFound) {
        tolkens.push_back(tolken(lookupResult.value, lookupResult.type));
      } else if (not lookupResult.matchFound and currentSequenceType == sequenceType::NUMBER) {
        tolkens.push_back(tolken(currentSequenceValue, tolkenType::NUMBER));
      } else if (not lookupResult.matchFound and currentSequenceType == sequenceType::ALPHANUMERIC_TEXT) {
        tolkens.push_back(tolken(currentSequenceValue, tolkenType::IDENTIFIER));
      }
    }
  }
  return tolkens;
}