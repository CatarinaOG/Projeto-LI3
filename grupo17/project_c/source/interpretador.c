#include "../includes/interpretador.h"

//-------------------------------------Interpretador----------------------------------------
int interpretador(){

    int exit = 0;
    char* line = NULL;
    size_t line_size = 0;
    char* var;
    char* commandORtable;
    char* fullComando;
    int read;

    // Cria uma Hash com todos os comandos
    GHashTable* comandos = g_hash_table_new(g_str_hash,g_str_equal);
    fillComandos(comandos);

    SGR sgr = NULL;
    showMenu();

    while( exit == 0 && (read = getline(&line,&line_size,stdin))>0 ){
        char* line2 = line;
        while( exit == 0 && (fullComando = strsep(&line2,";")) != NULL &&  fullComando[0] != '\n' ){
            
            /*    Tentativa de utilizar ; como delimitador 

            char* copyCommand = strdup(fullComando);
            int eToCSV = strcmp(strsep(&copyCommand,"(") , "toCSV\0");

            char* copyCommand2 = strdup(fullComando);
            char* ignore = strsep(&copyCommand2,"=");
            int eFromCSV = strcmp(strsep(&copyCommand2,"(") , "fromCSV\0");

            if( (eToCSV == 0 || eFromCSV == 0)  &&  isDelim(copyCommand)==0){
                strcat(fullComando,";");
                strcat(fullComando,strsep(&line,";"));
                printf("finalCommand:%s|\n",fullComando);
            } 
            */

            // Limpa a linha de " " e "\""
            cleanLine(fullComando);

            if(strcmp("exit\n",fullComando) == 0){
                exit = 1;
                free(line);
                g_hash_table_destroy(comandos);
                //destroySGR(sgr);
            }

            else {
                if(existsEqual(fullComando) == 1){
                    var = strsep(&fullComando,"=");
                    commandORtable = strsep(&fullComando,"([");
                    gpointer task = g_hash_table_lookup(comandos,commandORtable);
                    switch( GPOINTER_TO_INT(task) ){
                        case 1: sgr = callQuery1(var,fullComando,sgr); break;
                        case 2: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,2); break;
                        case 3: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,3); break;
                        case 4: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,4); break;
                        case 5: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,5); break;
                        case 6: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,6); break;
                        case 7: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,7); break;
                        case 8: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,8); break;
                        case 9: if(sgr != NULL)callQuery2a9(var,fullComando,sgr,9); break;
                        case 12: if(sgr != NULL)callFromCSV(var,fullComando,sgr); break;
                        case 13: if(sgr != NULL)callFilter(var,fullComando,sgr); break;
                        case 14: if(sgr != NULL)callProj(var,fullComando,sgr); break;
                        default: if(sgr != NULL)callIndex(var,fullComando,sgr,commandORtable); break;
                    }
                }
                else{
                    commandORtable = strsep(&fullComando,"([");
                    gpointer task = g_hash_table_lookup(comandos,commandORtable);
                    char** argumentos = getArguments(&fullComando);

                    switch( GPOINTER_TO_INT(task) ){
                        case 10: if(sgr != NULL) callShow(argumentos,sgr); break;
                        case 11: if(sgr != NULL) callToCSV(argumentos,sgr); break;        
                    }
                }

            }
        }
    }
return 0;
}

//-------------------------------------Auxiliares----------------------------------------

/*
int isDelim( char* line){
    return strcmp( strrchr(line,',') , ",\0");
}
*/

// Guarda num array de Strings cada um dos argumentos
char** getArguments(char** line){

    char** argumentos = malloc(sizeof(char*)*4);
    int i=0;

    while( (*line) ){
        argumentos[i] = strsep(line,",)");
        i++;
    }
    return argumentos;
}

