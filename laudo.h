#ifndef LAUDO_H
#define LAUDO_H


typedef struct laudo Laudo;

typedef struct laudo_no LaudoNo;

Laudo *criar_laudo();
int esta_vazia_laudo(Laudo *laudo);
void enfilerar_laudo(Laudo *laudo, int id_paciente, int tempo_gerado);
int desifilerar_laudo(Laudo *laudo);
void liberar_laudo(Laudo *laudo);
void listar_laudo(Laudo *laudo);
void analise_exame(LaudoNo *laudo);


#endif