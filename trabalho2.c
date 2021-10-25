#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct tm *data;

time_t segundos;

FILE *file,*arq, *tra;

struct t{

    int dia;
    int mes;
    int ano;

};

struct end{

    char pais[20];
    char estado[20];
    char cidade[20];
    char bairro[30];
    char rua[30];
    char numero[5];

};

struct clientes{

    char codigo[10];
    char nome[30];
    char cpf_cnpj[12];
    struct end endereco;
    char telefone[15];
};

typedef struct clientes cliente;

struct contas{

    cliente c;
    char agencia[20];
    char numero_da_conta[20];
    float saldo;
};

typedef struct contas conta;

struct transacao{
    char tipo[11];
    float valor;
    struct t tempo;
    conta acc;
    char descricao[100];
};
typedef  struct transacao transacao;

char debito[] = "DEBITO";
char credito[] = "CREDITO";


// funcoes parte clientes
void escrever_no_arquivo(cliente pessoa){

    file = fopen("clientes_cadastrados.txt","a");

    fputs(pessoa.codigo,file);
    fprintf(file,"\n");
    fputs(pessoa.nome,file);
    fprintf(file,"\n");
    fputs(pessoa.cpf_cnpj,file);
    fprintf(file,"\n");
    fputs(pessoa.telefone,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.pais,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.estado,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.cidade,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.bairro,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.rua,file);
    fprintf(file,"\n");
    fputs(pessoa.endereco.numero,file);
    fprintf(file,"\n");

    fclose(file);
}

int v_codigo_cpf(cliente **vetor,int contador){

    int cont1 = 0, cont2 = 0;

    for(int i = 0; i < contador; i++){
        if(strcmp(vetor[contador][0].cpf_cnpj,vetor[i][0].cpf_cnpj) == 0){
            cont1++;
        }
        if(strcmp(vetor[contador][0].codigo,vetor[i][0].codigo) == 0){
            cont2++;
        }
    }
    if(cont1 > 0 || cont2 > 0){
        return 1;
    }
    else{
        return 0;
    }
}

char ** listagem_clientes(char **lista, int contador){

    char **ptr;
    ptr = malloc(contador*sizeof(char*));
    //OK

    int i = 0;
    int cont1 = 0,cont2,cont3 = 0;

    while(i <= contador){

        if(contador > 1){

            for(int n = 0; n < contador; n++){

                if(tolower(lista[i][0]) < tolower(lista[n][0])){
                    cont1++;
                }
                if(tolower(lista[i][0]) == tolower(lista[n][0]) && i != n){
                    cont2 = 1;
                    do{

                        if(tolower(lista[i][cont2]) < tolower(lista[n][cont2])){
                            cont1++;
                        }
                        cont2++;

                    }while(tolower(lista[i][cont2]) == tolower(lista[n][cont2]));
                }

            }
            if(cont1 == contador - 1){

                ptr[cont3] = malloc(30*sizeof(char));
                strcpy(ptr[cont3],lista[i]);

                if( i != contador -1){
                    for(int m = i; m < (contador - 1); m++){

                        strcpy(lista[m],lista[m+1]);

                    }
                }

                lista = realloc(lista,(contador-1)*sizeof(char*));

                cont3 ++;

                i = 0;
                contador = contador - 1;
                cont1 = 0;
            }
            else{
                i++;
                cont1 = 0;
            }
        }
        else{
            ptr[cont3] = malloc(30*sizeof(char));
            strcpy(ptr[cont3],lista[i]);
            free(lista);
            break;
        }
    }

    return ptr;
}

void buscar_cliente(cliente **vetor,char codigo[],int contador){
    // se nao pegar do arquivo n vai ter \n e vai ficar baguncado
    int cont = 0;

    for(int i = 0; i < contador; i++){
        if(strcmp(vetor[i][0].codigo,codigo) == 0 || strcmp(vetor[i][0].cpf_cnpj,codigo) == 0 || strcmp(strlwr(vetor[i][0].nome),strlwr(codigo)) == 0){

            printf("-Codigo: %s\n",vetor[i][0].codigo);
            printf("-Nome: %s\n",vetor[i][0].nome);
            printf("-Cpf/Cnpj: %s\n",vetor[i][0].cpf_cnpj);
            printf("-Telefone: %s\n",vetor[i][0].telefone);
            printf("-Endereco\n");
            printf("\t-Pais: %s\n",vetor[i][0].endereco.pais);
            printf("\t-Estado: %s\n",vetor[i][0].endereco.estado);
            printf("\t-Cidade: %s\n",vetor[i][0].endereco.cidade);
            printf("\t-Bairro: %s\n",vetor[i][0].endereco.bairro);
            printf("\t-Rua: %s\n",vetor[i][0].endereco.rua);
            printf("\t-Numero: %s\n",vetor[i][0].endereco.numero);
            cont++;
        }
    }
    if(cont == 0){
        printf("\n CLIENTE NAO ENCONTRADO! \n");
    }
    printf("\n\n");
}

