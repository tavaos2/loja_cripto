# Exchange de Criptomoedas - Módulo Administrador

## Objetivo do Projeto
Este projeto faz parte de um sistema de exchange de criptomoedas, que possui dois módulos independentes: um para investidores e outro para administradores. O módulo descrito aqui é o **módulo administrador**, desenvolvido em C, e tem como objetivo permitir o gerenciamento de investidores e criptomoedas da plataforma. As funcionalidades do administrador incluem cadastrar e excluir investidores e criptomoedas, consultar saldos e extratos de investidores, e atualizar cotações de criptomoedas.

## Funcionalidades
1. **Efetuar Login**: O administrador faz login usando um CPF (login padrão: "admin") e senha (senha padrão: "1234"). Apenas após um login bem-sucedido, o menu principal é exibido.
2. **Cadastrar Novo Investidor**: Permite cadastrar novos investidores com nome, CPF e senha.
3. **Excluir Investidor**: Permite excluir um investidor especificado pelo CPF. A exclusão é realizada apenas após confirmação.
4. **Cadastrar Criptomoeda**: Adiciona uma nova criptomoeda com nome, cotação inicial, taxa de compra e taxa de venda.
5. **Excluir Criptomoeda**: Remove uma criptomoeda específica após confirmação.
6. **Consultar Saldo de um Investidor**: Consulta o saldo atual de um investidor especificado pelo CPF.
7. **Consultar Extrato de um Investidor**: Exibe o extrato de transações de um investidor especificado pelo CPF.

## Como Compilar o Programa
Para compilar o programa, siga as etapas abaixo:

1. Abra um terminal e navegue até o diretório onde o arquivo `projeto_3.c` está salvo.
2. Execute o comando de compilação utilizando o compilador `gcc`:
   ```bash
   gcc projeto_3.c -o projeto_3
   ```
   Esse comando gerará um arquivo executável chamado `projeto_3`.

## Como Executar o Programa
Para executar o programa, use o seguinte comando no terminal:
```bash
./projeto_3
```

ALUNOS: GUSTAVO SOUZA ROLIM CAVALCANTE 24.124.030-8, Thiago Montoia Israel 24.124.013-4 e Dante Ryuichi Kawazu 24.124.008-4
