#include <stdio.h>
#include <string.h>

#define MAX 100

/* struct com os dados do funcionario - requisito 1 e 2 */
typedef struct {
    char nome[100];
    int grauEstudo;
    int quantLinguas;
    int nivel;
    float produtividade;
    float salario;
} Funcionario;

/* requisito 4: retorna o fatorial do grau de estudo */
int calcularFormacao(int grau) {
    int resultado = 1;
    int i;
    for (i = 1; i <= grau; i++) {
        resultado = resultado * i;
    }
    return resultado;
}

/* requisito 5: eleva a quantidade de linguas ao cubo */
int calcularPoliglota(int linguas) {
    return linguas * linguas * linguas;
}

/* requisito 6: retorna o salario base conforme o nivel */
float calcularSalarioBase(int nivel) {
    return 1000.0 + (nivel - 1) * 500.0;
}

/* requisito 7: calcula o salario final */
float calcularSalario(Funcionario f) {
    float base      = calcularSalarioBase(f.nivel);
    int formacao    = calcularFormacao(f.grauEstudo);
    int poliglota   = calcularPoliglota(f.quantLinguas);

    float parteFixa = base + (formacao * 100) + (poliglota * 100);
    float salarioFinal;

    if (f.produtividade > 0.7) {
        salarioFinal = parteFixa + (base * f.produtividade);
    } else if (f.produtividade >= 0.4) {
        salarioFinal = parteFixa;
    } else {
        salarioFinal = parteFixa - (base * (0.4 - f.produtividade));
    }

    return salarioFinal;
}

/* cadastra todos os funcionarios */
void cadastrarFuncionarios(Funcionario lista[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\n--- Funcionario %d de %d ---\n", i + 1, n);

        printf("Nome: ");
        scanf(" %[^\n]", lista[i].nome);

        printf("Grau de estudo (1 a 5): ");
        scanf("%d", &lista[i].grauEstudo);
        while (lista[i].grauEstudo < 1 || lista[i].grauEstudo > 5) {
            printf("Invalido! Digite entre 1 e 5: ");
            scanf("%d", &lista[i].grauEstudo);
        }

        printf("Quantidade de linguas que fala: ");
        scanf("%d", &lista[i].quantLinguas);

        printf("Nivel do cargo (1 a 4): ");
        scanf("%d", &lista[i].nivel);
        while (lista[i].nivel < 1 || lista[i].nivel > 4) {
            printf("Invalido! Digite entre 1 e 4: ");
            scanf("%d", &lista[i].nivel);
        }

        printf("Indice de produtividade (0.0 a 1.0): ");
        scanf("%f", &lista[i].produtividade);
        while (lista[i].produtividade < 0 || lista[i].produtividade > 1.0) {
            printf("Invalido! Digite entre 0.0 e 1.0: ");
            scanf("%f", &lista[i].produtividade);
        }

        lista[i].salario = 0;
        printf("Funcionario cadastrado!\n");
    }
}

/* requisito 2: calcula e mostra o salario de todos */
void calcularTodosSalarios(Funcionario lista[], int n) {
    int i;
    printf("\n--- Salarios calculados ---\n");
    for (i = 0; i < n; i++) {
        lista[i].salario = calcularSalario(lista[i]);
        printf("%s: R$ %.2f\n", lista[i].nome, lista[i].salario);
    }
}

/* requisito 8: mostra quantos ganham acima da media */
void funcionariosAcimaMedia(Funcionario lista[], int n) {
    float soma = 0;
    int i, contador = 0;

    for (i = 0; i < n; i++) {
        soma = soma + lista[i].salario;
    }

    float media = soma / n;

    for (i = 0; i < n; i++) {
        if (lista[i].salario > media) {
            contador++;
        }
    }

    printf("\nMedia salarial: R$ %.2f\n", media);
    printf("Funcionarios acima da media: %d\n", contador);
}

/* busca um funcionario pelo nome, retorna a posicao ou -1 */
int buscarPorNome(Funcionario lista[], int n, char nome[]) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/* requisito 9: edita os dados de um funcionario */
void editarFuncionario(Funcionario lista[], int n) {
    char nomeBusca[100];
    printf("Nome do funcionario para editar: ");
    scanf(" %[^\n]", nomeBusca);

    int idx = buscarPorNome(lista, n, nomeBusca);
    if (idx == -1) {
        printf("Funcionario nao encontrado!\n");
        return;
    }

    int opcao;
    do {
        printf("\nEditando: %s\n", lista[idx].nome);
        printf("1 - Nome\n");
        printf("2 - Grau de estudo\n");
        printf("3 - Quantidade de linguas\n");
        printf("4 - Nivel do cargo\n");
        printf("5 - Indice de produtividade\n");
        printf("0 - Sair da edicao\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Novo nome: ");
                scanf(" %[^\n]", lista[idx].nome);
                printf("Alterado!\n");
                break;
            case 2:
                printf("Novo grau (1 a 5): ");
                scanf("%d", &lista[idx].grauEstudo);
                printf("Alterado!\n");
                break;
            case 3:
                printf("Nova quantidade de linguas: ");
                scanf("%d", &lista[idx].quantLinguas);
                printf("Alterado!\n");
                break;
            case 4:
                printf("Novo nivel (1 a 4): ");
                scanf("%d", &lista[idx].nivel);
                printf("Alterado!\n");
                break;
            case 5:
                printf("Nova produtividade (0.0 a 1.0): ");
                scanf("%f", &lista[idx].produtividade);
                printf("Alterado!\n");
                break;
            case 0:
                printf("Saindo da edicao.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

/* visualiza os dados de um funcionario especifico */
void visualizarFuncionario(Funcionario lista[], int n) {
    char nomeBusca[100];
    printf("Nome do funcionario: ");
    scanf(" %[^\n]", nomeBusca);

    int idx = buscarPorNome(lista, n, nomeBusca);
    if (idx == -1) {
        printf("Funcionario nao encontrado!\n");
        return;
    }

    printf("\n======= Dados do Funcionario =======\n");
    printf("Nome:           %s\n",   lista[idx].nome);
    printf("Grau de estudo: %d\n",   lista[idx].grauEstudo);
    printf("Linguas:        %d\n",   lista[idx].quantLinguas);
    printf("Nivel do cargo: %d\n",   lista[idx].nivel);
    printf("Produtividade:  %.2f\n", lista[idx].produtividade);
    if (lista[idx].salario == 0)
        printf("Salario:        (nao calculado ainda)\n");
    else
        printf("Salario:        R$ %.2f\n", lista[idx].salario);
    printf("====================================\n");
}

/* requisito 10: menu principal */
int main() {
    Funcionario lista[MAX];
    int n, opcao;

    printf("Quantos funcionarios trabalham na empresa? ");
    scanf("%d", &n);
    while (n < 1 || n > MAX) {
        printf("Digite entre 1 e %d: ", MAX);
        scanf("%d", &n);
    }

    do {
        printf("\n========= MENU =========\n");
        printf("1 - Cadastrar funcionarios\n");
        printf("2 - Calcular salarios\n");
        printf("3 - Funcionarios acima da media\n");
        printf("4 - Editar funcionario\n");
        printf("5 - Visualizar funcionario\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFuncionarios(lista, n);   break;
            case 2: calcularTodosSalarios(lista, n);   break;
            case 3: funcionariosAcimaMedia(lista, n);  break;
            case 4: editarFuncionario(lista, n);       break;
            case 5: visualizarFuncionario(lista, n);   break;
            case 0: printf("Encerrando. Ate logo!\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}