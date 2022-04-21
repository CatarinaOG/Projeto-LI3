#include "../includes/queriesAux.h"

//---------------------------------------Estruturas---------------------------
struct q4{
    char *id;
    char *name;
};

struct info_negocio{
    char *id;
    char *nome;
};

//-----------------------------------Funções Auxiliares----------------------------------


//-------------------CampoNegocio-----------------

// Adiciona todos os negócios sem revies à Hashtable com todos os negócios 
void addAllBusiness(GList* negocios, GHashTable* tableNegocios){

    for( ; negocios ; negocios = negocios->next){

        Business negocio = negocios->data;

        gboolean b = g_hash_table_contains(tableNegocios,getBusinessId(negocio));

        if( b == FALSE){

            CampoNegocio campo = fillCampoNegocioVazio(negocio);
            char* business_idDoCampo = getCampoNegocioBusiness_id(campo);
            g_hash_table_insert(tableNegocios,business_idDoCampo,campo);
        }
    }
}

//-----------------------query2-------------------
// Compara strings no case sensitive
int comparechar(char *c,char*s){
        
    char cs[strlen(c)];
    char ss[strlen(s)];
    strcpy(ss,s);
    strcpy(cs,c);

    for(int i = 0; cs[i]; i++){
        cs[i] = tolower(cs[i]);
    }

    for(int i = 0; ss[i]; i++){
        ss[i] = tolower(ss[i]);
    }
    if (!(strncmp(cs,ss,1))){return 0;}
    else return 1;
}

// Compara letra recebida com a primeira letra do nome de cada negócio
GList * searchletra(GHashTable *negocios,char c){
    char arr[2];
    arr[0] = c;
    arr[1] = '\0';
    GList *t = NULL;
    GList *l = g_hash_table_get_values (negocios);

    for ( ; l != NULL; l = l->next){
        gpointer elem = l->data;
        Business buss = elem;
            if (!(comparechar(arr,getBusinessName(buss))))
                t = g_list_prepend(t,getBusinessName(buss));
    }
    g_list_free(l);
    return t;
}

//-----------------------query4-------------------
// Procura nome de negócio associado ao id de negócio
GList *procuranomebus(GHashTable* negocios,char**nome){
    int j = 0;
    GList *l = g_hash_table_get_values (negocios);
    GList *t = NULL;

    while(strcmp(nome[j],"fim")){
        for (; l != NULL; l = l->next) {
            gpointer elem = l->data;
            Business buss = elem;
                
            if (!(strcmp(nome[j],getBusinessId(buss)))){
            
                Query4 q = malloc(sizeof(struct q4));
                q -> id = strdup(nome[j]);
                q -> name = strdup(getBusinessName(buss));
                t = g_list_prepend(t,q);
                j++;
                l = g_list_first(l);
                break;
            } 
        }
    }
    g_list_free(l);
    free(nome);
    return t; 
}

// Procura id de negócio associado ao id de utilizador recebido 
char ** procura(GHashTable* reviews,char*id){
    char **nome = NULL;
    GList *y = g_hash_table_get_values(reviews);
    int j = 0;
    for (;y!=NULL;y=y->next){
        gpointer elem = y->data;
        REVIEW rev = elem;

        if (!(strcmp(id,getUserID(rev)))){
            nome =realloc(nome,sizeof(char**)*(j+2));
            nome[j]=getBusinessID(rev);
            j++;
        }   
    }
    g_list_free(y);
    nome[j++]= "fim";
    return nome;
}

