#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CPF 12
#define MAX_SENHA 20
#define MAX_TRANSACOES 100
#define MAX_TRANSACAO_LEN 100
#define ARQUIVO "usuarios.bin"

// Cotações fixas
#define COTACAO_BTC 1000.0
#define COTACAO_ETH 500.0
#define COTACAO_XRP 100.0

typedef struct {
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];
    double saldo;
    double BTC;
    double ETH;
    double XRP;
    int num_transacoes;
    char transacoes[MAX_TRANSACOES][MAX_TRANSACAO_LEN];
} Usuario;

void cadastrarUsuario() {
    Usuario usuario = {0};
    FILE *file = fopen(ARQUIVO, "ab"); 
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Cadastro de Usuário\n");
    printf("Digite o CPF: ");
    scanf("%s", usuario.cpf);
    printf("Digite a senha: ");
    scanf("%s", usuario.senha);

    usuario.saldo = 0.0;
    usuario.BTC = 0.0;
    usuario.ETH = 0.0;
    usuario.XRP = 0.0;
    usuario.num_transacoes = 0;

    fwrite(&usuario, sizeof(Usuario), 1, file); 
    fclose(file);
    printf("Usuário cadastrado com sucesso!\n");
}

int loginUsuario() {
    Usuario usuario;
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];
    FILE *file = fopen(ARQUIVO, "rb"); 
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    printf("Login de Usuário\n");
    printf("Digite o CPF: ");
    scanf("%s", cpf);
    printf("Digite a senha: ");
    scanf("%s", senha);

    int idx = 0;
    while (fread(&usuario, sizeof(Usuario), 1, file)) {       
        if (strcmp(usuario.cpf, cpf) == 0 && strcmp(usuario.senha, senha) == 0) {
            fclose(file);
            printf("Login realizado com sucesso!\n");
            return idx; 
        }
        idx++;
    }

    fclose(file);
    printf("CPF ou senha incorretos.\n");
    return -1;
}

void consultar_saldo(Usuario *usuario) {
    printf("Saldo atual: R$ %.2f\n", usuario->saldo);
    printf("Saldo em Bitcoin (BTC): %.2f BTC\n", usuario->BTC);
    printf("Saldo em Ethereum (ETH): %.2f ETH\n", usuario->ETH);
    printf("Saldo em Ripple (XRP): %.2f XRP\n", usuario->XRP);
}

void consultar_extrato(Usuario *usuario) {
    printf("Extrato:\n");
    for (int i = 0; i < usuario->num_transacoes; i++) {
        printf("%s\n", usuario->transacoes[i]);
    }
}

void depositar(Usuario *usuario, double valor) {
    time_t agora = time(NULL);
    usuario->saldo += valor;

    char transacao[MAX_TRANSACAO_LEN];
    snprintf(transacao, MAX_TRANSACAO_LEN, "Depósito de R$ %.2f em %s", valor, ctime(&agora));
    strcpy(usuario->transacoes[usuario->num_transacoes++], transacao);

    printf("Depósito realizado com sucesso.\n");
}

int sacar(Usuario *usuario, double valor) {
    if (usuario->saldo >= valor) {
        time_t agora = time(NULL);
        usuario->saldo -= valor;

        char transacao[MAX_TRANSACAO_LEN];
        snprintf(transacao, MAX_TRANSACAO_LEN, "Saque de R$ %.2f em %s", valor, ctime(&agora));
        strcpy(usuario->transacoes[usuario->num_transacoes++], transacao);

        printf("Saque realizado com sucesso.\n");
        return 1;
    }
    printf("Saldo insuficiente.\n");
    return 0;
}


int verificarSenha(Usuario *usuario) {
    char senha[MAX_SENHA];
    printf("Digite sua senha para confirmar: ");
    scanf("%s", senha);
    if (strcmp(usuario->senha, senha) == 0) {
        return 1; 
    } else {
        printf("Senha incorreta!\n");
        return 0; 
    }
}


