#include "../includes/stats.h"

struct campoNegocio{
    char* business_id;
    char* business_name;
    char* city;
    char* estado;
    GList* categories;
    int nrReviews;
    float mediaEstrelas;
    GList* todasEstrelas;
};

struct campoUser{
    char* user_id;
    char* state;
    int bloqueado;
};


struct campoCategoria{
    char* category;
    GList* campos;    // lista de CampoNegocio
};

struct campoCidade{
    char* cidade;
    GList* campos;  // lista de CampoNegocio
};

//-----------------------------Ligação REVIEWS-NEGOCIOS   Estrutura: CampoNegocio-------------------------------------

// Calcula a média de um negócio
float media(GList* todasEstrelas, int nrEstrelas){

    float soma=0;

    for( ; todasEstrelas ; todasEstrelas = todasEstrelas->next){
        float* estrela = (float*) todasEstrelas->data;
        soma += *estrela;
    }
    return soma/nrEstrelas;
}

// Preenche um campo de Negocio que teve review
CampoNegocio fillCampoNegocio(REVIEW review, GHashTable* negocios){

    char* business_id = getBusinessID(review);
    float* stars = getStars(review);

    Business negocio = findNegocio(negocios,business_id);

    CampoNegocio campoNegocioAInserir = malloc(sizeof(struct campoNegocio));
    campoNegocioAInserir->business_id = strdup(business_id);
    campoNegocioAInserir->business_name = strdup(getBusinessName(negocio));
    campoNegocioAInserir->city = strdup(getBusinessCity(negocio));
    campoNegocioAInserir->estado = strdup(getBusinessState(negocio));
    campoNegocioAInserir->categories = getBusinessCategories(negocio);
    campoNegocioAInserir->nrReviews = 1;
    campoNegocioAInserir->mediaEstrelas = *stars;
    campoNegocioAInserir->todasEstrelas = NULL;
    campoNegocioAInserir->todasEstrelas = g_list_prepend(campoNegocioAInserir->todasEstrelas,stars);

return campoNegocioAInserir;
}

// Preenche um campo de Negocio que não teve review
CampoNegocio fillCampoNegocioVazio(Business negocio){

    CampoNegocio campo = malloc(sizeof(struct campoNegocio));
    campo->business_id = strdup(getBusinessId(negocio));
    campo->business_name = strdup(getBusinessName(negocio));
    campo->city = strdup(getBusinessCity(negocio));
    campo->estado = strdup(getBusinessState(negocio));
    campo->categories = getBusinessCategories(negocio);
    campo->mediaEstrelas = 0;
    campo->nrReviews = 0;
    campo->todasEstrelas = NULL;

return campo;
}

// Cria uma HashTable através das reviews com informaçao de cada negocio única
GHashTable* criaTableNegocios(GHashTable* negocios, GHashTable* reviewss){

    GHashTable* tableCampoNegocio = g_hash_table_new_full(g_str_hash,g_str_equal,destroyKeysNegocios,destroyValuesNegocios);
    GList* reviews = g_hash_table_get_values(reviewss);

    for( ; reviews ; reviews = reviews->next){

        REVIEW review = reviews->data;

        gboolean b = g_hash_table_contains(tableCampoNegocio,getBusinessID(review));

        if(b == TRUE){
            
            CampoNegocio campoNegocioExistente = g_hash_table_lookup(tableCampoNegocio,getBusinessID(review));

            float* stars = getStars(review);

            (campoNegocioExistente->nrReviews)++;
            campoNegocioExistente->todasEstrelas = g_list_prepend(campoNegocioExistente->todasEstrelas,stars);
            campoNegocioExistente->mediaEstrelas = media(campoNegocioExistente->todasEstrelas,campoNegocioExistente->nrReviews);
        }

        else{
            CampoNegocio campoNegocioAInserir = fillCampoNegocio(review,negocios);
            g_hash_table_insert(tableCampoNegocio,campoNegocioAInserir->business_id,campoNegocioAInserir);
        }
    }

    GList* listNegocios = g_hash_table_get_values(negocios);

    //Adiciona todos os negocios que não tiverem reviews
    addAllBusiness(listNegocios,tableCampoNegocio);

return tableCampoNegocio;
}

//-----------------------------Ligação REVIEWS-NEGOCIOS   Estrutura: CampoCidade-------------------------------------

