#ifndef INTERPRETADOR
#define INTERPRETADOR

#include <stdio.h>
#include "sgr.h"
#include "tasks.h"
#include "apresentador.h"
#include "queriesAux.h"

//-----------Interpretador----------------
int interpretador();

//-----------Auxiliares----------------
//int isDelim( char* line);
char** getArguments(char** line);
void fillComandos(GHashTable* comandos);
void cleanLine(char* line);
int existsEqual(char* line);

//-----------Calls----------------
SGR callQuery1(char* var, char* line, SGR sgr);
void callQuery2a9(char* var, char* line, SGR sgr, int query);
void callShow(char** argumentos, SGR sgr);
void callToCSV(char** argumentos, SGR sgr);
void callFromCSV(char* var , char* line, SGR sgr);
void callProj(char* var,char* line, SGR sgr);
void callIndex(char* var,char* line, SGR sgr, char* tableVariable);
void callFilter (char* var , char* line , SGR sgr);

#endif