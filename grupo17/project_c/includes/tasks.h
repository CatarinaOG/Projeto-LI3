#ifndef TASKS
#define TASKS

#include "sgr.h"

//-------------show-----------
void show(TABLE t);

//-------------toCSV-----------
void toCSV(TABLE t, char delim , char* file);

//-------------fromCSV-----------
TABLE fromCSV(char* file, char* delim);
int findColunas(char* line, char delim);

//-------------filter-----------
TABLE filter(TABLE t, char* coluna , char* valor , char* operador );
int colunaExists(TABLE t, char* coluna);
int operadorValido(char* op);
int matchTipos(char* valor, TABLE t);
char** copyArray ( char** linha , int* colunas );
int elimina (char** linha , int ind, int operador, int tiposDaoMatch, char* valor);

//-------------proj-----------
TABLE proj(TABLE t,int x);

//-------------index-----------
TABLE taskIndex(TABLE table, int linha, int coluna);

//----------------------Auxiliares interpretador------
char **getPart(char**arro,int x);
TABLE getShowN(TABLE t,int i);
int getPaginas(TABLE t);

#endif