void comprarCriptomoeda(Usuario *usuario, const char *moeda, double quantidade) {
    if (!verificarSenha(usuario)) {
        printf("Compra cancelada.\n");
        return;
    }

    double cotacao = 0.0;
    if (strcmp(moeda, "BTC") == 0) {
        cotacao = COTACAO_BTC;
    } else if (strcmp(moeda, "ETH") == 0) {
        cotacao = COTACAO_ETH;
    } else if (strcmp(moeda, "XRP") == 0) {
        cotacao = COTACAO_XRP;
    } else {
        printf("Criptomoeda inválida.\n");
        return;
    }

    double valorCompra = quantidade * cotacao;

    if (usuario->saldo >= valorCompra) {
        usuario->saldo -= valorCompra;

        if (strcmp(moeda, "BTC") == 0) {
            usuario->BTC += quantidade;
        } else if (strcmp(moeda, "ETH") == 0) {
            usuario->ETH += quantidade;
        } else if (strcmp(moeda, "XRP") == 0) {
            usuario->XRP += quantidade;
        }

        time_t agora = time(NULL);
        char transacao[MAX_TRANSACAO_LEN];
        snprintf(transacao, MAX_TRANSACAO_LEN, "Compra de %.2f %s por R$ %.2f em %s", quantidade, moeda, valorCompra, ctime(&agora));
        strcpy(usuario->transacoes[usuario->num_transacoes++], transacao);

        printf("Compra de %.2f %s realizada com sucesso.\n", quantidade, moeda);
    } else {
        printf("Saldo insuficiente para a compra.\n");
    }
}

void salvarUsuarios(Usuario *usuarios, int numUsuarios) {
    FILE *file = fopen(ARQUIVO, "wb");
    if (file == NULL) {
        perror("Erro ao salvar usuários");
        return;
    }
    fwrite(usuarios, sizeof(Usuario), numUsuarios, file);
    fclose(file);
}

int carregarUsuarios(Usuario *usuarios) {
    FILE *file = fopen(ARQUIVO, "rb");
    if (file == NULL) {
        return 0; 
    }
    int numUsuarios = 0;
    while (fread(&usuarios[numUsuarios], sizeof(Usuario), 1, file)) {
        numUsuarios++;
    }
    fclose(file);
    return numUsuarios;
}

int main() {
    Usuario usuarios[100];
    int numUsuarios = carregarUsuarios(usuarios);
    int opcao;
    int idxUsuarioLogado = -1;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Fazer Login\n");
        printf("3. Consultar Saldo\n");
        printf("4. Consultar Extrato\n");
        printf("5. Depositar\n");
        printf("6. Sacar\n");
        printf("7. Comprar Criptomoeda\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                numUsuarios = carregarUsuarios(usuarios); 
                break;
            case 2:
                idxUsuarioLogado = loginUsuario();
                break;
            case 3:
                if (idxUsuarioLogado != -1)
                    consultar_saldo(&usuarios[idxUsuarioLogado]);
                else
                    printf("Faça login primeiro.\n");
                break;
            case 4:
                if (idxUsuarioLogado != -1)
                    consultar_extrato(&usuarios[idxUsuarioLogado]);
                else
                    printf("Faça login primeiro.\n");
                break;
            case 5:
                if (idxUsuarioLogado != -1) {
                    double valor;
                    printf("Digite o valor a depositar: ");
                    scanf("%lf", &valor);
                    depositar(&usuarios[idxUsuarioLogado], valor);
                    salvarUsuarios(usuarios, numUsuarios);
                } else {
                    printf("Faça login primeiro.\n");
                }
                break;
            case 6:
                if (idxUsuarioLogado != -1) {
                    double valor;
                    printf("Digite o valor a sacar: ");
                    scanf("%lf", &valor);
                    if (sacar(&usuarios[idxUsuarioLogado], valor)) {
                        salvarUsuarios(usuarios, numUsuarios);
                    }
                } else {
                    printf("Faça login primeiro.\n");
                }
                break;
            case 7:
                if (idxUsuarioLogado != -1) {
                    char moeda[4];
                    double quantidade;
                    printf("Digite a criptomoeda (BTC, ETH, XRP): ");
                    scanf("%s", moeda);
                    printf("Digite a quantidade a comprar: ");
                    scanf("%lf", &quantidade);
                    comprarCriptomoeda(&usuarios[idxUsuarioLogado], moeda, quantidade);
                    salvarUsuarios(usuarios, numUsuarios);
                } else {
                    printf("Faça login primeiro.\n");
                }
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 8);

    return 0;
}
