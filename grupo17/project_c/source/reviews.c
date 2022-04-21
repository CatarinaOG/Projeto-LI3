#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "../includes/reviews.h"
#include "../includes/business.h"
#include <gmodule.h>
#include <glib.h>

struct review{
    char *review_id;
    char *user_id;
    char *business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char *date;
    char *text;
};

//----------------------------------------Frees-----------------------------------------------

void deleteKeysRev(gpointer review_id){
    free( (char*) review_id);
}

void deleteValuesRev(gpointer review){

    free( ((REVIEW) review)->review_id);
    free( ((REVIEW) review)->user_id);
    free( ((REVIEW) review)->business_id);
    free (((REVIEW)review)->date);
    free (((REVIEW)review)->text);
    free( (REVIEW) review);
}

//-----------------------------------------------Construtor----------------------------------------------------

// Verificar se o id do negócio é válido
int checkBusinessID(GHashTable* bus, char*idbus){
    if (g_hash_table_contains(bus,idbus)==TRUE) return 0; 
    else return 1;  
    }

// Verificar se o id do user é válido
int checkUserID(GHashTable* user, char *userid){
    if (g_hash_table_contains(user,userid)==TRUE) return 0; 
    else return 1;  
    }

// Adiciona à estrutura review cada campo
int addrevs(REVIEW rev,char *str){
    rev -> review_id = strdup(strsep(&str,";"));
    rev -> user_id = strdup(strsep(&str,";"));
    rev -> business_id = strdup(strsep(&str,";"));
    rev -> stars = atof(strsep(&str,";"));
    rev -> useful = atoi(strsep(&str,";"));
    rev -> funny = atoi(strsep(&str,";"));
    rev -> cool = atoi(strsep(&str,";"));
    rev -> date = strdup(strsep(&str,";"));
    rev -> text = strdup(strsep(&str,";"));
    if(rev->business_id == NULL || rev->user_id==NULL || rev->review_id==NULL||rev->stars<0.0||rev->useful<0||
    rev->funny<0||rev->cool<0||rev->date==NULL||rev->text==NULL) return 1;

return 0;
}

// Constrói e preenche o catálogo de reviews
GHashTable *readReviews(GHashTable *users,GHashTable*business, char*filename){
    FILE *file;
    size_t tmp_size = 0;
    char*tmp = NULL;
    int check;
    file = fopen(filename,"r");
    int i =1;
    tmp_size = getline(&tmp,&tmp_size,file);    
    GHashTable* review = g_hash_table_new_full(g_str_hash,g_str_equal,deleteKeysRev,deleteValuesRev); 

    while ((getline(&tmp,&tmp_size,file)>0)){
        REVIEW rev = malloc(sizeof(struct review));
        check = addrevs(rev,tmp);
        if ((check==0) && (!checkBusinessID(business,rev->business_id)) && (!checkUserID(users,rev->user_id))) 
        g_hash_table_insert(review,g_strdup(rev->review_id),rev);
    }
return review;
}

//------------------------------------------------Gets------------------------------------------------

char* getReviewID(REVIEW rev){
    return rev->review_id;
}

char* getUserID(REVIEW rev){
    return rev->user_id;
}

char* getBusinessID(REVIEW rev){
    return rev->business_id;
}

float* getStars(REVIEW rev){
    return &(rev->stars);
}

int getUSeful(REVIEW rev){
    return rev->useful;
}

int getFunny(REVIEW rev){
    return rev->funny;
}

int getCool(REVIEW rev){
    return rev->cool;
}

char* getDate(REVIEW rev){
    return rev->date;
}
char* getText(REVIEW rev){
    return rev->text;
}
REVIEW criaReview(){
    REVIEW rev = malloc(sizeof(struct review));
    return rev;
}