// Preenche a HashTable com todos os comandos possíveis (exceto index)
void fillComandos(GHashTable* comandos){

    g_hash_table_insert(comandos,"load_sgr",GINT_TO_POINTER(1));
    g_hash_table_insert(comandos,"businesses_started_by_letter",GINT_TO_POINTER(2));
    g_hash_table_insert(comandos,"business_info",GINT_TO_POINTER(3));
    g_hash_table_insert(comandos,"businesses_reviewed",GINT_TO_POINTER(4));
    g_hash_table_insert(comandos,"businesses_with_stars_and_city",GINT_TO_POINTER(5));
    g_hash_table_insert(comandos,"top_businesses_by_city",GINT_TO_POINTER(6));
    g_hash_table_insert(comandos,"international_users",GINT_TO_POINTER(7));
    g_hash_table_insert(comandos,"top_businesses_with_category",GINT_TO_POINTER(8));
    g_hash_table_insert(comandos,"reviews_with_word",GINT_TO_POINTER(9));
    g_hash_table_insert(comandos,"show",GINT_TO_POINTER(10));
    g_hash_table_insert(comandos,"toCSV",GINT_TO_POINTER(11));
    g_hash_table_insert(comandos,"fromCSV",GINT_TO_POINTER(12));
    g_hash_table_insert(comandos,"filter",GINT_TO_POINTER(13));
    g_hash_table_insert(comandos,"proj",GINT_TO_POINTER(14));
}

// Limpa a linha recebida da linha de comandos de " " e "\""
void cleanLine(char* line){

    for(int i=0 ; line[i] ; i++)
        if(line[i] == ' ' || line[i] == '\"')
            for(int j=i+1 ; line[j] ; j++)
                line[j-1] = line[j];

}

// Verifica se existe um igual na linha recebia
int existsEqual(char* line){

    for( int i=0 ; line[i]!='\0' ; i++)
        if(line[i] == '=') return 1;

    return 0;
}

//-------------------------------------Calls----------------------------------------

SGR callQuery1(char* var, char* line, SGR sgr){

    char* users;
    char* business;
    char* reviews;

    //Primeiro SGR
    if(sgr==NULL){
        if(line[0] == ')'){
            users = "users_full.csv";
            business = "business_full.csv";
            reviews = "reviews_1M.csv";
            line++;

        }
        else{
            users = strdup(strsep(&line,","));
            business = strdup(strsep(&line,","));
            reviews = strdup(strsep(&line,")"));
        }

        if(line[0] == '\0'){
            sgr = query1(users,business,reviews);
            setSGRName(sgr,var);
        }
        else printf("Erro na escrita do comando (Ex: falta de \";\")\n");
    }
    //Reload de SGR
    else{
        destroySGR(sgr);
        SGR newSGR = NULL;
        return callQuery1(var,line,newSGR);
    }

return sgr;
}

// Verifica se os argumentos inseridos foram lidos corretamente
int argsValidos(char** argumentos, int i){

    if(i==1) return (argumentos[1] == NULL) ? 0 : 1; 
    else return ( argumentos[1] == NULL || argumentos[2] == NULL) ? 0 : 1;

}

// Transforma a string recebida numa string começada por letra maiúscula e o resto da palavra em minúsculo
char* myToLower2(char* cs){
    cs[0] = toupper(cs[0]);
    for(int i = 1; cs[i]; i++){
    cs[i] = tolower(cs[i]);
    }
    return cs;
}

void callQuery2a9(char* var, char* line, SGR sgr, int query){
    char** argumentos = getArguments(&line);
    gboolean varExiste = variavelExiste(var,sgr);
    TABLE table = NULL;

    if( varExiste == FALSE ){
            if( strcmp(argumentos[0],getSGRName(sgr)) == 0 ){
                switch(query){
                    case 2: 
                        if(argsValidos(argumentos,1) == 1) table = query2(sgr,(argumentos[1])[0]);
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 3: 
                        if(argsValidos(argumentos,1) == 1) table = query3(sgr,argumentos[1]);
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 4: 
                        if(argsValidos(argumentos,1) == 1) table = query4(sgr,argumentos[1]);
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 5: 
                        if(argsValidos(argumentos,2) == 1) table = query5(sgr,atof(argumentos[1]),myToLower2(argumentos[2]));
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 6: 
                        if(argsValidos(argumentos,1) == 1) table = query6(sgr,atoi(argumentos[1]));
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 7: table = query7(sgr); break;
                    case 8: 
                        if(argsValidos(argumentos,2) == 1) table = query8(sgr,atoi(argumentos[1]),myToLower2(argumentos[2]));
                        else printf("argumento(s) inválido(s)\n"); break;
                    case 9: 
                        if(argsValidos(argumentos,1) == 1) table = query9(sgr,argumentos[1]);
                        else printf("argumento(s) inválido(s)\n"); break;
                    default: table = NULL; break;
                }
                if(table!=NULL){
                    setTableVariable(table,var); // Dá a variavel ao nome da table
                    addTableToSGR(sgr,table); // Insere table no SGR
                }
                else printf("tabela vazia\n");
            } 
            else printf("Sgr inserido nao existente\n");
    }
    else printf("Váriavel já existe\n");

    free(argumentos);
}



