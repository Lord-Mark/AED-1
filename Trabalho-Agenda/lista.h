//Obs: Tudo que começa com 's' é uma struct, só pra não causar confusão

/**
 * Armazena os dados de cada pessoa
*/
typedef struct
{
    char name[30]; //Armazena o nome
    int priority,  //Armazena a prioridade da pessoa
        age;       //Armazena a idade

} sNodoInfo;
/**
 * Armazena os dados dos nodos da lista
*/
struct stcNodo
{
    sNodoInfo info;        //Struct com as infos de cada pessoa
    struct stcNodo *pNext; //Próxima struct da lista
    struct stcNodo *pPrev; //Struct anterior da lista
};

typedef struct stcNodo sNodo;

/**
 * Armazena os dados da lista
*/
typedef struct
{
    sNodo *pFirst; //Primeira struct da lista
    sNodo *pLast;  //Última struct da lista
    int lastId;    //Segura o último "id" da lista, pode ser usado para ver o tamanho

} sKeeper;

/**
 * Remove o último item de uma extremidade e o retorna,
 * mas não retorna como ponteiro pois a indicação para o local é liberada
 * 
 * por padrão, é removido do final pro começo, mas essa
 * sequência pode ser invertida passando 1 para o segundo parâmetro,
 * então:
 * 0 -> pop no final
 * 1 -> pop no começo
*/
void pop(sKeeper *list, int invertPopSide)
{
    sNodo *aux = NULL;
    // Se first == last, então esse é o último item da lista
    // Ou a lista está vazia
    if (list->pFirst == list->pLast)
    {

        // Se pFirst == pLast == NULL, então a lista está vazia
        if (list->pFirst == NULL)
            return; //Retorna NULL

        // Se o código continua, então ainda resta um item

        //Teoricamente nesse ponto lastId já é zero,
        //então não é necessário decremento de lastId

        aux = list->pFirst;

        free(list->pFirst);

        // Ao remover esse item, pLast e pFirst passam a
        // apontar para NULL pois não há mais item
        list->pLast = NULL;
        list->pFirst = NULL;

        // aux ainda tem a instancia da localização de pFirst,
        // mesmo que a região tenha sido liberada. Agora o nodo é retornado
        // por valor, não por referência
        return;
    }

    // Caso o pop esteja invertido -> removendo do início
    if (invertPopSide)
    {
        aux = list->pFirst;

        list->lastId--;

        free(list->pFirst);

        // Setta o pFirst para o próximo nodo
        list->pFirst = aux->pNext;

        // Redireciona o prev do first para NULL
        list->pFirst->pPrev = NULL;

        // aux ainda tem a instancia da localização de pFirst,
        // mesmo que a região tenha sido liberada. Agora o nodo é retornado
        // por valor, não por referência
        return;
    }

    // Caso não tenha terminado em nenhuma das opções anteriores, então
    // o pop será no último item da lista

    aux = list->pLast;

    list->lastId--;

    free(list->pLast);

    //Setta o pLast para o nodo anterior
    list->pLast = aux->pPrev;

    //Redireciona o next do last para NULL
    list->pLast->pNext = NULL;

    //aux ainda tem a instancia da localização de pLast,
    //mesmo que a região tenha sido liberada. Agora o nodo é retornado
    //por valor, não por referência
    return;
}

/**
 * Retorna 1 se a lista estiver vazia;
 * Retorna 0 se a lista não estiver vazia;
*/
int empty(sKeeper *list)
{
    //Poderia deixar retornando apenas a comparação
    //porém acho que o operador ternário deixa mais explícito
    return (list->pFirst == NULL) ? 1 : 0;
}

//Limpa a lista
void clear(sKeeper *list)
{
    while (list->pFirst != NULL)
    {
        pop(list, 0);
    }
}

/**
 * Reseta/inicia a lista e retorna o ponteiro (já que ocorre malloc)
*/
sKeeper *reset(sKeeper *list)
{
    if (list != NULL)
    {
        clear(list);
        return list;
    }

    list = malloc(sizeof(sKeeper) * 1);

    list->lastId = 0;
    list->pFirst = NULL;
    list->pLast = NULL;
    return list;
}