void atualizacao_de_cliente(cliente **vetor,char codigo[],int contador){

    int c,c1 = 0;
    for(int i = 0; i < contador; i++){

        if(strcmp(vetor[i][0].codigo,codigo) == 0 || strcmp(vetor[i][0].cpf_cnpj,codigo) == 0){
            c = i;
            c1++;
        }

    }

    if(c1 == 0){
        printf("\n CLIENTE NAO ENCONTRADO! \n");
    }

    else{
        printf("\nCodigo:");
        gets(vetor[c][0].codigo);
        fflush(stdin);

        printf("\nNome:");
        gets(vetor[c][0].nome);
        fflush(stdin);

        printf("\nCPF/CNPJ:");
        gets(vetor[c][0].cpf_cnpj);
        fflush(stdin);


        printf("\nTelefone:");
        gets(vetor[c][0].telefone);
        fflush(stdin);

        printf("\nEndereco");
        printf("\n-Pais..:");
        gets(vetor[c][0].endereco.pais);
        fflush(stdin);

        printf("-Estado:");
        gets(vetor[c][0].endereco.estado);
        fflush(stdin);

        printf("-Cidade:");
        gets(vetor[c][0].endereco.cidade);
        fflush(stdin);

        printf("-Bairro:");
        gets(vetor[c][0].endereco.bairro);
        fflush(stdin);

        printf("-Rua...:");
        gets(vetor[c][0].endereco.rua);
        fflush(stdin);

        printf("-Numero:");
        gets(vetor[c][0].endereco.numero);
        fflush(stdin);

    }
}

void excluir_cliente(cliente **vetor,char codigo[],int *contador){

    int c,c1 = 0;

    for(int i = 0; i < *contador; i++){
        if(strcmp(vetor[i][0].codigo,codigo) == 0 || strcmp(vetor[i][0].cpf_cnpj,codigo) == 0){
            c = i;
            c1++;
        }
    }
    if(c1 == 0){
        printf("\n CLIENTE NAO ENCONTRADO! \n");
    }
    else{

        if( c < *contador -1){
            for(int m = c; m < (*contador - 1); m++){

                vetor[m] = vetor[m + 1];

            }
        }
        *contador = *contador - 1;

    }
}

void linha(char palavra[]){
    int numero_de_caracteres = 50;
    int numero_de_simbolos;

    numero_de_simbolos = numero_de_caracteres - (strlen(palavra) + 2);
    if(numero_de_simbolos % 2 == 0){

        for(int i = 0; i <= (numero_de_simbolos/2); i++){
            printf("=");
        }

        printf(" %s ",palavra);

        for(int i = 0; i <= (numero_de_simbolos/2); i++){
            printf("=");
        }
        printf("\n");

    }else{
        for(int i = 0; i <= ((numero_de_simbolos + 1)/2) -1 ; i++){
            printf("=");
        }

        printf(" %s ",palavra);

        for(int i = 0; i <= ((numero_de_simbolos + 1)/2) +1 ; i++){
            printf("=");
        }
        printf("\n");
    }
}

char geren_clientes(){

    char comando_clientes;

    linha("Gerenciar Clientes");
    printf("Digite um comando para prosseguir:\n");
    printf("C - Cadastrar um cliente.\n");
    printf("L - Listar todos os clientes cadastrados.\n");
    printf("B - Buscar cliente ja cadastrado.\n");
    printf("A - Atualizar um cliente cadastrado.\n");
    printf("E - Excluir um cliente cadastrado.\n");
    printf("S - Sair\n");

    scanf("\n%c",&comando_clientes);

    return comando_clientes;
}

char geren_contas(){

    char comando_contas;

    linha("Gerenciar Contas");
    printf("R - Listagem de todas as contas cadastradas.\n");
    printf("C - Cadastrar uma conta para um cliente.\n");
    printf("L - Listar todas as contas de um cliente.\n");
    printf("W - Realizar o saque em uma conta.\n");
    printf("D - Realizar o deposito em uma conta.\n");
    printf("T - Realizar a transferencia entre contas.\n");
    printf("E - Exibir extrato de uma conta.\n");
    printf("S - Sair\n");

    scanf("\n%c",&comando_contas);

    return comando_contas;
}

char menu(){

    char comando_menu;

    linha("Bem vindo!");
    printf("Digite um comando_menu para prosseguir:\n");
    printf("C - Gerenciar clientes\n");
    printf("T - Gerenciar contas\n");
    printf("S - Sair\n");

    fflush(stdin);
    scanf("\n%c",&comando_menu);

    return comando_menu;
}
void cadastro(cliente **vetor, int *cont){

    //alterar aqui

    fflush(stdin);
    linha("Cadastro do cliente");
    printf("Insira os dados do cliente em seus devidos campos:\n");

    printf("\nCodigo:");
    gets(vetor[*cont][0].codigo);
    fflush(stdin);

    printf("\nNome:");
    gets(vetor[*cont][0].nome);
    fflush(stdin);

    printf("\nCPF/CNPJ:");
    gets(vetor[*cont][0].cpf_cnpj);
    fflush(stdin);


    printf("\nTelefone:");
    gets(vetor[*cont][0].telefone);
    fflush(stdin);

    printf("\nEndereco");
    printf("\n-Pais..:");
    gets(vetor[*cont][0].endereco.pais);
    fflush(stdin);

    printf("-Estado:");
    gets(vetor[*cont][0].endereco.estado);
    fflush(stdin);

    printf("-Cidade:");
    gets(vetor[*cont][0].endereco.cidade);
    fflush(stdin);

    printf("-Bairro:");
    gets(vetor[*cont][0].endereco.bairro);
    fflush(stdin);

    printf("-Rua...:");
    gets(vetor[*cont][0].endereco.rua);
    fflush(stdin);

    printf("-Numero:");
    gets(vetor[*cont][0].endereco.numero);
    fflush(stdin);

    if(v_codigo_cpf(vetor,*cont) == 1){

        printf("\nERRO! - Cliente ja cadastrado!\n");

        free(vetor[*cont]);
        *cont = *cont - 1;

    }
    else{

        escrever_no_arquivo(vetor[*cont][0]);

    }
    printf("\n");
}
void reescrever_arquivo(cliente **vetor, int contador){

    file = fopen("clientes_cadastrados.txt","w");

    for(int i = 0; i < contador; i++){
        fputs(vetor[i][0].codigo,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].nome,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].cpf_cnpj,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].telefone,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.pais,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.estado,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.cidade,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.bairro,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.rua,file);
        fprintf(file,"\n");
        fputs(vetor[i][0].endereco.numero,file);
        fprintf(file,"\n");
    }

    fclose(file);
}

