#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CPF 12
#define MAX_SENHA 20
#define MAX_NOME 50
#define MAX_CRIPTOMOEDAS 100
#define ARQUIVO_USUARIOS "usuarios.bin"
#define ARQUIVO_CRIPTOMOEDAS "criptomoedas.bin"

typedef struct {
    char nome[MAX_NOME];
    double cotacaoInicial;
    double taxaCompra;
    double taxaVenda;
} Criptomoeda;

typedef struct {
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];
    char nome[MAX_NOME];
    double saldo;
    int ativo;
} Usuario;

void efetuarLoginAdministrador(char *cpf, char *senha) {
    if (strcmp(cpf, "admin") == 0 && strcmp(senha, "1234") == 0) {
        printf("Login realizado com sucesso!\n");
    } else {
        printf("CPF ou senha inválidos. Encerrando...\n");
        exit(1);
    }
}

void cadastrarInvestidor() {
    Usuario usuario = {0};
    FILE *file = fopen(ARQUIVO_USUARIOS, "ab");

    if (!file) {
        perror("Erro ao abrir o arquivo de usuários.");
        return;
    }

    printf("Cadastro de novo investidor\n");
    printf("Nome: ");
    scanf(" %[^\n]s", usuario.nome);
    printf("CPF: ");
    scanf("%s", usuario.cpf);
    printf("Senha: ");
    scanf("%s", usuario.senha);

    usuario.saldo = 0.0;
    usuario.ativo = 1;

    fwrite(&usuario, sizeof(Usuario), 1, file);
    fclose(file);

    printf("Investidor cadastrado com sucesso!\n");
}

void excluirInvestidor() {
    char cpf[MAX_CPF];
    printf("Digite o CPF do investidor a ser excluído: ");
    scanf("%s", cpf);

    FILE *file = fopen(ARQUIVO_USUARIOS, "rb+");
    if (!file) {
        perror("Erro ao abrir o arquivo de usuários.");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, file)) {
        if (strcmp(usuario.cpf, cpf) == 0 && usuario.ativo) {
            printf("Investidor encontrado: %s\n", usuario.nome);
            printf("Confirmar exclusão? (1 = sim, 0 = não): ");
            int confirm;
            scanf("%d", &confirm);
            if (confirm == 1) {
                usuario.ativo = 0;
                fseek(file, -sizeof(Usuario), SEEK_CUR);
                fwrite(&usuario, sizeof(Usuario), 1, file);
                printf("Investidor excluído com sucesso.\n");
            }
            fclose(file);
            return;
        }
    }

    printf("Investidor não encontrado.\n");
    fclose(file);
}
void cadastrarCriptomoeda() {
    Criptomoeda criptomoeda = {0};
    FILE file = fopen(ARQUIVO_CRIPTOMOEDAS, "ab");

    if (!file) {
        perror("Erro ao abrir o arquivo de criptomoedas.");
        return;
    }

    printf("Cadastro de nova criptomoeda\n");
    printf("Nome: ");
    scanf(" %[^\n]s", criptomoeda.nome);
    printf("Cotação inicial: ");
    scanf("%lf", &criptomoeda.cotacaoInicial);
    printf("Taxa de compra (%%): ");
    scanf("%lf", &criptomoeda.taxaCompra);
    printf("Taxa de venda (%%): ");
    scanf("%lf", &criptomoeda.taxaVenda);

    fwrite(&criptomoeda, sizeof(Criptomoeda), 1, file);
    fclose(file);

    printf("Criptomoeda cadastrada com sucesso!\n");
}

void excluirCriptomoeda() {
    char nome[MAX_NOME];
    printf("Digite o nome da criptomoeda a ser excluída: ");
    scanf(" %[^\n]s", nome);

    FILEfile = fopen(ARQUIVO_CRIPTOMOEDAS, "rb+");
    if (!file) {
        perror("Erro ao abrir o arquivo de criptomoedas.");
        return;
    }

    Criptomoeda criptomoeda;
    while (fread(&criptomoeda, sizeof(Criptomoeda), 1, file)) {
        if (strcmp(criptomoeda.nome, nome) == 0) {
            printf("Criptomoeda encontrada: %s\n", criptomoeda.nome);
            printf("Confirmar exclusão? (1 = sim, 0 = não): ");
            int confirm;
            scanf("%d", &confirm);
            if (confirm == 1) {
                fseek(file, -sizeof(Criptomoeda), SEEK_CUR);
                Criptomoeda vazia = {0};
                fwrite(&vazia, sizeof(Criptomoeda), 1, file);
                printf("Criptomoeda excluída com sucesso.\n");
            }
            fclose(file);
            return;
        }
    }

    printf("Criptomoeda não encontrada.\n");
    fclose(file);
}
