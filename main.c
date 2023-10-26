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

// STRUCTS
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

//DECLARAÇÕES DE FUNÇÕES MENU
void exibirMenuPrincipal();
void exibirMenuAdmin(tipoUsuario);
void exibirSubMenuCadastro();
void exibirSubMenuEventos();
void exibirSubMenuCardapio(tipoUsuario);
void exibirSubMenuCentroCustos();

//DECLARAÇÕES DE FUNÇÕES MENU
int fazerLogin(char *arquivo, char *tipoUsuario);

//DECLARAÇÕES DE FUNÇÕES LIMPAR
void limparBuffer();
void limparConsole();

//DECLARAÇÕES DE FUNÇÕES CRUD CARDAPIO
void criarCardapio();
void atualizarCardapio();
void excluirCardapio();
void exibirCardapiosDoArquivo();
void exibirCardapio(const Cardapio *cardapio);

//DECLARAÇÕES DE FUNÇÕES LER COM VALIDAÇÃO
void lerString(char *destino, int tamanho);
int confirmarExclusao();
int confirmarContinuacao();
int validarEntradaInt();
double validarEntradaDouble();

//DECLARAÇÕES DE FUNÇÕES PAUSA
void pausar();

int main() {
    setlocale(LC_ALL, "");

    exibirMenuPrincipal();

    return 0;
}

