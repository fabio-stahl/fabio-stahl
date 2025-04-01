#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define MIN_ID 1000000
#define MAX_ID 9999999

FILE *arq;
FILE *rel;

// Definição das estruturas
struct Cliente {
    int id;
    char nome[20];
    char end[50];
    char tip_env[15];
};

struct Veiculo {
    int id;
    char tipo[10];
    int capacidade;
    char status[7];
};

struct Entrega {
    int id;
    char orig[50];
    char dest[50];
    int temph;
};

struct Empregado {
    int id;
    char nome[50];
};

struct relatorio{
    int idF,idE,idV,idC;
    char orig[50], dest[50];
    int TempT;
};

// Variáveis globais para armazenar dados
struct Cliente cliente;
struct Veiculo veiculo;
struct Entrega entrega;
struct Empregado empregado;
struct relatorio Strrela;

// Declaração das funções
void ver();
void vizualizar();
void ver_tudo();
void vizu_tudo();
void vizu_especifico();
void vizu_cliente();
void vizu_veiculo();
void vizu_entrega();
void vizu_empregado();
int id_existe();
int id();
void cadastrarCliente();
void cadastrarVeiculo();
int cadastrarEntrega();
void cadastrarEmpregado();
int gerar_id();
int executar();
void copiar_exc(FILE *arqorig, FILE *arqtemp, int idBusca);
void excluir();
void editar();
void rela();
void doc();
void abrir();

