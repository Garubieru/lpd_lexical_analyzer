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

/*
Grupo:
  Gabriel da Silva Morishita Garbi - 32048661
  Bruno Seki Schenberg - 32041292

  Comando para buildar: gcc -g lpd_lex_analyzer.c ./utils/*.c -o lpd_lex_analyzer
*/

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

typedef struct TOKEN
{
  int line;
  TOKEN_TYPE type;
  wchar_t value[200];
} TOKEN;

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

int isVerboseMode(char *mode, int argc)
{
  int hasThirdArg = argc == 3;
  return hasThirdArg && strcmp(mode, "/v") == 0;
}

void notifyResult(int isErrorFound, char *fileName, int line)
{

  if (!isErrorFound)
  {
    printf("Succesfully identified all %s tokens. Run verbose mode (/v) to see results.\n", fileName);
  }
  else
  {
    printf("An error ocurred while trying to identify tokens on %s in line %d. Please, run verbose mode (/v) to see results.\n", fileName, line);
  }
}

TOKEN *tokens;
int parserErrors = 0;

void parser();
int id();
void dcl();
int tpo();
void sub();
void param();
void bco();
void cmd();
void wr();
void rd();
void check_if();
void fr();
void wh();
void rpt();
void atr();
void f();
void check_atr_or_f();
void e();
void check_exp();
void exps();
void tmo();
void frt();
int opcat3();
int opcat2();
int opcat1();

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  char *fileName = argv[1];
  char *mode = argv[2];
  int line = 1;

  wchar_t *buffer = readFile(fileName);
  int tokenCounter = 0;
  tokens = malloc(sizeof(TOKEN) * 1);

  int isErrorFound = 0;
  while (1)
  {
    TOKEN currentToken = scanner(&buffer, &line);
    tokenCounter++;
    tokens = realloc(tokens, tokenCounter * sizeof(TOKEN));
    tokens[tokenCounter - 1] = currentToken;
    int isErrorOrEOS = (currentToken.type == ERROR) || (currentToken.type == EOS);
    if (isErrorOrEOS)
    {
      if (currentToken.type == ERROR)
      {
        isErrorFound = 1;
      }
      break;
    }
  }

  notifyResult(isErrorFound, fileName, line);

  if (isVerboseMode(mode, argc))
  {
    for (int i = 0; i < tokenCounter; i++)
    {
      TOKEN token = tokens[i];
      printf("Line:%3d | %-30s | %5Ls\n", token.line, tokenToStr[token.type], token.value);
    }
  }

  parser();

  if (parserErrors > 0)
  {
    printf("CAGUEIII ERROR");
    return 1;
  }

  return 1;
}

int check(TOKEN_TYPE expectedTokenType)
{
  TOKEN_TYPE currentTokenType = tokens->type;
  int isExpectedToken = currentTokenType == expectedTokenType;
  if (isExpectedToken)
  {
    printf("value: %ls | line: %d\n", tokens->value, tokens->line);
    tokens++;
    return isExpectedToken;
  }
  else
  {
    parserErrors++;
    printf("[ERROR] value: %ls | line: %d\n", tokens->value, tokens->line);
    tokens++;
    return isExpectedToken;
  }
}

int id()
{
  return check(IDENTIFIER);
}

int tpo()
{
  if (tokens->type == INTENGER_TYPE_SYMBOL)
  {
    return check(INTENGER_TYPE_SYMBOL);
  }
  else if (tokens->type == FLOAT_TYPE_SYMBOL)
  {
    return check(FLOAT_TYPE_SYMBOL);
  }
  else if (tokens->type == CHAR_TYPE_SYMBOL)
  {
    return check(CHAR_TYPE_SYMBOL);
  }
}

void dcl()
{
  check(VAR_SYMBOL);
  tpo();
  id();
  while (tokens->type == COMMA_SYMBOL)
  {
    check(COMMA_SYMBOL);
    id();
  }
  check(SEMICOLON_SYMBOL);
  if (tokens->type == SUBROT_SYMBOL)
  {
    sub();
  }
}

void param()
{
  if (tpo())
  {
    id();
    while (tokens->type == COMMA_SYMBOL)
    {
      check(COMMA_SYMBOL);
      tpo();
      id();
    }
  }
}

void ftr()
{
  if (tokens->type == NOT_OP)
  {
    check(NOT_OP);
    ftr();
  }
  else if (tokens->type == PAREN_OPEN_SYMBOL)
  {
    check(PAREN_OPEN_SYMBOL);
    check_exp();
    check(PAREN_CLOSED_SYMBOL);
  }
  else
  {
    e();
  }
}

int opcat1()
{
  switch (tokens->type)
  {
  case MULTIPLIER_OP:
    return check(SUM_OP);
    break;
  case DIVISION_OP:
    return check(SUBTRACTION_OP);
    break;
  case AND_OP:
    return check(OR_OP);
    break;
  default:
    return 0;
    break;
  }
}

void tmo()
{
  ftr();
  while (opcat1())
  {
    ftr();
  }
}

int opcat2()
{
  switch (tokens->type)
  {
  case SUM_OP:
    return check(SUM_OP);
    break;
  case SUBTRACTION_OP:
    return check(SUBTRACTION_OP);
    break;
  case OR_OP:
    return check(OR_OP);
    break;
  default:
    return 0;
    break;
  }
}

