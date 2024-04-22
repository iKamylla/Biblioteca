#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <ctype.h>

// struct usuarios
typedef struct{
    char nome[20];
    int emprestimo;
} usuario;

// struct livros
typedef struct{
    char isbn[20];
    char titulo[50];
    char autor[20];
    int disponivel;
} livro;

// struct data
typedef struct{
    int dia;
    int mes;
    int ano;
} data;

// struct emprestimo
typedef struct{
    char isbn[20];
    char nome[20];
    data emprestimo;
    data prevista;
    data devolucao;
} emprestimo;

// struct aux
typedef struct{
    data dte;
    data dtp;
} aux;

void cadastroUsuario();
void cadastroLivro();
void emprestimos();
void devolucao();
void consultaUsuario();
void cunsultaLivro();
void lerArquivo();
data dataAtual();

// main
int main(){
    int opcao;

    do{
       printf("\n\t\t\t     Sistema de biblioteca\n\n");
       printf("\n\t\t     1 - Cadastrar Alunos\n");
       printf("\t\t     2 - Cadastrar Livros\n");
       printf("\t\t     3 - Emprestimos de Livros\n");
       printf("\t\t     4 - Devolucao de Livros\n");
       printf("\t\t     5 - Consultar alunos cadastrados\n");
       printf("\t\t     6 - Consultar livros cadastrados\n");
       printf("\t\t     0 - Sair do programa\n");
       printf("\nOpcao desejada: ");
       scanf("%d", &opcao);

        switch ( opcao ){
            case 1:
                cadastroUsuario(); break;
            case 2:
                cadastroLivro(); break;
            case 3:
                emprestimos(); break;
            case 4:
                devolucao(); break;
            case 5:
                consultaUsuario(); break;
            case 6:
                consultaLivro(); break;
            case 7:
                lerArquivo(); break;
            case 0:
                break;
            default:
                printf("\n\t\t\tOpcao invalida!\n\n");
        }
       }while( opcao != 0 );
    system("pause");
    return 0;
}

// função pra cadastro de usuarios
void cadastroUsuario(){
    FILE * arquivo;
    usuario dadosUsuario;
    int auxNome;
    char cadastroUsuario;
    dadosUsuario.emprestimo = 0;

    printf("\n\t\t\tCadastro de Usuarios\n\n");

    // verificar dados
    if((arquivo = fopen("usuarios.dat", "ab"))== NULL){
        printf("\nErro de abertura do arquivo usuarios.dat!");
        return 0;
    }
    fseek(arquivo,0,SEEK_END);
    auxNome= ftell(arquivo) / sizeof(usuario);

    do{
        dadosUsuario.emprestimo = 0;
        printf("\nNome: ");
        scanf("%59[^\n]", dadosUsuario.nome);
        printf("Emprestimos.: %d\n", dadosUsuario.emprestimo);
        fwrite(&dadosUsuario,sizeof(usuario),1,arquivo);

        do{
            printf("\nCadastrar outro usuario? (S/N): ");
            scanf(" %c", &cadastroUsuario);
            cadastroUsuario = toupper(cadastroUsuario);
        } while(cadastroUsuario != 'S' && cadastroUsuario != 'N');
        } while(cadastroUsuario == 'S');

    fclose(arquivo);
    system("cls");
}

// função pra cadastrar livros
void cadastroLivro(){
    FILE * arquivo;
    livro dadosLivro;
    char cadastroLivro;

    // verificar dados
    if((arquivo = fopen("livros.dat", "ab")) == NULL){
        printf("\nErro na abertura do arquivo livros.dat!\n\n");
        return 0;
    }

    printf("\n\t\t\tCadastrar Livros\n\n");

    do{
        printf("\nISBN: ");
        scanf(" %16[^\n]", dadosLivro.isbn);
        printf("Titulo: ");
        scanf(" %129[^\n]", dadosLivro.titulo);
        printf("Autor: ");
        scanf(" %179[^\n]", dadosLivro.autor);
        printf("Disponiveis: %d\n", dadosLivro.disponivel);
        fwrite(&dadosLivro,sizeof(livro),1,arquivo);

        do{
            printf("\nDeseja cadastrar outro livro?(S/N): ");
            scanf("%c", &cadastroLivro);
            cadastroLivro = toupper(cadastroLivro);
        } while(cadastroLivro != 'S' && cadastroLivro != 'N');
    } while(cadastroLivro == 'S');

    fclose(arquivo);
    system("cls");
}