//parte de contas
cliente *busca(cliente **vetor,int contador,char passe[]){

    int a = 0,c = 0;

    for(int i = 0; i < contador; i++){
        if(strcmp(vetor[i][0].codigo,passe) == 0){
          c = i;
          a++;
        }
    }
    for(int i = 0; i < contador; i++){
        if(strcmp(strlwr(vetor[i][0].nome),strlwr(passe)) == 0){
            c = i;
            a++;
        }
    }
    for(int i = 0; i < contador; i++){
        if(strcmp(vetor[i][0].cpf_cnpj,passe) == 0){
            c = i;
            a++;
        }
    }
    if(a == 0){
        return NULL;
    }
    else{
        return &vetor[c][0];
    }
}

int v_conta(conta **vetor,int contador){

    int cont = 0;

    for(int i = 0; i < contador; i++){
        if(strcmp(vetor[contador][0].numero_da_conta,vetor[i][0].numero_da_conta) == 0 && strcmp(vetor[contador][0].agencia,vetor[i][0].agencia) == 0){
            cont++;
        }
    }
    if(cont > 0){
        return 1;
    }
    else{
        return 0;
    }
}

void escrever_no_arquivo_para_contas(conta **vetor, int contador){

    arq = fopen("contas.txt","a");

    fputs(vetor[contador][0].c.codigo,arq);
    fprintf(arq,"\n");
    fputs(vetor[contador][0].agencia,arq);
    fprintf(arq,"\n");
    fputs(vetor[contador][0].numero_da_conta,arq);
    fprintf(arq,"\n");
    fprintf(arq,"%f",vetor[contador][0].saldo);
    fprintf(arq,"\n");

    fclose(arq);
}

void cadastro_de_conta(cliente **vet,int c,conta **vetor,int *contador){

    char passe[15];

    linha("Cadastro de conta");

    printf("\nInforme o codigo ou CPF/CNPJ do cliente a ser cadastrado:");
    fflush(stdin);
    gets(passe);

    if(busca(vet,c,strlwr(passe)) == NULL){
        printf("\nERRO! CLIENTE NAO ENCONTRADO!\n");
    }
    else{

        vetor[*contador][0].c = *busca(vet,c,passe);
        printf("\nInforme a agencia bancaria:");
        fflush(stdin);
        gets(vetor[*contador][0].agencia);

        printf("\nInforme o numero da conta:");
        fflush(stdin);
        gets(vetor[*contador][0].numero_da_conta);

        vetor[*contador][0].saldo = 0;

        if(v_conta(vetor,*contador) > 0){
            free(vetor[*contador]);
            *contador = *contador - 1;
            printf("\n\nERRO! CONTA JA CADASTRADA!\n\n");
        }
        else{
            escrever_no_arquivo_para_contas(vetor,*contador);
        }
    }
}


