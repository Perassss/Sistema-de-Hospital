#ifndef HOSPITAL_H
#define HOSPITAL_H

#define MAX_PACIENTES 100
#define MAX_PROCEDIMENTOS 50
#define MAX_RECURSOS 10
#define MAX_NOME 100
#define MAX_TEXTO 200

// Estrutura para representar um paciente
typedef struct {
    char nome[MAX_NOME];          // Nome do paciente
    int idade;                   // Idade do paciente
    char sexo;                   // 'M' para masculino, 'F' para feminino
    int n_sns;                   // Número SNS do paciente
    int nivel_urgencia;          // Nível de urgência (0 a 10)
} Paciente;

// Estrutura para representar os procedimentos hospitalares
typedef struct {
    int n_sns;                          // Número SNS do paciente associado
    int num_procedimentos;              // Quantidade de procedimentos futuros
    char procedimentos_futuros[MAX_TEXTO]; // Detalhes sobre procedimentos
} Procedimento;

// Estrutura para representar recursos hospitalares
typedef struct {
    char servico[MAX_TEXTO];  // Nome do recurso
    char tipo;                // Tipo do recurso (ex: 'M' para Medicamento)
    int quantidade;           // Número de recursos disponíveis
} Recurso;

// Funções para manipulação dos dados dos pacientes
void inserirPaciente(Paciente pacientes[], int *n_pacientes);
void listarPacientes(Paciente pacientes[], int n_pacientes);
Paciente* buscarPaciente(Paciente pacientes[], int n_pacientes, int n_sns);
int lerPacientesDeArquivo(Paciente pacientes[], const char *filename);
int salvarPacientesEmArquivo(Paciente pacientes[], int n_pacientes, const char *filename);

// Funções para manipulação de procedimentos
int lerProcedimentosDeArquivo(Procedimento procedimentos[], const char *filename);
int salvarProcedimentosEmArquivo(Procedimento procedimentos[], int n_procedimentos, const char *filename);

// Funções para manipulação de recursos
int lerRecursosDeArquivo(Recurso recursos[], const char *filename);
int salvarRecursosEmArquivo(Recurso recursos[], int n_recursos, const char *filename);
void inserirProcedimento(Procedimento procedimentos[], int *n_procedimentos);
void inserirRecurso(Recurso recursos[], int *n_recursos);
void listarProcedimentos(Procedimento procedimentos[], int n_procedimentos);
void listarRecursos(Recurso recursos[], int n_recursos);
void exibirMenu();

// Função para limpar o buffer de entrada
void limparBuffer(); // Add this line

#endif