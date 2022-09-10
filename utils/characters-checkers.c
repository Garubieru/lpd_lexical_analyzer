#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>

int isSpace(wchar_t *character)
{
  return *character == ' ';
}

int isTab(wchar_t *character)
{
  return *character == '\t';
}

int isEndOfLine(wchar_t *character)
{
  return *character == '\n' || *character == '\r';
}

int isEndOfFile(wchar_t *character)
{
  return *character == EOF || *character == '\x0';
}

int isSumOp(wchar_t *character)
{
  return *character == '+';
}

int isDivisionOp(wchar_t *character)
{
  return *character == '/';
}

int isMultiplierOp(wchar_t *character)
{
  return *character == '*';
}

int isSubtractionOp(wchar_t *character)
{
  return *character == '-';
}

int isDot(wchar_t *character)
{
  return *character == '.';
}

int isOpenParenthesis(wchar_t *character)
{
  return *character == '(';
}

int isClosedParenthesis(wchar_t *character)
{
  return *character == ')';
}

int isDigit(wchar_t *character)
{
  return *character >= '0' && *character <= '9';
}

int isAlpha(wchar_t *character)
{
  return iswalpha(*character);
}

int isExclamation(wchar_t *character)
{
  return *character == '!';
}

int isUnderline(wchar_t *character)
{
  return *character == '_';
}

int isEqual(wchar_t *character)
{
  return *character == '=';
}

int isSemicolonSymbol(wchar_t *character)
{
  return *character == ';';
}

int isDoubleQuotes(wchar_t *character)
{
  return *character == '"';
}

int isRightArrow(wchar_t *character)
{
  return *character == '>';
}

int isLeftArrow(wchar_t *character)
{
  return *character == '<';
}

int isComma(wchar_t *character)
{
  return *character == ',';
}

int isMinus(wchar_t *character)
{
  return *character = '-';
}

int isSingleQuote(wchar_t *character)
{
  return *character == '\'';
}

int isOpenBracket(wchar_t *character)
{
  return *character == '{';
}

int isCloseBracket(wchar_t *character)
{
  return *character == '}';
}

int isSpecialCharacter(wchar_t *character)
{
  return (*character == 33) ||
         (*character >= 35 && *character <= 47) ||
         (*character >= 58 && *character <= 64) ||
         (*character >= 91 && *character <= 96) ||
         (*character >= 123 && *character <= 126);
}