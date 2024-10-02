Este código implementa um sistema de login simples para usuários,
permitindo operações financeiras em uma carteira digital com criptomoedas, 
e mantém o histórico de transações para cada usuário.
O sistema armazena os dados em um arquivo binário e pode gerenciar vários usuários.

FUNÇÕES DO CÓDIGO:

Cadastro de Usuário:
A função cadastrarUsuario permite que o usuário insira seu CPF e senha e cria uma conta inicial com saldo zero. Os dados são salvos no arquivo usuarios.bin.

Login de Usuário:
A função loginUsuario permite que o usuário entre na sua conta informando o CPF e senha. Se a combinação for válida, o índice do usuário no sistema é retornado para que as demais operações possam ser realizadas.

Consultar Saldo:
A função consultar_saldo exibe o saldo atual do usuário em reais, Bitcoin (BTC), Ethereum (ETH) e Ripple (XRP).

Consultar Extrato:
A função consultar_extrato exibe o histórico de transações do usuario, como depósitos, saques, compras e vendas de criptomoedas.

Depositar:
A função depositar permite que o usuário adicione dinheiro à sua conta em reais. A operação é registrada no extrato.

Sacar:
A função sacar permite que o usuário retire dinheiro de sua conta, desde que tenha saldo suficiente. Também registra a transação no extrato.

Comprar Criptomoedas:
A função comprarCriptomoeda permite que o usuário compre criptomoedas (BTC, ETH ou XRP) usando seu saldo em reais. A transação só é completada se o usuário tiver saldo suficiente. O valor é calculado com base em uma cotaçao fixa e a compra é registrada no extrato.

Vender Criptomoedas:
A função venderCriptomoeda permite que o usuário venda suas criptomoedas e converta para reais. A transação só é concluída se o usuário tiver saldo suficiente da criptomoeda que deseja vender.

COMO USAR O CÓDIGO:
Menu Principal:
O programa apresenta um menu com opções como cadastrar usuario, fazer login, consultar saldo, etc.

Cadastro de Usuário:
Selecione a opção 1 para cadastrar um novo usuário.
Digite o CPF e a senha.

Login:
Selecione a opção 2 para fazer login.
Digite o CPF e a senha cadastrados.

Consultar Saldo:
Selecione a opção 3 para verificar o saldo em reais e criptomoedas.

Depositar Dinheiro:
Selecione a opção 5 para depositar uma quantia em reais.

Comprar Criptomoeda:
Selecione a opção 7 e informe a criptomoeda (BTC, ETH ou XRP) e a quantidade que deseja comprar.

Consultar Extrato:
Selecione a opção 4 para ver o histórico de transações.

Vender Criptomoeda:
Selecione a opção 8 e informe a criptomoeda e a quantidade que deseja vender.

Sacar Dinheiro:
Selecione a opção 6 para sacar uma quantia em reais.
Sair:

Selecione a opção 9 para encerrar o programa.
