#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que guarda os dados de cada funcionario
// Requisito 1 e 2 do trabalho
typedef struct
{
    char nome[100];
    int grauEstudo;      // vai de 1 a 5
    int quantLinguas;    // quantas linguas a pessoa fala
    int nivel;           // cargo: 1, 2, 3 ou 4
    float produtividade; // entre 0 e 1.0
    float salario;       // calculado depois, por isso comeca zerado
} Funcionario;

// =============================================
// FUNCOES AUXILIARES
// =============================================

// Funcao que calcula o fatorial do grau de instrucao
// Requisito 4: retorna o fatorial do grau de estudo
int calcularFormacao(int grau)
{
    int resultado = 1;
    int i;
    // calcula o fatorial: ex: grau 3 = 3*2*1 = 6
    for (i = 1; i <= grau; i++)
    {
        resultado = resultado * i;
    }
    return resultado;
}

// Funcao que calcula o fator poliglota
// Requisito 5: eleva a quantidade de linguas ao cubo
int calcularPoliglota(int linguas)
{
    // cubo = linguas * linguas * linguas
    return linguas * linguas * linguas;
}

// Funcao que retorna o salario base de acordo com o nivel
// Requisito 6: nivel 1 = 1000, nivel 2 = 1500, nivel 3 = 2000, nivel 4 = 2500...
float calcularSalarioBase(int nivel)
{
    // cada nivel acrescenta R$500 ao salario base inicial de R$1000
    float base = 1000.0 + (nivel - 1) * 500.0;
    return base;
}

// Funcao que calcula o salario final do funcionario
// Requisito 7: regra com base no indice de produtividade
float calcularSalario(Funcionario f)
{
    float base = calcularSalarioBase(f.nivel);
    int formacao = calcularFormacao(f.grauEstudo);
    int poliglota = calcularPoliglota(f.quantLinguas);

    float salarioFinal;

    // parte fixa que aparece em todos os casos
    float parteFixa = base + (formacao * 100) + (poliglota * 100);

    if (f.produtividade > 0.7)
    {
        // produtividade alta: recebe bonus
        salarioFinal = parteFixa + (base * f.produtividade);
    }
    else if (f.produtividade >= 0.4)
    {
        // produtividade media: recebe so a parte fixa
        salarioFinal = parteFixa;
    }
    else
    {
        // produtividade baixa: tem desconto
        salarioFinal = parteFixa - (base * (0.4 - f.produtividade));
    }

    return salarioFinal;
}

// Funcao que conta quantos funcionarios ganham acima da media
// Requisito 8
void funcionariosAcimaMedia(Funcionario *lista, int n)
{
    float soma = 0;
    int i;

    // soma todos os salarios
    for (i = 0; i < n; i++)
    {
        soma += lista[i].salario;
    }

    // calcula a media
    float media = soma / n;

    // conta quem esta acima da media
    int contador = 0;
    for (i = 0; i < n; i++)
    {
        if (lista[i].salario > media)
        {
            contador++;
        }
    }

    printf("\n--- Funcionarios acima da media ---\n");
    printf("Media salarial: R$ %.2f\n", media);
    printf("Quantidade de funcionarios acima da media: %d\n", contador);
}

// =============================================
// FUNCOES DO MENU PRINCIPAL
// =============================================

// Funcao para cadastrar um funcionario
// Requisito 3 e parte do 10
void cadastrarFuncionario(Funcionario *f)
{
    printf("\nNome do funcionario: ");
    // usa scanf com %[^\n] para aceitar espacos no nome
    scanf(" %[^\n]", f->nome);

    printf("Grau de estudo (1 a 5): ");
    scanf("%d", &f->grauEstudo);

    // valida o grau de estudo
    while (f->grauEstudo < 1 || f->grauEstudo > 5)
    {
        printf("Valor invalido! Digite entre 1 e 5: ");
        scanf("%d", &f->grauEstudo);
    }

    printf("Quantidade de linguas que fala: ");
    scanf("%d", &f->quantLinguas);

    printf("Nivel do cargo (1 a 4): ");
    scanf("%d", &f->nivel);

    // valida o nivel
    while (f->nivel < 1 || f->nivel > 4)
    {
        printf("Valor invalido! Digite entre 1 e 4: ");
        scanf("%d", &f->nivel);
    }

    printf("Indice de produtividade (0.0 a 1.0): ");
    scanf("%f", &f->produtividade);

    // valida a produtividade
    while (f->produtividade < 0 || f->produtividade > 1.0)
    {
        printf("Valor invalido! Digite entre 0.0 e 1.0: ");
        scanf("%f", &f->produtividade);
    }

    // salario comeca zerado ate ser calculado
    f->salario = 0;

    printf("Funcionario cadastrado com sucesso!\n");
}

// Funcao para calcular o salario de todos os funcionarios
void calcularSalariosTodos(Funcionario *lista, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        lista[i].salario = calcularSalario(lista[i]);
    }
    printf("\nSalarios calculados com sucesso!\n");

    // mostra os salarios calculados
    for (i = 0; i < n; i++)
    {
        printf("  %s: R$ %.2f\n", lista[i].nome, lista[i].salario);
    }
}

