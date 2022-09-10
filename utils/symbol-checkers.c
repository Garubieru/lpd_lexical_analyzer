#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include "../protocols/char-to-wchar.h"

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