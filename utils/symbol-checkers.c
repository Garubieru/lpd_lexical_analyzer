#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include "../protocols/char-to-wchar.h"

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

int isStringEqual(wchar_t *string, wchar_t *stringToCompare)
{
  return wcscmp(string, stringToCompare) == 0;
}

int isINTTypeSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[INT_ID]));
}

int isFLOATTypeSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[FLOAT_ID]));
}

int isCHARSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[CHAR_ID]));
}

int isVOIDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[VOID_ID]));
}

int isPRGSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[PRG_ID]));
}

int isBEGINSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[BEGIN_ID]));
}

int isVARSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[VAR_ID]));
}

int isSUBROTSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[SUBROT_ID]));
}

int isIFSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[IF_ID]));
}

int isELSESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[ELSE_ID]));
}

int isFORSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[FOR_ID]));
}

int isWHILESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[WHILE_ID]));
}

int isTHENSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[THEN_ID]));
}

int isREPEATSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[REPEAT_ID]));
}

int isUNTILSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[UNTIL_ID]));
}

int isANDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[AND_ID]));
}

int isORSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[OR_ID]));
}

int isNOTSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[NOT_ID]));
}

int isREADSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[READ_ID]));
}

int isWRITESymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[WRITE_ID]));
}

int isENDSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[END_ID]));
}

int isRETURNSymbol(wchar_t *word)
{
  return isStringEqual(word, charToWChar(reservedIdentifiers[RETURN_ID]));
}