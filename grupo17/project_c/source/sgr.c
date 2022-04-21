#include "../includes/sgr.h"

struct sgr{
    char *sgr_name;
    GHashTable* users;
    GHashTable* negocios;
    GHashTable* reviews;
    GHashTable* tables;
    GHashTable* fullCityInfo;
    GHashTable* fullBusinessInfo;
    GHashTable* fullCategoryInfo;
};

struct table{
    char* variable;
    GList* tabela;
    int colunas;
    int linhas;
};

//-------------------------------------Query1------------------------------------------

void deleteTableKeys (gpointer variable){
    free ((char*) variable);
}

void freeLinhas (gpointer linha){

        /* Tentativa de free à table
        for(int i=0 ; (((char**) linha)[i]) != NULL ; i++)
        free( ((char**) linha)[i] ); 
        */

    free((char**) linha);
}

void deleteTableValues ( gpointer table ){
    free( ((TABLE) table)->variable );
    g_list_free( ((TABLE) table)->tabela);
    free( (TABLE) table);
}

SGR query1(char *users, char *businesses, char *reviews){
    SGR s = malloc(sizeof(struct sgr));
    s->users = readUsers(users);
    s->negocios = readBusiness(businesses);
    s->reviews = readReviews(s->users,s->negocios,reviews);
    s->tables = g_hash_table_new_full(g_str_hash,g_str_equal,deleteTableKeys,deleteTableValues);
    s->fullCityInfo = NULL;
    s->fullBusinessInfo = NULL;
    s->fullCategoryInfo = NULL;
    return s;
}

//-------------------------------------Query2------------------------------------------

TABLE query2ToTable(GList *negocios,char letra){
    TABLE t = createTable();
    char *titulo =malloc(sizeof(char)*100); 
    snprintf(titulo,100, "Negócios começados pela letra %c:",letra);
    GList *tabela = NULL;
    char**arr = malloc(sizeof(char*)*1);
    arr[0] = strdup(titulo);
    tabela = g_list_prepend(tabela,arr);
    
    for (;negocios!=NULL;negocios=negocios->next){
        char *s = negocios->data;
        char**arr = malloc(sizeof(char*)*1);
        arr[0] = strdup(s);
        tabela = g_list_prepend(tabela,arr);
    }
    tabela = g_list_reverse(tabela);
    guint size = g_list_length(tabela) -1;
    char *numero = malloc(sizeof(char)*100); 
    snprintf(numero,100,"Número de negócios: %d",size);
    char**arr1 = malloc(sizeof(char*)*1);
    arr1[0] = strdup(numero);
    tabela = g_list_append(tabela,arr1);
    setTableTabela(t,tabela);

g_list_free(negocios);
free(titulo);
free(numero);

return t;
}

TABLE query2(SGR sgr,char letra){     
    GHashTable* negocios = sgr->negocios;         
    GList *letra_negocio = searchletra(negocios,letra);
    TABLE q2 = query2ToTable(letra_negocio,letra);
    q2->colunas = 1;
    q2->linhas = g_list_length(letra_negocio);

return q2;
}

//-------------------------------------Query3------------------------------------------

TABLE query3ToTable(GList* list){
    TABLE t = createTable();
    GList* tabela = NULL;
    char **titulos = malloc(sizeof(char*) * 5);
    
    titulos[0] = strdup("Nome");
    titulos[1] = strdup("Cidade");
    titulos[2] = strdup("Estado");
    titulos[3] = strdup("Estrelas");
    titulos[4] = strdup("Número total de Reviews");
    
    tabela = g_list_prepend(tabela,titulos);
    
    for(; list; list = list->next){   
        CampoNegocio negocio = list->data;
        char** arr = malloc(sizeof(char*) * 5);

        float mediaEstrelas = getCampoNegocioMediaEstrelas(negocio);
        char* mediaEstrelasChar = malloc(sizeof(char)*4);
        snprintf(mediaEstrelasChar ,4, "%1.1f",mediaEstrelas);

        int nrReviews = getCampoNegocioNrReviews(negocio);
        char* nrReviewsChar = malloc(sizeof(char) * 4);
        snprintf(nrReviewsChar ,4, "%d",nrReviews);

        arr[0] = strdup(getCampoNegocioBussiness_name(negocio));
        arr[1] = strdup(getCampoNegocioCity(negocio));
        arr[2] = strdup(getCampoNegocioEstado(negocio));
        arr[3] = mediaEstrelasChar;
        arr[4] = nrReviewsChar;

        tabela = g_list_prepend(tabela,arr);
    }

    g_list_free(list);
    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);
return t;
}

