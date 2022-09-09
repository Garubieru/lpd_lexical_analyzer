#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

wchar_t *charToWChar(const char *text)
{
  const size_t size = strlen(text) + 1;
  wchar_t *wText = malloc(sizeof(wchar_t) * size);
  mbstowcs(wText, text, size);
  return wText;
}

char *readFile(char *fileName)
{
  FILE *file = fopen(fileName, "r");

  if (fileName == NULL)
  {
    fprintf(stderr, "[ERROR] Provide a filename to be compiled.\n");
    exit(-1);
  }

  if (file == NULL)
  {
    fprintf(stderr, "[ERROR] File %s not found.\n", fileName);
    exit(-1);
  }

  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  rewind(file);

  char *buffer;
  buffer = malloc((fileSize) * sizeof(char));

  if (buffer == NULL)
  {
    exit(-1);
  }

  fread(buffer, sizeof(char), fileSize, file);
  fclose(file);

  return buffer;
}

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
  EOS,
  ERROR,
} TOKEN_TYPE;

typedef struct TOKEN
{
  int line;
  TOKEN_TYPE type;
  char value[20];
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
    "char"
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
    "end"
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
    "EOS",
    "ERROR",
};

int isSpace(char *character)
{
  return *character == ' ';
}

int isTab(char *character)
{
  return *character == '\t';
}

int isEndOfLine(char *character)
{
  return *character == '\n' || *character == '\r';
}

int isEndOfFile(char *character)
{
  return *character == EOF || *character == '\x0';
}

int isSumOp(char *character)
{
  return *character == '+';
}

int isDivisionOp(char *character)
{
  return *character == '/';
}

int isMultiplierOp(char *character)
{
  return *character == '*';
}

int isSubtractionOp(char *character)
{
  return *character == '-';
}

int isDot(char *character)
{
  return *character == '.';
}

int isOpenParenthesis(char *character)
{
  return *character == '(';
}

int isClosedParenthesis(char *character)
{
  return *character == ')';
}

int isDigit(char *character)
{
  return *character >= '0' && *character <= '9';
}

int isAlpha(char *character)
{
  return isalpha(*character);
}

int isExclamation(char *character)
{
  return *character == '!';
}

int isUnderline(char *character)
{
  return *character == '_';
}

int isEqual(char *character)
{
  return *character == '=';
}

int isSemicolonSymbol(char *character)
{
  return *character == ';';
}

int isDoubleQuoutes(char *character)
{
  return *character == '"';
}

int isRightArrow(char *character)
{
  return *character == '>';
}

int isLeftArrow(char *character)
{
  return *character == '<';
}

int isComma(char *character)
{
  return *character == ',';
}

int isMinus(char *character)
{
  return *character = '-';
}

int isStringEqual(char *string, char *stringToCompare)
{
  return strcmp(string, stringToCompare) == 0;
}

int isINTTypeSymbol(char *word)
{
  return isStringEqual(word, "int");
}

int isFLOATTypeSymbol(char *word)
{
  return isStringEqual(word, "float");
}

int isCHARSymbol(char *word)
{
  return isStringEqual(word, "char");
}

int isVOIDSymbol(char *word)
{
  return isStringEqual(word, "void");
}

int isPRGSymbol(char *word)
{
  return isStringEqual(word, "prg");
}

int isBEGINSymbol(char *word)
{
  return isStringEqual(word, "begin");
}

int isVARSymbol(char *word)
{
  return isStringEqual(word, "var");
}

int isSUBROTSymbol(char *word)
{
  return isStringEqual(word, "subrot");
}

int isIFSymbol(char *word)
{
  return isStringEqual(word, "if");
}

int isELSESymbol(char *word)
{
  return isStringEqual(word, "else");
}

int isFORSymbol(char *word)
{
  return isStringEqual(word, "for");
}

int isWHILESymbol(char *word)
{
  return isStringEqual(word, "while");
}

int isTHENSymbol(char *word)
{
  return isStringEqual(word, "then");
}

int isREPEATSymbol(char *word)
{
  return isStringEqual(word, "repeat");
}

int isUNTILSymbol(char *word)
{
  return isStringEqual(word, "until");
}

