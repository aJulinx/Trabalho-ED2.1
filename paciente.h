#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente_no {
    int id;
    int idade;
    char nome[99];
    char cpf[15];
    struct paciente_no *prox;  // Corrigido para usar o nome completo da estrutura
} PacienteNo;

typedef struct paciente_lista {
    PacienteNo *prim;
} PacienteLista;

const char *gerar_nome();
const char *gerar_cpf();
int gerar_id();
int gerar_idade();
PacienteNo *gerar_paciente();
PacienteLista *cria_lista();
int lista_vazia(PacienteLista *lista);
void inserir_lista(PacienteLista *lista, PacienteNo *pacitente);
int tamanho_lista(PacienteLista *lista);
void liberar_paciente(PacienteLista *lista);
void listar_pacientes(PacienteLista *lista);

#endif