char ** listagem_todas_acc_cadastrdas(conta **vetor,int contador){

    int cont1;
    int cont2;
    int cont3 = 0;
    char **lista_ordenada;
    char **ptr;

    ptr = malloc(contador * sizeof(char *));
    for(int i = 0; i< contador; i++){
        ptr[i] = malloc(30*sizeof(char));
        strcpy(ptr[i],vetor[i][0].c.nome);
    }


    lista_ordenada = malloc(contador * sizeof(char *));
    for(int i = 0; i< contador; i++){

        lista_ordenada[i] = malloc(30*sizeof(char));

    }

    int n = 0;
    while(contador != 0){
        cont1 = 0;

        for(int m = 0; m < contador; m++){

            if(ptr[n][0] < ptr[m][0]){
                cont1++;
            }
            if(ptr[n][0] == ptr[m][0] && strcmp(ptr[n],ptr[m]) != 0){
                cont2 = 1;

                while(ptr[n][cont2] == ptr[m][cont2]){

                    if(ptr[n][cont2] < ptr[m][cont2]){
                        cont1++;
                    }

                    cont2++;
                }
            }
            if(strcmp(ptr[n],ptr[m]) == 0){
                cont1 ++;
            }
        }

        if(cont1 >= contador){
           strcpy(lista_ordenada[cont3],ptr[n]);
           cont3++;

           if(n <= (contador - 1)){
               for(int i = n; i < contador - 1; i++){
                   strcpy(ptr[i],ptr[i+1]);
               }
           }

           ptr = realloc(ptr,(contador - 1)*sizeof(char*));

           contador = contador - 1;
           n = 0;

           if(contador == 0)
               break;
        }
        else{
            n++;
        }
    }

    return lista_ordenada;
}
//arrumar
void printar_contas(char **lista, conta **vetor, int contador, int contador2){

    conta ** ptr;
    int cont;
    int cont2;
    ptr = malloc(contador*sizeof(conta*));

    for(int i = 0; i < contador2; i++){

        if( i > 0 && strcmp(lista[i - 1],lista[i]) == 0){
            continue;
        }

        ptr[i] = malloc(1*sizeof(conta));
        cont = 0;

        for(int n = 0; n < contador; n++){

            if(strcmp(vetor[n][0].c.nome, lista[i]) == 0 && cont != 0){
                ptr[i] = realloc(ptr[i],(cont+1)*sizeof(conta));
                ptr[i][cont] = vetor[n][0];
                cont++;
            }

            if(strcmp(vetor[n][0].c.nome, lista[i]) == 0 && cont == 0){
                ptr[i][cont] = vetor[n][0];
                cont++;
            }
        }

        cont2 = 0;
        int n = 0;
        int c = 0;

        printf("\n%s\n",lista[i]);

        while(cont != 0){

            int m = 0;
            cont2 = 0;

            while(m < cont){

                if(ptr[i][n].saldo >= ptr[i][m].saldo){
                    cont2 ++;
                }
                m++;

            }

            if(cont2 == cont){
                printf("\n----Conta %d:",c+1);
                c++;
                printf("\n----Numero da Conta: %s",ptr[i][n].numero_da_conta);
                printf("\n----Agencia: %s",ptr[i][n].agencia);
                printf("\n----Saldo: %f\n",ptr[i][n].saldo);

                if(n < (cont -1)){
                    for(int x = n; x < cont - 1; x++){
                        ptr[i][x] = ptr[i][x + 1];

                    }
                }

                n = 0;
                cont = cont - 1;
                if(cont == 0){
                    break;
                }
            }

            else{
                n++;
            }
        }
    }
    printf("\n");

   /* for(int i = 0; i < contador2; i++){
        free(ptr[i]);
    }
    free(ptr);*/

}
conta pegar_acc(char agencia[],char numero[], conta **vetor, int contador){

    int c;

    for(int n = 0; n < contador; n++){

        if(strcmp(strlwr(agencia),strlwr(vetor[n][0].agencia)) == 0 && strcmp(numero,vetor[n][0].numero_da_conta) == 0){
            c = n;
        }
    }

    return vetor[c][0];

}

