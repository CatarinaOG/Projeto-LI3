#include "../includes/tasks.h"

//------------------------------------------------show---------------------------------------------------------

TABLE getShowN(TABLE t,int i){
	GList *x = getTabela(t);   
	
	if (i<1){
		printf("Número inserido tem que ser maior que 0"); 
		return NULL;
	}
	if(g_list_length(x)<13){
		return t;
	}
	GList *part = NULL;
	int tam = i*13;
	for(int z = ((i*13)-13);z<tam;z++){
		if ((g_list_nth_data(x,z))!=NULL) 
			part = g_list_prepend(part,g_list_nth_data(x,z));
	}
	part = g_list_reverse(part); 
	TABLE temp = createTable();
	setLinhas(temp,getLinhas(t));
	setColunas(temp,getColunas(t));
	setTabela(part,temp);   
	return temp;
}

int getPaginas(TABLE t){
	int lin = g_list_length(getTabela(t));    
	double tam = lin * 1.0;    
	double x = (tam/13)*1.0;
	if(lin % 13 ==0){
		return lin/13;
	}
	else round(x);
	return x+1; 
}

char **getPart(char**arro,int x){
	char **arrn = malloc(sizeof(char*)*x);    
	for (int i=0;i<x;i++){
		arrn[i]=strdup(arro[i]);
	}
	return arrn;
}

void show(TABLE t){
	int x = 0;
	int len = 0;
	int f = 0;
	int s = 0;
	int contador=0;
	int col = getColunas(t);
	int lin = getLinhas(t);
	GList *y = getTabela(t); 
	GList *first = g_list_first(y);
	char **arrf = first->data;
	for(int i =0;arrf[i]!=NULL;i++){
		f+=7;    
	}
	printf("\n\t");
	while(s!=(f)+col+5){
	    printf("-");
	    s++;
	}
	printf("\n\t");
	printf("| ");
	for(int i=0;i<col;i++){
		printf("%s",arrf[i]);
		printf(" | ");
	} 
	y = g_list_nth(y,1);
	for (;y!=NULL;y=y->next){
		char **arr = y->data;
		if(contador==0){
			len=s-col-5;
		}
		printf("\n\t");
		while(x!=(len+col)){
	    	printf("-");
	    	x++;
		}
		x = 0;
		len = 0;
		printf("\n\t");
		printf("| ");
		for(int z =0;z<col;z++){    
			printf("%s",arr[z]);
			len += 15;
			printf(" | ");
		}
		contador++;
		if (y->next == NULL){
	    	int i=0;
	    	printf("\n\t");
	    	while(i!=(len)+col){
	        	printf("-");
	       		i++;
	    	}
		}
	}
	printf("\n");}

//------------------------------------------------toCSV---------------------------------------------------------

void toCSV(TABLE t, char delim , char* file){

    FILE* fd = fopen(file, "w+");
    if( fd == NULL)
        printf("nao abriu\n");

    GList* tabela = getTabela(t);
    int colunas = getColunas(t);
    int i=0;

    for( ; tabela ; tabela=tabela->next){

        char** array = tabela->data;
        for(i=0 ; i<colunas-1 ; i++)
            fprintf(fd,"%s%c",array[i],delim);
        fprintf(fd,"%s\n",array[i]);
    }
    fclose(fd);
}

//------------------------------------------------fromCSV---------------------------------------------------------

TABLE fromCSV(char* file, char* delim){
    FILE* fd = fopen(file,"r");
    if( fd == NULL){
        printf("nao abriu");
        return NULL;
    }
    else{
        TABLE t = createTable();
        GList* table = NULL;
        int colunas;
        char** array;
        char* line = NULL;
        size_t line_size = 0;

        if( getline(&line,&line_size,fd) > 0 ){

            colunas = findColunas(line,delim[0]);
            array = malloc(sizeof(char*)*colunas);
            
            for( int i=0 ; i<colunas ; i++)
                array[i] = strdup(strsep(&line,delim));

            table = g_list_prepend(table,array);

            while( getline(&line,&line_size,fd) > 0){

                array = malloc(sizeof(char*)*colunas);
                for( int i=0 ; i<colunas ; i++)
                    array[i] = strdup(strsep(&line,delim));
                    
                table = g_list_prepend(table,array);
            }

            table = g_list_reverse(table);
            setTableTabela(t,table);
            setColunas(t,colunas);
            setLinhas(t,g_list_length(table));
        }
        else printf("ficheiro vazio");

        printf("acabou");
        return t;
    }
}

int findColunas(char* line, char delim){

    int conta=0;
    for(int i=0 ; line[i] ; i++ )
        if( line[i] == delim) conta++;

	return conta+1;
}


//------------------------------------------------filter---------------------------------------------------------

