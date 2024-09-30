#include <stdio.h> 
#include <string.h>

#define MAX_CPF 12
#define MAX_SENHA 20
#define ARQUIVO "usuarios.bin"

typedef struct {
    char cpf[MAX_CPF];
    char senha[MAX_SENHA];
} Usuario;


void cadastrarUsuario() {
    Usuario usuario;
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
        return 0;
    }

    printf("Login de Usuário\n");
    printf("Digite o CPF: ");
    scanf("%s", cpf);
    printf("Digite a senha: ");
    scanf("%s", senha);


    while (fread(&usuario, sizeof(Usuario), 1, file)) {       
        if (strcmp(usuario.cpf, cpf) == 0 && strcmp(usuario.senha, senha) == 0) {
            fclose(file);
            printf("Login realizado com sucesso!\n");
            return 1; 
        }
    }

    fclose(file);
    printf("CPF ou senha incorretos.\n");
    return 0; 
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Fazer Login\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                loginUsuario();
                break;
            case 3:
                printf("Saindo...\n"); 
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
