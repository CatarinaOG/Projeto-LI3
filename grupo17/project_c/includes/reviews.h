#ifndef REVIEWSH
#define REVIEWSH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <gmodule.h>
#include <glib.h>
#include "business.h"


typedef  struct review *REVIEW;

//---------------Frees------------------
void deleteKeysRev(gpointer review_id);
void deleteValuesRev(gpointer review);

//---------------Construtor-------------
int checkBusinessID(GHashTable *business, char*idbus);
int checkUserID(GHashTable *users, char *userid);
int addrevs(REVIEW rev,char *str);
GHashTable *readReviews(GHashTable *users,GHashTable*business, char*filename);

//---------------Gets----------------
char* getReviewID(REVIEW rev);
char* getUserID(REVIEW rev);
char* getBusinessID(REVIEW rev);
float* getStars(REVIEW rev);
int getUSeful(REVIEW rev);
int getFunny(REVIEW rev);
int getCool(REVIEW rev);
char* getDate(REVIEW rev);
char* getText(REVIEW rev);
REVIEW criaReview();

#endif