TABLE query3(SGR sgr, char *id){
    
    GHashTable* businesses = sgr->negocios;
    GHashTable* reviews = sgr->reviews;
    GHashTable *hash_negocios;

    // Cria hashTable com todos os negocios e as suas informações 
	if(sgr->fullBusinessInfo == NULL) sgr->fullBusinessInfo = criaTableNegocios(businesses,reviews);
    hash_negocios = sgr->fullBusinessInfo;
   
    GList *neg = id_negocio_info(hash_negocios,id);
    TABLE t = query3ToTable(neg);
    t->colunas = 5;
    t->linhas = 2;

    return t;
}

//-------------------------------------query4------------------------------------------
TABLE query4ToTable(GList *listaQ4){
    TABLE t = createTable();
    GList *tabela = NULL;
    char**arr = malloc(sizeof(char*)*2);
    arr[0] = strdup("ID de negócio:     \t");
    arr[1] = strdup("Nome do negócio:");
    tabela = g_list_prepend(tabela,arr);

    for(;listaQ4!=NULL;listaQ4=listaQ4->next){
        Query4 q = listaQ4->data;
        char *s = getidq4(q);
        char *f = getnameq4(q);
        char**arr = malloc(sizeof(char*)*2);
        arr[0] = strdup(s);
        arr[1] = strdup(f);
        free(q);
        tabela = g_list_prepend(tabela,arr); 
    }

    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

return t;
}


TABLE query4(SGR sgr,char *userid){
    GHashTable * reviews = sgr->reviews; 
    GHashTable * negocios = sgr->negocios;    
    char **arr = procura(reviews,userid);
    GList *lista_q4 = procuranomebus(negocios,arr);
    TABLE q4 = query4ToTable(lista_q4);
    q4 -> colunas = 2;
    q4->linhas = g_list_length(lista_q4);
    return q4; 
}

//-------------------------------------query5------------------------------------------
TABLE query5ToTable(GList* list){

    TABLE t = createTable();
    GList* tabela = NULL;
    
    char **titulos = malloc(sizeof(char*) * 2);
    titulos[0] = strdup("Id de Negócio");
    titulos[1] = strdup("Nome do Negócio");

    tabela = g_list_prepend(tabela,titulos);

    for(; list; list = list->next){

        InfoNegocio info_neg = list->data;
        char** arr = malloc(sizeof(char*) * 2);
        arr[0] = strdup(getInfoNegocioId(info_neg));
        arr[1] = strdup(getInfoNegocioNome(info_neg));
        tabela = g_list_prepend(tabela,arr);
        free(info_neg);
    }
    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

return t;
}

TABLE query5(SGR sgr, float stars, char *city){

    GHashTable* businesses = sgr->negocios;
    GHashTable* reviews = sgr->reviews;
	GHashTable *hash_negocios;
	GHashTable *hash_cities;

    // Cria hashTable com todos os negocios e as suas informações
	if(sgr->fullBusinessInfo == NULL) sgr->fullBusinessInfo = criaTableNegocios(businesses,reviews);
    hash_negocios = sgr->fullBusinessInfo;

    GList *values = g_hash_table_get_values(hash_negocios);

    // Cria hashTable com todas as cidades e as suas informações
    if(sgr->fullCityInfo == NULL) sgr->fullCityInfo = criaTableCidades(values);
    hash_cities= sgr->fullCityInfo;

    GList *info = negocios_n_estrelas(stars, city, hash_cities);
    TABLE t = query5ToTable(info);
    t->colunas = 2;
    t->linhas = g_list_length(info);
    
    return t;
} 

//-------------------------------------query6------------------------------------------
TABLE query6ToTable(GList* list){

    TABLE t = createTable();
    GList* tabela = NULL;

    char* cidade = strdup("Business_city");
    char* b_id = strdup("Business_id");
    char* b_name = strdup("Business_name");
    char* b_stars = strdup("nr_of_stars");

    char**arr = malloc(sizeof(char*)*4);
    arr[0] = strdup(cidade);
    arr[1] = strdup(b_id);
    arr[2] = strdup(b_name);
    arr[3] = strdup(b_stars);

    tabela = g_list_prepend(tabela,arr);

    for( ; list ; list = list->next){

        CampoCidade cidade = list->data;
        GList* negocios = getCidadesNegocios(cidade);

            for( ; negocios ; negocios = negocios->next ){

                CampoNegocio c = negocios->data;
                char** arr = malloc(sizeof(char*)*4);
                double mediaEstrelas = getCampoNegocioMediaEstrelas(c);
                char* mediaEstrelasChar = malloc(sizeof(char)*4);
                snprintf(mediaEstrelasChar ,4, "%1.1f",mediaEstrelas);

                arr[0] = strdup(getCampoNegocioCity(c));
                arr[1] = strdup(getCampoNegocioBusiness_id(c));
                arr[2] = strdup(getCampoNegocioBussiness_name(c));
                arr[3] = strdup(mediaEstrelasChar);
                tabela = g_list_prepend(tabela,arr);
            }
    }
    t->colunas = 4;
    t->linhas = g_list_length(tabela);
    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

return t;
}


