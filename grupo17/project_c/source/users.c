#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include "../includes/users.h"

struct user{
    char *id;
    char *name;
    GList *friends;
};

// Criação de um novo utilizador
int newUser(User user, char *str){

    user->id = strdup(strsep(&str,";"));
    user->name = strdup(strsep(&str,";"));
    user->friends = NULL;

    char *aux = strdup(strsep(&str,","));

    while(aux != NULL){
        user->friends = g_list_prepend(user->friends, aux);
        aux = strsep(&str,",");
    }
    if(user->id == NULL || user->name == NULL) return 1;

    return 0;
}

// Free da key
void deleteKey(gpointer id){
    free((char*)id);
}

// Free dos amigos
void deleteFriends(gpointer amigos){
    free((char *)amigos);
}
// Free dos values
void deleteValue(gpointer user){
    free(((User) user)->id);
    free(((User) user)->name);
    g_list_free_full (((User) user)->friends, deleteFriends);
    free((User) user);
}

// Constrói e preenche o catálogo de users
GHashTable* readUsers(char* f_user){

    FILE* fd = fopen(f_user,"r");
    if (fd == NULL)
        perror("erro: ");

    char* tmp = NULL;
    size_t size = 0;
    size = getline(&tmp,&size,fd);

    GHashTable* users = g_hash_table_new_full(g_str_hash, g_str_equal, deleteKey, deleteValue);

    while(getline(&tmp,&size,fd) > 0){
        User user = malloc(sizeof(struct user));
        newUser(user,tmp);
        if (!g_hash_table_contains(users, user->id)){
        g_hash_table_insert(users, user->id, user);  
        } 
    } 
    fclose(fd);
    free(tmp);

return users;
}