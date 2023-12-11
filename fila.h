#ifndef FILA_H
#define FILA_H


typedef struct fila Fila;
typedef struct fila_no FilaNo;


Fila *criar_fila();
int fila_esta_vazia(Fila *fila);
void enfilerar(Fila *fila, int id_paciente);
int desifilerar(Fila *fila);
void liberar_fila(Fila *fila);
void listar_fila(Fila *fila);

#endif