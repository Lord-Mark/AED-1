#include <stdio.h>
#include <stdlib.h>


/**
 * Retorna um novo vetor sem repetições
*/
int* noRepeat(int *vetor, int *size){
    
    /**
    * Vou utilizar esse código com "for" aninhado porque é mais fácil e mais rápido
    * resolver esse problema desta forma, porém sei que não é a forma mais eficiente
    * pois acaba sendo um O(n^3) (eu acho) o pior caso
    * uma forma muito mais eficiente eu acredito que seria organizar os dados primeiro
    * e depois comparar os valores da sequência pra saber se são repetidos ou não.
    * Dessa forma haveria uma complexidade de n^2 apenas
    */

    //percorre até o final do vetor
    for(int id=0; id < *size; id++){
        
        //Compara o valor com o restante dos valores, o id permanece fixo
        //enquanto o crawler (vasculhador) percorre o vetor
        for(int crawler = id+1; crawler < *size; crawler++){

            if(vetor[id] == vetor[crawler]){
                
                //Neste for, o crawler permanece fixo, enquanto o carrier (carregador)
                //carrega os valores por cima do valor indesejado
                for(int carrier = crawler; carrier < (*size - 1); carrier++){
                    vetor[carrier] = vetor[carrier+1];
                }
                
                //Crawler retorna 1 valor para checar se ainda existe outro valor repetido 
                crawler--;

                //Size diminui 1 valor, pois o último não importa mais e será removido
                (*size)--;
            }
        }
    }
    
    //Realloc supostamente seguro, já que ele só reduz o tamanho
    vetor = (int *)realloc(vetor, sizeof(int) * (*size));

    return vetor;
}

int main(){
    int size, *vetor, id;
    printf("Digite quantos numeros deseja inserir: ");
    scanf(" %d", &size);

    //Aloca o tamanho determinado
    vetor = (int *) malloc(sizeof(int) * size);

    for (id = 0; id < size; id++)
    {
        printf("Digite o valor %d: ", id);
        scanf(" %d", &vetor[id]);
    }
    
    vetor = noRepeat(vetor, &size);

    for (id = 0; id < size; id++)
    {
        printf("%d\n", vetor[id]);
    }
    
    free(vetor);
    
    
}