void callShow(char** argumentos, SGR sgr){

    if(sgr!=NULL){
        if(argumentos[0] != NULL){
            TABLE t = getTableFromSGR(sgr,argumentos[0]);

            if(t != NULL) paginacao(t);
            else printf("Tabela inserida inexistente\n");
        }
        else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");
    }
    else printf("Não existe nenhum sgr\n");
}

void callToCSV(char** argumentos, SGR sgr){ 

    if(sgr!=NULL){
        if(argumentos[0] != NULL && argumentos[1] != NULL && argumentos[2] != NULL){

            TABLE t = getTableFromSGR(sgr,argumentos[0]);

            if(t != NULL) toCSV(t,argumentos[1][0],argumentos[2]);
            else printf("Tabela inserida inexistente\n");
        }
        else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");   
    }
    else printf("Não existe nenhum sgr\n");
}

void callFromCSV(char* var , char* line, SGR sgr){

    if(sgr!=NULL){

        char** argumentos = getArguments(&line);
        int variavelAceite = variavelExiste(var,sgr);

        if( variavelAceite == 0 ){
            if(argumentos[0] != NULL && argumentos[1] != NULL){

                    TABLE table = fromCSV(argumentos[0],argumentos[1]);
                    if(table != NULL){
                        setTableVariable(table,var);
                        addTableToSGR(sgr,table);
                    }
                    else printf("Tabela returnada esta vazia\n");
            }
            else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");
        }
        else printf("Variavel já existe\n");
    }
    else printf("Não existe nenhum sgr\n");
}


void callProj(char* var,char* line, SGR sgr){

    char** argumentos = getArguments(&line);

    if(sgr!=NULL){

        TABLE newTable = NULL;
        int variavelAceite = variavelExiste(var,sgr);

        if( variavelAceite == 0){
            if(argumentos[0] != NULL && argumentos[1] != NULL){

                TABLE t = getTableFromSGR(sgr,argumentos[0]);
                if(t != NULL){

                    newTable = proj(t,atoi(argumentos[1]));
                    if(newTable != NULL){
                        setTableVariable(newTable,var);
                        addTableToSGR(sgr,newTable);
                    }
                    else printf("Tabela returnada esta vazia\n");
                } 
                else printf("Tabela inserida inexistente\n");
            }
            else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");
        }
        else printf("Variavel já existe\n");
    }
    else printf("Não existe nenhum sgr\n");
}


void callIndex(char* var,char* line, SGR sgr, char* tableVariable){

    if(sgr!=NULL){

        char* linha = strdup(strsep(&line,"]"));
        line++;
        char* coluna = strdup(strsep(&line,"]"));

        int variavelAceite = variavelExiste(var,sgr);
        TABLE newTable = NULL;
        
        if( variavelAceite == 0 ){
            if( line[0] == '\0') {
                TABLE table = getTableFromSGR(sgr,tableVariable);
                if(table != NULL){

                    newTable = taskIndex(table,atoi(linha),atoi(coluna));

                    if(newTable!=NULL){
                        setTableVariable(newTable,var);
                        addTableToSGR(sgr,newTable);
                    }
                    else printf("Valor inexistente\n");
                }
                else printf("Tabela inserida inexistente\n");
            }
            else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");
        }
        else printf("Váriavel inserida já existe\n");
    }
    else printf("Não existe nenhum sgr\n");
}

void callFilter (char* var , char* line , SGR sgr){

    if(sgr!=NULL){
        char** argumentos = getArguments(&line);

        if( argumentos[0]!=NULL && argumentos[1]!=NULL && argumentos[2]!=NULL && argumentos[3]!=NULL){
            TABLE t = getTableFromSGR(sgr,argumentos[0]);
            if( t!= NULL){

                TABLE table = filter(t,argumentos[1],argumentos[2],argumentos[3]);

                if( table != NULL){
                    setTableVariable(table,var);
                    addTableToSGR(sgr,table); 
                }
                else printf("Tabela returnada esta vazia\n");
            }
            else printf("Tabela inserida inexistente\n");
        }
        else printf("Erro na escrita dos argumentos (ex: falta de ;)\n");
    }
    else printf("Não existe nenhum sgr\n");
}