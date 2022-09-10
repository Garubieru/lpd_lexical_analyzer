#ifndef SYMBOLCHECKERS_H_
#define SYMBOLCHECKERS_H_

int isStringEqual(wchar_t *string, wchar_t *stringToCompare);

int isINTTypeSymbol(wchar_t *word);

int isFLOATTypeSymbol(wchar_t *word);

int isCHARSymbol(wchar_t *word);

int isVOIDSymbol(wchar_t *word);

int isPRGSymbol(wchar_t *word);

int isBEGINSymbol(wchar_t *word);

int isVARSymbol(wchar_t *word);

int isSUBROTSymbol(wchar_t *word);

int isIFSymbol(wchar_t *word);

int isELSESymbol(wchar_t *word);

int isFORSymbol(wchar_t *word);

int isWHILESymbol(wchar_t *word);

int isTHENSymbol(wchar_t *word);

int isREPEATSymbol(wchar_t *word);

int isUNTILSymbol(wchar_t *word);

int isANDSymbol(wchar_t *word);

int isORSymbol(wchar_t *word);

int isNOTSymbol(wchar_t *word);

int isREADSymbol(wchar_t *word);

int isWRITESymbol(wchar_t *word);

int isENDSymbol(wchar_t *word);

int isRETURNSymbol(wchar_t *word);

#endif