//-----------------------query5-------------------
// Retorna lista com os negocios da cidade com n ou mais estrelas
GList* negocios_n_estrelas(int n, char *city, GHashTable *hashCities){
    GList *info = NULL;
    if(g_hash_table_contains(hashCities, city)){
        CampoCidade cidade = g_hash_table_lookup(hashCities, city);
        GList *negocios = getCidadesNegocios(cidade);

        for(; negocios; negocios = negocios->next){
            CampoNegocio negocio = negocios->data;

            if(getCampoNegocioMediaEstrelas(negocio) >= n){
                InfoNegocio infoNegocio = malloc(sizeof(struct info_negocio));
                infoNegocio->id = getCampoNegocioBusiness_id(negocio);
                infoNegocio->nome = getCampoNegocioBussiness_name(negocio);
                info = g_list_prepend(info, infoNegocio);
            }
        }
    }
    else printf("Cidade inválida!\n");
    return info;
} 

//-----------------------query6-------------------
// Retorna uma lista com os top n negócios 
GList* topNCampos(GList* negocios, int N){

    GList* new = NULL;

    for( ; N>0 && negocios ; negocios = negocios->next , N--){
        CampoNegocio negocio = negocios->data;

        new = g_list_append(new,negocio);
    }
return new;
}

// Atualiza lista, ordenando e mantendo apenas os top n negócios
void keepOnlyTopN(GList* listCidades, int N){
    
    for( ; listCidades ; listCidades = listCidades->next){

        CampoCidade cidade = listCidades->data;

        GList* listOrdenada = g_list_sort(getCidadesNegocios(cidade),comparaMediaEstrelas);
        GList* topCampos = topNCampos(listOrdenada,N);
        setCidadesNegocios(cidade,topCampos);
    }
}

// Compara dois negócios relativamente à sua média de estrelas 
int comparaMediaEstrelas(gconstpointer a, gconstpointer b){

    CampoNegocio campoA = (CampoNegocio) a;
    CampoNegocio campoB = (CampoNegocio) b;

    float mediaA = getCampoNegocioMediaEstrelas(campoA);
    float mediaB = getCampoNegocioMediaEstrelas(campoB);

return mediaB-mediaA > 0 ? 1 : -1;
}

//-----------------------query7-------------------

// Função utilizada para eliminar todos os CampoUser que não tenham visitado mais que um estado
gboolean removeNaoBloqueados(gpointer key, gpointer value, gpointer user_data){
    char *username = key;
    user_data = NULL;
    CampoUser user = (CampoUser) value;
    int blocked = getCampoUserBloqueado(user);

    return blocked == 0 ? TRUE : FALSE;
}

//-----------------------query8-------------------

// Retorna uma lista ordenada com apenas os top m negócios 
GList* keepOnlyTopM(GList* listNegocios, int M){
    
    return topNCampos(g_list_sort(listNegocios,comparaMediaEstrelas),M);
}

//-----------------------query9-------------------

// Verifica se a palavra apontada pelo strstr é uma palavra completa
int strstrpre(char *haystack,char*needle){  
    char*f = strstr(haystack,needle);
    int x = strlen(needle);
    int z = 1;
    char *t = f-1;
    if (f!=NULL){

        if(!isalpha(t[0]) && t[0]!='-'){
            z  = 0;
        } else {
            strstrpre(f+x,needle);
        }
    }
    if (z == 1) return 1;
    else  if (z==0) return 0;
    else return 1;
}

// Verifica se a palavra apontada pelo strstr é uma palavra completa
int strsstrpos(char*haystack,char*needle){
    char *s = strstr(haystack,needle);
    char*f = s+strlen(needle); 
    int y=0;
    char c = 39;
    if (s!=NULL){
        if(!isalpha(f[0]) && f[0]!='-' && f[0]!= c){
        y = 1;
        } 
        else {
            haystack = s + strlen(needle);strsstrpos(haystack,needle);   
        }
    }
    if (y==1) return 0;
    else return 1;
} 

//------------------------------------Gets e Sets-----------------------------------------------
char* getidq4(Query4 q){
    return q->id;
}

char* getnameq4(Query4 q){
    return q->name;    
}

char *getInfoNegocioId(InfoNegocio infoneg){
    return infoneg->id;
}

char *getInfoNegocioNome(InfoNegocio infoneg){
    return infoneg->nome;
}
