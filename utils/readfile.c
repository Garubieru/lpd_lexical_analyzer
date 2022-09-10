#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../protocols/char-to-wchar.h"

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