#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
 * TODO:
 * Revisar os comentários
*/

typedef struct stcNode
{
    struct stcNode *highNode; //Ponteiro para o Node com um valor maior
    struct stcNode *lowNode;  //Ponteiro para o Node com um valor menor
    int value;                //Valor do Node
    int balanceFactor;        //Fator de balanceamento do Node
} sNode;

/** 
 * Salva a raiz da árvore 
 * obs: Poderia ter usado ponteiro duplo para isso, porém acho mais
 * simples usando uma struct, pois para mim fica mais "óbvio"
*/
typedef struct
{
    sNode *firstNode; //Raiz da árvore

} rootNode;

//Cria um registro vazio e o retorna
rootNode *startTree()
{
    rootNode *tree;
    tree = malloc(sizeof(rootNode) * 1);

    if (tree == NULL)
    {
        printf("Não foi possível alocar a árvore");
        exit(1);
    }
    tree->firstNode = NULL;

    return tree;
}

//Checa se a árvore está vazia
int isEmpty(rootNode *tree)
{
    //If ternário, se a árvore for nula, retorna 1, se não, retorna zero
    return (tree->firstNode == NULL) ? 1 : 0;
}

int isBalanced(sNode *node)
{

    if (node->balanceFactor >= 2 || node->balanceFactor <= -2)
    {
        return 0;
    }
    return 1;
}
/**
 * Identifica qual a rotação necessária
 * retornos:
 * 2 -> rotação dupla para a direita
 * 1 -> rotação simples para a direita
 * 0 -> não precisa rotação
 * -1 -> rotação simples para a esquerda
 * -2 -> rotação dupla para a esquerda
 */
int identifyRotation(sNode *pivot)
{
    //Variáveis para auxiliar na manipulação da árvore
    sNode *secondNode;
    int rotation = 0;

    //Se não está desbalanceado, retornará zero
    if (isBalanced(pivot))
    {
        return 0;
    }

    //if ternário, se o bf de pivot for maior que zero, second vai para esquerda, se não, direita
    secondNode = (pivot->balanceFactor > 0) ? pivot->lowNode : pivot->highNode;

    /**
     * Uma breve explicação da lógica a seguir.
     * 
     * Pode-se identificar o tipo de rotação através dos fatores de balanceamento
     * do primeiro e do segundo nó, somando-os temos:
     * 
     * 2+1 = 3 -> rotação simples para a direita
     * 2-1 = 1 -> rotação dupla para a direita
     * 
     * E o mesmo se repete com os valores negativos, mas daí seria para a esquerda
    */

    rotation = pivot->balanceFactor - secondNode->balanceFactor;

    //Se a rotação é positiva, então é para a esquerda
    if (rotation > 0)
    {
        //Se igual a 1, retorna 1, se não retorna 2
        return (rotation == 1) ? 1 : 2;
    }

    //Se igual a -1, retorna -1, se não retorna -2
    return (rotation == -1) ? -1 : -2;
}

//Rotação simples para a direita
sNode *rightRotation(sNode *pivot)
{
    sNode *secondNode;

    //Pega o segundo nó
    secondNode = pivot->lowNode;

    //Transfere o nó da direita do segundo para a esquerda do pivô
    pivot->lowNode = secondNode->highNode;

    //Coloca o pivô na direita do segundo nó
    secondNode->highNode = pivot;

    return secondNode;
}

//Rotação simples para a esquerda
sNode *leftRotation(sNode *pivot)
{
    sNode *secondNode;

    //Pega o segundo nó
    secondNode = pivot->highNode;

    //Transfere o nó da direita do segundo para a esquerda do pivô
    pivot->highNode = secondNode->lowNode;

    //Coloca o pivô na direita do segundo nó
    secondNode->lowNode = pivot;

    return secondNode;
}

//Percorre recursivamente os nós e calcula o fator de balanceamento individualmente,
//retorna no final o fator da raiz
int calculateBalanceFactor(sNode *tree)
{
    int leftValue = 0,  //Conta quantos acessos ocorreram na esquerda
        rightValue = 0, //Conta quantos acessos ocorreram na direita
        bigger = 0;     //Armazena o maior valor entre a esquerda e a direita, para retornar ao nó anterior

    //Enquanto o lowNode apontar para um valor válido, a recursão continua
    if (tree->lowNode != NULL)
    {
        leftValue = calculateBalanceFactor(tree->lowNode);
    }

    //Enquanto o highNode apontar para um valor válido, a recursão continua
    if (tree->highNode != NULL)
    {
        rightValue = calculateBalanceFactor(tree->highNode);
    }

    //Adiciona o balanço ao nó
    tree->balanceFactor = (leftValue - rightValue);

    //Pega o maior valor (if ternário)
    bigger = (rightValue > leftValue) ? rightValue : leftValue;

    //Retorna o maior valor +1
    return bigger + 1;
}

