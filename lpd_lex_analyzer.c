#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include "protocols/readfile.h"
#include "protocols/char-to-wchar.h"
#include "protocols/characters-checkers.h"
#include "protocols/symbol-checkers.h"

typedef enum TOKEN_TYPE
{
  IDENTIFIER,
  ATTRIB_OP,
  SUM_OP,
  SUBTRACTION_OP,
  MULTIPLIER_OP,
  DIVISION_OP,
  EQUALITY_OP,
  DIFF_OP,
  GREATHER_OP,
  LESSER_OP,
  GREATER_THAN_OR_EQUAL_OP,
  LESS_THAN_OR_EQUAL_OP,
  AND_OP,
  OR_OP,
  NOT_OP,
  FOR_SYMBOL,
  WHILE_SYMBOL,
  REPEAT_SYMPOL,
  UNTIL_SYMBOL,
  PRG_SYMBOL,
  BEGIN_SYMBOL,
  VAR_SYMBOL,
  SUBROT_SYMBOL,
  READ_SYMBOL,
  WRITE_SYMBOL,
  END_SYMBOL,
  IF_SYMBOL,
  ELSE_SYMBOL,
  THEN_SYMBOL,
  RETURN_SYMBOL,
  PAREN_OPEN_SYMBOL,
  PAREN_CLOSED_SYMBOL,
  INTENGER_TYPE_SYMBOL,
  FLOAT_TYPE_SYMBOL,
  VOID_TYPE_SYMBOL,
  CHAR_TYPE_SYMBOL,
  INTENGER,
  FLOAT,
  SEMICOLON_SYMBOL,
  DOT_SYMBOL,
  COMMA_SYMBOL,
  STRING_SYMBOL,
  CHAR_SYMBOL,
  COMMENTARY,
  EOS,
  ERROR,
} TOKEN_TYPE;

typedef struct TOKEN
{
  int line;
  TOKEN_TYPE type;
  wchar_t value[200];
} TOKEN;

typedef enum RESERVED_IDENTIFIERS
{
  PRG_ID,
  VAR_ID,
  BEGIN_ID,
  CHAR_ID,
  INT_ID,
  FLOAT_ID,
  VOID_ID,
  SUBROT_ID,
  IF_ID,
  ELSE_ID,
  FOR_ID,
  WHILE_ID,
  THEN_ID,
  REPEAT_ID,
  UNTIL_ID,
  AND_ID,
  OR_ID,
  NOT_ID,
  READ_ID,
  WRITE_ID,
  END_ID,
  RETURN_ID,
} RESERVED_IDENTIFIERS;

char *reservedIdentifiers[] = {
    "prg",
    "var",
    "begin",
    "char",
    "int",
    "float",
    "void",
    "subrot",
    "if",
    "else",
    "for",
    "while",
    "then",
    "repeat",
    "until",
    "and",
    "or",
    "not",
    "read",
    "write",
    "end",
    "return"};

char *tokenToStr[] = {
    "IDENTIFIER",
    "ATTRIB_OP",
    "SUM_OP",
    "SUBTRACTION_OP",
    "MULTIPLIER_OP",
    "DIVISION_OP",
    "EQUALITY_OP",
    "DIFF_OP",
    "GREATHER_OP",
    "LESSER_OP",
    "GREATER_THAN_OR_EQUAL_OP",
    "LESS_THAN_OR_EQUAL_OP",
    "AND_OP",
    "OR_OP",
    "NOT_OP",
    "FOR_SYMBOL",
    "WHILE_SYMBOL",
    "REPEAT_SYMPOL",
    "UNTIL_SYMBOL",
    "PRG_SYMBOL",
    "BEGIN_SYMBOL",
    "VAR_SYMBOL",
    "SUBROT_SYMBOL",
    "READ_SYMBOL",
    "WRITE_SYMBOL",
    "END_SYMBOL",
    "IF_SYMBOL",
    "ELSE_SYMBOL",
    "THEN_SYMBOL",
    "RETURN_SYMBOL",
    "PAREN_OPEN_SYMBOL",
    "PAREN_CLOSED_SYMBOL",
    "INTENGER_TYPE_SYMBOL",
    "FLOAT_TYPE_SYMBOL",
    "VOID_TYPE_SYMBOL",
    "CHAR_TYPE_SYMBOL",
    "INTENGER",
    "FLOAT",
    "SEMICOLON_SYMBOL",
    "DOT_SYMBOL",
    "COMMA_SYMBOL",
    "STRING_SYMBOL",
    "CHAR_SYMBOL",
    "COMMENTARY",
    "EOS",
    "ERROR",
};


