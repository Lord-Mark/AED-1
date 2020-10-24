
int ** criaMatriz(int *tamanhoMatrizColunaLinha){
    int **matriz;

    // Limpa a tela
    system("cls||clear");

    printf("Digite quantas colunas quer que a matriz tenha: ");
    scanf(" %d", &(tamanhoMatrizColunaLinha[0]));

    printf("Digite quantas linhas quer que a matriz tenha: ");
    scanf(" %d", &(tamanhoMatrizColunaLinha[1]));

    //Aloca as colunas
    matriz = (int **) malloc(sizeof(int *)*(tamanhoMatrizColunaLinha[0]));

    //Aloca todas as linhas
    for(int i = 0; i < tamanhoMatrizColunaLinha[0]; i++){
        matriz[i] = (int *) malloc(sizeof(int) * tamanhoMatrizColunaLinha[1]);
    }

    system("cls||clear");

    return matriz;
}

void inserirMatriz(int **matriz, int *tamanhoMatrizColunaLinha){

    for(int coluna=0; coluna< tamanhoMatrizColunaLinha[0]; coluna++){
        for (int  linha = 0; linha < tamanhoMatrizColunaLinha[1]; linha++)
        {
            printf("Digite o elemento %d,%d da matriz: ", coluna, linha);
            scanf(" %d", &(matriz[coluna][linha]));
        }
        
    }
}

int somaMatriz(int **matriz, int *tamanhoMatrizColunaLinha){
    
    int soma = 0;

    for(int col = 0; col < tamanhoMatrizColunaLinha[0]; col++){
        for (int lin = 0; lin < tamanhoMatrizColunaLinha[1]; lin++)
        {
            soma += matriz[col][lin];
        }
    }

    printf("\n\nA soma dos elementos é %d\n", soma);

}

// Adiciona mais uma coluna na matriz
int** inserirColuna(int ** matriz, int *tamanhoMatrizColunaLinha){

    int escolha;

    matriz = (int **)realloc(matriz, (tamanhoMatrizColunaLinha[0]+1)*sizeof(int*) );
    matriz[tamanhoMatrizColunaLinha[0]] = (int *) malloc(sizeof(int) * tamanhoMatrizColunaLinha[1]);
    
    printf("Deseja preencher a nova coluna?\n");
    printf("\t0 - Sim\n");
    printf("\t1 - Não\n");
    printf("Sua escolha: ");

    scanf(" %d", &escolha);

    if(!escolha){

        for(int linha = 0; linha < tamanhoMatrizColunaLinha[1]; linha++){

            printf("Digite o elemento %d,%d da matriz: ",
                    tamanhoMatrizColunaLinha[0],
                    linha
            );
            scanf(" %d", &(matriz[tamanhoMatrizColunaLinha[0]][linha]));

        }

    }
    tamanhoMatrizColunaLinha[0] += 1;

    return matriz;
}

void liberaMatriz(int **matriz, int *tamanhoMatrizColunaLinha){

    for(int coluna=0; coluna< tamanhoMatrizColunaLinha[0]; coluna++){
        free(matriz[coluna]);
    }
    free(matriz);
}

void imprimeMatriz(int **matriz, int *tamanhoMatrizColunaLinha){
    
    system("cls||clear");

    for(int coluna=0; coluna< tamanhoMatrizColunaLinha[0]; coluna++){
        for (int  linha = 0; linha < tamanhoMatrizColunaLinha[1]; linha++)
        {
            printf(" %d |", matriz[coluna][linha]);
        }
        printf("\n");
    }
}

void imprimeVetor (int *vetor, int tamanhoVetor) {

    for (int count = 0; count < tamanhoVetor; count++)
    {
        printf("%d\n", vetor[count]);
    }
    
}