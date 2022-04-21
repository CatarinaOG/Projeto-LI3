#ifndef BUSINESSH
#define BUSINESSH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gmodule.h>

typedef struct business *Business;

GHashTable* readBusiness(char* fileName);
char* getBusinessId(Business negocio);
char* getBusinessName(Business negocio);
char* getBusinessCity(Business negocio);
char* getBusinessState(Business negocio);
GList* getBusinessCategories(Business negocio);
Business criaNegocio();
Business findNegocio(GHashTable* negocios, char* business_id);

#endif