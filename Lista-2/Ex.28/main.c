#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcs.h"

int main(){
    char input=1;
    int tamanhoRegistro = 0;
    Pessoa *registros;

    while (input != '0')
    {
        registros = inserirPessoa(registros, &tamanhoRegistro);

        //Limpa a tela
        system("cls||clear");

        printf("Digite zero para parar o programa e qualquer outra coisa pra continuar: ");
        scanf(" %c", &input);

    }

    listar(registros, tamanhoRegistro);
    
    free(registros);
    
    return 0;
}