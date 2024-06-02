#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 100
#define MAX_LIVROS 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    int ISBN;
    char nome[100];
    char autor[100];
    float valor;
} Livro;

typedef struct {
    char cpf[12];
    char nome[100];
    int idade;
} Usuario;

typedef struct {
    int ISBNs[10];
    time_t dataEmprestimo;
    time_t dataDevolucao;
    float multaPorDia;
} Emprestimo;

Livro livros[MAX_LIVROS];
Usuario usuarios[MAX_USUARIOS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int numLivros = 0, numUsuarios = 0, numEmprestimos = 0;
float taxaMulta = 0.10;

void cadastrarLivro() {
    system("cls");
    printf("\n\tCadastrar Livros\n");
    if (numLivros >= MAX_LIVROS) {
        printf("\n\tLimite de livros atingido!\n");
        return;
    }
    printf("\n\tISBN do livro: ");
    scanf("%d", &livros[numLivros].ISBN);
    printf("\n\tNome do livro: ");
    scanf(" %[^\n]", livros[numLivros].nome);
    printf("\n\tAutor do livro: ");
    scanf(" %[^\n]", livros[numLivros].autor);
    printf("\n\tValor do livro: ");
    scanf("%f", &livros[numLivros].valor);
    numLivros++;
    printf("\n\tLivro cadastrado!\n");
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void editarLivro() {
    system("cls");
    int isbn, found = 0;
    printf("\n\tEditar Livros\n");
    printf("\n\tISBN do livro que deseja editar: ");
    scanf("%d", &isbn);
    for (int i = 0; i < numLivros; i++) {
        if (livros[i].ISBN == isbn) {
            printf("\n\tEditando livro %s:\n", livros[i].nome);
            printf("\n\tNovo ISBN (anterior %d): ", livros[i].ISBN);
            scanf("\n\t%d", &livros[i].ISBN);
            printf("\n\tNovo nome (anterior %s): ", livros[i].nome);
            scanf(" %[^\n]", livros[i].nome);
            printf("\n\tNovo autor (anterior %s): ", livros[i].autor);
            scanf(" %[^\n]", livros[i].autor);
            printf("n\tNovo valor (anterior %.2f): ", livros[i].valor);
            scanf("%f", &livros[i].valor);
            found = 1;
            printf("\n\tLivro editado!\n");
            break;
        }
    }
    if (!found) {
        printf("\n\tISBN nao encontrado!\n");
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void deletarLivro() {
    system("cls");
    int isbn, found = 0;
    printf("\n\tDeletar Livros\n");
    printf("\n\tISBN do livro que deseja deletar: ");
    scanf("%d", &isbn);
    for (int i = 0; i < numLivros; i++) {
        if (livros[i].ISBN == isbn) {
            for (int j = i; j < numLivros - 1; j++) {
                livros[j] = livros[j + 1];
            }
            numLivros--;
            found = 1;
            printf("\n\tLivro deletado!\n");
            break;
        }
    }
    if (!found) {
        printf("\n\tISBN nao encontrado!\n");
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void livrosCrescente(Livro *livros, int numLivros, int opcao) {
    for (int i = 0; i < numLivros - 1; i++) {
        for (int j = 0; j < numLivros - 1 - i; j++) {
            int troca = 0;
            switch (opcao) {
                case 1: // ISBN
                    if (livros[j].ISBN > livros[j + 1].ISBN) troca = 1;
                    break;
                case 2: // Nome
                    if (strcmp(livros[j].nome, livros[j + 1].nome) > 0) troca = 1;
                    break;
                case 3: // Autor
                    if (strcmp(livros[j].autor, livros[j + 1].autor) > 0) troca = 1;
                    break;
                case 4: // Valor
                    if (livros[j].valor > livros[j + 1].valor) troca = 1;
                    break;
            }
            if (troca) {
                Livro temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

void livrosDecrescente(Livro *livros, int numLivros, int opcao) {
    for (int i = 0; i < numLivros - 1; i++) {
        for (int j = 0; j < numLivros - 1 - i; j++) {
            int troca = 0;
            switch (opcao) {
                case 1: // ISBN
                    if (livros[j].ISBN < livros[j + 1].ISBN) troca = 1;
                    break;
                case 2: // Nome
                    if (strcmp(livros[j].nome, livros[j + 1].nome) < 0) troca = 1;
                    break;
                case 3: // Autor
                    if (strcmp(livros[j].autor, livros[j + 1].autor) < 0) troca = 1;
                    break;
                case 4: // Valor
                    if (livros[j].valor < livros[j + 1].valor) troca = 1;
                    break;
            }
            if (troca) {
                Livro temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

void visualizarLivrosOrdenados(int ordem, int criterio) {
    printf("\n\tVisualizar Livros\n");
    if (numLivros == 0) {
        printf("\n\tNenhum livro cadastrado!\n");
        printf("\n\tENTER para continuar.\n");
        getchar(); getchar();
        return;
    }
    if (ordem == 1)
        livrosCrescente(livros, numLivros, criterio);
    else
        livrosDecrescente(livros, numLivros, criterio);

    printf("\n\tLivros ordenados:\n");
    for (int i = 0; i < numLivros; i++) {
        printf("\tISBN: %d, Nome: %s, Autor: %s, Valor: %.2f\n", livros[i].ISBN, livros[i].nome, livros[i].autor, livros[i].valor);
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}


void visualizarLivros() {
    system("cls");
    printf("\n\tVisualizar Livros\n");
    if (numLivros == 0) {
        printf("\n\tNenhum livro cadastrado!\n");
        return;
    }
    int opcao, ordem;
    printf("\n\tEscolha uma opcao de ordenacao:\n\n");
    printf("\t1 - ISBN\n");
    printf("\t2 - Nome\n");
    printf("\t3 - Autor\n");
    printf("\t4 - Valor\n");
    printf("\n\tOpcao desejada: ");
    scanf("%d", &opcao);

    printf("\n\tEscolha a ordem de ordenacao:\n\n");
    printf("\t1 - Crescente\n");
    printf("\t2 - Decrescente\n");
    printf("\n\tOpcao desejada: ");
    scanf("%d", &ordem);

    visualizarLivrosOrdenados(ordem, opcao);
}

void cadastrarUsuario() {
    system("cls");
    printf("\n\tCadastrar Usuario\n");
    if (numUsuarios >= MAX_USUARIOS) {
        printf("\n\tLimite de usuarios atingido!\n");
        return;
    }
    printf("\n\tCPF do usuario (11 caracteres): ");
    scanf("%s", usuarios[numUsuarios].cpf);
    printf("\n\tNome do usuario: ");
    scanf("%s", usuarios[numUsuarios].nome);
    printf("\n\tIdade do usuario: ");
    scanf("%d", &usuarios[numUsuarios].idade);
    numUsuarios++;
    printf("\n\tUsuario cadastrado!\n");
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void visualizarUsuarios() {
    system("cls");
    printf("\n\tVisualizar Usuario\n");
    if (numUsuarios == 0) {
        printf("\n\tNenhum usuario cadastrado!\n");
        return;
    }
    printf("\n\tUsuarios cadastrados:\n");
    for (int i = 0; i < numUsuarios; i++) {
        printf("\n\t%d. CPF: %s, Nome: %s, Idade: %d\n", i + 1, usuarios[i].cpf, usuarios[i].nome, usuarios[i].idade);
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void editarUsuario() {
    system("cls");
    char cpf[12];
    int found = 0;
    printf("\n\tEditar Usuario\n");
    printf("n\tCPF do usuario que deseja editar: ");
    scanf("%s", cpf);
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            printf("\n\tEditando usuario %s:\n", usuarios[i].nome);
            printf("\n\ts", usuarios[i].cpf);
            printf("\n\tNovo nome (anterior %s): ", usuarios[i].nome);
            scanf(" %[^\n]", usuarios[i].nome);
            printf("\n\tNova idade (anterior %d): ", usuarios[i].idade);
            scanf("%d", &usuarios[i].idade);
            found = 1;
            printf("\n\tUsuario editado!\n");
            break;
        }
    }
    if (!found) {
        printf("\n\tCPF nao encontrado!\n");
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void deletarUsuario() {
    system("cls");
    char cpf[12];
    int found = 0;
    printf("\n\tDeletar Usuario\n");
    printf("\n\tCPF do usuario que deseja deletar: ");
    scanf("%s", cpf);
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0) {
            for (int j = i; j < numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            numUsuarios--;
            found = 1;
            printf("\n\tUsuario deletado!\n");
            break;
        }
    }
    if (!found) {
        printf("\n\tCPF nao encontrado!\n");
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void visualizarEmprestimos() {
    system("cls");
    printf("\n\tVisualizar Emprestimo\n");
    if (numEmprestimos == 0) {
        printf("\n\tNenhum emprestimo cadastrado!\n");
        return;
    }
    printf("\n\tEmprestimos cadastrados:\n");
    char buf[20];
    for (int i = 0; i < numEmprestimos; i++) {
        printf("\n\tEmprestimo %d:\n", i + 1);
        printf("\n\tLivros emprestados: ");
        for (int j = 0; j < 10 && emprestimos[i].ISBNs[j] != 0; j++) {
            printf("%d ", emprestimos[i].ISBNs[j]);
        }
        printf("\n");
        strftime(buf, 20, "\n\t%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].dataEmprestimo));
        printf("\n\tData do emprestimo: %s\n", buf);
        strftime(buf, 20, "\n\t%Y-%m-%d %H:%M:%S", localtime(&emprestimos[i].dataDevolucao));
        printf("\n\tData de devolucao: %s\n", buf);
        printf("\n\tMulta por dia: %.2f\n", emprestimos[i].multaPorDia);
    }
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void cadastrarEmprestimo() {
    system("cls");
    printf("\n\tCadastrar Emprestimo\n");
    if (numEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\n\tLimite de emprestimos atingido!\n");
        return;
    }
    printf("\n\tNumero de livros do emprestimo: ");
    int numLivrosEmprestimo;
    scanf("%d", &numLivrosEmprestimo);
    for (int i = 0; i < numLivrosEmprestimo; i++) {
        printf("\n\tISBN do livro %d: ", i + 1);
        scanf("%d", &emprestimos[numEmprestimos].ISBNs[i]);
    }
    emprestimos[numEmprestimos].dataEmprestimo = time(NULL);
    printf("\n\tNumero de dias de emprestimo: ");
    int diasEmprestimo;
    scanf("%d", &diasEmprestimo);
    emprestimos[numEmprestimos].dataDevolucao = emprestimos[numEmprestimos].dataEmprestimo + (diasEmprestimo * 86400);

    // Calculando a multa por dia
    emprestimos[numEmprestimos].multaPorDia = 0;
    for (int i = 0; i < numLivrosEmprestimo; i++) {
        for (int j = 0; j < numLivros; j++) {
            if (emprestimos[numEmprestimos].ISBNs[i] == livros[j].ISBN) {
                emprestimos[numEmprestimos].multaPorDia += livros[j].valor * taxaMulta;
                break;
            }
        }
    }
    numEmprestimos++;
    printf("\n\tEmprestimo feito!\n");
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

void modificarMulta() {
    system("cls");
    printf("\n\tModificar Multa\n");
    printf("\n\tNova taxa de multa por dia (formato decimal, ex: 0.20 para 20%%): ");
    scanf("%f", &taxaMulta);
    printf("\n\tTaxa de multa modificada para %.2f%%\n", taxaMulta * 100);
    printf("\n\tENTER para continuar.\n");
    getchar(); getchar();
}

int main() {
    int opcao;
    do {
        system("cls");
        printf("\n\t======================||Biblioteca||======================\n\n\t\t\t\t   MENU\n\n");
        printf("\t1 - Cadastrar usuario\t\t4 - Visualizar usuarios\n");
        printf("\t2 - Cadastrar livro\t\t5 - Visualizar livros\n");
        printf("\t3 - Cadastrar emprestimo\t6 - Visualizar emprestimos\n\n");
        printf("\t7 - Editar livro\t\t9 - Deletar livro\n");
        printf("\t8 - Editar usuario\t\t10 - Deletar usuario\n\n");
        printf("\t11 - Modificar multa\t\t12 - Sair\n\n");
        printf("\tOpcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                cadastrarLivro();
                break;
            case 3:
                cadastrarEmprestimo();
                break;
            case 4:
                visualizarUsuarios();
                break;
            case 5:
                visualizarLivros();
                break;
            case 6:
                visualizarEmprestimos();
                break;
            case 7:
                editarLivro();
                break;
            case 8:
                editarUsuario();
                break;
            case 9:
                deletarLivro();
                break;
            case 10:
                deletarUsuario();
                break;
            case 11:
                modificarMulta();
                break;
            case 12:
                printf("\n\tSaindo do sistema...\n\n\tVolte sempre!\n");
                break;
            default:
                printf("\n\tOpcao invalida!\n");
        }
    } while (opcao != 12);
    return 0;
}
