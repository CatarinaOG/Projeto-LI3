#include "../includes/apresentador.h"

// Preenche uma GHashTable com todos os comandos que são aceites
void fillComandosPagina(GHashTable* comandos){
    g_hash_table_insert(comandos,"quit\n",GINT_TO_POINTER(1));
    g_hash_table_insert(comandos,"next\n",GINT_TO_POINTER(2));
    g_hash_table_insert(comandos,"back\n",GINT_TO_POINTER(3));
    g_hash_table_insert(comandos,"inicio\n",GINT_TO_POINTER(4));
    g_hash_table_insert(comandos,"fim\n",GINT_TO_POINTER(5));
    g_hash_table_insert(comandos,"num\n",GINT_TO_POINTER(6));
    g_hash_table_insert(comandos,"ajuda\n",GINT_TO_POINTER(7));
}

// Divide uma table recebida em páginas e permite percorrê-las
int paginacao (TABLE t){
    int systemRet;
    int exit = 0;
    int i = 1;

    TABLE temp = createTable();
    GHashTable* comandos = g_hash_table_new(g_str_hash,g_str_equal);
    fillComandosPagina(comandos);
    char* line = malloc(sizeof(char*)*50);
    systemRet= system("clear");
        if(systemRet == -1)
    printf("Imprimindo primeira página da tabela\n");
    temp = getShowN(t,1);
    show(temp);

    printf("Insira \"quit\" se quiser parar de ver a página e voltar ao interpretador.\n");
    printf("Insira \"next\" se quiser ver a página seguinte.\n");
    printf("Insira \"back\" se quiser ver a página anterior.\n");
    printf("Insira um número se quiser ir para uma página específica.\n");
    printf("Insira \"fim\" se quiser ir até ao fim da tabela.\n");
    printf("Insira \"inicio\" se quiser ir até ao início da tabela.\n");
    printf("Insira \"num\" se quiser saber o número de páginas.\n");
    printf("Insira \"ajuda\" se quiser ver os comandos possíveis\n");

    int paginas = getPaginas(t);
    printf("Número de páginas total: %d.\n",paginas);

    while( exit == 0 && fgets(line,50,stdin)!=NULL){  
        gpointer task = g_hash_table_lookup(comandos,line); 

        switch(GPOINTER_TO_INT(task)){     
            case 1: systemRet= system("clear"); exit=1;printf("Saindo do programa.\n");g_list_free(getTabela(temp)); break;   

            case 2:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1)
                    perror("erro de terminal");
                if(i==paginas){temp=getShowN(t,paginas); show(temp);break;}
                i++;
                temp = getShowN(t,i);
                show(temp); 
                printf("Página %d\n",i);   
                break;

            case 3:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1)
                    perror("erro de terminal");
                if(i==1){temp=getShowN(t,1); show(temp);break;}
                i--;
                temp=getShowN(t,i);
                show(temp);
                printf("Página %d\n",i);    
                break;

            default:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1)
                    perror("erro de terminal");
                i=atoi(line);
                if(i==0){printf("Não foi inserido número, imprimindo a primeira página:\n");temp=getShowN(t,1); show(temp);break;}
                else
                temp=getShowN(t,i);
                show(temp);
                printf("Página %d\n",i);
                if(i==paginas) printf("chegou ao fim\n");    
                break;

            case 4:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1) perror("erro de terminal");
                i = 1;
                temp=getShowN(t,i);
                show(temp);
                printf("Página %d\n",i);
                break;
            case 5:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1)
                perror("erro de terminal");
                if(paginas==1){temp = getShowN(t,1); show(temp);}
                i=paginas;
                temp=getShowN(t,i);
                show(temp);
                printf("Chegou ao fim\n");
                break;
            case 6:
                g_list_free(getTabela(temp));
                systemRet= system("clear");
                if(systemRet == -1) perror("erro de terminal");
                printf("Número de páginas total: %d.\n",paginas);
                break;
            case 7:
            g_list_free(getTabela(temp));
            systemRet= system("clear");
            if(systemRet == -1) perror("erro de terminal");
              printf("Insira \"quit\" se quiser parar de ver a página e voltar ao interpretador.\n");
              printf("Insira \"next\" se quiser ver a página seguinte.\n");
              printf("Insira \"back\" se quiser ver a página anterior.\n");
              printf("Insira um número se quiser ir para uma página específica.\n");
              printf("Insira \"fim\" se quiser ir até ao fim da tabela.\n");
              printf("Insira \"inicio\" se quiser ir até ao início da tabela.\n");
              printf("Insira \"num\" se quiser saber o número de páginas.\n");
              printf("Insira \"ajuda\" se quiser ver os comandos possíveis\n");
              break;
        }
    }
    free(line);
    g_hash_table_destroy(comandos);
 return 0;   
}

// Apresentação do menu
void showMenu(){
    printf("---------------------------------------EXEMPLOS---------------------------------------\n");
    printf("-> Atribuição do valor de queries:    x = businesses_started_by_letter(sgr, “A”);\n");
    printf("-> Visualização de variáveis:    show(x);\n");
    printf("-> Escrita para csv:    toCSV(x, delim, filepath);\n");
    printf("-> Leitura de csv:    x = fromCSV(filepath, delim);\n");
    printf("-> Filtragem de resultados:    y = filter(x, column_name, value, oper);\n");
    printf("-> Projeção de colunas:    y = proj( x, cols);\n");
    printf("-> Indexação:    z = x[1][1];\n");
    printf("-> Terminação:    exit\n");
    printf("--------------------------------------------------------------------------------------\n");
 }