//FUNÇÕES DE MENU
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
void exibirSubMenuCardapio(tipoUsuario) {
    int escolha;
    do {
        system(CLEAR_SCREEN);
        printf(GREEN"\n\t====== Gerenciamento Debroi Evento - %s ======\n",tipoUsuario);
        printf(RESET"\t\t1. Criar Cardapio\n");
        printf("\t\t2. Ver Cardapios Disponiveis\n");
        printf("\t\t3. Excluir Cardapios\n");
        printf("\t\t4. Atualizar Cardapio\n");
        printf(RED"\t\t5. Voltar\n"RESET);
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
                modificarCardapio();
                //atualizarCardapio();
                // Adicione o código para o caso 4 (Cadastro Locais) aqui
                break;
            case 5:
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
//FUNÇÃO LOGIN
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
//FUNÇÃO PARA LIMPAR
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void limparConsole() {
    system(CLEAR_SCREEN);
}
//FUNÇÕES CRUD CARDAPIO
void criarCardapio() {
    Cardapio novoCardapio;
    limparConsole();
    printf(GREEN"\n\t========= Cadastro de Cardápio -  Debroi Eventos ==========\n"RESET);
    do {
        printf("\t\tNome do Cardápio: ");
        lerString(novoCardapio.nome, 50);

        printf("\t\tDescrição do Cardápio: ");
        lerString(novoCardapio.descricao, 100);

        printf("\t\tIngredientes: ");
        lerString(novoCardapio.ingredientes, 200);

        printf("\t\tQuantidade de Pessoas: ");
        novoCardapio.quantidadePessoas = validarEntradaInt();

        printf("\t\tValor do cardápio por pessoa: ");
        novoCardapio.valor = validarEntradaDouble();

        printf("\t\tDisponibilidade (1 para ativo, 0 para inativo): ");
        novoCardapio.disponibilidade = validarEntradaInt();

        FILE *arquivo = fopen("cardapios.txt", "a");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Escrever os dados no arquivo
        fprintf(arquivo, "%s;%s;%s;%d;%.2lf;%d\n", novoCardapio.nome, novoCardapio.descricao,
                novoCardapio.ingredientes, novoCardapio.quantidadePessoas,
                novoCardapio.valor, novoCardapio.disponibilidade);
        // Fechar o arquivo
        fclose(arquivo);
        printf("Cardápio criado e salvo com sucesso!\n");
        sleep(1);
        limparConsole();

    } while (confirmarContinuacao() != 0);
    printf("\n\n\t\tVoltando ao menu anterior... ");
    sleep(1);
}
void modificarCardapio() {
    char nomeModificar[50];
    printf("Digite o nome do cardapio que deseja modificar: ");
    lerString(nomeModificar,50);

    FILE *arquivoEntrada = fopen("cardapios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapio;

    int encontrado = 0;
    int escolha;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor,
                  &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeModificar) == 0) {
            // Se o nome corresponder, permita ao usuário modificar as características
             do{
                    printf("\t============= Cardapio Atual =============\n");
                    exibirCardapio(&cardapio);
                    printf("\n\t============= O que deseja atualizar =======\n");
                    printf("\t\t1. Nome\n");
                    printf("\t\t2. Descrição\n");
                    printf("\t\t3. Ingredientes\n");
                    printf("\t\t4. Valor do cardapio por pessoas\n");
                    printf("\t\t5. Disponibilidade\n");
                    printf("\t\t6. Voltar\n");
                    printf("\n\t===========================================\n");
                    printf("\tDigite a opção escolhida: ");
                    scanf("%d", &escolha);

            switch (escolha) {
            case 1:
                printf("\t\t Novo Nome: ");
                lerString(cardapio.nome,50);
                limparConsole();
                break;
            case 2:
                printf("\t\tNova Descricao: ");
                lerString(cardapio.descricao,100);
                limparConsole();
                break;
            case 3:
                printf("\t\tNovos Ingredientes: ");
                lerString(cardapio.ingredientes,200);
                limparConsole();

                break;
            case 4:
                printf("\t\tNovo Valor: ");
                cardapio.valor = validarEntradaDouble();
                limparConsole();

                break;
            case 5:
                printf("\t\tNova Disponibilidade (1 para ativo, 0 para inativo): ");
                cardapio.disponibilidade = validarEntradaInt();
                limparConsole();

                break;
            case 6:
                limparConsole();
               // exibirSubMenuCardapio(tipoUsuario);
                break;
            default:
                printf("\n\t\tOpção inválida! Tente novamente.\n");
                sleep(2);
                break;
 } } while (escolha != 6);
            encontrado = 1;
        }

        // Escreva no arquivo temporário
        fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                cardapio.ingredientes, cardapio.quantidadePessoas,
                cardapio.valor, cardapio.disponibilidade);
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    if (encontrado) {
        printf("Cardapio modificado com sucesso!\n");
        sleep(2);
    } else {
        printf("Cardapio nao encontrado.\n");
        sleep(2);
    }
}
void excluirCardapio() {
     char nomeExcluir[50];
    printf("Digite o nome do cardapio que deseja excluir: ");
    lerString(nomeExcluir, 50);

    FILE *arquivoEntrada = fopen("cardapios.txt", "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");

    if (arquivoEntrada == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapio;
    int encontrado = 0;

    while (fscanf(arquivoEntrada, "%[^;];%[^;];%[^;];%d;%f;%d\n",
                  cardapio.nome, cardapio.descricao, cardapio.ingredientes,
                  &cardapio.quantidadePessoas, &cardapio.valor,
                  &cardapio.disponibilidade) != EOF) {

        if (strcmp(cardapio.nome, nomeExcluir) == 0) {
            encontrado = 1;
            exibirCardapio(&cardapio); // Exibir detalhes do cardápio antes de excluir

            if (!confirmarExclusao()) {
                fclose(arquivoEntrada);
                fclose(arquivoTemp);
                remove("temp.txt");
                printf("Exclusao cancelada.\n");
                return;
            }
        } else {
            // Escrever no arquivo temporário apenas se não for o cardápio a ser excluído
            fprintf(arquivoTemp, "%s;%s;%s;%d;%f;%d\n", cardapio.nome, cardapio.descricao,
                    cardapio.ingredientes, cardapio.quantidadePessoas,
                    cardapio.valor, cardapio.disponibilidade);
        }
    }

    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    if (!encontrado) {
        remove("temp.txt"); // Se não foi encontrado, remover o arquivo temporário
        printf("Cardapio nao encontrado.\n");
        return;
    }

    // Remover o arquivo original
    remove("cardapios.txt");

    // Renomear o arquivo temporário para o original
    rename("temp.txt", "cardapios.txt");

    printf("Cardapio excluido com sucesso!\n");
}
void exibirCardapiosDoArquivo() {
    FILE *arquivo = fopen("cardapios.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cardapio cardapioLido;
    int pageSize = 3; // Número de cardápios por página
    int pagina = 1;
    int contador = 0;
    int reiniciarArquivo = 1;

    do {
        if (reiniciarArquivo) {
            rewind(arquivo);
            reiniciarArquivo = 0;
        }

        printf("\t=========== CARDAPIOS (\e[0;32mPAGINA %d\e[m) =============\n", pagina);

        char linha[512];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            sscanf(linha, "%[^;];%[^;];%[^;];%d;%f;%d\n", cardapioLido.nome, cardapioLido.descricao,
                   cardapioLido.ingredientes, &cardapioLido.quantidadePessoas, &cardapioLido.valor,
                   &cardapioLido.disponibilidade);

            exibirCardapio(&cardapioLido);
            printf("\n");

            contador++;

            if (contador >= pageSize) {
                break;
            }
        }

        if (feof(arquivo)) {
            break; // Se chegamos ao final do arquivo, saímos do loop externo
        }

        pausar();

        printf("\n\tPressione '\e[0;32mn\e[m' para avançar, '\e[0;33mp\e[m' para retroceder, ou '\e[1;91mq\e[m' para sair...\n\t\t");
        char input = getchar();
        while (getchar() != '\n');

        if (input == 'q' || input == 'Q') {
            break; // Sair do loop se o usuário digitar 'q' ou 'Q'
        } else if (input == 'n' || input == 'N') {
            // Avançar para a próxima página
            limparConsole();
            pagina++;
            contador = 0;
        } else if (input == 'p' || input == 'P' && pagina > 1) {
            // Retroceder para a página anterior
            limparConsole();
            pagina--;
            contador = 0;
            reiniciarArquivo = 1; // Reiniciar o arquivo ao retroceder
        }

    } while (1);

    fclose(arquivo);
}
void exibirCardapio(const Cardapio *cardapio) {
    printf("\t\tNome:\e[0;36m %s\e[m\n", cardapio->nome);
    printf("\t\tDescricao:\e[0;36m %s\e[m\n", cardapio->descricao);
    printf("\t\tIngredientes:\e[0;36m %s\e[m\n", cardapio->ingredientes);
    printf("\t\tQuantidade de Pessoas:\e[0;36m %d\e[m\n", cardapio->quantidadePessoas);
    printf("\t\tValor:\e[0;36m %.2f\e[m\n", cardapio->valor);
    printf("\t\tDisponibilidade:\e[0;36m  %s\e[m\n", cardapio->disponibilidade ? "\e[0;32mAtivo\e[m" : "\e[1;91mInativo\e[m");
}
//FUNÇÕES PARA LER ENTRADAS COM VALIDAÇÃO
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
int confirmarExclusao() {
    char resposta;
    printf("Tem certeza que deseja excluir o cardapio? (S/N): ");
    scanf(" %c", &resposta);  // Adicionamos um espaço antes do %c para consumir a nova linha pendente
    limparBuffer(); // Limpar o buffer para evitar problemas de leitura posterior

    return (resposta == 'S' || resposta == 's');
}
int confirmarContinuacao() {
    char resposta;
    printf("Deseja continuar o realizando este tipo de operação? (S/N): ");
    scanf(" %c", &resposta);  // Adicionamos um espaço antes do %c para consumir a nova linha pendente
    limparBuffer(); // Limpar o buffer para evitar problemas de leitura posterior

    return (resposta == 'S' || resposta == 's');
}
int validarEntradaInt() {
    int valor;

    while (1) {
        if (scanf("%d", &valor) == 1) {
            limparBuffer();
            return valor;
        } else {
            printf("Por favor, insira um valor válido (número inteiro).\n");
            limparBuffer();
        }
    }
}
double validarEntradaDouble() {
    double valor;

    while (1) {
        if (scanf("%lf", &valor) == 1) {
            limparBuffer();
            return valor;
        } else {
            printf("Por favor, insira um valor válido (número real).\n");
            limparBuffer();
        }
    }
}
//fUNÇÃO PAUSAR
void pausar() {
    printf("\t\tPressione Enter para continuar...");
    while (getchar() != '\n');
}
