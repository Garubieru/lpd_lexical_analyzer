#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

wchar_t *charToWChar(char *text)
{
  const size_t size = strlen(text) + 1;
  wchar_t *wText = malloc(sizeof(wchar_t) * size);
  mbstowcs(wText, text, size);
  return wText;
}

wchar_t *readFile(char *fileName)
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

  return charToWChar(buffer);
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
    "CHAR_SYMBOL",
    "COMMENTARY",
    "EOS",
    "ERROR",
};

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

int isStringEqual(wchar_t *string, wchar_t *stringToCompare)
{
  return wcscmp(string, stringToCompare) == 0;
}

int isINTTypeSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("int"));
}

int isFLOATTypeSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("float"));
}

int isCHARSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("char"));
}

int isVOIDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("void"));
}

int isPRGSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("prg"));
}

int isBEGINSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("begin"));
}

int isVARSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("var"));
}

int isSUBROTSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("subrot"));
}

int isIFSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("if"));
}

int isELSESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("else"));
}

int isFORSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("for"));
}

int isWHILESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("while"));
}

int isTHENSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("then"));
}

int isREPEATSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("repeat"));
}

int isUNTILSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("until"));
}

int isANDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("and"));
}

int isORSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("or"));
}

int isNOTSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("not"));
}

int isREADSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("read"));
}

int isWRITESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("write"));
}

int isENDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("end"));
}

int isRETURNSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar("return"));
}

int isSpecialCharacter(wchar_t *character)
{
  return (*character == 33) ||
         (*character >= 35 && *character <= 47) ||
         (*character >= 58 && *character <= 64) ||
         (*character >= 91 && *character <= 96) ||
         (*character >= 123 && *character <= 126);
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