// função emprestimos
void Emprestimos(){
    FILE * fp, * fpa, * fpl, * fpr;
    emprestimo dadosEmprestimo;
    emprestimo auxisbn;
    emprestimo guard_valor;
    usuario dadosUsuario;
    livro dadosLivro;
    aux dataAux;
    data controle;
    int cont = 1, auxEmp = 0, auxDia, auxMes, auxAno, contseq=0;
    char op, auxis[20], auxisb[20];

    if((fp = fopen ("emprestimo.dat", "ab")) == NULL){
        printf("\n\nErro na abertura do arquivo emprestimo.dat!\n\n");
        return 0;
    }
    if((fpl = fopen ("livro.dat", "r+b")) == NULL){
        printf("\nErro na leitura do arquivo livro.dat");
        return;
    }
    if((fpa = fopen ("usuario.dat", "r+b")) == NULL){
        printf("\nErro na leitura do arquivo usuario.dat!\n\n");
        return;
    }
    if((fpr = fopen ("emprestimo.dat", "rb")) == NULL){
        printf("\n\nErro na abertura do arquivo emprestimo.dat!\n\n");
        return;
    }
    printf("\n\n\n\t\t\tEmprestimos de Livros\n\n");
    printf("\nIsbn: ");
    scanf(" %16[^\n]", auxisbn.isbn);
    strcpy(auxisb,auxis);

    // verifica se o isbn é válido e exibe as informações
    while(1){
        fread(&dadosLivro, sizeof(livro),1,fpl);

        if(feof(fpl)){
        printf("\nNao ha livro com o este ISBN no acervo da biblioteca!\n\n");
        return 0;
        }
        if(strcasecmp (auxisbn.isbn,dadosLivro.isbn) == 0){
        printf("Titulo: %s\n", dadosLivro.titulo);
        printf("Disponiveis: %d\n", dadosLivro.disponivel);
        guard_valor = auxisbn;
        break;
        }
    }
       printf("\Nome: ");
       scanf("%s", &dadosEmprestimo.nome);
       auxEmp = dadosEmprestimo.nome;

    // verifica se o nome é válido e exibe as informações
    while(1){
        fread(&dadosUsuario, sizeof(usuario),1,fpa);
        if(feof(fpa)){
        printf("\nO nome %c nao esta cadastrado!\n\n", dadosEmprestimo.nome);
        return;
        }
        if(dadosEmprestimo.nome == dadosUsuario.nome){
            printf("Nome: %s\n", dadosUsuario.nome);
            printf("Livros emprestados: %d\n", dadosUsuario.emprestimo);
            break;
        }
    }
    dataAux.dte = dataAtual(controle);
    dataAux.dte.mes += 1;

    if(dadosUsuario.emprestimo < 3){ // verifica se o usuario possui mais de três emprestimos

    fseek(fpr,0,SEEK_CUR); // verifica se o usuario possui pendências de entrega

    while(1){
            fread(&dadosEmprestimo,sizeof(emprestimo),1,fpr);
            if(feof(fpr)){
                break;
            }
            if(dadosEmprestimo.nome == auxNome){
                if(dadosEmprestimo.prevista.ano <= dataAux.dte.ano){
                    if(dadosEmprestimo.prevista.mes <= dataAux.dte.mes){
                        if(dadosEmprestimo.prevista.dia <= dataAux.dte.dia && dadosEmprestimo.devolucao.dia == 0){
                            printf("\n\t\t\tEntrega pendente!\n\n");
                            return 0;
                        }
                    }
                }
                if(dadosEmprestimo.prevista.mes < dataAux.dte.mes && dadosEmprestimo.devolucao.mes == 00){
                        printf("\n\t\t\tEntrega pendente!\n\n");
                        return 0;
                }
                if(dadosEmprestimo.prevista.ano < dataAux.dte.ano && dadosEmprestimo.devolucao.ano == 0000){
                        printf("\n\t\t\tEntrega pendente!\n\n");
                        return 0;
                }
            }
    }
    // tratamento das datas
    dataAux.dtp = dataAtual(controle);
    dataAux.dtp.dia += 10;
    dataAux.dtp.mes += 1;

    while( cont <= 12 ){
            if(dataAux.dtp.mes <= 7){
                if(cont == 2 && dataAux.dtp.dia > 28 && dataAux.dtp.mes == 2){
                dataAux.dtp.dia -= 28; dataAux.dtp.mes += 1; break;
            } else{
                if(cont % 2 == 1 && dataAux.dtp.dia > 31 && dataAux.dtp.mes == cont){
                dataAux.dtp.dia -= 31; dataAux.dtp.mes += 1; break;
              } else{
                  if(cont % 2 == 0 && dataAux.dtp.dia > 30 && dataAux.dtp.mes == cont){
                  dataAux.dtp.dia -= 30; dataAux.dtp.mes += 1; break;
                  }
                }
              }
            } else{
                if(dataAux.dtp.dia > 31 && dataAux.dte.mes == 12){
                dataAux.dtp.dia -= 31; dataAux.dtp.ano += 1;
                dataAux.dtp.mes = 1; break;
              } else{
                if(cont % 2 == 0 && dataAux.dtp.dia > 31 && dataAux.dtp.mes == cont){
                dataAux.dtp.dia -= 31; dataAux.dtp.mes += 1; break;
                } else{
                    if(cont % 2 == 1 && dataAux.dtp.dia > 30 && dataAux.dtp.mes == cont){
                    dataAux.dtp.dia -= 30; dataAux.dtp.mes += 1; break;
                    }
                  }
                }
              }
     cont++;
   }
    if(dadosLivro.disponivel >= 1){ // verifica se ha livros disponíveis

    // efetua a escrita no arquivo emprestimo.dat
    while(1){
            dadosEmprestimo = auxisbn;
            printf("\nIsbn: %s\n", dadosEmprestimo.isbn);

            dadosEmprestimo.devolucao.dia = dadosEmprestimo.devolucao.mes = dadosEmprestimo.devolucao.ano = 0;
            dadosEmprestimo.emprestimo.dia = dataAux.dte.dia; dadosEmprestimo.emprestimo.mes = dataAux.dte.mes;
            dadosEmprestimo.emprestimo.ano = dataAux.dte.ano;
            dadosEmprestimo.prevista.dia = dataAux.dtp.dia; dadosEmprestimo.prevista.mes = dataAux.dtp.mes;
            dadosEmprestimo.prevista.ano = dataAux.dtp.ano;

            DadosEmprestimo.nome = auxmatricula;

            printf("Matricula...................: %08d\n", DadosEmprestimo.matricula);
            printf("Data do emprestimo..........: ");
            printf("%02d %02d %d\n", DadosEmprestimo.emprestimo.dia, DadosEmprestimo.emprestimo.mes, DadosEmprestimo.emprestimo.ano);
            printf("Data prevista para devolucao: ");
            printf("%02d %02d %d\n", DadosEmprestimo.prevista.dia, DadosEmprestimo.prevista.mes, DadosEmprestimo.prevista.ano);
            printf("Data da efetiva devolucao...: ");
            printf("%02d %02d %04d\n\n", DadosEmprestimo.devolucao.dia, DadosEmprestimo.devolucao.mes, DadosEmprestimo.devolucao.ano);
            fwrite(&DadosEmprestimo,sizeof(emprestimo),1,fp);
            break;
    }
        rewind(fpa);
        while(1){
        fread(&DadosAluno,sizeof(aluno),1,fpa);
        if(feof(fpa)){
        printf("\nError");
        break;
        }
        if(DadosAluno.matricula == DadosEmprestimo.matricula){
        DadosAluno.emprestimos += 1;
        fseek(fpa, -sizeof(aluno),SEEK_CUR);
        fwrite(&DadosAluno,sizeof(aluno),1,fpa);
        printf("\t\t\tTotal Emprestimos Aluno.: %d\n", DadosAluno.emprestimos);
        break;
        }
     }
        rewind(fpl);
        while(1){
        fread(&DadosLivro,sizeof(livro),1,fpl);
        if(feof(fpl)){
        printf("\nError");
        break;
        }
        if(strcasecmp (DadosEmprestimo.isbn,DadosLivro.isbn) == 0){
        DadosLivro.disponiveis -= 1;
        fseek(fpl, -sizeof(livro),SEEK_CUR);
        fwrite(&DadosLivro,sizeof(livro),1,fpl);
        printf("\t\t\tTotal Livros Disponiveis: %d\n", DadosLivro.disponiveis);
        break;
        }
     }
 }
 else{
      printf("\n\n\t\t\tNao ha livros disponiveis\n");

      /*Calcula e devolve a data da entrega mais próxima*/

        rewind(fpr);
        while(1){
        fread(&DadosEmprestimo,sizeof(emprestimo),1,fpr);
        if(feof(fpr)){
        fclose(fpr);
        break;
        }
        if(strcasecmp (guard_valor.isbn,DadosEmprestimo.isbn) == 0){
        if(contseq == 0){
        Auxano = DadosEmprestimo.prevista.ano;
        Auxmes = DadosEmprestimo.prevista.mes;
        Auxdia = DadosEmprestimo.prevista.dia;
        }
        if( DadosEmprestimo.devolucao.dia == 00 ){
        if(Auxano >= DadosEmprestimo.prevista.ano){
                  if(Auxmes >= DadosEmprestimo.prevista.mes){
                            if(Auxdia >= DadosEmprestimo.prevista.dia){
                            Auxano = DadosEmprestimo.prevista.ano;
                            Auxmes = DadosEmprestimo.prevista.mes;
                            Auxdia <= DadosEmprestimo.prevista.dia;
                            }
                         }
                      }
                   }
        }
        cont++;
     }
     printf("\n\n\t\tData da entrega mais proxima: %02d %02d %d\n", Auxdia, Auxmes, Auxano);
     }
 }
      else{
      printf("\n\t\t\tCota de livros atingida\n\n");
      return;
      }

    fclose(fp);
    fclose(fpl);
    fclose(fpa);
}



