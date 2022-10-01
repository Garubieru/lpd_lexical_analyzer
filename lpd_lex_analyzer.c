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
#include "utils/token-type.c"

#define TRUE 1
#define FALSE 0

/*
Grupo:
  Gabriel da Silva Morishita Garbi - 32048661
  Bruno Seki Schenberg - 32041292

  Comando para buildar: gcc -g lpd_lex_analyzer.c ./utils/*.c -o lpd_lex_analyzer
*/

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

void setProgramLocal();
void setModes(int argc, char *argv[]);
int isVerboseMode(char *mode);
int isDebugMode(char *mode);
TOKEN scanner(wchar_t **buffer, int *line);
void printToken(TOKEN token);
void notifyTokensResult(int isErrorFound, char *fileName, int line);
void notifyParserResult(int parserErrors);
void parser();
void ini();
int id();
void dcl();
int tpo();
void sub();
void param();
void bco();
void cmd();
void wr();
void rd();
void IF();
void rt();
void fr();
void wh();
void rpt();
void atr();
void f();
void AF();
void e();
void EXP();
void exps();
void tmo();
void frt();
int opcat3();
int opcat2();
int opcat1();

TOKEN *tokens;
int parserErrors = 0;
int isVerboseModeSet = FALSE;
int isDebugModeSet = FALSE;

int main(int argc, char *argv[])
{
  setProgramLocal();

  char *fileName = argv[1];
  setModes(argc, argv);

  wchar_t *buffer = readFile(fileName);
  tokens = malloc(sizeof(TOKEN));
  int line = 1;
  int tokenCounter = 0;

  int isTokenErrorFound = FALSE;
  while (TRUE)
  {
    TOKEN currentToken = scanner(&buffer, &line);
    if (isVerboseModeSet)
    {
      printToken(currentToken);
    }
    if (currentToken.type == COMMENTARY)
    {
      continue;
    }
    tokenCounter++;
    tokens = realloc(tokens, tokenCounter * sizeof(TOKEN));
    tokens[tokenCounter - 1] = currentToken;

    int isErrorOrEOS = (currentToken.type == ERROR) || (currentToken.type == EOS);
    if (isErrorOrEOS)
    {
      if (currentToken.type == ERROR)
      {
        isTokenErrorFound = TRUE;
      }
      break;
    }
  }

  notifyTokensResult(isTokenErrorFound, fileName, line);

  if (!isTokenErrorFound)
  {
    parser();
    notifyParserResult(parserErrors);
  }

  return 1;
}

void setProgramLocal()
{
  setlocale(LC_ALL, "");
}

void setModes(int argc, char *argv[])
{
  int modesStartIndex = 2;
  for (int index = modesStartIndex; index < argc; index++)
  {
    if (isVerboseMode(argv[index]))
    {
      isVerboseModeSet = TRUE;
      continue;
    }

    if (isDebugMode(argv[index]))
    {
      isDebugModeSet = TRUE;
      continue;
    }
  }
}

int isVerboseMode(char *mode)
{
  return strcmp(mode, "/v") == 0;
}

int isDebugMode(char *mode)
{
  return strcmp(mode, "/d") == 0;
}

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

void printToken(TOKEN token)
{
  printf("Line:%3d | %-30s | %5ls\n", token.line, tokenToStr[token.type], token.value);
}

void notifyTokensResult(int isErrorFound, char *fileName, int line)
{
  if (!isErrorFound)
  {
    printf("[LEXICAL] Succesfully identified all %s tokens.\n", fileName);
  }
  else
  {
    printf("[LEXICAL] An error ocurred while trying to identify tokens on %s in line %d.\n", fileName, line);
  }
  if (!isVerboseModeSet)
  {
    printf("[LEXICAL] Run verbose mode (/v) to see results.\n");
  }
}

void notifyParserResult(int parserErrors)
{
  if (parserErrors > 0)
  {
    printf("[SINTAX] An syntax error ocurred.\n");
  }
  else
  {
    printf("[SINTAX] Program syntax is correct.\n");
  }
  if (!isDebugModeSet)
  {
    printf("[SINTAX] Run debug mode (/d) to see results.\n");
  }
}

int check(TOKEN_TYPE expectedTokenType)
{
  TOKEN_TYPE currentTokenType = tokens->type;

  int isExpectedToken = currentTokenType == expectedTokenType;
  if (isExpectedToken)
  {
    if (isDebugModeSet)
    {
      printf("[OK] value: %5ls | line: %3d\n", tokens->value, tokens->line);
    }
    tokens++;
    return isExpectedToken;
  }

  parserErrors++;
  printf("[ERROR] value: %5ls | line: %3d\n", tokens->value, tokens->line);
  tokens++;
  return isExpectedToken;
}

int id()
{
  return check(IDENTIFIER);
}

int tpo()
{
  switch (tokens->type)
  {
  case INTENGER_TYPE_SYMBOL:
    return check(INTENGER_TYPE_SYMBOL);
    break;
  case FLOAT_TYPE_SYMBOL:
    return check(FLOAT_TYPE_SYMBOL);
    break;
  case CHAR_TYPE_SYMBOL:
    return check(CHAR_TYPE_SYMBOL);
    break;
  default:
    break;
  }
}

