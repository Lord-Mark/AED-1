#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcs.h"

int main(){

    char input = '0';

    //Salva as dimensões da matriz; pos 0 == coluna; pos 1 == linha
    int tamanhoMatrizColunaLinha[2], 
        **matriz;
    
    

    while (input != '6')
    {
        
        // Menu
        printf("\n\nEscolha sua opcao:\n");
        printf("\t1 - Criar/redimensionar matriz\n");
        printf("\t2 - Inserir elementos na matriz\n");
        printf("\t3 - Exibir a soma dos elementos da matriz\n");
        printf("\t4 - Inserir uma coluna nova\n");
        printf("\t5 - Imprimir matriz\n");
        printf("\t6 - Sair\n");
        printf("Sua escolha: ");

        scanf(" %c", &input);

        switch (input)
        {
        case '1':
            matriz = criaMatriz(tamanhoMatrizColunaLinha);
        break;
        
        case '2':
            inserirMatriz(matriz, tamanhoMatrizColunaLinha);
        break;

        case '3':
            somaMatriz(matriz, tamanhoMatrizColunaLinha);
        break;

        case '4':
            matriz = inserirColuna(matriz, tamanhoMatrizColunaLinha);
        break;

        case '5':
            imprimeMatriz(matriz, tamanhoMatrizColunaLinha);
        break;

        case '6':
            liberaMatriz(matriz, tamanhoMatrizColunaLinha);
            return 0;
        break;

        default:
        
        break;
        }

    }
    
    
    return 0;
}