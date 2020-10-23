typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

void * inserirPessoa(Pessoa *registros, int *tamanhoRegistro){
    //Se o tamanho do registro for zero, ele aloca a primeira posição
    
    if(!*tamanhoRegistro){
        registros = (Pessoa *) malloc(sizeof(Pessoa)*1);
    }else
    {
        registros = (Pessoa *) realloc(registros, sizeof(Pessoa)*(*tamanhoRegistro+1));
    }
    
    printf("Digite um nome: ");
    scanf(" %[^\n]", registros[*tamanhoRegistro].nome);

    printf("Digite a idade de %s: ", registros[*tamanhoRegistro].nome);
    scanf(" %d", &(registros[*tamanhoRegistro].idade));

    printf("Digite a altura (cm) de %s: ", registros[*tamanhoRegistro].nome);
    scanf(" %d", &(registros[*tamanhoRegistro].altura));

    *tamanhoRegistro += 1;

    return registros;
}

void listar(Pessoa *registros, int tamanhoRegistro){
    
    for(int counter = 0; counter < tamanhoRegistro; counter++){

        // O print ia ficar muito grande, então declarei desta forma
        // pois as PSR's do PHP dizem que por convenção se deve
        // quebrar +/- assim declarações muito extensas para facilitar a leitura
        printf("\n%s: idade %d anos, altura: %d cm\n",
                registros[counter].nome,
                registros[counter].idade,
                registros[counter].altura
        );

                                            
    }
}