int isTypeSymbol()
{
  return tokens->type == INTENGER_TYPE_SYMBOL || tokens->type == FLOAT_TYPE_SYMBOL || tokens->type == CHAR_TYPE_SYMBOL;
}

void dcl()
{
  check(VAR_SYMBOL);
  while (isTypeSymbol())
  {
    tpo();
    id();
    while (tokens->type == COMMA_SYMBOL)
    {
      check(COMMA_SYMBOL);
      id();
    }
    check(SEMICOLON_SYMBOL);
  }

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
    EXP();
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
    return check(MULTIPLIER_OP);
    break;
  case DIVISION_OP:
    return check(DIVISION_OP);
    break;
  case AND_OP:
    return check(AND_OP);
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
    return check(GREATER_THAN_OR_EQUAL_OP);
    break;
  case LESSER_OP:
    return check(LESSER_OP);
    break;
  case LESS_THAN_OR_EQUAL_OP:
    return check(LESS_THAN_OR_EQUAL_OP);
    break;
  case EQUALITY_OP:
    return check(EQUALITY_OP);
    break;
  case DIFF_OP:
    return check(DIFF_OP);
    break;
  default:
    return 0;
    break;
  }
}

void EXP()
{
  exps();
  while (opcat3())
  {
    exps();
  }
}

void f()
{
  id();
  check(PAREN_OPEN_SYMBOL);
  EXP();
  check(PAREN_CLOSED_SYMBOL);
}

void e()
{
  switch (tokens->type)
  {
  case STRING_SYMBOL:
    check(STRING_SYMBOL);
    break;
  case FLOAT:
    check(FLOAT);
    break;
  case INTENGER:
    check(INTENGER);
    break;
  case CHAR_SYMBOL:
    check(CHAR_SYMBOL);
    break;
  case IDENTIFIER:
    AF();
    break;
  default:
    tokens++;
    break;
  }
}

void rd()
{
  check(READ_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  id();
  check(PAREN_CLOSED_SYMBOL);
}

void wr()
{
  check(WRITE_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  e();
  while (tokens->type == COMMA_SYMBOL)
  {
    check(COMMA_SYMBOL);
    e();
  }
  check(PAREN_CLOSED_SYMBOL);
}

void IF()
{

  check(IF_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  EXP();
  check(PAREN_CLOSED_SYMBOL);
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
  EXP();
}

void fr()
{
  check(FOR_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  atr();
  check(SEMICOLON_SYMBOL);
  EXP();
  check(SEMICOLON_SYMBOL);
  atr();
  check(PAREN_CLOSED_SYMBOL);
  cmd();
}

void wh()
{
  check(WHILE_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  EXP();
  check(PAREN_CLOSED_SYMBOL);
  cmd();
}

void rpt()
{
  check(REPEAT_SYMPOL);
  cmd();
  check(SEMICOLON_SYMBOL);
  check(UNTIL_SYMBOL);
  check(PAREN_OPEN_SYMBOL);
  EXP();
  check(PAREN_OPEN_SYMBOL);
}

void AF()
{
  id();
  if (tokens->type == ATTRIB_OP)
  {
    check(ATTRIB_OP);
    EXP();
  }
  else if (tokens->type == PAREN_OPEN_SYMBOL)
  {
    check(PAREN_OPEN_SYMBOL);
    EXP();

    while (tokens->type == COMMA_SYMBOL)
    {
      check(COMMA_SYMBOL);
      EXP();
    }
    check(PAREN_CLOSED_SYMBOL);
  }
}

void cmd()
{
  switch (tokens->type)
  {
  case WRITE_SYMBOL:
    wr();
    break;
  case READ_SYMBOL:
    rd();
    break;
  case IF_SYMBOL:
    IF();
    break;
  case FOR_SYMBOL:
    fr();
    break;
  case WHILE_SYMBOL:
    wh();
    break;
  case REPEAT_SYMPOL:
    rpt();
    break;
  case IDENTIFIER:
    AF();
    break;
  case BEGIN_SYMBOL:
    bco();
  default:
    break;
  }
}

void rt()
{
  check(RETURN_SYMBOL);
  EXP();
  check(SEMICOLON_SYMBOL);
}

void bco()
{
  check(BEGIN_SYMBOL);
  while (tokens->type == WRITE_SYMBOL ||
         tokens->type == READ_SYMBOL ||
         tokens->type == IF_SYMBOL ||
         tokens->type == FOR_SYMBOL ||
         tokens->type == WHILE_SYMBOL ||
         tokens->type == REPEAT_SYMPOL ||
         tokens->type == IDENTIFIER)
  {
    cmd();
    check(SEMICOLON_SYMBOL);
  }
  if (tokens->type == RETURN_SYMBOL)
  {
    rt();
  }
  check(END_SYMBOL);
}

void sub()
{
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
  check(SEMICOLON_SYMBOL);
}

void ini()
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

void parser()
{
  ini();
}