TOKEN scanner(wchar_t **buffer, int *line)
{
  TOKEN token;
  wcscpy(token.value, charToWChar(""));
  token.type = ERROR;

  while (isSpace(*buffer) || isTab(*buffer) || isEndOfLine(*buffer))
  {
    if (isEndOfLine(*buffer))
    {
      (*line)++;
    }
    (*buffer)++;
  }

  if (isClosedParenthesis(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = PAREN_CLOSED_SYMBOL;
  }
  else if (isSumOp(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SUM_OP;
  }
  else if (isMultiplierOp(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = MULTIPLIER_OP;
  }
  else if (isDivisionOp(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = DIVISION_OP;
  }
  else if (isSubtractionOp(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SUBTRACTION_OP;
  }
  else if (isAlpha(*buffer))
  {
    while (isAlpha(*buffer) || isDigit(*buffer) || isUnderline(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }

    token.type = IDENTIFIER;

    if (isINTTypeSymbol(token.value))
    {
      token.type = INTENGER_TYPE_SYMBOL;
    }
    else if (isFLOATTypeSymbol(token.value))
    {
      token.type = FLOAT_TYPE_SYMBOL;
    }
    else if (isCHARSymbol(token.value))
    {
      token.type = CHAR_TYPE_SYMBOL;
    }
    else if (isVOIDSymbol(token.value))
    {
      token.type = VOID_TYPE_SYMBOL;
    }
    else if (isPRGSymbol(token.value))
    {
      token.type = PRG_SYMBOL;
    }
    else if (isBEGINSymbol(token.value))
    {
      token.type = BEGIN_SYMBOL;
    }
    else if (isVARSymbol(token.value))
    {
      token.type = VAR_SYMBOL;
    }
    else if (isSUBROTSymbol(token.value))
    {
      token.type = SUBROT_SYMBOL;
    }
    else if (isIFSymbol(token.value))
    {
      token.type = IF_SYMBOL;
    }
    else if (isELSESymbol(token.value))
    {
      token.type = ELSE_SYMBOL;
    }
    else if (isFORSymbol(token.value))
    {
      token.type = FOR_SYMBOL;
    }
    else if (isWHILESymbol(token.value))
    {
      token.type = WHILE_SYMBOL;
    }
    else if (isTHENSymbol(token.value))
    {
      token.type = THEN_SYMBOL;
    }
    else if (isREPEATSymbol(token.value))
    {
      token.type = REPEAT_SYMPOL;
    }
    else if (isUNTILSymbol(token.value))
    {
      token.type = UNTIL_SYMBOL;
    }
    else if (isANDSymbol(token.value))
    {
      token.type = AND_OP;
    }
    else if (isORSymbol(token.value))
    {
      token.type = OR_OP;
    }
    else if (isNOTSymbol(token.value))
    {
      token.type = NOT_OP;
    }
    else if (isREADSymbol(token.value))
    {
      token.type = READ_SYMBOL;
    }
    else if (isWRITESymbol(token.value))
    {
      token.type = WRITE_SYMBOL;
    }
    else if (isENDSymbol(token.value))
    {
      token.type = END_SYMBOL;
    }
    else if (isRETURNSymbol(token.value))
    {
      token.type = RETURN_SYMBOL;
    }
  }
  else if (isDigit(*buffer))
  {
    while (isDigit(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }
    token.type = INTENGER;
    if (isDot(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
      while (isDigit(*buffer))
      {
        wcsncat(token.value, *buffer, 1);
        (*buffer)++;
      }
      token.type = FLOAT;
    }
  }
  else if (isOpenParenthesis(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = PAREN_OPEN_SYMBOL;
  }
  else if (isSemicolonSymbol(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SEMICOLON_SYMBOL;
  }
  else if (isDot(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = DOT_SYMBOL;
  }
  else if (isEqual(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      token.type = EQUALITY_OP;
      (*buffer)++;
    }
  }
  else if (isRightArrow(*buffer))
  {
    token.type = GREATHER_OP;
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      token.type = GREATER_THAN_OR_EQUAL_OP;
      (*buffer)++;
    }
  }
  else if (isLeftArrow(*buffer))
  {
    token.type = LESSER_OP;
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      token.type = LESS_THAN_OR_EQUAL_OP;
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }
    else if (isMinus(*buffer))
    {
      token.type = ATTRIB_OP;
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }
  }
  else if (isComma(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    token.type = COMMA_SYMBOL;
    (*buffer)++;
  }
  else if (isExclamation(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      token.type = DIFF_OP;
      (*buffer)++;
    }
  }
  else if (isDoubleQuotes(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;
    while (isAlpha(*buffer) || isSpace(*buffer) || isDigit(*buffer) || isSpecialCharacter(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }

    if (isDoubleQuotes(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      token.type = STRING_SYMBOL;
      (*buffer)++;
    }
  }
  else if (isSingleQuote(*buffer))
  {
    wcsncat(token.value, *buffer, 1);
    (*buffer)++;

    if (isAlpha(*buffer) || isDigit(*buffer) || isSpecialCharacter(*buffer))
    {
      wcsncat(token.value, *buffer, 1);
      (*buffer)++;
    }
    wcsncat(token.value, *buffer, 1);
    if (isSingleQuote(*buffer))
    {
      token.type = CHAR_SYMBOL;
      (*buffer)++;
    }
  }
  else if (isOpenBracket(*buffer))
  {
    (*buffer)++;
    while (!isCloseBracket(*buffer))
    {
      (*buffer)++;
    }
    token.type = COMMENTARY;
    (*buffer)++;
  }
  else if (isEndOfFile(*buffer))
  {
    token.type = EOS;
    wcscpy(token.value, charToWChar("EOF"));
  }
  else
  {
    wcsncat(token.value, *buffer, 1);
  }

  token.line = *line;
  return token;
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  char *fileName = argv[1];
  int line = 1;
  wchar_t *buffer = readFile(fileName);
  TOKEN *tokens;
  int tokenCounter = 0;

  tokens = malloc(sizeof(TOKEN) * 1);
  while (1)
  {
    TOKEN currentToken = scanner(&buffer, &line);
    tokenCounter++;
    tokens = realloc(tokens, tokenCounter * sizeof(TOKEN));
    tokens[tokenCounter - 1] = currentToken;
    if ((currentToken.type == ERROR) || (currentToken.type == EOS))
      break;
  }

  for (int i = 0; i < tokenCounter; i++)
  {
    printf("Line:%3d | %-30s | %5Ls\n", tokens[i].line, tokenToStr[tokens[i].type], tokens[i].value);
  }

  return 0;
}