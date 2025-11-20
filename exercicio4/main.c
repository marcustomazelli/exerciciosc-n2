#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO "FUNCIONARIOS.BIN"

typedef struct {
    int id;
    char nome[100];
    char setor[50];
    double salario;
} Funcionario;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void lerLinha(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin)) {
        size_t len = strcspn(destino, "\n");
        destino[len] = '\0';
    }
}

int igualIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

void exibirFuncionario(const Funcionario *f) {
    printf("ID: %d | Nome: %s | Setor: %s | Salario: R$ %.2f\n",
           f->id, f->nome, f->setor, f->salario);
}

int idExiste(int idBuscado) {
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (!arquivo) {
        return 0;
    }

    Funcionario f;
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.id == idBuscado) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

void cadastrarFuncionario() {
    Funcionario f;

    printf("ID do funcionario: ");
    scanf("%d", &f.id);
    limparBuffer();

    if (idExiste(f.id)) {
        printf("ID ja cadastrado. Escolha outro.\n");
        return;
    }

    printf("Nome do funcionario: ");
    lerLinha(f.nome, sizeof(f.nome));

    printf("Setor do funcionario: ");
    lerLinha(f.setor, sizeof(f.setor));

    printf("Salario do funcionario: ");
    scanf("%lf", &f.salario);
    limparBuffer();

    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (!arquivo) {
        perror("Nao foi possivel abrir o arquivo para gravar");
        return;
    }

    fwrite(&f, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("Funcionario cadastrado com sucesso.\n");
}

void consultarTodos() {
    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (!arquivo) {
        printf("Nenhum funcionario cadastrado ate o momento.\n");
        return;
    }

    Funcionario f;
    printf("Lista de funcionarios:\n");
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        exibirFuncionario(&f);
    }

    fclose(arquivo);
}

void consultarPorId() {
    int id;
    printf("Informe o ID para consulta: ");
    scanf("%d", &id);
    limparBuffer();

    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (!arquivo) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    Funcionario f;
    int encontrado = 0;
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (f.id == id) {
            exibirFuncionario(&f);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionario com ID %d nao encontrado.\n", id);
    }

    fclose(arquivo);
}

void consultarPorSetor() {
    char setorBusca[50];
    printf("Informe o setor para consulta: ");
    lerLinha(setorBusca, sizeof(setorBusca));

    FILE *arquivo = fopen(ARQUIVO, "rb");
    if (!arquivo) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    Funcionario f;
    int encontrados = 0;
    while (fread(&f, sizeof(Funcionario), 1, arquivo) == 1) {
        if (igualIgnoreCase(f.setor, setorBusca)) {
            exibirFuncionario(&f);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum funcionario encontrado no setor informado.\n");
    }

    fclose(arquivo);
}

void consultarFuncionario() {
    int opcao = 0;

    do {
        printf("\nMenu de consulta:\n");
        printf("1 - Consultar todos\n");
        printf("2 - Consultar por ID\n");
        printf("3 - Consultar por setor\n");
        printf("4 - Retornar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            consultarTodos();
        } else if (opcao == 2) {
            consultarPorId();
        } else if (opcao == 3) {
            consultarPorSetor();
        } else if (opcao == 4) {
            printf("Retornando ao menu principal...\n");
        } else {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 4);
}

void removerFuncionario() {
    int id;
    printf("Informe o ID para remover: ");
    scanf("%d", &id);
    limparBuffer();

    FILE *entrada = fopen(ARQUIVO, "rb");
    if (!entrada) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    FILE *saida = fopen("FUNCIONARIOS_TMP.BIN", "wb");
    if (!saida) {
        perror("Nao foi possivel criar arquivo temporario");
        fclose(entrada);
        return;
    }

    Funcionario f;
    int removidos = 0;
    while (fread(&f, sizeof(Funcionario), 1, entrada) == 1) {
        if (f.id == id) {
            removidos++;
        } else {
            fwrite(&f, sizeof(Funcionario), 1, saida);
        }
    }

    fclose(entrada);
    fclose(saida);

    if (removidos > 0) {
        remove(ARQUIVO);
        rename("FUNCIONARIOS_TMP.BIN", ARQUIVO);
        printf("Funcionario removido com sucesso.\n");
    } else {
        remove("FUNCIONARIOS_TMP.BIN");
        printf("Nenhum funcionario com o ID informado foi encontrado.\n");
    }
}

int main() {
    printf("Bem-vindo, Marco Tomazelli!\n");

    int opcao = 0;

    do {
        printf("\nMenu principal:\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Consultar funcionario\n");
        printf("3 - Remover funcionario\n");
        printf("4 - Encerrar programa\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        if (opcao == 1) {
            cadastrarFuncionario();
        } else if (opcao == 2) {
            consultarFuncionario();
        } else if (opcao == 3) {
            removerFuncionario();
        } else if (opcao == 4) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
