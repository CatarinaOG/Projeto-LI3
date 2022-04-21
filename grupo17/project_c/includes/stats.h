#ifndef STATS
#define STATS
#include "business.h"
#include "reviews.h"
#include "business.h"
#include "queriesAux.h"

typedef struct campoNegocio *CampoNegocio;
typedef struct campoUser *CampoUser;
typedef struct campoCategoria *CampoCategoria;
typedef struct campoCidade *CampoCidade;

//------------Ligação REVIEWS-NEGOCIOS   Estrutura: CampoNegocio----------------
CampoNegocio fillCampoNegocio(REVIEW review, GHashTable* negocios);
CampoNegocio fillCampoNegocioVazio(Business negocio);
GHashTable* criaTableNegocios(GHashTable* negocios, GHashTable* reviews);

//-----------------Ligação REVIEWS-NEGOCIOS   Estrutura: CampoCidade------------------
GHashTable* criaTableCidades(GList* camposestrelas);

//-----------------Ligação: REVIEWS-BUSINESS    Estrutura: CampoUser---------------
GHashTable* criaTableEstados(GHashTable* negocios, GList* reviews);

//--------------Ligação: REVIEWS-BUSINESS    Estrutura: CampoCategoria---------------
GHashTable* criaTableCategorias(GList* listCamposNegocio);



//----------------------------------CampoNegocio-----------------------------
char* getCampoNegocioBusiness_id(CampoNegocio campo);
char* getCampoNegocioBussiness_name(CampoNegocio campo);
char* getCampoNegocioCity(CampoNegocio campo);
char* getCampoNegocioEstado(CampoNegocio campo);
int getCampoNegocioNrReviews(CampoNegocio campo);
float getCampoNegocioMediaEstrelas(CampoNegocio campo);
GList* getCampoNegocioTodasEstrelas(CampoNegocio campo);
//------------------------------------CampoUser----------------------------------
int getCampoUserBloqueado(CampoUser user);
char* getCampoUserUserId(CampoUser user);
//------------------------------------CampoCidade----------------------------------
char* getCampoCidadeCity(CampoCidade cidade);
GList* getCidadesNegocios(CampoCidade cidade);
void setCidadesNegocios(CampoCidade cidade , GList* list);
//----------------------------------CampoCategoria---------------------------------
void setCampoCategoriaCampos(CampoCategoria categoria, GList* list);
GList* getCategoriasNegocios(CampoCategoria categoria);
char* getCategoriaName( CampoCategoria categoria);


//----------------------------------frees---------------------------------
//-------CampoNegocio-------
void destroyNegociosCategories( gpointer category);
void destroyNegociosAllStars(gpointer star);
void destroyKeysNegocios(gpointer id);
void destroyValuesNegocios(gpointer negocio);

//-------CampoCidade-------
void destroyCampoCidadeCampos( gpointer negocio);
void destroyCampoCidadeKeys(gpointer cidade);
void destroyCampoCidadeValues(gpointer cidade);

//-------Estados-------
void destroyCampoUserKeys(gpointer estado);
void destroyCampoUserValues(gpointer estado);
//-------CampoCategoria-------
void destroyCategorykey(gpointer category);
void destroyCategoryValue(gpointer Categoria);
void destroyCategoryCampos( gpointer negocio );


//-------------------------------auxiliares temporarias------------------------------
// Query 3
GList *id_negocio_info(GHashTable *hash_reviews, char *id);

#endif 