void saque(conta **vetor, int contador, transacao *v_transacao, int *contador_transacao){

    time(&segundos);
    data = localtime(&segundos);

    char agencia[20],numero[20];
    int c = 0, cont = 0;

    linha("REALIZAR SAQUE");
    printf("Informe a agencia do cliente:");
    fflush(stdin);
    gets(agencia);
    printf("\nInforme o numero da conta que deseja realizar o saque:");
    fflush(stdin);
    gets(numero);
    printf("\n");


        for(int n = 0; n < contador; n++){

            if(strcmp(strlwr(agencia),strlwr(vetor[n][0].agencia)) == 0 && strcmp(numero,vetor[n][0].numero_da_conta) == 0){
                c = n;
                cont ++;
            }

        }
    if(cont == 0){
        printf("\nERRO! CONTA NAO ENCONTRADA!\n");
    }
    else{
        printf("Cliente: %s\n",vetor[c][0].c.nome);
        printf("CPF/CNPJ: %s\n",vetor[c][0].c.cpf_cnpj);
        printf("Agencia: %s\n",strupr(vetor[c][0].agencia));
        printf("Numero da conta: %s\n",vetor[c][0].numero_da_conta);
        printf("Saldo: %.4f\n",vetor[c][0].saldo);

        float quantidade = 0;
        do{

            fflush(stdin);
            printf("\nInforme a quantidade de dinheiro que deseja sacar:");
            scanf("%f",&quantidade);

            if(quantidade > vetor[c][0].saldo){
                printf("\nERRO! INFORME UMA QUANTIA MENOR QUE O SALDO DISPONIVEL!\n");
            }

        }while(quantidade > vetor[c][0].saldo);


        char descricao[100];
        fflush(stdin);
        printf("\nInforme a descricao do saque:");
        gets(descricao);

        strcpy(v_transacao[*contador_transacao].tipo,debito);
        v_transacao[*contador_transacao].valor = quantidade;
        v_transacao[*contador_transacao].tempo.dia = data -> tm_mday;
        v_transacao[*contador_transacao].tempo.mes = data -> tm_mon+1;
        v_transacao[*contador_transacao].tempo.ano = data -> tm_year+1900;
        v_transacao[*contador_transacao].acc = vetor[c][0];
        strcpy(v_transacao[*contador_transacao].descricao,descricao);

        vetor[c][0].saldo = vetor[c][0].saldo - quantidade;

        *contador_transacao = *contador_transacao + 1;

        int vetor_notas[7] = {200,100,50,20,10,5,2};
        int frequencia_notas[7] = {0,0,0,0,0,0,0};
        int cont1 = 0;

        printf("\nO valor sera sacado em:\n");
        while(quantidade != 0){

            if(quantidade >= (float) vetor_notas[cont1]){
                quantidade = quantidade - (float) vetor_notas[cont1];
                frequencia_notas[cont1]++;
            }
            if((float) vetor_notas[cont1] > quantidade){
                if(frequencia_notas[cont1] > 0){
                    printf("%d notas de %d\n",frequencia_notas[cont1],vetor_notas[cont1]);
                }
                cont1++;
            }
            if(quantidade < 2){
                break;
            }

        }

    }


}
void rescrever_no_arquivo_para_contas(conta **vetor, int contador){

    arq = fopen("contas.txt","w");

    for(int i = 0; i < contador; i++){

        fputs(vetor[i][0].c.codigo,arq);
        fprintf(arq,"\n");
        fputs(vetor[i][0].agencia,arq);
        fprintf(arq,"\n");
        fputs(vetor[i][0].numero_da_conta,arq);
        fprintf(arq,"\n");
        fprintf(arq,"%f",vetor[i][0].saldo);
        fprintf(arq,"\n");

    }
    fclose(arq);

}
void arquivar_transacoes(transacao *vetor,int contador){

    tra = fopen("transacoes.txt","w");

    for(int i = 0; i < contador; i++){

        fputs(vetor[i].tipo,tra);
        fprintf(tra,"\n");
        fprintf(tra,"%f",vetor[i].valor);
        fprintf(tra,"\n");
        fputs(vetor[i].acc.agencia,tra);
        fprintf(tra,"\n");
        fputs(vetor[i].acc.numero_da_conta,tra);
        fprintf(tra,"\n");
        fprintf(tra,"%d/%d/%d",vetor[i].tempo.dia,vetor[i].tempo.mes,vetor[i].tempo.ano);
        fprintf(tra,"\n");
        fputs(vetor[i].descricao,tra);
        fprintf(tra,"\n");

    }
    fclose(tra);

}
void deposito(conta **vetor, int contador, transacao *v_transacao, int *contador_transacao){

    time(&segundos);
    data = localtime(&segundos);

    char agencia[20],numero[20];
    int c = 0, cont = 0;

    printf("Informe a agencia do cliente:");
    fflush(stdin);
    gets(agencia);
    printf("\nInforme o numero da conta que deseja realizar o deposito:");
    fflush(stdin);
    gets(numero);
    printf("\n");


    for(int n = 0; n < contador; n++){

        if(strcmp(strlwr(agencia),strlwr(vetor[n][0].agencia)) == 0 && strcmp(numero,vetor[n][0].numero_da_conta) == 0){
            c = n;
            cont ++;
        }

    }
    if(cont == 0){
        printf("\nERRO! CONTA NAO ENCONTRADA!\n");
    }
    else{
        printf("Cliente: %s\n",vetor[c][0].c.nome);
        printf("CPF/CNPJ: %s\n",vetor[c][0].c.cpf_cnpj);
        printf("Agencia: %s\n",strupr(vetor[c][0].agencia));
        printf("Numero da conta: %s\n",vetor[c][0].numero_da_conta);
        printf("Saldo: %.4f\n",vetor[c][0].saldo);

        float quantidade = 0;

        fflush(stdin);
        printf("\nInforme a quantidade de dinheiro que deseja depositar:");
        scanf("%f",&quantidade);


        char descricao[100];
        fflush(stdin);
        printf("\nInforme a descricao do saque:");
        gets(descricao);

        strcpy(v_transacao[*contador_transacao].tipo,credito);
        v_transacao[*contador_transacao].valor = quantidade;
        v_transacao[*contador_transacao].tempo.dia = data -> tm_mday;
        v_transacao[*contador_transacao].tempo.mes = data -> tm_mon+1;
        v_transacao[*contador_transacao].tempo.ano = data -> tm_year+1900;
        v_transacao[*contador_transacao].acc = vetor[c][0];
        strcpy(v_transacao[*contador_transacao].descricao,descricao);

        vetor[c][0].saldo += quantidade;

        *contador_transacao = *contador_transacao + 1;
    }
}
void transferencia(conta **vetor, int contador, transacao *v_transacao, int *contador_transacao){

    time(&segundos);
    data = localtime(&segundos);

    char agencia[20],numero[20];
    int a = 0,b = 0,cont = 0;

    printf("Informe a agencia da conta de origem:");
    fflush(stdin);
    gets(agencia);
    printf("\nInforme o numero da conta de origem:");
    fflush(stdin);
    gets(numero);
    printf("\n");


    for(int n = 0; n < contador; n++){

        if(strcmp(strlwr(agencia),strlwr(vetor[n][0].agencia)) == 0 && strcmp(numero,vetor[n][0].numero_da_conta) == 0){
            a = n;
            cont ++;
        }

    }
    if(cont == 0){
        printf("\nERRO! CONTA NAO ENCONTRADA!\n");
    }
    else{
        printf("Cliente: %s\n",vetor[a][0].c.nome);
        printf("CPF/CNPJ: %s\n",vetor[a][0].c.cpf_cnpj);
        printf("Agencia: %s\n",strupr(vetor[a][0].agencia));
        printf("Numero da conta: %s\n",vetor[a][0].numero_da_conta);
        printf("Saldo: %.4f\n",vetor[a][0].saldo);

        printf("\nInforme a agencia da conta de destino:");
        fflush(stdin);
        gets(agencia);
        printf("\nInforme o numero da conta de destino:");
        fflush(stdin);
        gets(numero);
        printf("\n");

        cont = 0;
        for(int n = 0; n < contador; n++){
            
            if(strcmp(strlwr(agencia),strlwr(vetor[n][0].agencia)) == 0 && strcmp(numero,vetor[n][0].numero_da_conta) == 0){
                b = n;
                cont ++;
            }

        }
        if(cont == 0){
            printf("\nERRO! CONTA NAO ENCONTRADA!\n");
        }
        else{
            printf("Cliente: %s\n",vetor[b][0].c.nome);
            printf("CPF/CNPJ: %s\n",vetor[b][0].c.cpf_cnpj);
            printf("Agencia: %s\n",strupr(vetor[b][0].agencia));
            printf("Numero da conta: %s\n",vetor[b][0].numero_da_conta);
            printf("Saldo: %.4f\n",vetor[b][0].saldo);

            float quantidade = 0;
            do{

                fflush(stdin);
                printf("\nInforme a quantidade de dinheiro que deseja transferir:");
                scanf("%f",&quantidade);

                if(quantidade > vetor[a][0].saldo){
                    printf("\nERRO! INFORME UMA QUANTIA MENOR QUE O SALDO DISPONIVEL!\n");
                }

            }while(quantidade > vetor[a][0].saldo);


            char descricao1[100] = "Transferencia para conta: ",ag[15],nc[15];
            strcpy(ag,vetor[b][0].agencia);
            strcpy(nc,vetor[b][0].numero_da_conta);
            strcat(descricao1,ag);
            strcat(descricao1," - ");
            strcat(descricao1,nc);

            char descricao2[100] = "Transferencia de conta: ";
            strcpy(ag,vetor[a][0].agencia);
            strcpy(nc,vetor[a][0].numero_da_conta);
            strcat(descricao2,ag);
            strcat(descricao2," - ");
            strcat(descricao2,nc);

            vetor[a][0].saldo -= quantidade;
            vetor[b][0].saldo += quantidade;

            strcpy(v_transacao[*contador_transacao].tipo,debito);
            v_transacao[*contador_transacao].valor = quantidade;
            v_transacao[*contador_transacao].tempo.dia = data -> tm_mday;
            v_transacao[*contador_transacao].tempo.mes = data -> tm_mon+1;
            v_transacao[*contador_transacao].tempo.ano = data -> tm_year+1900;
            v_transacao[*contador_transacao].acc = vetor[a][0];
            strcpy(v_transacao[*contador_transacao].descricao,descricao1);

            *contador_transacao = *contador_transacao + 1;

            strcpy(v_transacao[*contador_transacao].tipo,credito);
            v_transacao[*contador_transacao].valor = quantidade;
            v_transacao[*contador_transacao].tempo.dia = data -> tm_mday;
            v_transacao[*contador_transacao].tempo.mes = data -> tm_mon+1;
            v_transacao[*contador_transacao].tempo.ano = data -> tm_year+1900;
            v_transacao[*contador_transacao].acc = vetor[b][0];
            strcpy(v_transacao[*contador_transacao].descricao,descricao2);

            *contador_transacao = *contador_transacao + 1;

        }
    }
}
void extrato(conta **vetor_c,int contador_contas,transacao *vetor, int contador){
    time(&segundos);
    data = localtime(&segundos);

    linha("EXIBIR EXTRATO DE UMA CONTA");

    int tempo_presente = ((data->tm_mday * data->tm_mon) * data ->tm_year) - ((vetor[0].tempo.dia * vetor[0].tempo.mes) * vetor[0].tempo.ano);

    char agencia[20],numero[20];
    int a = 0,cont = 0;

    printf("Informe a agencia da conta a qual tera o extrato exibido:");
    fflush(stdin);
    gets(agencia);
    printf("\nInforme o numero da conta de origem a qual tera o extrato exibido:");
    fflush(stdin);
    gets(numero);
    printf("\n");


    for(int n = 0; n < contador_contas; n++){

        if(strcmp(strlwr(agencia),strlwr(vetor_c[n][0].agencia)) == 0 && strcmp(numero,vetor_c[n][0].numero_da_conta) == 0){
            a = n;
            cont ++;
        }

    }
    if(cont == 0){
        printf("\nERRO! CONTA NAO ENCONTRADA!\n");
    }
    else{

        int q_dias;
        printf("Informe a quantidade de dias que deseja exibir o extrato:");
        fflush(stdin);
        scanf("%d",&q_dias);
        printf("\n");

        int t_analise = tempo_presente - q_dias;

        int t_extrato;
        for(int i = contador; i >= 0; i--){

            t_extrato = ((vetor[i].tempo.dia * vetor[i].tempo.mes) * vetor[i].tempo.ano) - ((vetor[0].tempo.dia * vetor[0].tempo.mes) * vetor[0].tempo.ano);

            if(t_extrato > t_analise && strcmp(vetor[i].acc.agencia,agencia) == 0 && strcmp(vetor[i].acc.numero_da_conta,numero) == 0){
                printf("Tipo: %s\nValor: %f\nData: %d/%d/%d\nAgencia: %s\nNumero da conta: %s\nDescricao: %s\n\n",vetor[i].tipo,vetor[i].valor,vetor[i].tempo.dia,vetor[i].tempo.mes,vetor[i].tempo.ano,
                       vetor[i].acc.agencia,vetor[i].acc.numero_da_conta,vetor[i].descricao);
            }
        }
    }

}

