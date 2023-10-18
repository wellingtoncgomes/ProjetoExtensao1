#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

#define MAX_NOME 50
#define MAX_DATA 20
#define MAX_HORA 10
#define MAX_EVENTOS 100
#define MAX_MESAS 10
#define MAX_ARQUIVO 100
#define MAX_USUARIO 20
#define MAX_SENHA 20

#define RED "\e[1;91m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define WHITE "\e[0;37m"
#define CYAN "\e[0;36m"
#define RESET "\e[m"
#define WHITEB "\e[47m"

char tipoUsuario[MAX_USUARIO];
int isAdmin=0;
// Estrutura para armazenar informações do usuário
typedef struct {
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];
} Usuario;


typedef struct {
    char nome[50];
    char descricao[100];
    char ingredientes[200];
    int quantidadePessoas;
    float valor;
    int disponibilidade;
} Cardapio;

// Função para ler uma string segura com fgets
void lerString(char *destino, int tamanho) {
    fflush(stdin);  // Limpa o buffer de entrada
    fgets(destino, tamanho, stdin);

    // Limpa o buffer de entrada
    if (strchr(destino, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } else {
        destino[strcspn(destino, "\n")] = '\0'; // Remove a quebra de linha
    }
}
void criarCardapio();
void limparBuffer();
void exibirCardapiosDoArquivo();
void trocarDisponibilidade();
void atualizarCardapio();
void exibirCardapio(const Cardapio *cardapio);
void exibirSubMenuCardapio();
void exibirCardapiosDoArquivo();
void excluirCardapio();
// Função para exibir o menu principal
void exibirMenuPrincipal() {
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Eventos ======\n"RESET);
        printf("\t\t1. Iniciar como Administrador\n");
        printf("\t\t2. Iniciar como Usuário\n");
        printf(RED"\t\t3. Sair\n"RESET);
        printf(GREEN"\t==========================================\n"RESET);
        printf("\t\tEscolha uma opção: ");
        scanf("%d", &escolha);

       switch (escolha) {
            case 1:
                limparConsole();
                strcpy(tipoUsuario, "Admin");
                if (fazerLogin("./Admin.txt", tipoUsuario)) {
                    if (strcmp(tipoUsuario, "Admin") == 0) {  // Comparando strings usando strcmp
                        isAdmin = 1;
                    }
                    exibirMenuAdmin(tipoUsuario);
                }
                break;
            case 2:
                limparConsole();
                strcpy(tipoUsuario, "Usuario");
                if (fazerLogin("./Usuario.txt", tipoUsuario)) {
                    if (strcmp(tipoUsuario, "Usuario") == 0) {  // Comparando strings usando strcmp
                        isAdmin = 0;
                    }
                    exibirMenuAdmin(tipoUsuario);
                }
                break;
            case 3:
                limparConsole();
                printf(RED"\n\t\tSaindo do programa...\n"RESET);
                sleep(3);
                limparConsole();
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 3);
}

void exibirMenuAdmin(tipoUsuario) {
    int escolha;
    if(isAdmin){
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - %s ======\n",tipoUsuario);
        printf(RESET"\t\t1. Cadastros\n");
        printf("\t\t2. Eventos\n");
        printf("\t\t3. Centro de Custos\n");
        printf(RED"\t\t4. Voltar Menu Inicial\n");
        printf(GREEN"\t=================================================\n"RESET);
        printf("\t\tEscolha uma opção: "GREEN);
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();
                exibirSubMenuCadastro();
                break;
            case 2:
                limparConsole();
                exibirSubMenuEventos();
                break;
            case 3:
                limparConsole();
                exibirSubMenuCentroCustos();
                break;
            case 4:
                // Adicionado comando para voltar ao menu principal
                exibirMenuPrincipal();
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 4);
}else{
     do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - %s ======\n",tipoUsuario);
        printf(RESET"\t\t1. Eventos\n");
        printf("\t\t2. Buscar Mesa Convidado\n");
        printf(RED"\t\t3. Voltar Menu Inicial\n");
        printf(GREEN"\t============================================================\n"RESET);
        printf("\t\tEscolha uma opção: "GREEN);
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();
                exibirSubMenuEventos();
                break;
            case 2:
                limparConsole();
                break;
            case 3:
                exibirMenuPrincipal();
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 4);
}
}
void exibirSubMenuCadastro() {
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - Administrador ======\n"RESET);
        printf("\t\t1. Cadastro Funcionario\n");
        printf("\t\t2. Cadastro Eventos\n");
        printf("\t\t3. Cadastro Cardapio\n");
        printf("\t\t4. Cadastro Locais\n");
        printf("\t\t5. Cadastro Usuarios\n");
        printf(RED"\t\t6. Voltar\n"RESET);
        printf("\t=====================================\n");
        printf("\t\tEscolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();
                // Adicione o código para o caso 1 (Cadastro Funcionario) aqui
                break;
            case 2:
                limparConsole();
                // Adicione o código para o caso 2 (Cadastro Eventos) aqui
                break;
            case 3:
                limparConsole();
                exibirSubMenuCardapio(tipoUsuario);
                // Adicione o código para o caso 3 (Cadastro Cardapio) aqui
                break;
            case 4:
                limparConsole();
                // Adicione o código para o caso 4 (Cadastro Locais) aqui
                break;
            case 5:
                limparConsole();
                // Adicione o código para o caso 5 (Cadastro Usuarios) aqui
                break;
            case 6:
                exibirMenuAdmin(tipoUsuario);
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 6);
}
void exibirSubMenuEventos(){
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - Administrador ======\n"RESET);
        printf("\t\t1. Criar Eventos\n");
        printf("\t\t2. Ver Eventos\n");
        printf("\t\t3. Atualizar Eventos\n");
        printf("\t\t4. Excluir Ecentos\n");
        printf(RED"\t\t5. Voltar\n"RESET);
        printf("\t=====================================\n");
        printf("\t\tEscolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();

                break;
            case 2:
                limparConsole();

                break;
            case 3:
                limparConsole();

                break;
            case 4:
                limparConsole();
            case 5:
                limparConsole();
                exibirMenuAdmin(tipoUsuario);

                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 5);

}
void exibirSubMenuCentroCustos(){
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - Administrador ======\n"RESET);
        printf("\t\t1. Despesas\n");
        printf("\t\t2. Receitas\n");
        printf("\t\t3. Relatorios\n");
        printf(RED"\t\t4. Voltar\n"RESET);
        printf("\t=====================================\n");
        printf("\tEscolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();

                break;
            case 2:
                limparConsole();

                break;
            case 3:
                limparConsole();

                break;
            case 4:
                limparConsole();
                exibirMenuAdmin(tipoUsuario);

                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 4);

}

