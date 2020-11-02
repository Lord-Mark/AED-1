#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **stringMap(char linha[80], int *wordAmount)
{
    //Determina o início da palavra sendo analisada
    int wordStart = 0,  //Determina o início da palavra sendo analisada
        wordSize = 0,   //Determina o tamanho da palavra encontrada
        maxSize = 0;

    char **words;        //Salva as palavras

    *wordAmount = 0;

    //Determina o maxSize, talvez fosse interessante criar uma função só pra isso
    //Mas é um código simples que não vai precisar ser reutilizado
    for (int id = 0; id < 80; id++)
    {
        if (linha[id] == ' ')
        {
            wordSize = id - wordStart;

            if (wordSize > maxSize)
            {
                maxSize = wordSize;
            }
            wordStart = id + 1;
            (*wordAmount)++;
        }

        //Termina o laço quando encontra o fim da string e analisa a última palavra
        if (linha[id] == '\0')
        {
            wordSize = id - wordStart;

            if (wordSize > maxSize)
            {
                maxSize = wordSize;
            }

            (*wordAmount)++;

            break;
        }
    }

    // printf("maxSize: %d\n", maxSize);

    words = (char **) malloc(sizeof(char *) * (*wordAmount));
    int crawler = 0, charID;

    //Percorre o vetor alocando as posições e armazenando as palavras
    for (int id = 0; id < *wordAmount; id++)
    {
        words[id] = (char *) malloc(sizeof(char) * (maxSize+1));

        //Passa por todo o vetor copiando o conteúdo
        for (charID = 0; linha[crawler] != ' ' && linha[crawler] != '\0' && charID < maxSize; crawler++, charID++)
        {
            words[id][charID] = linha[crawler];
        }

        words[id][charID+1] = '\0';

        //teoricamente nem seria necessário esse if, pois o primeiro for já tem a quantidade de palavras definido,
        //mas vou deixar por garantia
        if(linha[crawler] == '\0'){
            break;
        }
        //Se o for terminou, então ele encontrou um espaço,
        //então esse incremento para evitar o espaço 
        crawler++;
    }

    return words;
}

int main()
{
    char linha[80], **words;
    int wordAmount = 0; //O tamanho da maior palavra na string, só pra simplificar os realloc

    printf("Entre com uma string de até 80 caracteres:\n");
    scanf(" %[^\n]", linha);

    words = stringMap(linha, &wordAmount);

    for(int i = 0; i < wordAmount; i++){
        printf("%s\n", words[i]);
    }

    for(int i = 0; i < wordAmount; i++){
        free(words[i]);
    }
    free(words);

    return 0;
}