#include "paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

const char *gerar_nome() {
    const char *nomes[] = {"Julin", "Ismael", "Israel", "Eric", "Marcos", "Rose", "Ana", "Yasmin"};
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    int indice = rand() % num_nomes;

    return nomes[indice];
}

const char *gerar_cpf() {
    int bloco1 = rand() % 1000;
    int bloco2 = rand() % 1000;
    int bloco3 = rand() % 1000;


    static char cpf[15];
    snprintf(cpf, sizeof(cpf), "%03d.%03d.%03d-01", bloco1, bloco2, bloco3);


    return cpf;
}


int gerar_idade() {
    return rand() % 63 + 18;
}

PacienteNo *gerar_paciente() {
    PacienteNo *novoPaciente = (PacienteNo *)malloc(sizeof(PacienteNo));
    
    static int id = 1;
    novoPaciente->id = id++;
    novoPaciente->idade = gerar_idade();
    strncpy(novoPaciente->nome, gerar_nome(), sizeof(novoPaciente->nome) - 1);
    novoPaciente->nome[sizeof(novoPaciente->nome) - 1] = '\0';
    strncpy(novoPaciente->cpf, gerar_cpf(), sizeof(novoPaciente->cpf) - 1);
    novoPaciente->cpf[sizeof(novoPaciente->cpf) - 1] = '\0';

    novoPaciente->prox = NULL;

    return novoPaciente;
}

PacienteLista *cria_lista(){

    PacienteLista *paciente = (PacienteLista *)malloc(sizeof(PacienteLista));
    paciente->prim = NULL;
    return paciente;

}

int lista_vazia (PacienteLista *lista){
    return lista->prim==NULL;
}

void inserir_lista(PacienteLista *lista, PacienteNo *paciente) {
    PacienteNo *novo_paciente = (PacienteNo *)malloc(sizeof(PacienteNo));

    if (novo_paciente == NULL) {
        printf("Algo deu errado, alocação de memória não realizada");
        exit(EXIT_FAILURE);
    }

    novo_paciente->id = paciente->id;
    novo_paciente->idade = paciente->idade;
    strncpy(novo_paciente->nome, paciente->nome, sizeof(novo_paciente->nome) - 1);
    strncpy(novo_paciente->cpf, paciente->cpf, sizeof(novo_paciente->cpf) - 1);

    novo_paciente->prox = lista->prim;
    lista->prim = novo_paciente;
}


int tamanho_lista (PacienteLista *lista){
    int contador=0;
    PacienteNo *atual = lista->prim;

    while (atual !=NULL){
        contador++;
        atual=atual->prox;
    }

    return contador;
}

void liberar_paciente(PacienteLista *lista){
    PacienteNo *atual = lista->prim;

    while(atual!=NULL){
        PacienteNo *temp = atual->prox;
        free(atual);
        atual=temp;
    }
    free(lista);
}

void listar_pacientes(PacienteLista *lista){
    for(PacienteNo *atual = lista->prim; atual!=NULL;atual=atual->prox){
        printf("Nome: %s \n CPF: %s \n Idade: %d \n ID: %d \n\n", atual->nome, atual->cpf, atual->idade, atual->id);
    }
}