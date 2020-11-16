#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Insere um registro na lista
void insertPerson(sKeeper *list, void *pBuffer)
{

    //Armazena temporariamente a idade
    int *tmpAge = pBuffer;

    //Armazena temporáriamente o nome
    char *tmpName = (pBuffer + (sizeof(int)));

    //Esta variável não está armazenada na memória, foi apenas instanciada e será
    //apontada para um ponto da lista (que pode ficar fora do pBuffer)
    sNodo *nodo;

    printf("\nDigite o nome da pessoa: ");
    scanf(" %[^\n]", tmpName);

    printf("Digite a idade da pessoa: ");
    scanf(" %d", tmpAge);

    //Os itens são inseridos usando prioridade de chegada, usando um id como prioridade
    nodo = push(list, &list->lastId);

    setName(&(nodo->info), tmpName);
    setAge(&(nodo->info), tmpAge);
}

//Busca uma pessoa na lista e a imprime caso achar
void search(sKeeper *list, void *pBuffer)
{
    int *id;
    id = pBuffer;

    printf("Qual id deseja buscar?\n");
    scanf(" %d", id);

    sNodo *nodo;

    for (nodo = list->pFirst; nodo != NULL; nodo = nodo->pNext)
    {
        if (nodo->info.priority == *id)
        {
            printf("\nId encontrado:\nNome: %s\nIdade: %d\n",
                   nodo->info.name,
                   nodo->info.age);
            return;
        }
    }
    printf("Id não encontrado");
}
/**
 * Cria uma fila ordenada de acordo com os parâmetros do usuário e a imprime
*/
void printList(sKeeper *list, void *pBuffer)
{
    //Cria a lista
    sKeeper *fila = NULL;
    fila = reset(fila);

    sNodo *filaAux,
        *listAux;

    int *chooseParam, //Escolhe o parâmetro
        *chooseOrder; //Escolhe a ordem, se vai ser crescente ou decrescente

    chooseParam = pBuffer;
    chooseOrder = (pBuffer + sizeof(int));

    if (empty(list))
    {
        printf("\n\nNenhum registro encontrado!\n\n");
        return;
    }

    printf("\nEscolha o parâmetro de ordenação\n");
    printf("\t1 - idade\n");
    printf("\t2 - id\n");
    printf("Sua escolha: ");

    scanf(" %d", chooseParam);

    printf("Qual a ordem?\n");
    printf("\t1 - crescente\n");
    printf("\t2 - decrescente\n");
    printf("Sua escolha: ");

    scanf(" %d", chooseOrder);

    //Cria a lista
    if (*chooseParam == 1) // Ordem por idade
    {
        // listAux = list->pFirst;
        // filaAux = push(fila, listAux);

        // Preenche a fila
        for (listAux = list->pFirst; listAux != NULL; listAux = listAux->pNext)
        {
            filaAux = push(fila, &listAux->info.age);

            setName(&(filaAux)->info, listAux->info.name);

            setAge(&(filaAux)->info, &listAux->info.age);
        }
    }
    else if (*chooseParam == 2) // Ordem por id
    {
        //Essa opção não é muito necessária, só estou criando uma fila para este caso
        //pois o exercício pede que uma fila seja criada, mas o que está acontecendo aqui
        //é basicamente uma cópia da lista

        for (listAux = list->pFirst; listAux != NULL; listAux = listAux->pNext)
        {
            filaAux = push(fila, &listAux->info.priority);

            setName(&(filaAux)->info, listAux->info.name);
            setAge(&(filaAux)->info, &listAux->info.age);
        }
    }
    else
    {
        printf("\nOpção de ordem inválida!\n");
        clear(fila);
        free(fila);

        return;
    }

    //Imprime a lista
    if (*chooseOrder == 1) //Crescente
    {
        for (filaAux = fila->pFirst; filaAux != NULL; filaAux = filaAux->pNext)
        {
            printf("\nNome: %s\nIdade: %d\nPrioridade: %d\n",
                   filaAux->info.name,
                   filaAux->info.age,
                   filaAux->info.priority);
        }
    }
    else if (*chooseOrder == 2) //Decrescente
    {
        for (filaAux = fila->pLast; filaAux != NULL; filaAux = filaAux->pPrev)
        {
            printf("\nNome: %s\nIdade: %d\nPrioridade: %d\n",
                   filaAux->info.name,
                   filaAux->info.age,
                   filaAux->info.priority);
        }
    }
    else
    {
        printf("\nOpção de ordem inválida!\n");
    }

    clear(fila);
    free(fila);
}

int main()
{
    sKeeper *list = NULL;

    //list não tem prioridade, então a variável prioridade se torna o id de cada nodo
    list = reset(list);

    int *escolha;

    void *pBuffer = (void *)malloc(sizeof(int) + (sizeof(char) * 100));

    escolha = pBuffer;

    while (1)
    {

        printf("\nDigite sua escolha:\n");
        printf("\t1 - Adicionar pessoa\n");
        printf("\t2 - Exibir lista\n");
        printf("\t3 - Buscar id\n");
        printf("\t4 - Limpar lista\n");
        printf("\t5 - Sair\n");
        printf("\nSua escolha: ");

        scanf(" %d", escolha);

        switch (*escolha)
        {
        case 1:
            insertPerson(list, pBuffer);
            break;

        case 2:
            printList(list, pBuffer);
            break;

        case 3:
            search(list, pBuffer);
            break;

        case 4:
            clear(list);
            break;

        case 5:
            clear(list);
            free(list);
            free(pBuffer);
            return 0;
            break;

        default:
            printf("\n\nEscolha inválida, tente novamente...\n\n");
            break;
        }
    }
    return 0;
}