/**
 * Insere um item à lista de acordo com a prioridade passada;
 * 
 * priority teoricamente está apontando para um int do pBuffer
 * 
*/
sNodo *push(sKeeper *list, int *priority)
{
    //Armazena as informações do nó criado
    sNodo *nodo;
    nodo = (sNodo *)malloc(sizeof(sNodo) * 1);

    //Se a lista está vazia, então first e last = nodo
    if (empty(list))
    {
        list->pFirst = nodo;
        list->pLast = nodo;

        nodo->pNext = NULL;
        nodo->pPrev = NULL;
        nodo->info.priority = *priority;

        //lastId continua igual a zero, pois esse é o item zero

        return nodo;
    }

    //Se a prioridade do último for menor que a prioridade
    //do nodo passado, então o nodo se torna o último
    if (*priority >= list->pLast->info.priority)
    {
        sNodo *aux;

        //Salva o ponteiro do 'antigo último'
        aux = list->pLast;

        //transforma o nodo no 'novo último'
        list->pLast = nodo;

        //Setta o prev do nodo para o ponteiro anterior
        nodo->pPrev = aux;

        //Setta o next do nodo para NULL, pois é o último
        nodo->pNext = NULL;

        //Setta o next do ponteiro anterior para o 'novo último'
        aux->pNext = nodo;

        list->lastId++;

        nodo->info.priority = *priority;

        return nodo;
    }
    //Se a prioridade do primeiro for maior que a prioridade
    //do nodo passado, então o nodo se torna o primeiro
    if (*priority <= list->pFirst->info.priority)
    {
        sNodo *aux;

        //Salva o ponteiro do 'antigo primeiro'
        aux = list->pFirst;

        //transforma o nodo no 'novo primeiro'
        list->pFirst = nodo;

        //Setta o next do nodo para o aux
        //Equivalente a:
        //nodo->pNext = aux;
        list->pFirst->pNext = aux;

        //Setta o prev do nodo para NULL, pois é o último
        //Equivalente a:
        // nodo->pFirst = NULL;
        list->pFirst->pPrev = NULL;

        //Setta o prev do ponteiro para o 'novo primeiro'
        aux->pPrev = list->pFirst;

        list->lastId++;

        nodo->info.priority = *priority;

        return nodo;
    }

    //Se nenhum dos ifs anteriores foram executados, então
    //a prioridade está no meio da lista

    sNodo *prevNodo = list->pFirst,      //Armazena o nodo para comparar
        *nextNodo = list->pFirst->pNext; //Armazena o próximo nodo para comparar

    //Percorre a lista toda, a condição não seria necessária
    //Já que, teoricamente, não pode ser o último item,
    //mas se a condição for atingida quer dizer que algo está errado.
    while (nextNodo != NULL)
    {
        //Se a prioridade do nodo passado for maior ou igual ao próximo
        //nodo da lista, então nodo será colocado entre prevNodo e nextNodo
        if (*priority <= nextNodo->info.priority)
        {
            //Define o next e o prev do nodo passado
            nodo->pNext = nextNodo;
            nodo->pPrev = prevNodo;

            //Altera os apontamentos dos ponteiros vizinhos para
            //apontar para nodo
            nextNodo->pPrev = nodo;
            prevNodo->pNext = nodo;

            nodo->info.priority = *priority;

            //Atualiza o tamanho da lista
            list->lastId++;

            return nodo;
        }

        prevNodo = nextNodo;
        nextNodo = nextNodo->pNext;
    }

    printf("\n\n\t---Ocorreu algum erro!---\n\n");
}

/*  ----------- |===========|------------    */
/* //###########// Setters \\###########\\   */
/*||###########||     &     ||###########||  */
/* \\###########\\ Getters //###########//   */
/*  ------------||====|====||------------    */

//Define o nome da pessoa
//name está definido em pBuffer
void setName(sNodoInfo *info, char *name)
{
    strcpy(info->name, name);
}

//Define a idade da pessoa
//Age está definido em pBuffer
void setAge(sNodoInfo *info, int *age)
{
    info->age = *age;
}