int main(){

    cliente **vetor_cadastro;
    int contador_cadastro;
    int posicao = 0;

    file = fopen("clientes_cadastrados.txt","r");

    int p0 = ftell(file);
    fseek(file, 0, SEEK_END);
    int pf = ftell(file);

    if(p0 == pf){

        vetor_cadastro = malloc(1*sizeof(cliente*));
        contador_cadastro = 0;
        vetor_cadastro[contador_cadastro] = malloc(1*sizeof(cliente));

    }
    else{

        //Ponteiro de ponteiro para poder excluir clientes com o free
        vetor_cadastro = malloc(1*sizeof(cliente*));
        contador_cadastro = 0;
        vetor_cadastro[contador_cadastro] = malloc(1*sizeof(cliente));

        fseek(file,0,SEEK_SET);
        while(posicao != pf){

            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].codigo);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].nome);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].cpf_cnpj);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].telefone);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.pais);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.estado);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.cidade);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.bairro);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.rua);
            fscanf(file,"\n");
            fscanf(file,"%[^\n]",vetor_cadastro[contador_cadastro][0].endereco.numero);
            fscanf(file,"\n");

            posicao = ftell(file);
            contador_cadastro++;
            vetor_cadastro = realloc(vetor_cadastro,(contador_cadastro+1) * sizeof(cliente*));
            vetor_cadastro[contador_cadastro] = malloc(1*sizeof(cliente));
        }
    }
    fclose(file);

    posicao = 0;

    conta **vetor_contas;
    int contador_contas;

    arq = fopen("contas.txt","r");

    p0 = ftell(arq);
    fseek(arq,0,SEEK_END);
    pf = ftell(arq);

    if(p0 == pf){

        vetor_contas = malloc(1*sizeof(conta *));
        contador_contas = 0;
        vetor_contas[contador_contas] = malloc(1*sizeof(conta));

    }
    else{

        vetor_contas = malloc(1*sizeof(conta *));
        contador_contas = 0;
        vetor_contas[contador_contas] = malloc(1*sizeof(conta));

        fseek(file,0,SEEK_SET);
        while(posicao != pf){

            char cod[10];
            fscanf(arq,"%[^\n]",cod);
            fscanf(arq,"\n");
            vetor_contas[contador_contas][0].c = *busca(vetor_cadastro,contador_cadastro,cod);
            fscanf(arq,"%[^\n]",vetor_contas[contador_contas][0].agencia);
            fscanf(arq,"\n");
            fscanf(arq,"%[^\n]",vetor_contas[contador_contas][0].numero_da_conta);
            fscanf(arq,"\n");
            fscanf(arq,"%f",&vetor_contas[contador_contas][0].saldo);
            fscanf(arq,"\n");

            posicao = ftell(arq);
            contador_contas++;
            vetor_contas = realloc(vetor_contas,(contador_contas +1)*sizeof(conta *));
            vetor_contas[contador_contas] = malloc(1*sizeof(conta));

        }
    }
    fclose(arq);

    posicao = 0;

    transacao *vetor_transacao;
    int contador_transacao;

    tra = fopen("transacoes.txt","r");

    p0 = ftell(tra);
    fseek(arq,0,SEEK_END);
    pf = ftell(tra);

    if(p0 == pf){

        vetor_transacao = malloc(1*sizeof(transacao));
        contador_transacao = 0;

    }
    else{

        vetor_transacao = malloc(1*sizeof(transacao));
        contador_transacao = 0;

        fseek(file,0,SEEK_SET);
        while(posicao != pf){

            fscanf(tra,"%[^\n]",vetor_transacao[contador_transacao].tipo);
            fscanf(tra,"\n");
            fscanf(tra,"%f",&vetor_transacao[contador_transacao].valor);
            fscanf(tra,"\n");

            char agencia[12];
            char numero[12];
            fscanf(tra,"%[^\n]",agencia);
            fscanf(tra,"\n");
            fscanf(tra,"%[^\n]",numero);
            fscanf(tra,"\n");
            vetor_transacao[contador_transacao].acc = pegar_acc(agencia,numero,vetor_contas,contador_contas);

            fscanf(tra,"%d/%d/%d",&vetor_transacao[contador_transacao].tempo.dia,&vetor_transacao[contador_transacao].tempo.mes,&vetor_transacao[contador_transacao].tempo.ano);
            fscanf(tra,"\n");
            fscanf(tra,"%[^\n]",vetor_transacao[contador_transacao].descricao);
            fscanf(tra,"\n");

            posicao = ftell(tra);
            contador_transacao++;
            vetor_transacao = realloc(vetor_transacao,(contador_transacao +1)*sizeof(transacao));

        }
    }
    fclose(tra);

    char comando = ' ';
    char comando1 = ' ';

    while(tolower(comando) != 's'){

        comando = menu();

        if(tolower(comando) == 'c' ){

            while(tolower(comando1) != 's'){
                comando1 = geren_clientes();

                if(tolower(comando1) == 'c'){

                    cadastro(vetor_cadastro,&contador_cadastro);
                    contador_cadastro++;
                    vetor_cadastro = realloc(vetor_cadastro,(contador_cadastro+1) * sizeof(cliente*));
                    vetor_cadastro[contador_cadastro] = malloc(1*sizeof(cliente));

                }

                if(tolower(comando1) == 'l'){

                    char **lista_nomes;
                    lista_nomes = malloc((contador_cadastro)*sizeof(char*));

                    for(int i = 0; i < contador_cadastro; i++){

                        lista_nomes[i] = malloc(30*sizeof(char));
                        strcpy(lista_nomes[i],vetor_cadastro[i][0].nome);


                    }

                    char **lista = listagem_clientes(lista_nomes,contador_cadastro);

                    linha("LISTAGEM DE TODOS OS CLIENTES CADASTRADOS");

                    for(int i = 0; i < contador_cadastro; i++){

                        printf("-%s\n",lista[i]);

                    }

                }
                char codigo[30];

                if(tolower(comando1) == 'b'){

                    linha("Busca por cliente");
                    printf("Digite o nome completo, codigo ou cpf do cliente que desejas buscar:");
                    fflush(stdin);
                    gets(codigo);
                    printf("\n");
                    buscar_cliente(vetor_cadastro,codigo,contador_cadastro);

                }

                if(tolower(comando1) == 'a'){

                    linha("Atualizar um cliente cadastrado");
                    printf("Informe o codigo ou CPF/CNPJ do cliente que deseja atualizar:");
                    fflush(stdin);
                    gets(codigo);
                    atualizacao_de_cliente(vetor_cadastro,codigo,contador_cadastro);

                }

                if(tolower(comando1) == 'e'){
                    linha("Excluir um cliente cadastrado");
                    printf("Informe o codigo ou CPF/CNPJ do cliente que deseja excluir:");
                    fflush(stdin);
                    gets(codigo);
                    excluir_cliente(vetor_cadastro,codigo,&contador_cadastro);
                    vetor_cadastro = realloc(vetor_cadastro,contador_cadastro*sizeof(cliente*));

                }

            }
            comando1 = ' ';
            reescrever_arquivo(vetor_cadastro,contador_cadastro);
        }

        // Tudo certo!! :v
        if(tolower(comando) == 't'){


            while(tolower(comando1) != 's'){

                comando1 = geren_contas();

                if(tolower(comando1) == 'r'){
                    //listagem de todas as contas cadastrads
                    char **listagem;
                    linha("LISTAGEM DE TODAS AS CONTAS CADASTRADAS");
                    listagem = listagem_todas_acc_cadastrdas(vetor_contas,contador_contas);
                    printar_contas(listagem,vetor_contas,contador_contas,contador_contas);
                }

                if(tolower(comando1) == 'c'){
                    //cadastrar uma conta para um cliente
                    cadastro_de_conta(vetor_cadastro,contador_cadastro,vetor_contas,&contador_contas);
                    contador_contas++;
                    vetor_contas = realloc(vetor_contas,(contador_contas+1)*sizeof(conta *));
                    vetor_contas[contador_contas] = malloc(1*sizeof(conta));


                }

                if(tolower(comando1) == 'l'){
                    //listagem de todas as contas de um cliente
                    linha("LISTAGEM DAS CONTAS DE UM CLIENTE");
                    printf("Informe o codigo ou CPF/CNPJ do cliente:");
                    char passe[20];
                    fflush(stdin);
                    gets(passe);
                    char **nome = malloc(1*sizeof(char*));
                    nome[0] = malloc(30 * sizeof(char));
                    if(busca(vetor_cadastro,contador_cadastro,passe) == NULL){
                        printf("\nERRO! CLIENTE NAO ENCONTRADO!\n");
                    }
                    else{
                        strcpy(nome[0],busca(vetor_cadastro,contador_cadastro,passe)->nome);
                        printar_contas(nome,vetor_contas,contador_contas,1);

                        free(nome[0]);
                        free(nome);
                    }
                }

                if(tolower(comando1) == 'w'){
                    //Realizar saque em uma conta
                    saque(vetor_contas,contador_contas,vetor_transacao,&contador_transacao);
                    vetor_transacao = realloc(vetor_transacao,(contador_transacao + 1)*sizeof(transacao));

                }

                if(tolower(comando1) == 'd'){
                    //Realizar deposito em uma conta
                    linha("REALIZAR DEPOSITO EM UMA CONTA");
                    deposito(vetor_contas,contador_contas,vetor_transacao,&contador_transacao);
                    vetor_transacao = realloc(vetor_transacao,(contador_transacao + 1)*sizeof(transacao));

                }

                if(tolower(comando1) == 't'){
                    //Realizar transferencia entre contas
                    linha("REALIZAR TRANSACAO");
                    vetor_transacao = realloc(vetor_transacao,(contador_transacao + 2)*sizeof(transacao));
                    transferencia(vetor_contas,contador_contas,vetor_transacao,&contador_transacao);
                    vetor_transacao = realloc(vetor_transacao,(contador_transacao + 1)*sizeof(transacao));
                }

                if(tolower(comando1) == 'e'){
                    //Exibir extrato de uma conta
                    extrato(vetor_contas,contador_contas,vetor_transacao,contador_transacao);
                }

            }
            comando1 = ' ';
        }
        rescrever_no_arquivo_para_contas(vetor_contas,contador_contas);
    }
    arquivar_transacoes(vetor_transacao,contador_transacao);

    return 0;
}