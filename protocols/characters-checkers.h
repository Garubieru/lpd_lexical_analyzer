#ifndef CHARACTERSCHECKERS_H_
#define CHARACTERSCHECKERS_H_

int isSpace(wchar_t *character);

int isTab(wchar_t *character);

int isEndOfLine(wchar_t *character);

int isEndOfFile(wchar_t *character);

int isSumOp(wchar_t *character);

int isDivisionOp(wchar_t *character);

int isMultiplierOp(wchar_t *character);

int isSubtractionOp(wchar_t *character);

int isDot(wchar_t *character);

int isOpenParenthesis(wchar_t *character);

int isClosedParenthesis(wchar_t *character);

int isDigit(wchar_t *character);

int isAlpha(wchar_t *character);

int isExclamation(wchar_t *character);

int isUnderline(wchar_t *character);

int isEqual(wchar_t *character);

int isSemicolonSymbol(wchar_t *character);

int isDoubleQuotes(wchar_t *character);

int isRightArrow(wchar_t *character);

int isLeftArrow(wchar_t *character);

int isComma(wchar_t *character);

int isMinus(wchar_t *character);

int isSingleQuote(wchar_t *character);

int isOpenBracket(wchar_t *character);

int isCloseBracket(wchar_t *character);

int isSpecialCharacter(wchar_t *character);

#endif