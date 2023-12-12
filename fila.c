#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct fila{

    FilaNo *frente;
    FilaNo *tras;

};


struct fila_no{

    int id_paciente;
    FilaNo *prox;
};

Fila *criar_fila(){
    Fila *fila=(Fila *)malloc(sizeof(Fila));
    fila->frente=fila->tras=NULL;

    return fila;
}

int fila_esta_vazia(Fila *fila){
    return fila->frente == NULL;
}


void enfilerar(Fila *fila, int id_paciente){
    FilaNo *no = (FilaNo *)malloc(sizeof(FilaNo));

    no->id_paciente = id_paciente;
    no->prox=NULL;

    if(fila_esta_vazia(fila)){
        fila->frente = no; 
    }else{
        fila->tras->prox=no;
    }
    
    fila->tras=no;
}

int desifilerar(Fila *fila){
    assert(!fila_esta_vazia(fila));

    int desi = fila->frente->id_paciente;
    FilaNo *fi = fila->frente;

    if(fila->frente !=fila->tras){
        fila->frente = fila->frente->prox;
    }else{
        fila->frente = fila->tras = NULL;
    }

    free(fi);

    return desi;
}

void liberar_fila(Fila *fila){
    FilaNo *no = fila->frente;
    while(no!=NULL){
        FilaNo *no2 = no->prox;
        free(no);
        no=no2;
    }
    free(fila);
}

void listar_fila(Fila *fila){

    for(FilaNo *no = fila->frente; no!=NULL; no = no->prox){
        printf("%d", no->id_paciente);
    }

}

int tamanho_fila_exame(Fila *fila) {
    int tamanho = 0;
    FilaNo *no = fila->frente;

    while (no != NULL) {
        tamanho++;
        no = no->prox;
    }

    return tamanho;
}