// Funcao que busca um funcionario pelo nome
// Retorna o indice se achar, -1 se nao achar
int buscarPorNome(Funcionario *lista, int n, char *nome)
{
    int i;
    for (i = 0; i < n; i++)
    {
        // strcmp retorna 0 quando os nomes sao iguais
        if (strcmp(lista[i].nome, nome) == 0)
        {
            return i;
        }
    }
    return -1; // nao encontrou
}

// Funcao para editar os dados de um funcionario
// Requisito 9
void editarFuncionario(Funcionario *lista, int n)
{
    char nomeBusca[100];
    printf("\nDigite o nome do funcionario que deseja editar: ");
    scanf(" %[^\n]", nomeBusca);

    int indice = buscarPorNome(lista, n, nomeBusca);

    if (indice == -1)
    {
        printf("Funcionario nao encontrado!\n");
        return;
    }

    // ponteiro para facilitar o acesso
    Funcionario *f = &lista[indice];

    int opcaoEditar;

    // loop que fica aberto enquanto o usuario nao sair
    do
    {
        printf("\n--- Editando: %s ---\n", f->nome);
        printf("Qual campo deseja alterar?\n");
        printf("1 - Nome (atual: %s)\n", f->nome);
        printf("2 - Grau de estudo (atual: %d)\n", f->grauEstudo);
        printf("3 - Quantidade de linguas (atual: %d)\n", f->quantLinguas);
        printf("4 - Nivel do cargo (atual: %d)\n", f->nivel);
        printf("5 - Indice de produtividade (atual: %.2f)\n", f->produtividade);
        printf("0 - Sair da edicao\n");
        printf("Opcao: ");
        scanf("%d", &opcaoEditar);

        switch (opcaoEditar)
        {
        case 1:
            printf("Novo nome: ");
            scanf(" %[^\n]", f->nome);
            printf("Nome alterado!\n");
            break;
        case 2:
            printf("Novo grau de estudo (1 a 5): ");
            scanf("%d", &f->grauEstudo);
            printf("Grau alterado!\n");
            break;
        case 3:
            printf("Nova quantidade de linguas: ");
            scanf("%d", &f->quantLinguas);
            printf("Linguas alteradas!\n");
            break;
        case 4:
            printf("Novo nivel (1 a 4): ");
            scanf("%d", &f->nivel);
            printf("Nivel alterado!\n");
            break;
        case 5:
            printf("Novo indice de produtividade (0.0 a 1.0): ");
            scanf("%f", &f->produtividade);
            printf("Produtividade alterada!\n");
            break;
        case 0:
            printf("Saindo do modo de edicao...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcaoEditar != 0); // fica no loop ate escolher 0
}

// Funcao para visualizar os dados de um funcionario especifico
void visualizarFuncionario(Funcionario *lista, int n)
{
    char nomeBusca[100];
    printf("\nDigite o nome do funcionario: ");
    scanf(" %[^\n]", nomeBusca);

    int indice = buscarPorNome(lista, n, nomeBusca);

    if (indice == -1)
    {
        printf("Funcionario nao encontrado!\n");
        return;
    }

    Funcionario f = lista[indice];

    printf("\n========= Dados do Funcionario =========\n");
    printf("Nome:                %s\n", f.nome);
    printf("Grau de estudo:      %d\n", f.grauEstudo);
    printf("Linguas que fala:    %d\n", f.quantLinguas);
    printf("Nivel do cargo:      %d\n", f.nivel);
    printf("Produtividade:       %.2f\n", f.produtividade);

    // verifica se o salario ja foi calculado
    if (f.salario == 0)
    {
        printf("Salario:             (ainda nao calculado)\n");
    }
    else
    {
        printf("Salario:             R$ %.2f\n", f.salario);
    }
    printf("========================================\n");
}


// FUNCAO PRINCIPAL


int main()
{
    int n; // quantidade de funcionarios

    printf("=== Sistema de Funcionarios ===\n");
    printf("Quantos funcionarios trabalham na empresa? ");
    scanf("%d", &n);

    // aloca memoria dinamicamente para n funcionarios (requisito 3)
    Funcionario *lista = (Funcionario *)malloc(n * sizeof(Funcionario));

    // verifica se a alocacao deu certo
    if (lista == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    int opcao;

    // menu principal - fica em loop ate o usuario escolher sair
    do
    {
        printf("\n======= MENU PRINCIPAL =======\n");
        printf("1 - Cadastrar funcionarios\n");
        printf("2 - Calcular salarios\n");
        printf("3 - Ver quem ganha acima da media\n");
        printf("4 - Editar dados de um funcionario\n");
        printf("5 - Visualizar dados de um funcionario\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // cadastra todos os funcionarios em sequencia
            {
                int i;
                for (i = 0; i < n; i++)
                {
                    printf("\n--- Cadastrando funcionario %d de %d ---\n", i + 1, n);
                    cadastrarFuncionario(&lista[i]);
                }
            }
            break;
        case 2:
            calcularSalariosTodos(lista, n);
            break;
        case 3:
            // precisa ter calculado os salarios antes
            funcionariosAcimaMedia(lista, n);
            break;
        case 4:
            editarFuncionario(lista, n);
            break;
        case 5:
            visualizarFuncionario(lista, n);
            break;
        case 0:
            printf("Encerrando o programa. Ate logo!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // libera a memoria que foi alocada com malloc
    free(lista);

    return 0;
}