void limparConsole() {
    system(CLEAR_SCREEN);
}

int fazerLogin(char *arquivo, char *tipoUsuario) {
    FILE *f = fopen(arquivo, "r");

    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    char login[MAX_USUARIO];
    char senha[MAX_SENHA];
    char loginArquivo[MAX_USUARIO];
    char senhaArquivo[MAX_SENHA];


    int tentativas = 0;
    int loginValido = 0;

    do {
        limparConsole();
        printf(RED"\t==============================\n ");
        printf(YELLOW"\t    Login - %s \n", tipoUsuario);
        printf(RED"\t==============================\n"RESET);
        printf("\tDigite o login: ");
        lerString(login, MAX_USUARIO);
        printf("\tDigite a senha: ");
        lerString(senha, MAX_SENHA);


        fseek(f, 0, SEEK_SET);

        while (fscanf(f, "%19[^;];%19[^\n]\n", loginArquivo, senhaArquivo) == 2) {
            if (strcmp(loginArquivo, login) == 0 && strcmp(senhaArquivo, senha) == 0) {
                loginValido = 1;
                break;
            }
        }

        if (!loginValido) {
            printf(RED"\n\tLogin ou senha incorretos! Tente novamente.\n"RESET);
            tentativas++;
            sleep(1);

        }

    } while (!loginValido && tentativas < 3);

    fclose(f);

    if (loginValido) {
        limparConsole();
        printf(GREEN"\n\tLogin bem-sucedido!\n"RESET);
        sleep(2);

    } else {
        limparConsole();
        printf(RED"\n\tNúmero máximo de tentativas alcançado. Saindo do login."RESET);
        sleep(2);
    }

    return loginValido;
}
int main() {
    setlocale(LC_ALL, "");

    // Array para armazenar informações do usuário
    Usuario usuarios[MAX_EVENTOS];
    int numUsuarios = 0;

    // Adicione alguns usuários para ilustrar (substitua isso com a leitura de um arquivo TXT)
    //strcpy(usuarios[0].usuario, "admin");
    //strcpy(usuarios[0].senha, "admin123");
    //numUsuarios++;

    exibirMenuPrincipal();

    return 0;
}
void exibirSubMenuCardapio(tipoUsuario) {
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - %s ======\n",tipoUsuario);
        printf(RESET"\t\t1. Criar Cardapio\n");
        printf("\t\t2. Ver Cardapios Disponiveis\n");
        printf("\t\t3. Excluir Cardapios\n");
        printf("\t\t4. Atualizar Cardapio\n");
        printf("\t\t5. Inativar Cardapio\n");
        printf(RED"\t\t6. Voltar\n"RESET);
        printf("\t=====================================\n");
        printf("\t\tEscolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparConsole();
                criarCardapio();
                // Adicione o código para o caso 1 (Cadastro Funcionario) aqui
                break;
            case 2:
                limparConsole();
                exibirCardapiosDoArquivo();
                // Adicione o código para o caso 2 (Cadastro Eventos) aqui
                break;
            case 3:
                limparConsole();
                excluirCardapio();
                // Adicione o código para o caso 3 (Cadastro Cardapio) aqui
                break;
            case 4:
                limparConsole();
                atualizarCardapio();
                // Adicione o código para o caso 4 (Cadastro Locais) aqui
                break;
            case 5:
                limparConsole();
                trocarDisponibilidade();
                // Adicione o código para o caso 5 (Cadastro Usuarios) aqui
                break;
            case 6:
                limparConsole();
                exibirSubMenuCadastro(tipoUsuario);
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
    } while (escolha != 6);
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void criarCardapio() {
    Cardapio novoCardapio;

    printf("Nome do Cardapio: ");
    scanf("%s", novoCardapio.nome);

    printf("Descricao do Cardapio: ");
    scanf("%s", novoCardapio.descricao);

    printf("Ingredientes: ");
    scanf("%s", novoCardapio.ingredientes);

    printf("Quantidade de Pessoas: ");
    scanf("%d", &novoCardapio.quantidadePessoas);

    printf("Valor do Cardapio: ");
    scanf("%f", &novoCardapio.valor);

    printf("Disponibilidade (1 para ativo, 0 para inativo): ");
    scanf("%d", &novoCardapio.disponibilidade);

    // Abrir o arquivo em modo de escrita (append)
    FILE *arquivo = fopen("cardapios.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escrever os dados no arquivo
    fprintf(arquivo, "%s;%s;%s;%d;%.2f;%d\n", novoCardapio.nome, novoCardapio.descricao,
            novoCardapio.ingredientes, novoCardapio.quantidadePessoas,
            novoCardapio.valor, novoCardapio.disponibilidade);

    // Fechar o arquivo
    fclose(arquivo);

    printf("Cardapio criado e salvo com sucesso!\n");
    sleep(2);
}
void atualizarCardapio() {
    char nomeBusca[50];
    printf("Digite o nome do cardapio que deseja atualizar: ");
    scanf("%s", nomeBusca);

    FILE *arquivo = fopen("cardapios.txt", "r");
    FILE *temporario = fopen("temporario.txt", "w");

    if (arquivo == NULL || temporario == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Cardapio cardapio;

    while (fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor, &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeBusca) == 0) {
            // Permitir ao usuário atualizar todos os itens
            printf("Digite os novos dados para o cardapio:\n");

            printf("Nome: ");
            scanf("%s", cardapio.nome);

            printf("Descricao: ");
            scanf("%s", cardapio.descricao);

            printf("Ingredientes: ");
            scanf("%s", cardapio.ingredientes);

            printf("Quantidade de Pessoas: ");
            scanf("%d", &cardapio.quantidadePessoas);

            printf("Valor: ");
            scanf("%f", &cardapio.valor);

            printf("Disponibilidade (1 para ativo, 0 para inativo): ");
            scanf("%d", &cardapio.disponibilidade);
        }

        // Escrever os dados no arquivo temporário
        fprintf(temporario, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                cardapio.ingredientes, cardapio.quantidadePessoas,
                cardapio.valor, cardapio.disponibilidade);
    }

    // Fechar os arquivos
    fclose(arquivo);
    fclose(temporario);

    // Substituir o arquivo original pelo temporário
    remove("cardapios.txt");
    rename("temporario.txt", "cardapios.txt");

    printf("Cardapio atualizado com sucesso!\n");
}
void excluirCardapio() {
    char nomeExcluir[50];
    printf("Digite o nome do cardapio que deseja excluir: ");
    scanf("%s", nomeExcluir);

    FILE *arquivoEntrada = fopen("cardapios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapio;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor,
                  &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeExcluir) != 0) {
            // Se o nome não corresponder, escreva no arquivo temporário
            fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                    cardapio.ingredientes, cardapio.quantidadePessoas,
                    cardapio.valor, cardapio.disponibilidade);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    printf("Cardapio excluido com sucesso!\n");
}
void trocarDisponibilidade() {
    char nomeBusca[50];
    printf("Digite o nome do cardapio que deseja atualizar: ");
    scanf("%s", nomeBusca);

    FILE *arquivo = fopen("cardapios.txt", "r");
    FILE *temporario = fopen("temporario.txt", "w");

    if (arquivo == NULL || temporario == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Cardapio cardapio;

    while (fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor, &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeBusca) == 0) {
            // Atualizar a disponibilidade no registro atual
            cardapio.disponibilidade = !cardapio.disponibilidade;
        }

        // Escrever os dados no arquivo temporário
        fprintf(temporario, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                cardapio.ingredientes, cardapio.quantidadePessoas,
                cardapio.valor, cardapio.disponibilidade);
    }

    // Fechar os arquivos
    fclose(arquivo);
    fclose(temporario);

    // Substituir o arquivo original pelo temporário
    remove("cardapios.txt");
    rename("temporario.txt", "cardapios.txt");

    printf("Disponibilidade do cardapio atualizada com sucesso!\n");
}


void exibirCardapiosDoArquivo() {
    FILE *arquivo = fopen("cardapios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapioLido;
    // Ler os dados do arquivo e exibir no console
    while (fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%d\n", cardapioLido.nome, cardapioLido.descricao,
                  cardapioLido.ingredientes, &cardapioLido.quantidadePessoas, &cardapioLido.valor,
                  &cardapioLido.disponibilidade) != EOF) {
        exibirCardapio(&cardapioLido);
        printf("\n");
    }

    printf("precione ENTER para sair!!");
    while (getchar() != '\n');
        getchar();
    // Fechar o arquivo
    fclose(arquivo);
}
void exibirCardapio(const Cardapio *cardapio) {
    printf("Nome: %s\n", cardapio->nome);
    printf("Descricao: %s\n", cardapio->descricao);
    printf("Ingredientes: %s\n", cardapio->ingredientes);
    printf("Quantidade de Pessoas: %d\n", cardapio->quantidadePessoas);
    printf("Valor: %.2f\n", cardapio->valor);
    printf("Disponibilidade: %s\n", cardapio->disponibilidade ? "Ativo" : "Inativo");

}