TABLE query6( SGR sgr , int N){

    GHashTable* negocios = sgr->negocios;
    GHashTable* reviews = sgr->reviews;

    // Cria hashTable com todos os negocios e as suas info
    if( sgr->fullBusinessInfo == NULL) sgr->fullBusinessInfo = criaTableNegocios(negocios,reviews);
    GHashTable* tableBusinesses = sgr->fullBusinessInfo;
    GList* listBusinessses = g_hash_table_get_values(tableBusinesses);

    // Cria hashTable com todas as cidades e as suas info
    if( sgr->fullCityInfo == NULL) sgr->fullCityInfo = criaTableCidades(listBusinessses);
    GHashTable* table_cidades = sgr->fullCityInfo;
    GList* listCidades = g_hash_table_get_values(table_cidades);

    // Guarda apenas os topN negocios em cada cidade
    keepOnlyTopN(listCidades,N);
    TABLE t = query6ToTable(listCidades);

return t;
}

//-------------------------------------query7------------------------------------------

TABLE query7ToTable(GList* list){
    TABLE t = createTable();
    GList *tabela = NULL;

    char *titulo = strdup("International Users");

    char**arr = malloc(sizeof(char*)*1);
    arr[0] = strdup(titulo);
    tabela = g_list_prepend(tabela,arr);

    for ( ; list ; list=list->next){
        CampoUser user = list->data;
        char**arr = malloc(sizeof(char*)*1);
        arr[0]=strdup(getCampoUserUserId(user));
        tabela = g_list_prepend(tabela,arr);
    }

    t->colunas = 1;
    t->linhas = g_list_length(tabela);
    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

return t;
}

TABLE query7(SGR sgr){
    GHashTable* negocioss = sgr->negocios;
    GHashTable* reviewss = sgr->reviews;
    GList* reviews = g_hash_table_get_values(reviewss);

    // Cria hashTable com todos os users e as suas info
    GHashTable* hashStates = criaTableEstados(negocioss,reviews);

    // Remove todos os users que não tenham visitado mais que 1 estado
    g_hash_table_foreach_remove(hashStates,removeNaoBloqueados,NULL);

    GList* listStates = g_hash_table_get_values(hashStates);
    TABLE t = query7ToTable(listStates);

return t;
}

//-------------------------------------query8------------------------------------------

TABLE query8ToTable(GList* list){

    TABLE t = createTable();
    GList* tabela = NULL;

    char* b_id = strdup("Business_id");
    char* b_name = strdup("Business_name");
    char* b_stars = strdup("nr of stars");

    char**arr = malloc(sizeof(char*)*3);
    arr[0] = strdup(b_id);
    arr[1] = strdup(b_name);
    arr[2] = strdup(b_stars);

    tabela = g_list_prepend(tabela,arr);

    for( ; list ; list = list->next){

        CampoNegocio negocio = list->data;

        char** arr = malloc(sizeof(char*)*3);
        float mediaEstrelas = getCampoNegocioMediaEstrelas(negocio);
        char* mediaEstrelasChar = malloc(sizeof(char)*4);
        snprintf(mediaEstrelasChar ,4, "%1.1f",mediaEstrelas);

        arr[0] = strdup(getCampoNegocioBusiness_id(negocio));
        arr[1] = strdup(getCampoNegocioBussiness_name(negocio));
        arr[2] = mediaEstrelasChar;
        tabela = g_list_prepend(tabela,arr);
    }
    t->colunas = 3;
    t->linhas = g_list_length(tabela);

    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

return t;
}


TABLE query8 (SGR sgr, int M, char* category){

    GHashTable* negocioss = sgr->negocios;
    GHashTable* reviews = sgr->reviews;
    GList* negocios = g_hash_table_get_values(negocioss);
    
    // Cria hashTable com todos os negocios e as suas info
    if( sgr->fullBusinessInfo == NULL) sgr->fullBusinessInfo = criaTableNegocios(negocioss,reviews);
    GHashTable* tableBusinesses = sgr->fullBusinessInfo;
    GList* listBusinesses = g_hash_table_get_values(tableBusinesses);

    // Cria hashTable com todas as categorias e os seus negocios
    if( sgr->fullCategoryInfo == NULL) sgr->fullCategoryInfo = criaTableCategorias(listBusinesses);
    GHashTable* tableCategories = sgr->fullCategoryInfo;
    
    // Encontra a categoria desejada
    CampoCategoria categoria = g_hash_table_lookup(tableCategories,category);

    // Lista de negocios dessa mesma categoria
    GList* listNegocios = getCategoriasNegocios(categoria);

    // Guarda apenas os topM negocios dessa categoria
    GList* newList = keepOnlyTopM(listNegocios,M);

    TABLE t = query8ToTable(newList);
    
return t;
}

