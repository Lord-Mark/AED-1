#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void *realloc2(void *oldPointer, size_t newSize, size_t oldSize){

    void * newPointer = malloc(newSize);

    //Se o tamanho diminui, então copia só até o novo tamanho
    if(newSize < oldSize ){
        memcpy(newPointer, oldPointer, newSize);
        free(oldPointer);

        return newPointer;
    }
    //Se o tamanho aumenta (ou fica igual), ele copia todo o conteúdo da var antiga
    memcpy(newPointer, oldPointer, oldSize);
    free(oldPointer);

    return newPointer;
}


int main(){

    /**
    * Variável responsável por armazenar o tamanho da variável 
    * (__msize não funfa no Linux e a func equivalente no Linux não funfa no Win)
    */
    size_t varSize = 3, newSize;

    //variável de teste que aloca 3 espaços
    int *testVar = (int *) malloc(varSize*sizeof(int));
    
    //preenche o vetor
    testVar[0] = 1;
    testVar[1] = 3;
    testVar[2] = 5;
    
    for(int i = 0; i<3; i++){
        printf("testeVar[%d] == %d\n", i, testVar[i]);
    }

    //Aumentando o tamanho da variável
    newSize = 5;
    int *verifyVar = realloc2(testVar, (newSize*sizeof(int)), varSize*sizeof(int));
    varSize = newSize; //Atualizando o tamanho da variável
    
    testVar = verifyVar; //Pega o novo ponteiro

    //Preenche os novos espaços criados
    verifyVar[3] = 7;
    verifyVar[4] = 2;
    

    printf("\nTeste 1: Aumentando\nVerifica se o conteúdo foi copiado e se os valores batem:\n");
    for(int i = 0; i < varSize; i++){
        printf("testVar[%d]: %d - verifyVar[%d]: %d\n", i, testVar[i], i, verifyVar[i]);
    }

    //Diminuindo o tamanho da variável
    newSize = 3;
    verifyVar = realloc2(testVar, (newSize*sizeof(int)), varSize*sizeof(int));
    varSize = newSize; //Atualiza o tamanho da variável
    testVar = verifyVar; //Atualiza o ponteiro

    printf("\nTeste 2: Diminuindo\nVerifica se o conteúdo foi copiado e se os valores batem:\n");
    for(int i = 0; i < varSize; i++){
        printf("testVar[%d]: %d - verifyVar[%d]: %d\n", i, testVar[i], i, verifyVar[i]);
    }

    free(verifyVar);

    return 0;
}
