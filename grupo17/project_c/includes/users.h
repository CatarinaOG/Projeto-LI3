#ifndef USERSH
#define USERSH
#include <stdio.h>

// Estrutura
typedef struct user *User; 

// Funções 
int newUser(User user, char* str);
GHashTable* readUsers(char* users);

#endif
