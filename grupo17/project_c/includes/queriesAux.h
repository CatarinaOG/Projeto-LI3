#ifndef QUERIESAUX
#define QUERIESAUX

#include <gmodule.h>
#include "stats.h"

typedef struct q4 *Query4;
typedef struct info_negocio *InfoNegocio;

//-------------------CampoNegocio-----------------
void addAllBusiness(GList* negocioss,GHashTable* tableReviews);

//-----------------------Query2-------------------
GList* searchletra(GHashTable *negocios,char c);

//-----------------------Query4-------------------
GList *procuranomebus(GHashTable* negocios,char**nome);
char ** procura(GHashTable* reviews,char*id);

//-----------------------Query5-------------------
GList* negocios_n_estrelas(int n, char *city, GHashTable *hash_cities);

//-----------------------Query6-------------------
GList* topNCampos(GList* negocios, int N);
void keepOnlyTopN(GList* listCidades,int N);
int comparaMediaEstrelas(gconstpointer a, gconstpointer b);

//-----------------------Query7-------------------
gboolean removeNaoBloqueados(gpointer key, gpointer value, gpointer user_data);

//-----------------------Query8-------------------
GList* keepOnlyTopM(GList* listCategories, int M);

//-----------------------Query9-------------------
int strsstrpos(char*haystack,char*needle);
int strstrpre(char *haystack,char*needle);

//-----------------------Gets------------------
char* getidq4(Query4 q);
char* getnameq4(Query4 q);
char *getInfoNegocioId(InfoNegocio infoneg);
char *getInfoNegocioNome(InfoNegocio infoneg);

#endif