#include <stdio.h>
#include <stdlib.h>
#include <string.h>

wchar_t *charToWChar(char *text)
{
  const size_t size = strlen(text) + 1;
  wchar_t *wText = malloc(sizeof(wchar_t) * size);
  mbstowcs(wText, text, size);
  return wText;
}