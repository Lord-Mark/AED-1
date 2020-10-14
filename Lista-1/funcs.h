#include <string.h>

void addName(char **nameList){
    char name[30];
    int sizeList;
    //printf("nameList size: %ld\n", strlen(*nameList));
    
    printf("\nDigite um nome a ser adicionado: ");
    scanf("%s", name);
    
    sizeList = (2+ strlen(name) + strlen(*nameList)) * sizeof(char);

    *nameList = (char *)realloc( *nameList, sizeList);
    
    /**
     * Antes de adicionar um nome é adicionado um separador ';'
     * seria mais esperto colocar no final? Sim!
     * Mas por um motivo particular achei melhor definir no começo
    */
    strcat(*nameList, ";");
    strcat(*nameList, name);
    
    //printf("Nome digitado: %s\nTamanho name: %ld\nTamanho nameList: %ld\n", *nameList, strlen(name), strlen(*nameList));

}

void removeName(char **nameList){

    int chosenNameID,       //ID passado pelo user
        charID,             //ID do caractere
        nameSize = 0,       //Tamanho do nome selecionado
        nameIDCounter = 0,  //Conta os nomes na string
        stringCrowlerID;    //controla o id dos caracteres a serem reposicionados na string
    
    printf("\nDigite o id do nome a ser removido: ");
    scanf("%d", &chosenNameID);

    //Encontra a palavra
    for(charID = 0; charID < strlen(*nameList); charID++){

        if(nameList[0][charID] == ';'){
            nameIDCounter++;
            
            /**
            * Quando encontrar a palavra, o for termina e o "charID"
            * terá a posição inicial do nome
            */
            if(nameIDCounter == chosenNameID){
                break;
            }
        }
    }

    //Se a quantidade de nomes contados for menor que o id dado pelo user, então o id não existe
    if(nameIDCounter < chosenNameID){
        printf("O id fornecido não existe");
        return;
    }

    //Conta o tamanho do nome selecionado; no final, nameSize terá o tamanho do nome.
    do{
        nameSize++;
        printf("%c", nameList[0][charID+nameSize]);
    } while (nameList[0][charID+nameSize] != ';' && (charID+nameSize) < strlen(*nameList));


    /**
     * Basicamente reescreve o final da string a partir da posição inicial do nome
     * 
     * OBS 1: posição inicial do stringCrowlerID == posição final do nome
     * OBS 2: quando o for terminar, charID+nameSize será o tamanho final da string
    */
    for(stringCrowlerID = charID+nameSize; stringCrowlerID < strlen(*nameList); stringCrowlerID++, charID++){
        nameList[0][charID] = nameList[0][stringCrowlerID];
    }
    nameList[0][charID] = '\0';
    *nameList = (char *)realloc(*nameList, (charID+nameSize)*sizeof(char));
}

void list(char **nameList){
    int nameID = 0; //Só pra contar os nomes

    for(int charID = 0; charID < strlen(*nameList); charID++){
        if(nameList[0][charID] != ';'){            
            printf("%c", nameList[0][charID]);
        }else{
            printf("\n%d - ", (nameID+1)); //+1 pois mostrará o id do nome seguinte
            nameID++;
        }
    }
}