//Recebe um nó "pivô", que é o nó onde ocorre um FB de 2 ou -2, retorna o novo pivô
sNode *rebalanceNode(sNode *pivot)
{
    int rotation;

    rotation = identifyRotation(pivot);
    switch (rotation)
    {
    case 2:
        pivot->lowNode = leftRotation(pivot->lowNode);
        return rightRotation(pivot);
        break;
    case 1:
        return rightRotation(pivot);
        break;
    case -1:
        return leftRotation(pivot);
        break;
    case -2:
        pivot->highNode = rightRotation(pivot->highNode);
        return leftRotation(pivot);
        break;
    default:
        printf("\n\nNANNNIII?!!?!\n%d\n", rotation);
        break;
    }
}

//Busca os nós desbalanceados e o passa para rebalanceNode
void rebalance(sNode *tree, rootNode *root)
{

    //Enquanto o lowNode apontar para um valor válido, a recursão continua
    if (tree == NULL)
    {
        return;
    }

    rebalance(tree->lowNode, NULL);
    rebalance(tree->highNode, NULL);

    //Testa os valores seguintes se precisam ser rebalanceados
    if (tree->highNode != NULL && !isBalanced(tree->highNode))
    {
        /**
         * Calcula o BF antes para o caso de ocorrer vários nós e subnós
         * desbalanceados, nesse caso a rotação acabaria acontecendo em todos
         * os nós com BF 2 ou -2,
         * sendo que apenas uma rotação já resolveria o problema
        */
        calculateBalanceFactor(tree);

        //Se ainda estiver desbalanceado, então faz o rebalanceamento necessário
        if (!isBalanced(tree->highNode))
        {
            tree->highNode = rebalanceNode(tree->highNode);

            //Recalcula os balanços a partir de onde ocorreu a alteração
            calculateBalanceFactor(tree);
        }
    }
    else if (tree->lowNode != NULL && !isBalanced(tree->lowNode))
    {
        /**
         * Calcula o BF antes para o caso de ocorrer vários nós e subnós
         * desbalanceados, nesse caso a rotação acabaria acontecendo em todos
         * os nós com BF 2 ou -2,
         * sendo que apenas uma rotação já resolveria o problema
        */
        calculateBalanceFactor(tree);

        //Se ainda estiver desbalanceado, então faz o rebalanceamento necessário
        if (!isBalanced(tree->lowNode))
        {
            tree->lowNode = rebalanceNode(tree->lowNode);

            //Recalcula os balanços a partir de onde ocorreu a alteração
            calculateBalanceFactor(tree);
        }
    }

    //Se root != NULL é porque essa é a primeira chamada da função
    if (root != NULL)
    {
        if (!isBalanced(root->firstNode))
        {
            calculateBalanceFactor(root->firstNode);

            if (!isBalanced(root->firstNode))
            {
                root->firstNode = rebalanceNode(root->firstNode);
            }
            calculateBalanceFactor(root->firstNode);
        }
    }
}

//Cria um nó vazio
sNode *createNode()
{
    sNode *node = malloc(sizeof(sNode) * 1);

    if (node == NULL)
    {
        printf("Não foi possível alocar um novo nó");
        return NULL;
    }

    node->highNode = NULL;
    node->lowNode = NULL;

    //O fator de balanço será corrigido posteriormente, este valor
    //é apenas uma forma de identificar que o nó ainda não foi introduzido à árvore
    node->balanceFactor = -10;

    return node;
}

//Insere um valor à árvore
void insertNode(int value, rootNode *tree)
{
    //Inicia um nó vazio para ser adicionado na árvore
    sNode *node = createNode();
    node->value = value;

    //Se a árvore for vazia, então salva o nó na raiz
    if (isEmpty(tree))
    {
        tree->firstNode = node;
        node->balanceFactor = 0;
    }

    //Nó temporário para percorrer a árvore
    sNode *treeCrawler;
    treeCrawler = tree->firstNode;

    //Percorre a árvore buscando onde o nó deve ser inserido.
    while (treeCrawler != NULL)
    {
        /**
         * Se o valor for menor que o nó, então vai para a esquerda;
         * Se o valor for maior que o nó, então vai para a direita;
         * Se o nó for igual a raiz, então o programa para
         * Se o valor de algum nó for igual ao valor passado, então o nó é liberado
        */
        if (value < treeCrawler->value)
        {
            //Se o próximo nó for NULL, então esse é o último nó deste lado
            if (treeCrawler->lowNode == NULL)
            {
                treeCrawler->lowNode = node;
                node->balanceFactor = 0;
                break;
            }
            //Se não for NULL, então vai para o próximo e checa novamente
            treeCrawler = treeCrawler->lowNode;
        }
        else if (value > treeCrawler->value)
        {
            //Se o próximo nó for NULL, então esse é o último nó deste lado
            if (treeCrawler->highNode == NULL)
            {
                treeCrawler->highNode = node;
                node->balanceFactor = 0;
                break;
            }
            //Se não for NULL, então vai para o próximo e checa novamente
            treeCrawler = treeCrawler->highNode;
        }
        else if (node == tree->firstNode)
        {
            break;
        }
        //Se o nó não é a raiz e o valor é igual, então é um valor duplicado
        else if (value == treeCrawler->value)
        {
            free(node);
            break;
        }
    }
    calculateBalanceFactor(tree->firstNode);
    rebalance(tree->firstNode, tree);
}