GHashTable* criaTableCidades(GList* campo_negocio){

    GHashTable* tableCidades = g_hash_table_new_full(g_str_hash,g_str_equal,destroyCampoCidadeKeys,destroyCampoCidadeValues);

        for( ; campo_negocio; campo_negocio = campo_negocio->next){

        CampoNegocio campo = campo_negocio->data;
        char* cidadeDoCampo = getCampoNegocioCity(campo);
        gboolean b2 = g_hash_table_contains(tableCidades,cidadeDoCampo);

        if( b2 == TRUE ){

            CampoCidade cidadeExistente = g_hash_table_lookup(tableCidades,cidadeDoCampo);
            cidadeExistente->campos = g_list_prepend(cidadeExistente->campos,campo);
        }
        else{

            CampoCidade cidadeNova = malloc(sizeof(struct campoCidade));
            cidadeNova->cidade = strdup(cidadeDoCampo);
            cidadeNova->campos = NULL;
            cidadeNova->campos = g_list_prepend(cidadeNova->campos,campo);

            g_hash_table_insert(tableCidades,cidadeNova->cidade,cidadeNova); 
        }
    }
    return tableCidades;
}

//-----------------------------Ligação: REVIEWS-BUSINESS    Estrutura: CampoUser -------------------------------------


// Preenche um campo Estado inicial
void fillTableEstados(CampoUser user, GHashTable* negocios, REVIEW review){

    Business negocio = g_hash_table_lookup(negocios,getBusinessID(review));

    user->user_id = strdup(getUserID(review));
    user->state = strdup(getBusinessState(negocio));
    user->bloqueado = 0;
}

// Cria uma HashTable de Users cada um com um estado que bloqueia quando deu reviews em mais que um estado
GHashTable* criaTableEstados(GHashTable* negocios, GList* reviews){

    GHashTable* states = g_hash_table_new_full(g_str_hash,g_str_equal,destroyCampoUserKeys,destroyCampoUserValues);
      for( ; reviews ; reviews = reviews->next ){ 
          REVIEW review = reviews->data;

            char* id= getUserID(review);
            gboolean b = g_hash_table_contains(states,id);

            if( b==FALSE ){
                CampoUser estado = malloc(sizeof(struct campoUser));
                fillTableEstados(estado,negocios,review);
                g_hash_table_insert(states,strdup(estado->user_id),estado);
            }
            else{
            CampoUser user = malloc(sizeof(struct campoUser));
            user = g_hash_table_lookup(states,id);

            if(user->bloqueado == 0){
                Business negocio = g_hash_table_lookup(negocios,getBusinessID(review));

                if(strcmp(user->state,getBusinessState(negocio)) != 0) user->bloqueado = 1;
            }
          }
        }
    
return states;
}

//-----------------------------Ligação: REVIEWS-BUSINESS    Estrutura: campoCategoria -------------------------------------


// Cria uma HashTable com categorias e para cada uma os negocios que têm essa categoria
GHashTable* criaTableCategorias(GList* listCamposNegocio){

    GHashTable* tableCategories = g_hash_table_new_full(g_str_hash,g_str_equal,destroyCategorykey,destroyCategoryValue);

    for( ; listCamposNegocio ; listCamposNegocio = listCamposNegocio->next){

        CampoNegocio campoE = listCamposNegocio->data;
        GList* categorias = campoE->categories;

        for( ; categorias ; categorias = categorias->next){

            char* categoriaAtual = categorias->data;
            gboolean b3 = g_hash_table_contains(tableCategories,categoriaAtual);

            if( b3 == TRUE){
                CampoCategoria categoriaIgual = g_hash_table_lookup(tableCategories,categoriaAtual);
                categoriaIgual->campos = g_list_prepend(categoriaIgual->campos,campoE);
            }

            else{

                CampoCategoria newCategoria = malloc(sizeof(struct campoCategoria));
                newCategoria->category = strdup(categoriaAtual);
                newCategoria->campos = NULL;
                newCategoria->campos = g_list_prepend(newCategoria->campos,campoE);
                g_hash_table_insert(tableCategories,newCategoria->category,newCategoria);
            }
        }
    }
return tableCategories; 
}


//---------------------------------------CampoNegocio-----------------------------

char* getCampoNegocioBusiness_id(CampoNegocio campo){
    return campo->business_id;
}

char* getCampoNegocioBussiness_name(CampoNegocio campo){
    return campo->business_name;
}