TABLE filter(TABLE t, char* coluna , char* valor , char* operador ){

    int ind = colunaExists(t,coluna);
    int operValido = operadorValido(operador);
    int tiposDaoMatch = matchTipos(valor,t);
    
    GList* originalList = getTabela(t);
    int colunas = getColunas(t);

    TABLE new = createTable();
    GList* list = NULL;

    if( ind>0 ){
        if ( operValido>0 ){
            if( tiposDaoMatch != -1){
                for( ; originalList ; originalList=originalList->next){

                    char** array = originalList->data;
                    if( elimina(array,ind,operValido,tiposDaoMatch,valor) == 0)
                        list = g_list_prepend(list,copyArray(array,&colunas));
                }

                list = g_list_reverse(list);
                setTableTabela(new,list);
                setColunas(new,colunas);
                setLinhas(new,g_list_length(list));

            }
            else printf("valor inserido não é do mesmo tipo que a coluna inserida");
        }
        else printf("operador invalido");
    }
    else printf("nao existe coluna inserida");

return new;
}

int colunaExists(TABLE t, char* coluna){

    GList* linhas = getTabela(t);
    char** array = linhas->data;

    int nrColunas = getColunas(t);
    int ind = -1;

    for(int i=0 ; i<nrColunas ; i++)
        if( strcmp(array[i],coluna) == 0 ) ind = i;

	return ind;
}

int operadorValido(char* op){

    if( strcmp("LT",op) == 0 ) return 1;
    else if ( strcmp("EQ",op) == 0 ) return 2;
    else if (strcmp("GT",op) == 0 ) return 3;
    else return -1;
}

int matchTipos(char* valor, TABLE t){

    GList* l = getTabela(t);
    char** array = l->next->data;

    if( isdigit(atoi(valor)) > 0 && isdigit(atoi(array[0])) > 0 ) return 1;
    else if ( isdigit(atoi(valor)) == 0 && isdigit(atoi(array[0])) == 0) return 2;
    else return -1;
}


char** copyArray ( char** linha , int* colunas ){

    char** array = malloc(sizeof(char*)* (*colunas));

    for( int i=0 ; i<(*colunas) ; i++)
        array[i] = strdup(linha[i]);

	return array;
}


int elimina (char** linha , int ind, int operador, int tiposDaoMatch, char* valor){

    //digitos
    if ( tiposDaoMatch == 1 ){

        double valorNumerico = strtod(valor,NULL);
        double valorTestar = strtod(linha[ind],NULL);

        switch(operador){
            case 1: return ((valorNumerico - valorTestar) > 0) ? 0 : 1;
            case 2: return ((valorNumerico - valorTestar) == 0) ? 0 : 1;
            case 3: return ((valorNumerico - valorTestar) < 0) ? 0 : 1;
        }
    }
    //palavras
    else {

        char valorAlpha = tolower(valor[0]);
        char valorTestar = tolower(linha[ind][0]);

        switch(operador){
            case 1: return (valorAlpha > valorTestar) ? 0 : 1;
            case 2: return (valorAlpha == valorTestar) ? 0 : 1;
            case 3: return (valorAlpha < valorTestar) ? 0 : 1;
        }
    }
    return 0;
}

//------------------------------------------------proj---------------------------------------------------------

TABLE proj(TABLE t,int x){
	int col = getColunas(t);
	GList *new = NULL;
	if (col<x){
		printf("Número inserido superior ao número de colunas total, retornando tabela original:\n");
		return t;
	}
	GList *ori = getTabela(t);
	for(;ori!=NULL;ori=ori->next){
		char**arro=ori->data;
		char **arrn = getPart(arro,x);
		new = g_list_prepend(new,arrn);
	}
	new = g_list_reverse(new);
	setTableTabela(t,new);
	setColunas(t,x);
	setLinhas(t,g_list_length(new));
	return t;
} 

//------------------------------------------------index---------------------------------------------------------

TABLE taskIndex(TABLE table, int linha, int coluna){
    if(linha >= (getLinhas(table)-1) || coluna >= getColunas(table)){
        printf("Linha ou coluna inserida inexistente!\n");
        return NULL;
    }
    else{
        GList *l = getTabela(table);
        GList *result = NULL;

        gpointer p = g_list_nth_data(l, linha + 1); 
        char **r = (char**)p;  
        char *z = strdup(*(r+coluna));
        char **y = malloc(sizeof(char*)); 
        *y = z;
        result = g_list_prepend(result, y);

        char **array = l->data;
        char *b = strdup(*(array+coluna));
        char** linha0 = malloc(sizeof(char*));
        *linha0 = b;
        result = g_list_prepend(result,linha0);
            
        TABLE ret_table = createTable();
        setTableTabela(ret_table, result);
        setLinhas(ret_table, 2);
        setColunas(ret_table, 1);
        return ret_table;
    }
}