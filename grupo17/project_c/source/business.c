#include "../includes/business.h"

struct business{
    char* id;
    char* name;
    char* city;
    char* state;
    GList* categories;
};

//----------------------------------------Frees-----------------------------------------------

void deleteCategories(gpointer category){
    free( (char*) category);
}


void deleteKeys(gpointer id){
    free( (char*) id );
}

void deleteValues(gpointer negocio){
    free( ((Business) negocio)->id);
    free( ((Business) negocio)->name);
    free( ((Business) negocio)->city);
    free( ((Business) negocio)->state);
    g_list_free_full ( ((Business) negocio)->categories , deleteCategories);
    free( (Business) negocio);
}

//-----------------------------------------------Construtor----------------------------------------------------


// Transforma a string recebida numa string começada por letra maiúscula e o resto da palavra em minúsculo
char* myToLower(char* cs){
    cs[0] = toupper(cs[0]);
    for(int i = 1; cs[i]; i++){
    cs[i] = tolower(cs[i]);
    }
    return cs;
}

// Constrói e preenche a estrutura de um negócio
int getStructBussiness(Business negocio, char* tmp){
    int i;

    negocio->id = strdup(strsep(&tmp,";"));
    negocio->name = strdup(myToLower(strsep(&tmp,";")));
    negocio->city = strdup(myToLower(strsep(&tmp,";")));
    negocio->state = strdup(strsep(&tmp,";"));
    negocio->categories = NULL;

    if (tmp[0] == '\0' || tmp[0] == '\n') return 0;

    for(i=0 ; tmp ; i++)
        negocio->categories = g_list_prepend(negocio->categories,strdup(strsep(&tmp,",\n"))); 

    if (negocio->id == NULL || negocio->name == NULL || strlen(negocio->state) != 2) return 1;

    return 0;
}

// Constrói e preenche o catálogo de negócios
GHashTable* readBusiness(char* fileName){

    FILE* fd = fopen(fileName,"r");
    if (fd == NULL)
        perror("fopen: ");

    size_t tmp_size = 0;
    char* tmp = NULL;
    int verifica;

    tmp_size = getline(&tmp,&tmp_size,fd); 

    GHashTable* negocios = g_hash_table_new_full(g_str_hash,g_str_equal,deleteKeys,deleteValues);

     while(getline(&tmp,&tmp_size,fd) > 0){

        Business negocio = malloc(sizeof(struct business));
        verifica = getStructBussiness(negocio,tmp);
        if (verifica == 0) g_hash_table_insert(negocios,g_strdup(negocio->id),negocio);
        else deleteValues(negocio);
    }

    free(tmp);
    fclose(fd);

return negocios;
}

//------------------------------------------------Gets------------------------------------------------

char* getBusinessId(Business negocio){
    return negocio->id;
}

char* getBusinessName(Business negocio){
    return strdup(negocio->name);
}

char* getBusinessCity(Business negocio){
    return negocio->city;
}

char* getBusinessState(Business negocio){
    return negocio->state;
}

// Retorna uma cópia profunda da lista de categorias de um negócio
GList* getBusinessCategories(Business negocio){

    GList* newListCategories = NULL;
    
    for( ; negocio->categories ; (negocio->categories) = (negocio->categories)->next ){
        char* categoria = (negocio->categories)->data;
        newListCategories = g_list_prepend(newListCategories,strdup(categoria));
    }

    return newListCategories;
}

// Aloca espaço para um negócio
Business criaNegocio(){
      Business negocio = malloc(sizeof(struct business));
      return negocio;
}

// Retorna a estrutura de um negócio cujo id foi fornecido
Business findNegocio(GHashTable* negocios, char* business_id){

    Business foundBusiness = g_hash_table_lookup(negocios,business_id);

return foundBusiness;
}