//Função para indentar o print e alinhar as saídas
void indentPrint(int value, int firstBrake, int secBrake)
{

    if (firstBrake < 0)
    {
        if (value > firstBrake)
        {
            printf(" ");
        }
        return;
    }

    if (value < firstBrake)
    {
        printf("  ");
    }
    else if (value < secBrake)
    {
        printf(" ");
    }
}
//Uma função pra fazer um print bonitinho e alinhadinho
void printNode(sNode *node)
{
    // Tudo que tem nessa função é basicamente pra fazer esse print, porém alinhado:
    // printf("Valor: %d | FB: %d | %d <-esquerda direita-> %d\n");

    int right = 0, left = 0;

    if (node->highNode != NULL)
        right = node->highNode->value;
    if (node->lowNode != NULL)
        left = node->lowNode->value;

    printf("Valor: %d ", node->value);
    indentPrint(node->value, 10, 100);

    printf(" FB:");
    indentPrint(node->balanceFactor, -1, 10);
    printf("%d  ", node->balanceFactor);

    indentPrint(left, 10, 100);
    printf(" %d <-esquerda ", left);
    printf("direita-> %d\n", right);
}

//Acessa recursivamente da esquerda para a direita todos os valores e os printa
void showTree(sNode *tree)
{
    //Quando apontar para um valor inválido, a recursão termina
    if (tree == NULL)
        return;

    showTree(tree->lowNode);

    printNode(tree);

    showTree(tree->highNode);
}

//Apaga apenas um nó
void deleteNode(int deleteValue, rootNode *tree)
{
    sNode *treeCrawler = tree->firstNode;
    sNode *substituteNode, *son, *aux;

    if (tree->firstNode->value != deleteValue)
    {
        //O while vai terminar quando um dos filhos forem o valor ou quando chegar no final sem resultado
        while (treeCrawler != NULL)
        {
            if (treeCrawler->lowNode->value == deleteValue)
            {
                son = treeCrawler->lowNode;
                break;
            }
            else if (treeCrawler->highNode->value == deleteValue)
            {
                son = treeCrawler->highNode;
                break;
            }
            else if (treeCrawler->value < deleteValue)
            {
                treeCrawler = treeCrawler->lowNode;
            }
            else if (treeCrawler->value > deleteValue)
            {
                treeCrawler = treeCrawler->highNode;
            }
        }
    }

    if (treeCrawler == NULL)
    {
        printf("Valor não encontrado\n");
        return;
    }

    /**
     * Se entrar no if, quer dizer que não é o primeiro nó, e treeCrowler é o pai do nó a ser deletado
     * Se não entrar, quer dizer que treeCrowler == tree->first, ou seja, é o próprio nó, essa lógica
     * é necessária pois se for o primeiro nó, é preciso alterar tree->first
    */
    if (tree->firstNode->value != deleteValue)
    {
        //Se o nó da esquerda não existe, então só tem um nó filho que está na direita
        if (son->lowNode == NULL)
        {
            if (treeCrawler->lowNode == son)
            {
                treeCrawler->lowNode = son->highNode;
            }
            else
            {
                treeCrawler->highNode = son->highNode;
            }
            free(son);
            calculateBalanceFactor(tree->firstNode);
            rebalance(tree->firstNode, tree);
            return;
        }
        //Se ambos os lados forem nulos, então dá pra apagar o nó sem salvar ponteiro
        if (son->highNode == NULL && son->lowNode == NULL)
        {
            treeCrawler->lowNode == NULL;
            treeCrawler->highNode == NULL;
            free(son);
            return;
        }

        substituteNode = son->lowNode;
        for (aux = substituteNode->highNode; aux->highNode != NULL; aux->highNode)
        {
            substituteNode = substituteNode->highNode;
        }

        substituteNode->highNode = NULL;
        substituteNode = aux;

        //salva os apontamentos do nó deletado no novo nó
        substituteNode->highNode = son->highNode;
        substituteNode->lowNode = son->lowNode;

        if (treeCrawler->lowNode == son)
        {
            treeCrawler->lowNode = substituteNode;
        }
        else
        {
            treeCrawler->highNode = substituteNode;
        }

        free(son);
        calculateBalanceFactor(tree->firstNode);
        rebalance(tree->firstNode, tree);
        return;
    }
    else
    {

        //Se o nó da esquerda não existe, então só tem um nó filho que está na direita
        if (treeCrawler->lowNode == NULL)
        {
            tree->firstNode = treeCrawler->highNode;
            free(treeCrawler);
            calculateBalanceFactor(tree->firstNode);
            rebalance(tree->firstNode, tree);
            return;
        }

        //Se ambos os lados forem nulos, a árvore estará vazia
        if (treeCrawler->highNode == NULL && treeCrawler->lowNode == NULL)
        {
            tree->firstNode = NULL;
            free(treeCrawler);
        }

        substituteNode = treeCrawler->lowNode;

        for (aux = substituteNode->highNode; aux->highNode != NULL; aux->highNode)
        {
            substituteNode = substituteNode->highNode;
        }

        substituteNode->highNode = NULL;
        substituteNode = aux;
        //salva o valor da direita do nó deletado no novo nó
        substituteNode->highNode = treeCrawler->highNode;
        substituteNode->lowNode = treeCrawler->lowNode;

        tree->firstNode = substituteNode;
        free(treeCrawler);
        calculateBalanceFactor(tree->firstNode);
        rebalance(tree->firstNode, tree);
        return;
    }
}

