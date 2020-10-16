#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(){

    int menuOption;

    //ponteiro de ponteiro definido para evitar de perder o ponteiro ao realocar na memória.
    char **nameList = (char **) malloc(1*sizeof(char *));
    *nameList = (char *) malloc(1*sizeof(char));
    
    //Inicia a variável e evita a mensagem de "uninitialised value" pelo valgrind ao dar strlen.
    nameList[0][0] = '\0';
    
    for(;;)
    {
        //system("cls||clear");
        fflush(stdin);
        //printf("nameList size: %ld\nTudo: %s\n", strlen(nameList), nameList);

        printf("\n\nEscolha sua opcao:\n");
        printf("\t1 - Adicionar Nome\n");
        printf("\t2 - Remover Nome\n");
        printf("\t3 - Listar\n");
        printf("\t4 - Sair\n");
        printf("Sua escolha: ");

        while( !scanf(" %d",&menuOption ))
        {
            fflush(stdin);
            __wur(stdin);
            printf("\nEntrada inválida, tente novamente!\n");
            
            printf("\n\nEscolha sua opcao:\n");
            printf("\t1 - Adicionar Nome\n");
            printf("\t2 - Remover Nome\n");
            printf("\t3 - Listar\n");
            printf("\t4 - Sair\n");
            printf("Sua escolha: ");
        }

        //scanf("%d", &menuOption);

        switch (menuOption)
        {
        case 1:
            addName(nameList);
        break;

        case 2:
            list(nameList); //Lista os nomes para escolher o id
            removeName(nameList);
        break;

        case 3:
            list(nameList);
        break;

        case 4:
            free(*nameList);
            free(nameList);
            return 0;
        break;

        default:
            continue;
        break;
        }
    }
    free(nameList);
    return 0;
}