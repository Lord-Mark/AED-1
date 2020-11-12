/**
 * Armazena os dados de cada pessoa
*/
typedef struct
{
    char name[30]; //Armazena o nome
    int id,        //Armazena o id da pessoa
        age;       //Armazena a idade

} nodoInfo;

/**
 * Armazena os dados dos nodos da lista
*/
typedef struct
{
    nodoInfo info; //Struct com as infos de cada pessoa
    nodo *pNext;   //Próxima struct da lista
    nodo *pPrev;   //Struct anterior

} nodo;

/**
 * Armazena os dados da lista
*/
typedef struct
{
    nodo *pFirst; //Primeira struct da lista
    nodo *pLast;  //Última struct da lista
    int size;     //Segura o tamanho da lista

} sentinela;
