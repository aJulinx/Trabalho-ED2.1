#ifndef CONSULTA_H
#define CONSULTA_H

typedef struct consulta {
    int id_paciente;
    int duracao;

}Consulta;

Consulta *criar_consulta(int numero);
void consultar(Consulta *consulta, int id_paciente, int id_tipo);
int consulta_disponivel(Consulta *consulta);
int consulta_ocupada(Consulta **consulta, int numero);
int consulta_tempo_passando(Consulta *consulta);
int pegar_id_paciente(Consulta *consulta);
void liberar_salas(Consulta **consulta, int numero);
int gen_randint(int initial_number, int final_number);


#endif