//------------------------------------query9------------------------------------------
TABLE query9ToTable(GList *reviews,char *palavra){
    TABLE t = createTable();
    char *titulo =malloc(sizeof(char)*100); 
    snprintf(titulo,100,"IDs de review onde é mencionada a palavra %s :",palavra);
    GList *tabela = NULL;
    char**arr = malloc(sizeof(char*)*1);
    arr[0] = strdup(titulo);
    tabela = g_list_prepend(tabela,arr);

    for (;reviews!=NULL;reviews=reviews->next){
        char *s = reviews->data;
        char**arr = malloc(sizeof(char*)*1);
        arr[0]=strdup(s);
        tabela = g_list_prepend(tabela,arr);
    }

    tabela = g_list_reverse(tabela);
    setTableTabela(t,tabela);

free(titulo);
return t;
}

TABLE query9(SGR sgr,char *word){   
    if (word==NULL){printf("A palavra inserida não é válida");return NULL;}     
    GList *ids = NULL;
    GHashTable *reviews = sgr->reviews;
    GList *reviews_list = g_hash_table_get_values(reviews);

    for (;reviews_list!=NULL;reviews_list=reviews_list->next){
        gpointer elem = reviews_list->data;
        REVIEW revp = elem;  

        if (!strstrpre(getText(revp),word)&& !strsstrpos(getText(revp),word))
            ids = g_list_prepend(ids,getReviewID(revp));
    }

    TABLE q9 = query9ToTable(ids,word);
    q9->colunas = 1;
    q9->linhas = g_list_length(ids); 
    g_list_free(reviews_list);
    return q9;  
}

//---------------------------------------SGR-----------------------------

SGR createSGR(){
    return malloc(sizeof(struct sgr));
}

GHashTable *getbus (SGR sgr){
    return sgr->negocios;
}

GHashTable *getuser (SGR sgr){
    return sgr->users;
}
void setSGRName(SGR s, char* nome){
    s->sgr_name = strdup(nome);
}

char* getSGRName(SGR sgr){
    return sgr->sgr_name;
}

void addTableToSGR(SGR sgr,TABLE table){
    g_hash_table_insert(sgr->tables,strdup(table->variable),table);
}

TABLE getTableFromSGR(SGR sgr, char* tableVariable){
    return g_hash_table_lookup(sgr->tables,tableVariable);
}

void setfullBusinessInfo(SGR sgr, GHashTable *full_business_info){
    sgr->fullBusinessInfo = full_business_info;
}

void setfullCityInfo(SGR sgr, GHashTable *full_city_info){
    sgr->fullCityInfo = full_city_info;
}

void destroySGR(SGR sgr){

        if(sgr!=NULL){
        free(sgr->sgr_name);
        if(sgr->users != NULL) g_hash_table_destroy( sgr->users );
        if(sgr->negocios != NULL) g_hash_table_destroy( sgr->negocios );
        if(sgr->reviews != NULL) g_hash_table_destroy( sgr->reviews );
        //if(sgr->tables != NULL) g_hash_table_destroy( sgr->tables );
        //if(sgr->fullCityInfo != NULL) g_hash_table_destroy( sgr->fullCityInfo );
        //if(sgr->fullBusinessInfo != NULL) g_hash_table_destroy( sgr->fullBusinessInfo );
        //free(sgr);
    }}

//---------------------------------------TABLE-----------------------------

TABLE createTable(){
    TABLE t = malloc(sizeof(struct table)); 
    return t;
}

void setTableTabela(TABLE t, GList* list){
    t->tabela = NULL;
    t->tabela = list;
}

void setTableVariable(TABLE table, char* variable){
    table->variable = strdup(variable);
}

GList *getTabela(TABLE t){
    return t->tabela;    
} 

int getColunas(TABLE t){
    return t->colunas;    
}

int getLinhas(TABLE t){
    return t->linhas;    
}

void setTabela(GList*x,TABLE t){
    t->tabela = x;    
}

void setLinhas(TABLE x, int lin){
    x->linhas = lin;    
}

void setColunas(TABLE x, int col){
    x->colunas = col;    
}

gboolean variavelExiste ( char* variable, SGR sgr){

    GHashTable* t = sgr->tables;

return g_hash_table_contains(t,variable);
}
