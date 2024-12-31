#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inserirPaciente(Paciente pacientes[], int *n_pacientes) {
    if (*n_pacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido!\n");
        return;
    }

    Paciente novoPaciente;

    printf("Digite o nome do paciente: ");
    limparBuffer();
    fgets(novoPaciente.nome, MAX_NOME, stdin);
    novoPaciente.nome[strcspn(novoPaciente.nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &novoPaciente.idade);

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &novoPaciente.sexo);

    printf("Digite o número SNS: ");
    scanf("%d", &novoPaciente.n_sns);

    printf("Digite o nível de urgência (0-10): ");
    scanf("%d", &novoPaciente.nivel_urgencia);

    if (novoPaciente.idade <= 0 || novoPaciente.nivel_urgencia < 0) {
        printf("Dados inválidos para o paciente!\n");
        return;
    }

    pacientes[*n_pacientes] = novoPaciente;
    (*n_pacientes)++;
}

void listarPacientes(Paciente pacientes[], int n_pacientes) {
    if (n_pacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    printf("\nLista de Pacientes:\n");
    for (int i = 0; i < n_pacientes; i++) {
        if (pacientes[i].nivel_urgencia >= 0) {
            printf("Paciente %d: Nome: %s | Idade: %d | Sexo: %c | SNS: %d | Urgência: %d\n", 
                i + 1, pacientes[i].nome, pacientes[i].idade, pacientes[i].sexo, pacientes[i].n_sns, pacientes[i].nivel_urgencia);
        }
    }
}

Paciente* buscarPaciente(Paciente pacientes[], int n_pacientes, int n_sns) {
    for (int i = 0; i < n_pacientes; i++) {
        if (pacientes[i].n_sns == n_sns) {
            return &pacientes[i];
        }
    }
    return NULL;
}

int salvarPacientesEmArquivo(Paciente pacientes[], int n_pacientes, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar pacientes.\n");
        return -1;
    }

    for (int i = 0; i < n_pacientes; i++) {
        if (pacientes[i].nivel_urgencia >= 0) {
            fprintf(file, "%s,%d,%c,%d,%d\n", pacientes[i].nome, 
                    pacientes[i].idade, pacientes[i].sexo, 
                    pacientes[i].n_sns, pacientes[i].nivel_urgencia);
        }
    }

    fclose(file);
    return 0;
}

void inserirProcedimento(Procedimento procedimentos[], int *n_procedimentos) {
    if (*n_procedimentos >= MAX_PROCEDIMENTOS) {
        printf("Limite de procedimentos atingido!\n");
        return;
    }

    Procedimento novoProcedimento;

    printf("Digite o número SNS do paciente: ");
    scanf("%d", &novoProcedimento.n_sns);

    printf("Digite o número de procedimentos futuros: ");
    scanf("%d", &novoProcedimento.num_procedimentos);

    limparBuffer();  // Consumir o '\n' deixado pelo scanf
    printf("Digite a descrição dos procedimentos futuros: ");
    fgets(novoProcedimento.procedimentos_futuros, MAX_TEXTO, stdin);
    novoProcedimento.procedimentos_futuros[strcspn(novoProcedimento.procedimentos_futuros, "\n")] = '\0';

    procedimentos[*n_procedimentos] = novoProcedimento;
    (*n_procedimentos)++;
    printf("Procedimento adicionado com sucesso!\n");
}

void listarProcedimentos(Procedimento procedimentos[], int n_procedimentos) {
    // Check if the number of procedures is valid
    if (n_procedimentos < 0) {
        printf("Número de procedimentos inválido.\n");
        return;
    }

    if (n_procedimentos == 0) {
        printf("\nNenhum procedimento cadastrado.\n");
    } else {
        printf("\nLista de Procedimentos:\n");
        for (int i = 0; i < n_procedimentos; i++) {
            printf("Procedimento %d: SNS: %d | Número de Procedimentos: %d | Descrição: %s\n", 
                   i + 1, procedimentos[i].n_sns, procedimentos[i].num_procedimentos, procedimentos[i].procedimentos_futuros);
        }
    }
}