//Destrói tudo a partir de um nó
void destroyFromPivot(sNode *pivot)
{
    if (pivot == NULL)
    {
        return;
    }

    destroyFromPivot(pivot->lowNode);
    destroyFromPivot(pivot->highNode);

    free(pivot);
}

//Destrói a árvore inteira
void destroyTree(rootNode *tree)
{
    destroyFromPivot(tree->firstNode);
    free(tree);
}

//Mantive os nomes que deram pra manter e modifiquei os que são diferentes
int EhArvoreArvl(sNode *pRaiz)
{
    int fb;
    if (pRaiz == NULL)
        return 1;
    if (!EhArvoreArvl(pRaiz->lowNode))
        return 0;

    if (!EhArvoreArvl(pRaiz->highNode))
        return 0;

    //Fiz essa adaptação no código pois minha função de calcular o fb retorna uma coisa diferente
    //O valor que esse trecho busca está dentro do nó
    calculateBalanceFactor(pRaiz);
    fb = pRaiz->balanceFactor;

    if ((fb > 1) || (fb < -1))
        return 0;
    else
        return 1;
}

void insertRandom(rootNode *tree)
{
    int size, value;

    srand(time(0));

    printf("Digite quantos nós quer criar: ");
    scanf(" %d", &size);

    printf("Valores gerados:\n");

    for (int i = 0; i < size; i++)
    {
        value = rand() % 1000;
        insertNode(value, tree);

        printf("| %d ", value);
    }

    printf("|\n\n");

    showTree(tree->firstNode);

    printf("\n");

    if (EhArvoreArvl(tree->firstNode))
    {
        printf("É uma árvore AVL :D\n\n");
    }
    else
    {
        printf("Não é uma árvore AVL :(\n\n");
    }
}

void deleteValue(rootNode *tree)
{
    int value;

    printf("Digite o valor a ser removido: ");
    scanf(" %d", &value);

    deleteNode(value, tree);
}

//Pegar valores passados manualmente
void insertValue(rootNode *tree)
{
    int value;

    printf("Digite o valor a ser adicionado: ");
    scanf(" %d", &value);

    insertNode(value, tree);
}

//Adicionar valores manualmente
void debugManual()
{
    int option = 0;

    rootNode *tree;
    tree = startTree();

    while (1)
    {
        printf("\n\t--Menu--\n");
        printf("\t\t 1 - Adicionar valores\n");
        printf("\t\t 2 - Exibir valores ordenados\n");
        printf("\t\t 3 - Deletar um nó\n");
        printf("\t\t 4 - Inserir uma quantidade de valores aleatórios\n");
        printf("\t\t 5 - Sair\n");
        printf("\tSua escolha: ");
        scanf(" %d", &option);

        switch (option)
        {
        case 1:
            insertValue(tree);
            break;
        case 2:
            calculateBalanceFactor(tree->firstNode);
            showTree(tree->firstNode);
            break;
        case 3:
            deleteValue(tree);
            break;
        case 4:
            insertRandom(tree);
            break;
        case 5:
            destroyTree(tree);
            return;
            break;
        default:
            break;
        }
    }
}

int main()
{
    /**
     * DebugMode ativa a inserção manual
     * 0 => insersão randomica
     * 1 => insersão manual
    */
    int debugMode = 1;

    if (debugMode)
    {
        debugManual();
    }
    else
    {
        rootNode *tree;
        tree = startTree();

        insertRandom(tree);

        destroyTree(tree);
    }

    return 0;
}