void exps()
{
  tmo();
  while (opcat2())
  {
    tmo();
  }
}

int opcat3()
{
  switch (tokens->type)
  {
  case GREATHER_OP:
    return check(GREATHER_OP);
    break;
  case GREATER_THAN_OR_EQUAL_OP:
    return check(GREATHER_OP);
    break;
  case LESSER_OP:
    return check(GREATHER_OP);
    break;
  case LESS_THAN_OR_EQUAL_OP:
    return check(GREATHER_OP);
    break;
  case EQUALITY_OP:
    return check(GREATHER_OP);
    break;
  case DIFF_OP:
    return check(GREATHER_OP);
    break;
  default:
    break;
  }
}

void check_exp()
{
  exps();
  while (opcat3())
  {
    exps();
  }
}

void f()
{
  check(IDENTIFIER);
  check(PAREN_OPEN_SYMBOL);
  check_exp();
  check(PAREN_CLOSED_SYMBOL);
}

void e()
{
  if (tokens->type == STRING_SYMBOL)
  {
    check(STRING_SYMBOL);
  }
  else if (tokens->type == FLOAT)
  {
    check(FLOAT);
  }
  else if (tokens->type == INTENGER)
  {
    check(INTENGER);
  }
  else if (tokens->type == CHAR_SYMBOL)
  {
    check(CHAR_SYMBOL);
  }
  else if (tokens->type == IDENTIFIER)
  {
    f();
  }
  else if (tokens->type == COMMA_SYMBOL)
  {
    check(COMMA_SYMBOL);
    printf("oiiii");

    check(FLOAT);
    printf("oiiii");
  }
}

void rd()
{
  check(READ_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  id();
  check(PAREN_CLOSED_SYMBOL);
  check(SEMICOLON_SYMBOL);
  cmd();
}

void wr()
{
  check(WRITE_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  printf("AAAAAAAAAAAAA");

  e();
  printf("AAAAAAAAAAAAA");
  check(PAREN_CLOSED_SYMBOL);
  check(SEMICOLON_SYMBOL);
  cmd();
}

void check_if()
{

  check(IF_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  check_exp();
  check(THEN_SYMBOL);
  cmd();
  if (tokens->type == ELSE_SYMBOL)
  {
    check(ELSE_SYMBOL);
    cmd();
  }
}

void atr()
{
  id();
  check(ATTRIB_OP);
  check_exp();
}

void fr()
{
  check(FOR_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  atr();
  check(SEMICOLON_SYMBOL);
  check_exp();
  check(SEMICOLON_SYMBOL);
  atr();
  check(PAREN_CLOSED_SYMBOL);
  cmd();
}

void wh()
{
  check(WHILE_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  check_exp();
  check(PAREN_CLOSED_SYMBOL);
  cmd();
}

void rpt()
{
  check(REPEAT_SYMPOL);
  cmd();
  check(UNTIL_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  check_exp();
  check(PAREN_OPEN_SYMBOL);
}

void check_atr_or_f()
{
  id();
  if (tokens->type == ATTRIB_OP)
  {
    check(ATTRIB_OP);
    check_exp();
  }
  else if (tokens->type == PAREN_OPEN_SYMBOL)
  {
    check(PAREN_OPEN_SYMBOL);
    check_exp();
    check(PAREN_CLOSED_SYMBOL);
  }
}

void rt()
{
}

void cmd()
{
  if (tokens->type == WRITE_SYMBOL)
  {
    wr();
  }
  else if (tokens->type == READ_SYMBOL)
  {
    rd();
  }
  else if (tokens->type == IF_SYMBOL)
  {
    check_if();
  }
  else if (tokens->type == FOR_SYMBOL)
  {
    fr();
  }
  else if (tokens->type == WHILE_SYMBOL)
  {
    wh();
  }
  else if (tokens->type == REPEAT_SYMPOL)
  {
    rpt();
  }
  else if (tokens->type == IDENTIFIER)
  {
    check_atr_or_f();
  }
  else if (tokens->type == BEGIN_SYMBOL)
  {
    bco();
  }
  else if (tokens->type == RETURN_SYMBOL)
  {
    rt();
  }
}

void bco()
{
  check(BEGIN_SYMBOL);
  cmd();
  check(END_SYMBOL);
}

void sub()
{
  printf("aaaaaa");
  check(SUBROT_SYMBOL);
  if (tokens->type == VOID_TYPE_SYMBOL)
  {
    check(VOID_TYPE_SYMBOL);
  }
  else
  {
    tpo();
  }
  id();
  check(PAREN_OPEN_SYMBOL);
  param();
  check(PAREN_CLOSED_SYMBOL);
  if (tokens->type == VAR_SYMBOL)
  {
    dcl();
  }
  else if (tokens->type == SUBROT_SYMBOL)
  {
    sub();
  }
  bco();
}

void parser()
{
  check(PRG_SYMBOL);
  id();
  check(SEMICOLON_SYMBOL);

  if (tokens->type == VAR_SYMBOL)
  {
    dcl();
  }
  else if (tokens->type == SUBROT_SYMBOL)
  {
    sub();
  }

  bco();
  check(DOT_SYMBOL);
}