int isANDSymbol(char *word)
{
  return isStringEqual(word, "and");
}

int isORSymbol(char *word)
{
  return isStringEqual(word, "or");
}

int isNOTSymbol(char *word)
{
  return isStringEqual(word, "not");
}

int isREADSymbol(char *word)
{
  return isStringEqual(word, "read");
}

int isWRITESymbol(char *word)
{
  return isStringEqual(word, "write");
}

int isENDSymbol(char *word)
{
  return isStringEqual(word, "end");
}

int isRETURNSymbol(char *word)
{
  return isStringEqual(word, "return");
}

TOKEN scanner(char **buffer, int *line)
{
  TOKEN token;
  strcpy(token.value, "");
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
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = PAREN_CLOSED_SYMBOL;
  }
  else if (isSumOp(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SUM_OP;
  }
  else if (isMultiplierOp(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = MULTIPLIER_OP;
  }
  else if (isDivisionOp(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = DIVISION_OP;
  }
  else if (isSubtractionOp(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SUBTRACTION_OP;
  }
  else if (isAlpha(*buffer))
  {
    while (isAlpha(*buffer) || isDigit(*buffer) || isUnderline(*buffer))
    {
      strncat(token.value, *buffer, 1);
      (*buffer)++;
    }

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
    else
    {
      token.type = IDENTIFIER;
    }
  }
  else if (isDigit(*buffer))
  {
    while (isDigit(*buffer))
    {
      strncat(token.value, *buffer, 1);
      (*buffer)++;
    }
    token.type = INTENGER;
    if (isDot(*buffer))
    {
      strncat(token.value, *buffer, 1);
      (*buffer)++;
      while (isDigit(*buffer))
      {
        strncat(token.value, *buffer, 1);
        (*buffer)++;
      }
      token.type = FLOAT;
    }
  }
  else if (isOpenParenthesis(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = PAREN_OPEN_SYMBOL;
  }
  else if (isSemicolonSymbol(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = SEMICOLON_SYMBOL;
  }
  else if (isDot(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    token.type = DOT_SYMBOL;
  }
  else if (isEqual(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      strncat(token.value, *buffer, 1);
      token.type = EQUALITY_OP;
      (*buffer++);
    }
  }
  else if (isRightArrow(*buffer))
  {
    token.type = GREATHER_OP;
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      strncat(token.value, *buffer, 1);
      token.type = GREATER_THAN_OR_EQUAL_OP;
      (*buffer)++;
    }
  }
  else if (isLeftArrow(*buffer))
  {
    token.type = LESSER_OP;
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      token.type = LESS_THAN_OR_EQUAL_OP;
      strncat(token.value, *buffer, 1);
      (*buffer)++;
    }
    if (isMinus(*buffer))
    {
      token.type = ATTRIB_OP;
      strncat(token.value, *buffer, 1);
      (*buffer)++;
    }
  }
  else if (isComma(*buffer))
  {
    strncat(token.value, *buffer, 1);
    token.type = COMMA_SYMBOL;
    (*buffer)++;
  }
  else if (isExclamation(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    if (isEqual(*buffer))
    {
      strncat(token.value, *buffer, 1);
      token.type = DIFF_OP;
      (*buffer)++;
    }
  }
  else if (isDoubleQuoutes(*buffer))
  {
    strncat(token.value, *buffer, 1);
    (*buffer)++;
    while (isAlpha(*buffer) || isSpace(*buffer) || isDigit(*buffer))
    {
      strncat(token.value, *buffer, 1);
      (*buffer)++;
    }
  }
  else if (isEndOfFile(*buffer))
  {
    token.type = EOS;
    strcpy(token.value, "EOF");
  }

  token.line = *line;
  return token;
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  char *fileName = argv[1];
  int line = 1;
  char *buffer = readFile(fileName);

  TOKEN tk;
  do
  {
    tk = scanner(&buffer, &line);
    printf("Line:%3d | %-30s | %5s\n", tk.line, tokenToStr[tk.type], tk.value);
  } while ((tk.type != ERROR) && (tk.type != EOS));

  return 0;
}