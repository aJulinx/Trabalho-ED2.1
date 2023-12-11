#include "laudo.h"
#include "consulta.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct laudo{

    LaudoNo *frente;
    LaudoNo *tras;

};

struct laudo_no{
    int id_paciente;
    int tempo_gerado;
    char condicao[50];
    LaudoNo *prox;
};

Laudo *criar_laudo() {
    Laudo *laudo = (Laudo *)malloc(sizeof(Laudo));
    laudo->frente = laudo->tras = NULL;
    return laudo;
}

int esta_vazia_laudo(Laudo *laudo) {
    return laudo->frente == NULL;
}

void enfilerar_laudo(Laudo *laudo, int id_paciente, int tempo_gerado) {
    LaudoNo *no = (LaudoNo *)malloc(sizeof(LaudoNo));

    no->id_paciente = id_paciente;
    no->tempo_gerado = tempo_gerado;
    analise_exame(no);
    no->prox = NULL;

    if (esta_vazia_laudo(laudo)) {
        laudo->frente = no;
    } else {
        laudo->tras->prox = no;
    }

    laudo->tras = no;
}

int desifilerar_laudo(Laudo *laudo) {
    assert(!esta_vazia_laudo(laudo));

    int id_paciente = laudo->frente->id_paciente;
    LaudoNo *fi = laudo->frente;

    if (laudo->frente != laudo->tras) {
        laudo->frente = laudo->frente->prox;
    } else {
        laudo->frente = laudo->tras = NULL;
    }

    free(fi);

    return id_paciente;
}

void liberar_laudo(Laudo *laudo) {
    LaudoNo *no = laudo->frente;
    while (no != NULL) {
        LaudoNo *no2 = no->prox;
        free(no);
        no = no2;
    }
    free(laudo);
}

void listar_laudo(Laudo *laudo) {
    for (LaudoNo *no = laudo->frente; no != NULL; no = no->prox) {
        printf("ID: %d, Condição: %s\n", no->id_paciente, no->condicao);
    }
    printf("\n");
}

void analise_exame(LaudoNo *laudo) {
    int chance = gen_randint(0, 100);

    if (chance <= 30) {
        strcpy(laudo->condicao, "saude normal");
    } else if (chance > 30 && chance <= 50) {
        strcpy(laudo->condicao, "bronquite");
    } else if (chance > 50 && chance <= 70) {
        strcpy(laudo->condicao, "pneumonia");
    } else if (chance > 70 && chance <= 85) {
        strcpy(laudo->condicao, "fratura de femur");
    } else if (chance > 85) {
        strcpy(laudo->condicao, "apendicite");
    }
}
