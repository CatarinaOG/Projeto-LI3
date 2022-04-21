#ifndef SGRH
#define SGRH

#include <gmodule.h> 
#include "business.h"
#include <math.h>
#include "users.h" 
#include "reviews.h"
#include "stats.h"

typedef struct sgr *SGR;
typedef struct table *TABLE;

//------------------------queries--------------------
SGR query1(char *users, char *businesses, char *reviews);
TABLE query2(SGR sgr,char letra);
TABLE query3(SGR sgr, char *id);
TABLE query4(SGR sgr,char *userid);
TABLE query5(SGR sgr, float stars, char *city);
TABLE query6( SGR sgr , int N);
TABLE query7(SGR sgr);
TABLE query8 (SGR sgr, int M, char* category);
TABLE query9(SGR sgr,char *word);
//--------------------------SGR-------------------------
SGR createSGR();
void setSGRName(SGR s, char* nome);
char* getSGRName(SGR sgr);
void addTableToSGR(SGR sgr,TABLE table);
TABLE getTableFromSGR(SGR sgr, char* tableVariable);
void setfullBusinessInfo(SGR sgr, GHashTable *full_business_info);
void setfullCityInfo(SGR sgr, GHashTable *full_city_info);
void destroySGR(SGR sgr);
//--------------------------TABLE-------------------------
TABLE createTable();
void setTableTabela(TABLE t, GList* list);
void setTableVariable(TABLE table, char* variable);
GList *getTabela(TABLE t);
int getLinhas(TABLE t);
int getColunas(TABLE t);
void setTabela(GList*x,TABLE t);
void setLinhas(TABLE x, int lin);
void setColunas(TABLE x, int col);
gboolean variavelExiste ( char* variable, SGR sgr);




#endif