char* getCampoNegocioCity(CampoNegocio campo){
    return campo->city;
}

char* getCampoNegocioEstado(CampoNegocio campo){
    return campo->estado;
}

int getCampoNegocioNrReviews(CampoNegocio campo){
    return campo->nrReviews;
}

float getCampoNegocioMediaEstrelas(CampoNegocio campo){
    return campo->mediaEstrelas;
}

GList* getCampoNegocioTodasEstrelas(CampoNegocio campo){

    GList* newList = NULL;

    for( ; campo->todasEstrelas ; campo->todasEstrelas = (campo->todasEstrelas)->next){

        int* estrela = (campo->todasEstrelas)->data;
        newList = g_list_prepend(newList,estrela);

    }
return newList;
}

//---------------------------------------CampoUser-----------------------------

int getCampoUserBloqueado(CampoUser user){
    return user->bloqueado;
}

char* getCampoUserUserId(CampoUser user){
    return user->user_id;
}


//---------------------------------------CampoCidade-----------------------------

char* getCidadesCity(CampoCidade cidade){
    return cidade->cidade;
}

GList* getCidadesNegocios(CampoCidade cidade){
    return cidade->campos;
}

void setCidadesNegocios(CampoCidade cidade , GList* list){
    cidade->campos = list;
}

//---------------------------------------CampoCategoria-----------------------------

void setCategoriasCampos(CampoCategoria categoria, GList* list){
    categoria->campos = list;
}

GList* getCategoriasNegocios(CampoCategoria categoria){
    return categoria->campos;
}

char* getCategoriaName(CampoCategoria categoria){
    return categoria->category;
}

// Auxiliar à Query 3
GList *id_negocio_info(GHashTable *hash_negocios, char *id){
    CampoNegocio neg = malloc(sizeof(struct campoNegocio));
    GList *infoDoNeg = NULL;
    
    if (g_hash_table_contains(hash_negocios, id)){ 
        CampoNegocio b = g_hash_table_lookup(hash_negocios, id);
        neg->business_id = id;
        neg->business_name = getCampoNegocioBussiness_name(b);
        neg->city = getCampoNegocioCity(b);
        neg->estado = getCampoNegocioEstado(b);
        neg->mediaEstrelas = getCampoNegocioMediaEstrelas(b);
        neg->nrReviews = getCampoNegocioNrReviews(b);
        neg->todasEstrelas = NULL; 
        infoDoNeg = g_list_prepend(infoDoNeg, neg);
    }
    else printf("Id inválido\n");
    return infoDoNeg;
}

//---------------------------------------Frees-----------------------------
//-------CampoNegocio-------

void destroyNegociosCategories( gpointer category){
    free( (char*) category);
}

void destroyNegociosAllStars(gpointer star){
    free( (float*) star );
}

void destroyKeysNegocios(gpointer id){
    free( (char*) id);
}

void destroyValuesNegocios(gpointer negocio){

    free( ((CampoNegocio) negocio)->business_name);
    free( ((CampoNegocio) negocio)->city);
    free( ((CampoNegocio) negocio)->estado);
    g_list_free_full ( ((CampoNegocio) negocio)->categories , destroyNegociosCategories);
    g_list_free_full( ((CampoNegocio) negocio)->todasEstrelas , destroyNegociosAllStars);
    free( (CampoNegocio) negocio);
}

//-------CampoCidade-------
void destroyCampoCidadeCampos( gpointer negocio){
    destroyValuesNegocios( (CampoNegocio) negocio);
}

void destroyCampoCidadeKeys(gpointer cidade){
    free( (char*) cidade);
}

void destroyCampoCidadeValues(gpointer cidade){
    g_list_free_full( ((CampoCidade) cidade)->campos , destroyCampoCidadeCampos);
}

//-------CampoUser-------


void destroyCampoUserKeys(gpointer user){
    free( (char*) user);
}

void destroyCampoUserValues(gpointer user){
    free( ((CampoUser) user)->state );
    free( ((CampoUser) user)->user_id );
    free( (CampoUser) user);
}

//-------CampoCategoria-------

void destroyCategorykey(gpointer category){
    free( (char*) category);
}

void destroyCategoryValue(gpointer Categoria){
    g_list_free_full( ((CampoCategoria) Categoria)->campos , destroyCategoryCampos );
}

void destroyCategoryCampos( gpointer negocio ){
    destroyValuesNegocios( (CampoNegocio) negocio);   
}