void inserirRecurso(Recurso recursos[], int *n_recursos) {
    if (*n_recursos >= MAX_RECURSOS) {
        printf("Limite de recursos atingido!\n");
        return;
    }

    Recurso novoRecurso;    

    printf("Digite o nome do serviço: ");
    limparBuffer();
    fgets(novoRecurso.servico, MAX_TEXTO, stdin);
    novoRecurso.servico[strcspn(novoRecurso.servico, "\n")] = '\0';

    printf("Digite a quantidade do recurso: ");
    scanf("%d", &novoRecurso.quantidade);

    recursos[*n_recursos] = novoRecurso;
    (*n_recursos)++;
    printf("Recurso inserido com sucesso!\n");
}

void listarRecursos(Recurso recursos[], int n_recursos) {
    // Check if the number of resources is valid
    if (n_recursos < 0) {
        printf("Número de recursos inválido.\n");
        return;
    }

    if (n_recursos == 0) {
        printf("\nNenhum recurso cadastrado.\n");
    } else {
        printf("\nLista de Recursos:\n");
        for (int i = 0; i < n_recursos; i++) {
            printf("Recurso %d: Serviço: %s | Quantidade: %d\n", 
                   i + 1, recursos[i].servico, recursos[i].quantidade);
        }
    }
}

int lerPacientesDeArquivo(Paciente pacientes[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de pacientes.\n");
        return -1;
    }

    int n_pacientes = 0;
    while (fscanf(file, "%99[^,],%d,%c,%d,%d\n", 
            pacientes[n_pacientes].nome, 
            &pacientes[n_pacientes].idade, 
            &pacientes[n_pacientes].sexo, 
            &pacientes[n_pacientes].n_sns, 
            &pacientes[n_pacientes].nivel_urgencia) == 5) {
        
        if (pacientes[n_pacientes].nivel_urgencia < 0) {
            continue; // Ignorar pacientes com nível de urgência inválido
        }

        n_pacientes++;
        if (n_pacientes >= MAX_PACIENTES)
            break;
    }

    fclose(file);
    return n_pacientes;
}

int salvarProcedimentosEmArquivo(Procedimento procedimentos[], int n_procedimentos, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar procedimentos.\n");
        return -1;
    }

    for (int i = 0; i < n_procedimentos; i++) {
        fprintf(file, "%d,%d,%s\n", procedimentos[i].n_sns, 
                procedimentos[i].num_procedimentos, procedimentos[i].procedimentos_futuros);
    }

    fclose(file);
    return 0;
}

int lerProcedimentosDeArquivo(Procedimento procedimentos[], const char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de procedimentos.\n");
        return 0;
 }

    int n = 0;
    while (fscanf(file, "%d,%d,%199[^\n]", 
            &procedimentos[n].n_sns, 
            &procedimentos[n].num_procedimentos, 
            procedimentos[n].procedimentos_futuros) == 3) {
        n++;
    }

    fclose(file);
    return n;
}

int lerRecursosDeArquivo(Recurso recursos[], const char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de recursos.\n");
        return 0;
    }

    int n = 0;
    while (fscanf(file, "%c,%99[^,],%d\n", 
            &recursos[n].tipo, 
            recursos[n].servico, 
            &recursos[n].quantidade) == 3) {
        n++;
    }

    fclose(file);
    return n;
}

int salvarRecursosEmArquivo(Recurso recursos[], int n_recursos, const char* nome_arquivo) {
    if (n_recursos <= 0) {
        printf("Nenhum recurso para salvar.\n");
        return 0; // Return early if there are no resources
    }

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return 0;
    }

    for (int i = 0; i < n_recursos; i++) {
        fprintf(arquivo, "%c,%s,%d\n", recursos[i].tipo, recursos[i].servico, recursos[i].quantidade);
    }

    fclose(arquivo);
    printf("Recursos salvos com sucesso no arquivo %s.\n", nome_arquivo);
    return 1; // Retorna 1 em caso de sucesso
}