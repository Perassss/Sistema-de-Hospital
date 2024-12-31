#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

void inserirProcedimento(Procedimento procedimentos[], int *n_procedimentos);
void inserirRecurso(Recurso recursos[], int *n_recursos);
void listarProcedimentos(Procedimento procedimentos[], int n_procedimentos);
void listarRecursos(Recurso recursos[], int n_recursos);
void exibirMenu();
void editarRegistro(Paciente pacientes[], int n_pacientes);
void eliminarRegistro(Paciente pacientes[], int *n_pacientes);
void consultarRegistrosPorFiltros(Paciente pacientes[], int n_pacientes, Procedimento procedimentos[], int n_procedimentos, Recurso recursos[], int n_recursos);

void exibirMenu() {
    printf("\n###########################\n");
    printf("#   Menu de Funcionamento #\n");
    printf("###########################\n");
    printf("1. Inserir novo paciente\n");
    printf("2. Inserir novos procedimentos\n");
    printf("3. Inserir novos recursos hospitalares\n");
    printf("4. Listar todos os registros em memória\n");
    printf("5. Consultar registro por SNS\n");
    printf("6. Consultar registros por filtros\n");
    printf("7. Editar registro\n");
    printf("8. Eliminar registro\n");
    printf("9. Guardar os dados\n");
    printf("0. Sair\n");
    printf("###########################\n");
    printf("Escolha uma opção: ");
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Paciente pacientes[MAX_PACIENTES];
    Procedimento procedimentos[MAX_PROCEDIMENTOS];
    Recurso recursos[MAX_RECURSOS];

    int n_pacientes = 0, n_procedimentos = 0, n_recursos = 0;
    int escolha, n_sns;

    // Inicializar carregamento de arquivos
    n_pacientes = lerPacientesDeArquivo(pacientes, "pacientes.txt");
    n_procedimentos = lerProcedimentosDeArquivo(procedimentos, "procedimentos.txt");
    n_recursos = lerRecursosDeArquivo(recursos, "recursos.txt");

    // Verificar se os dados foram carregados corretamente
    if (n_pacientes > 0 || n_procedimentos > 0 || n_recursos > 0) {
        printf("\nDados carregados dos ficheiros com sucesso.\n");
    } else {
        printf("\nNenhum dado carregado. Inicializando registros vazios.\n");
    }

    do {
        exibirMenu();
        if (scanf("%d", &escolha) != 1) {
            printf("\nErro de entrada. Reinicie o programa e tente novamente.\n");
            break;
        }

        switch (escolha) {
            case 1:
                inserirPaciente(pacientes, &n_pacientes);
                break;
            case 2:
                inserirProcedimento(procedimentos, &n_procedimentos);
                break;
            case 3:
                inserirRecurso(recursos, &n_recursos);
                break;
            case 4:
                listarPacientes(pacientes, n_pacientes);
                listarProcedimentos(procedimentos, n_procedimentos);
                listarRecursos(recursos, n_recursos);
                break;
            case 5:
                printf("Digite o número SNS do paciente: ");
                if (scanf("%d", &n_sns) == 1) {
                    Paciente *pac = buscarPaciente(pacientes, n_pacientes, n_sns);
                    if (pac) {
                        printf("\nPaciente encontrado: %s | Idade: %d | Sexo: %c | Urgência: %d\n",
                               pac->nome, pac->idade, pac->sexo, pac->nivel_urgencia);
                    } else {
                        printf("\nPaciente com SNS %d não encontrado.\n", n_sns);
                    }
                }
                break;
            case 6:
                consultarRegistrosPorFiltros(pacientes, n_pacientes, procedimentos, n_procedimentos, recursos, n_recursos);
                break;
            case 7:
                editarRegistro(pacientes, n_pacientes);
                break;
            case 8:
                eliminarRegistro(pacientes, &n_pacientes);
                break;
            case 9:
                salvarPacientesEmArquivo(pacientes, n_pacientes, "pacientes.txt");
                salvarProcedimentosEmArquivo(procedimentos, n_procedimentos, "procedimentos.txt");
                salvarRecursosEmArquivo(recursos, n_recursos, "recursos.txt");
                printf("\nDados salvos com sucesso nos ficheiros.\n");
                break;
            case 0:
                printf("\nSair...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 0);

    return 0;
}

void editarRegistro(Paciente pacientes[], int n_pacientes) {
    int sns, i;
    printf("Digite o SNS do paciente a ser editado: ");
    if (scanf("%d", &sns) == 1) {
        for (i = 0; i < n_pacientes; i++) {
            if (pacientes[i].n_sns == sns) {
                printf("\nPaciente encontrado: %s\n", pacientes[i].nome);
                printf("Novo nome (atual: %s): ", pacientes[i].nome);
                limparBuffer();
                fgets(pacientes[i].nome, MAX_NOME, stdin);
                pacientes[i].nome[strcspn(pacientes[i].nome, "\n")] = '\0';
                printf("Nova idade (atual: %d): ", pacientes[i].idade);
                scanf("%d", &pacientes[i].idade);
                printf("Novo nível de urgência (atual: %d): ", pacientes[i].nivel_urgencia);
                scanf("%d", &pacientes[i].nivel_urgencia);
                printf("Novo sexo (M/F) (atual: %c): ", pacientes[i].sexo);
                scanf(" %c", &pacientes[i].sexo);
                printf("\nRegistro do paciente atualizado com sucesso!\n");
                return;
            }
        }
        printf("\nPaciente com SNS %d não encontrado.\n", sns);
    } else {
        printf("\nErro de entrada.\n");
    }
}

void eliminarRegistro(Paciente pacientes[], int *n_pacientes) {
    int sns, i, j;
    printf("Digite o SNS do paciente a ser eliminado: ");
    if (scanf("%d", &sns) == 1) {
        for (i = 0; i < *n_pacientes; i++) {
            if (pacientes[i].n_sns == sns) {
                for (j = i; j < *n_pacientes - 1; j++) {
                    pacientes[j] = pacientes[j + 1];
                }
                (*n_pacientes)--;
                printf("\nPaciente com SNS %d eliminado com sucesso.\n", sns);
                return;
            }
        }
        printf("\nPaciente com SNS %d não encontrado.\n", sns);
    } else {
        printf("\nErro de entrada.\n");
    }
}

void consultarRegistrosPorFiltros(Paciente pacientes[], int n_pacientes, Procedimento procedimentos[], int n_procedimentos, Recurso recursos[], int n_recursos) {
    int escolhaFiltro, idadeFiltro, urgenciaFiltro;
    char sexoFiltro;
    int encontrado = 0;

    printf("\nEscolha um critério de filtro para pacientes:\n");
    printf("1. Filtrar por idade\n");
    printf("2. Filtrar por sexo\n");
    printf("3. Filtrar por nível de urgência\n");
    printf("4. Filtrar por número de procedimentos (para um paciente)\n");
    printf("0. Voltar\n");
    printf("Escolha uma opção: ");
    
    if (scanf("%d", &escolhaFiltro) != 1) {
        printf("\nErro na escolha do filtro.\n");
        return;
    }

    switch (escolhaFiltro) {
        case 1:
            printf("Digite a idade para filtro: ");
            if (scanf("%d", &idadeFiltro) != 1) {
                printf("\nErro ao ler a idade.\n");
                return;
            }

            for (int i = 0; i < n_pacientes; i++) {
                if (pacientes[i].idade == idadeFiltro) {
                    printf("Paciente encontrado: %s | Idade: %d | Sexo: %c | Urgência: %d\n", 
                        pacientes[i].nome, pacientes[i].idade, pacientes[i].sexo, pacientes[i].nivel_urgencia);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum paciente encontrado com essa idade.\n");
            }
            break;

        case 2:
            printf("Digite o sexo para filtro (M/F): ");
            if (scanf(" %c", &sexoFiltro) != 1) {
                printf("\nErro ao ler o sexo.\n");
                return;
            }

            for (int i = 0; i < n_pacientes; i++) {
                if (pacientes[i].sexo == sexoFiltro) {
                    printf("Paciente encontrado: %s | Idade: %d | Sexo: %c | Urgência: %d\n", 
                        pacientes[i].nome, pacientes[i].idade, pacientes[i].sexo, pacientes[i].nivel_urgencia);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum paciente encontrado com esse sexo.\n");
            }
            break;

        case 3:
            printf("Digite o nível de urgência para filtro (1-10): ");
            if (scanf("%d", &urgenciaFiltro) != 1 || urgenciaFiltro < 1 || urgenciaFiltro > 10) {
                printf("\nErro ao ler o nível de urgência.\n");
                return;
            }

            for (int i = 0; i < n_pacientes; i++) {
                if (pacientes[i].nivel_urgencia == urgenciaFiltro) {
                    printf("Paciente encontrado: %s | Idade: %d | Sexo: %c | Urgência: %d\n", 
                        pacientes[i].nome, pacientes[i].idade, pacientes[i].sexo, pacientes[i].nivel_urgencia);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum paciente encontrado com esse nível de urgência.\n");
            }
            break;

        case 4:
            printf("Digite o número de procedimentos realizados para o filtro: ");
            int numProcedimentos;
            if (scanf("%d", &numProcedimentos) != 1) {
                printf("\nErro ao ler o número de procedimentos.\n");
                return;
            }

            for (int i = 0; i < n_pacientes; i++) {
                int countProcedimentos = 0;
                for (int j = 0; j < n_procedimentos; j++) {
                    if (procedimentos[j].n_sns == pacientes[i].n_sns) {
                        countProcedimentos++;
                    }
                }
                if (countProcedimentos == numProcedimentos) {
                    printf("Paciente encontrado: %s | Procedimentos realizados: %d\n", pacientes[i].nome, countProcedimentos);
                    encontrado = 1;
                }
            }
            if (!encontrado) {
                printf("Nenhum paciente encontrado com esse número de procedimentos.\n");
            }
            break;


        case 0:
            printf("\nVoltando ao menu principal...\n");
            break;

        default:
            printf("\nOpção inválida.\n");
            break;
    }
}