int main() {
    setlocale(LC_ALL, "Portuguese");  // Corrige acentos no terminal
    int opcao=0;
    char nome[10];

    do{
        printf("\nDigite a opção desejada:\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Veículo\n");
        printf("3 - Cadastrar Entrega\n");
        printf("4 - Cadastrar Funcionário: \n");
        printf("5 - Executar entrega\n");
        printf("6 - Excluir dados\n");
        printf("7 - Editar dados\n");
        printf("8 - Gerar relatório\n");
        printf("9 - Visualizar Dados\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);
        getchar(); // Evita problemas no buffer após scanf

        switch (opcao) {
            case 1:
                doc(opcao,nome);
                cadastrarCliente();
                break;
            case 2:
                doc(opcao,nome);
                cadastrarVeiculo();
                break;
            case 3:
                doc(opcao,nome);
                cadastrarEntrega();
                break;
            case 4:
                doc(opcao,nome);
                cadastrarEmpregado();
                break;
            case 5:
                executar();
                break;
            case 6:
                excluir();
                break;
            case 7:
                editar();
                break;
            case 8:
                rela();
                break;
            case 9:
                vizualizar();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

void doc(int n, char *nome){

    switch(n){
    case 1:
        strcpy(nome,"cliente.dat");
        abrir(nome);
        break;
    case 2:
        strcpy(nome,"veiculo.dat");
        abrir(nome);
        break;
    case 3:
        strcpy(nome,"entrega.dat");
        abrir(nome);
        break;
    case 4:
        strcpy(nome,"empregado.dat");
        abrir(nome);
        break;
    }

}

// Função para abrir cada um dos arquivos de texto
void abrir(char *nome) {
    arq = fopen(nome, "a+b");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }
}

void rela(){
    FILE * ft;
    ft=fopen("relatorio.dat","rb");
    if(!ft){
        printf("Falha ao abrir relatório");
        return;
    }
    while(fread(&Strrela,sizeof(struct relatorio),1,ft) == 1){
        printf("\n ID do Funcionário: %i \n ID da Entrega: %i \n ID do Veículo: %i \n ID do Cliente: %i \n Origem: %s \n Destino: %s \n Tempo da entrega: %i horas\n\n\n",Strrela.idF,Strrela.idE,Strrela.idV,Strrela.idC,Strrela.orig,Strrela.dest,Strrela.TempT);
    }
    fclose(ft);
}

// Cadastro de Cliente
void cadastrarCliente() {
    int sucesso=0;
    cliente.id = id(3);
    printf("ID Cliente: %d\n", cliente.id);

    printf("Nome: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    printf("Endereço: ");
    fgets(cliente.end, sizeof(cliente.end), stdin);
    cliente.end[strcspn(cliente.end, "\n")] = '\0';

    printf("Tipo de envio: ");
    fgets(cliente.tip_env, sizeof(cliente.tip_env), stdin);
    cliente.tip_env[strcspn(cliente.tip_env, "\n")] = '\0';
    sucesso = fwrite(&cliente,sizeof(struct Cliente),1,arq);
    fclose(arq);
    if(sucesso){
        printf("Cliente cadastrado com Sucesso!\n");
    }
    else{
        printf("Falha ao cadastrar Cliente!\n");
    }
}

// Cadastro de Veículo
void cadastrarVeiculo() {
    int sucesso = 0, esc=-1;
    veiculo.id = id(4);
    printf("ID Veículo: %d\n", veiculo.id);

    printf("Capacidade do veículo: ");
    scanf("%d", &veiculo.capacidade);
    getchar(); // Limpa buffer

    printf("Tipo do Veículo: \n");
    printf("1 - Moto\n");
    printf("2 - Carro\n");
    printf("3 - Van\n");
    scanf("%d", &esc);
    switch(esc){
        case 1:
           strcpy(veiculo.tipo, "Moto");
           break;
        case 2:
            strcpy(veiculo.tipo, "Carro");
            break;
        case 3:
            strcpy(veiculo.tipo, "Van");
            break;
        default:
            printf("Opção inválida\n");
    }
    printf("Status do veículo: \n");
    printf("1 - Livre\n");
    printf("2 - Ocupado\n");
    scanf("%d", &esc);
    switch(esc){
        case 1:
           strcpy(veiculo.status, "livre");
           break;
        case 2:
            strcpy(veiculo.status, "ocupado");
            break;
        default:
            printf("Opção inválida\n");
    }
    sucesso = fwrite(&veiculo,sizeof(struct Veiculo),1,arq);
    fclose(arq);
    if(sucesso){
        printf("Veículo cadastrado com Sucesso!\n");
    }
    else{
        printf("Falha ao cadastrar Veículo!\n");
    }
}

// Cadastro de Entrega
int cadastrarEntrega() {
    int sucesso;
    entrega.id = id(2);
    printf("ID Entrega: %d\n", entrega.id);

    printf("Origem: ");
    fgets(entrega.orig, sizeof(entrega.orig), stdin);
    entrega.orig[strcspn(entrega.orig, "\n")] = '\0';

    printf("Destino: ");
    fgets(entrega.dest, sizeof(entrega.dest), stdin);
    entrega.dest[strcspn(entrega.dest, "\n")] = '\0';

    printf("Tempo de entrega estimado em horas: ");
    scanf("%i",&entrega.temph);
    getchar();

    sucesso = fwrite(&entrega,sizeof(struct Entrega),1,arq);
    fclose(arq);
    if(sucesso){
        printf("Entrega cadastrada com Sucesso!\n");
    }
    else{
        printf("Falha ao cadastrar Entrega!\n");
    }
    return 0;
}

// Cadastro de Empregado
void cadastrarEmpregado() {
    int sucesso=0;
    empregado.id = id(1);
    printf("ID Empregado: %d\n", empregado.id);
    printf("Nome do empregado: ");
    fgets(empregado.nome, sizeof(empregado.nome), stdin);
    empregado.nome[strcspn(empregado.nome, "\n")] = '\0';
    sucesso = fwrite(&empregado,sizeof(struct Empregado),1,arq);
    fclose(arq);
    if(sucesso){
        printf("Empregado cadastrado com Sucesso!\n");
    }
    else{
        printf("Falha ao cadastrar Empregado!\n");
    }
}

//executar entrega
int executar(){
    struct Entrega cad;
    struct Veiculo temp;
    struct Empregado emp;
    struct Cliente cli;
    char tipoveic[10];
    int n,k,x,id,esc=-1,sucesso;
    FILE *arqtemp;

    arqtemp=fopen("entrega.dat","rb");
    printf("Digite o ID da entrega: ");
    scanf("%i",&id);
    getchar();

    while(fread(&cad,sizeof(struct Entrega),1,arqtemp) == 1){
        if(id == cad.id){
            Strrela.idE=cad.id;                                             //parte do código em que começa o preenchimento do relatório
            strcpy(Strrela.orig,cad.orig);
            strcpy(Strrela.dest,cad.dest);
            Strrela.TempT=cad.temph*1.1;
        }
    }
    fclose(arqtemp);

    arqtemp=fopen("veiculo.dat","rb");                                   //abrir o arquivo veiculo.dat para buscar o tipo do veículo
     if (arqtemp == NULL) {
        printf("Erro ao abrir o arquivo de Veículos!\n");
        return 0;
    }

    printf("Qual tipo de veículo:\n");
    printf("1 - Moto\n");
    printf("2 - Carro\n");
    printf("3 - Van\n");
    scanf("%d", &esc);
    switch(esc){
        case 1:
           strcpy(tipoveic, "Moto");
           break;
        case 2:
            strcpy(tipoveic, "Carro");
            break;
        case 3:
            strcpy(tipoveic, "Van");
            break;
        default:
            printf("Opção inválida\n");
    }
    rewind(arqtemp);
    while (fread(&temp,sizeof(struct Veiculo),1,arqtemp) == 1) {            //verifica se há o tipo solicitado e se o status do veículo é livre
        if (strcmp(temp.tipo, tipoveic) == 0 && strcmp(temp.status,"livre") == 0){
                Strrela.idV=temp.id;
                continue;
        }
    }
    fclose(arqtemp);

    n=0;
    arqtemp=fopen("empregado.dat", "rb");                                                                               //escolha do empregado
    if (arqtemp == NULL) {
        printf("Erro ao abrir o arquivo de empregados!\n");
        return 0;
    }

    while(fread(&emp,sizeof(struct Empregado),1,arqtemp) == 1){
        n++;                                                                                                        //contador de quantos empregados tem o arquivo de texto
    }
    if (n == 0) {
        printf("Nenhum empregado encontrado no arquivo.\n");
        fclose(arqtemp);
        return 1;
    }

    srand(time(NULL));                                                                                          // Inicializa a semente do gerador de números aleatórios
    x=rand() % n;                                                                                               //escolhe entre os funcionários um aleatoriamente para fazer a entrega
    rewind(arqtemp);

    for(int i=0;i<=x;i++){
        fread(&emp,sizeof(struct Empregado),1,arqtemp);
        Strrela.idF=emp.id;
    }
    fclose(arqtemp);

    arqtemp=fopen("cliente.dat","rb");

    int saida=1;
    while(saida != 0){
        rewind(arqtemp);
        printf("Qual o ID do cliente?: \n");                                                 //se houver cadastro
        scanf("%d",&k);
        getchar();
        while(fread(&cli,sizeof(struct Cliente),1,arqtemp) == 1){
            if(k == cli.id){
                printf("Cliente existe.\n");
                Strrela.idC=cli.id;
                rel=fopen("relatorio.dat", "a+b");                                                                           // processo de jogar para o arquivo do relatório
                if (rel == NULL) {
                    printf("Erro ao abrir o arquivo relatorio.dat!\n");
                    return 1;
                }
                sucesso=fwrite(&Strrela,sizeof(struct relatorio),1,rel);
                fclose(rel);
                rewind(arqtemp);
                if(sucesso == 1){
                    FILE * ft = fopen("arqmod.dat", "wb");
                    while(fread(&cad,sizeof(struct Entrega),1,arqtemp) == 1){
                        if(Strrela.idE != cad.id){
                            fwrite(&cad,sizeof(struct Entrega),1,ft);
                        }
                    }
                    fclose(ft);
                    remove("entrega.dat");
                    rename("arqmod.dat", "entrega.dat");
                    printf("Registro relalizado com sucesso!\n");
                }
                saida=0;

                break;
            }
        }
        if(saida == 1){
            printf("Se desejar cancelar a busca Digite '0':\nSe quiser continuar digite '1':\n");
            scanf("%i",&saida);
                if(saida == 0){
                    printf("Cancelando busca, entrega não executada.");
                }
        }
    }
    fclose(arqtemp);
    return 0;
}

void excluir() {
    int idBusca, encontrado=0;
    printf("\nQual tipo de dado deseja excluir?\n");
    printf("1 - Cliente\n");
    printf("2 - Veículo\n");
    printf("3 - Entrega\n");
    printf("4 - Empregado\n");
    printf("0 - Voltar\n");
    printf("Escolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    switch(opcao) {
        case 1: {
            FILE *arqorig_cliente = fopen("cliente.dat", "rb+");
            if (arqorig_cliente == NULL) {
                arqorig_cliente = fopen("cliente.dat", "wb+");  // Cria o arquivo se não existir
            }
            if (arqorig_cliente == NULL){
                printf("Erro ao abrir arquivos!\n");
            }
            FILE *arqtemp_cliente = fopen("clientemod.dat", "wb+");
            printf("Digite o ID do Cliente que deseja excluir: ");
            scanf("%d", &idBusca);
            while (fread(&cliente, sizeof(cliente), 1, arqorig_cliente)) {
                if (cliente.id != idBusca) {
                    fwrite(&cliente, sizeof(cliente), 1, arqtemp_cliente);
                }
                else{
                    encontrado=1;
                }
            }
            if(encontrado==1){
                fclose(arqorig_cliente);
                fclose(arqtemp_cliente);
                remove("cliente.dat");
                rename("clientemod.dat", "cliente.dat");
                printf("Registro excluído com sucesso!\n");
            }
            else{
                printf("Registro não encontrado!\n");
            }
            break;
        }
        case 2: {
            struct Veiculo veiculo;
            FILE *arqorig_veiculo = fopen("veiculo.dat", "rb+");
            if (arqorig_veiculo == NULL) {
                arqorig_veiculo = fopen("veiculo.dat", "wb+");
            }
            if (arqorig_veiculo == NULL){
                printf("Erro ao abrir arquivos!\n");
            }


    FILE *arqtemp_veiculo = fopen("veiculomod.dat", "wb+");

            printf("Digite o ID do veiculo que deseja excluir: ");
            scanf("%d", &idBusca);
            while (fread(&veiculo, sizeof(veiculo), 1, arqorig_veiculo)) {
                if (veiculo.id != idBusca) {
                    fwrite(&veiculo, sizeof(veiculo), 1, arqtemp_veiculo);
                }
                else{
                    encontrado=1;
                }
            }
            if(encontrado){
                fclose(arqorig_veiculo);
                fclose(arqtemp_veiculo);
                remove("veiculo.dat");
                rename("veiculomod.dat", "veiculo.dat");
                printf("Registro excluído com sucesso!\n");

            }
            else{
                printf("Registro não encontrado!\n");
            }
            break;
        }
        case 3: {
            struct Entrega entrega;
            FILE *arqorig_entrega = fopen("entrega.dat", "rb+");
            if (arqorig_entrega == NULL) {
                arqorig_entrega = fopen("entrega.dat", "wb+");
            }
            if (arqorig_entrega == NULL){
                printf("Erro ao abrir arquivos!\n");
            }

    FILE *arqtemp_entrega = fopen("entregamod.dat", "wb+");

            printf("Digite o ID do entrega que deseja excluir: ");
            scanf("%d", &idBusca);
            while (fread(&entrega, sizeof(entrega), 1, arqorig_entrega)) {
                if (entrega.id != idBusca) {
                    fwrite(&entrega, sizeof(entrega), 1, arqtemp_entrega);
                }
                else{
                    encontrado=1;
                }
                if(encontrado){
                    fclose(arqorig_entrega);
                    fclose(arqtemp_entrega);
                    remove("entrega.dat");
                    rename("entregamod.dat", "entrega.dat");
                    printf("Registro excluído com sucesso!\n");

                }
                else{
                    printf("Registro não encontrado!\n");
                }
          }
            break;
        }
        case 4: {
            struct Empregado empregado;
            FILE *arqorig_empregado = fopen("empregado.dat", "rb+");
            if (arqorig_empregado == NULL) {
                arqorig_empregado = fopen("empregado.dat", "wb+");
            }
            if (arqorig_empregado == NULL){
                printf("Erro ao abrir arquivos!\n");
            }
    FILE *arqtemp_empregado = fopen("empregadomod.dat", "wb+");

            printf("Digite o ID do empregado que deseja excluir: ");
            scanf("%d", &idBusca);
            while (fread(&empregado, sizeof(empregado), 1, arqorig_empregado)) {
                if (empregado.id != idBusca) {
                    fwrite(&empregado, sizeof(empregado), 1, arqtemp_empregado);
                }
                else{
                    encontrado=1;
                }
            }
            if(encontrado){
                fclose(arqorig_empregado);
                fclose(arqtemp_empregado);
                remove("empregado.dat");
                rename("empregadomod.dat", "empregado.dat");
                printf("Registro excluído com sucesso!\n");

            }
            else{
                printf("Registro não encontrado!\n");
            }
            break;
        }
        case 0:
            printf("Voltando...\n");
        default:
            printf("Opção inválida!\n");
            return;
    }
}

void copiar_exc(FILE *arqorig, FILE *arqtemp, int idBusca) {
    char linha[1000];
    while (fgets(linha, sizeof(linha), arqorig) != NULL) {
        int idRegistro;
        sscanf(linha, "%d", &idRegistro);
        if (idRegistro != idBusca) {
            fputs(linha, arqtemp);
        }
    }
}

void editar() {
    int esc;
    int idBusca, encontrado = 0;
    char nomeArquivo[20], tempArquivo[] = "tempEdit.dat";
    printf("\nQual tipo de dado deseja editar?\n");
    printf("1 - Cliente\n");
    printf("2 - Veículo\n");
    printf("3 - Entrega\n");
    printf("4 - Empregado\n");
    printf("0 - Voltar\n");
    printf("Escolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer

    switch (opcao) {
        case 1:
            strcpy(nomeArquivo, "cliente.dat");
            break;
        case 2:
            strcpy(nomeArquivo, "veiculo.dat");
            break;
        case 3:
            strcpy(nomeArquivo, "entrega.dat");
            break;
        case 4:
            strcpy(nomeArquivo, "empregado.dat");
            break;
        case 0:
            printf("Voltando...\n");
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("Digite o ID do registro que deseja editar: ");
    scanf("%d", &idBusca);
    getchar(); // Limpa o buffer

    FILE *arquivo = fopen(nomeArquivo, "rb");
    FILE *tempEdit = fopen(tempArquivo, "wb");

    if (!arquivo || !tempEdit) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    if (opcao == 1) {
        struct Cliente cliente;
        while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
            if (cliente.id == idBusca) {
                encontrado = 1;
                printf("Novo Nome: ");
                fgets(cliente.nome, sizeof(cliente.nome), stdin);
                cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

                printf("Novo Endereço: ");
                fgets(cliente.end, sizeof(cliente.end), stdin);
                cliente.end[strcspn(cliente.end, "\n")] = '\0';

                printf("Novo Tipo de Envio: ");
                fgets(cliente.tip_env, sizeof(cliente.tip_env), stdin);
                cliente.tip_env[strcspn(cliente.tip_env, "\n")] = '\0';
            }
            fwrite(&cliente, sizeof(struct Cliente), 1, tempEdit);
        }
    } else if (opcao == 2) {
        struct Veiculo veiculo;
        while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivo)) {
            if (veiculo.id == idBusca) {
                encontrado = 1;
                printf("Qual tipo de veículo:\n");
                printf("1 - Moto\n");
                printf("2 - Carro\n");
                printf("3 - Van\n");
                scanf("%d", &esc);
                switch(esc){
                    case 1:
                       strcpy(veiculo.tipo, "Moto");
                       break;
                    case 2:
                        strcpy(veiculo.tipo, "Carro");
                        break;
                    case 3:
                        strcpy(veiculo.tipo, "Van");
                        break;
                    default:
                        printf("Opção inválida\n");
                }

                printf("Nova Capacidade: ");
                scanf("%d", &veiculo.capacidade);
                getchar();

                printf("Status do veículo: \n");
                printf("1 - Livre\n");
                printf("2 - Ocupado\n");
                scanf("%d", &esc);
                switch(esc){
                    case 1:
                       strcpy(veiculo.status, "livre");
                       break;
                    case 2:
                        strcpy(veiculo.status, "ocupado");
                        break;
                    default:
                        printf("Opção inválida\n");
                }
            }
            fwrite(&veiculo, sizeof(struct Veiculo), 1, tempEdit);
        }
    } else if (opcao == 3) {
        struct Entrega entrega;
        while (fread(&entrega, sizeof(struct Entrega), 1, arquivo)) {
            if (entrega.id == idBusca) {
                encontrado = 1;
                printf("Nova Origem: ");
                fgets(entrega.orig, sizeof(entrega.orig), stdin);
                entrega.orig[strcspn(entrega.orig, "\n")] = '\0';

                printf("Novo Destino: ");
                fgets(entrega.dest, sizeof(entrega.dest), stdin);
                entrega.dest[strcspn(entrega.dest, "\n")] = '\0';

                printf("Novo Tempo Estimado: ");
                scanf("%d", &entrega.temph);
                getchar();
            }
            fwrite(&entrega, sizeof(struct Entrega), 1, tempEdit);
        }
    } else if (opcao == 4) {
        struct Empregado empregado;
        while (fread(&empregado, sizeof(struct Empregado), 1, arquivo)) {
            if (empregado.id == idBusca) {
                encontrado = 1;
                printf("Novo Nome do Empregado: ");
                fgets(empregado.nome, sizeof(empregado.nome), stdin);
                empregado.nome[strcspn(empregado.nome, "\n")] = '\0';
            }
            fwrite(&empregado, sizeof(struct Empregado), 1, tempEdit);
        }
    }
    fclose(arquivo);
    fclose(tempEdit);

    if (!encontrado) {
        printf("Registro não encontrado!\n");
        remove(tempArquivo);
    } else {
        remove(nomeArquivo);
        rename(tempArquivo, nomeArquivo);
        printf("Registro atualizado com sucesso!\n");
    }
}

void vizualizar (){
    int esc;
    printf("Modo de vizualização:\n");
    printf("1 - Todos\n");
    printf("2 - ID Específico\n");
    printf("0 - Voltar\n");
    scanf("%i",&esc);
    switch (esc){
        case 1:
            vizu_tudo();
            break;
        case 2:
            vizu_especifico();
            break;
        case 0:
            printf("Voltando...\n");
        default:
            printf("Opção inválida\n");
    }
}

void vizu_tudo(){
    int esc;
    printf("Escolha a opção a ser vizualizada\n");
    printf("1 - Cliente\n");
    printf("2 - Funcionários\n");
    printf("3 - Veículos\n");
    printf("4 - Entregas\n");
    printf("5 - Voltar\n");
    scanf("%i",&esc);

    switch(esc){
        case 1:
            ver_tudo("cliente.dat",esc);
            break;
        case 2:
            ver_tudo("empregado.dat",esc);
            break;
        case 3:
            ver_tudo("veiculo.dat",esc);
            break;
        case 4:
            ver_tudo("entrega.dat",esc);
            break;
         case 5:
            printf("Voltando...\n");
            return;
        default:
            printf("Opção não cadastrada.");
            break;
    }
}

void ver_tudo(const char *nome, int n) {
    FILE *Ar;
    Ar = fopen(nome, "rb");
    if (Ar == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    if (n == 1) {
        struct Cliente temp_C;
        while (fread(&temp_C, sizeof(struct Cliente), 1, Ar) == 1) {
            printf("\nID: %d\nNome: %s\nEndereço: %s\nTipo de Envio: %s\n\n", temp_C.id, temp_C.nome, temp_C.end, temp_C.tip_env);
        }
    } else if (n == 2) {
        struct Empregado temp_Emp;
        while (fread(&temp_Emp, sizeof(struct Empregado), 1, Ar) == 1) {
            printf("\nID: %d\nNome: %s\n\n", temp_Emp.id, temp_Emp.nome);
        }
    } else if (n == 3) {
        struct Veiculo temp_V;
        while (fread(&temp_V, sizeof(struct Veiculo), 1, Ar) == 1) {
            printf("\nID: %d\nTipo: %s\nCapacidade: %d\nStatus: %s\n\n", temp_V.id, temp_V.tipo, temp_V.capacidade, temp_V.status);
        }
    } else if (n == 4) {
        struct Entrega temp_E;
        while (fread(&temp_E, sizeof(struct Entrega), 1, Ar) == 1) {
            printf("\nID: %d\nOrigem: %s\nDestino: %s\nTempo: %d horas\n\n", temp_E.id, temp_E.orig, temp_E.dest, temp_E.temph);
        }
    }
    fclose(Ar);
    getchar();
}

void vizu_especifico(){
    int esc;
    printf("Escolha a opção a ser vizualizada\n");
    printf("1 - Cliente\n");
    printf("2 - Funcionário\n");
    printf("3 - Veículo\n");
    printf("4 - Entrega\n");
    printf("5 - Voltar\n");
    scanf("%i",&esc);
    switch(esc){
        case 1:
            vizu_cliente("cliente.dat");
            break;
        case 2:
            vizu_empregado("empregado.dat");
            break;
        case 3:
            vizu_veiculo("veiculo.dat");
            break;
        case 4:
            vizu_entrega("entrega.dat");
            break;
         case 5:
            break;
        default:
            printf("Opção inválida\n");
    }
}

void vizu_cliente(const char * nome){
    int id;
    struct Cliente tempC;
    FILE *Ar;
    Ar = fopen(nome, "rb");
    if (Ar == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    printf("Digite o ID: ");
    scanf("%i",&id);
    while(fread(&tempC,sizeof(struct Cliente),1,Ar) == 1){
        if(id == tempC.id){
            printf("ID:%i \nEndereço:%s \nNome:%s \nTipo de envio:%s\n",tempC.id, tempC.end, tempC.nome, tempC.tip_env);
            break;
        }
    }
}

void vizu_empregado(const char * nome){
    int id;
    struct Empregado tempEmp;
    FILE *Ar;
    Ar = fopen(nome, "rb");
    if (Ar == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    printf("Digite o ID: ");
    scanf("%i",&id);
    while(fread(&tempEmp,sizeof(struct Empregado),1,Ar) == 1){
        if(id == tempEmp.id){
            printf("ID: %i \n Nome: %s\n",tempEmp.id, tempEmp.nome);
            break;
        }
    }
}

void vizu_veiculo(const char * nome){
    int id;
    struct Veiculo tempVeic;
    FILE *Ar;
    Ar = fopen(nome, "rb");
    if (Ar == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    printf("Digite o ID: ");
    scanf("%i",&id);
    while(fread(&tempVeic,sizeof(struct Veiculo),1,Ar) == 1){
        if(id == tempVeic.id){
            printf("ID:%i \nTipo:%s \nCapacidade:%i \nStatus:%s\n",tempVeic.id,tempVeic.tipo,tempVeic.capacidade,tempVeic.status);
            break;
        }
    }
}

void vizu_entrega(const char * nome){
    int id;
    struct Entrega tempEntr;
    FILE *Ar;
    Ar = fopen(nome, "rb");
    if (Ar == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome);
        return;
    }
    printf("Digite o ID: ");
    scanf("%i",&id);
    while(fread(&tempEntr,sizeof(struct Entrega),1,Ar) == 1){
        if(id == tempEntr.id){
            printf("ID: %i \nOrigem: %s \nDestino:%s \nTempo: %i\n", tempEntr.id, tempEntr.orig, tempEntr.dest, tempEntr.temph);
            break;
        }
    }
}

// Função para gerar ID
int id(int n) {
    srand(time(NULL));
    switch (n) {
        case 1: return gerar_id("empregado.dat");
        case 2: return gerar_id("entrega.dat");
        case 3: return gerar_id("cliente.dat");
        case 4: return gerar_id("veiculo.dat");
    }
    return 0;
}

int gerar_id(const char *nome) {
    int novo_id;
    do {
        novo_id = (rand() % (MAX_ID - MIN_ID + 1)) + MIN_ID;                                         //  7 dígitos
    } while (id_existe(novo_id, nome));
    return novo_id;
}

int id_existe(int id, const char *nome) {
    FILE *file = fopen(nome, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", nome);
        return 0;
    }

    int temp_id;
    while (fscanf(file, "%d", &temp_id) == 1) {                                                         // Lê apenas o ID
        if (temp_id == id) {
            fclose(file);
            return 1;                                                                                    // ID já existe
        }
    }
    fclose(file);
    return 0;                                                                                           // ID não encontrado
}
