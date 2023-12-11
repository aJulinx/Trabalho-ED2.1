#include "paciente.h"
#include "consulta.h"
#include "fila.h"
#include "laudo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    /*//Declaração de variáveis
    int contador=0;
    int contador_pausa=0;

    PacienteLista *lista_pacientes=cria_lista();
    Fila *fila_exames = cria_fila();
    Fila *fila_laudos = criar_fila();
    Consulta **maquinas = criar_consulta(5);
    Consulta **radiologistas = criar_consulta(3);



    while(contador<=43200){
        if(gen_randint(0,100)<=20){
            PacienteNo *pacientes = gerar_paciente();
            inserir_lista(lista_pacientes, pacientes);
        }
    }
*/

// Testando TAD Paciente
    PacienteLista *lista_pacientes = cria_lista();
    for (int i = 0; i < 5; i++) {
        PacienteNo *novo_paciente = gerar_paciente();
        inserir_lista(lista_pacientes, novo_paciente);
    }
    printf("Lista de Pacientes:\n");
    listar_pacientes(lista_pacientes);
    liberar_paciente(lista_pacientes);

    // Testando TAD Consulta
    int num_salas = 3;
    Consulta **salas = criar_consulta(num_salas);
    for (int i = 0; i < num_salas; i++) {
        int id_tipo = i % 2; // Alternando entre tipos 0 e 1
        consultar(salas[i], i + 1, id_tipo);
    }
    printf("\nStatus das Salas de Consulta:\n");
    for (int i = 0; i < num_salas; i++) {
        printf("Sala %d - Paciente ID: %d, Duração: %d\n", i + 1, pegar_id_paciente(salas[i]), salas[i]->duracao);
    }
    liberar_salas(salas, num_salas);

    // Testando TAD Fila
    Fila *fila_espera = criar_fila();
    for (int i = 6; i <= 10; i++) {
        enfilerar(fila_espera, i);
    }
    printf("\nFila de Espera:\n");
    listar_fila(fila_espera);
    while (!fila_esta_vazia(fila_espera)) {
        int paciente_atendido = desifilerar(fila_espera);
        printf("Paciente %d atendido.\n", paciente_atendido);
    }
    liberar_fila(fila_espera);

    // Testando TAD Laudo
    Laudo *laudo = criar_laudo();
    for (int i = 1; i <= 3; i++) {
        enfilerar_laudo(laudo, i, i * 10);
    }
    printf("\nLaudos na Fila:\n");
    listar_laudo(laudo);
    while (!esta_vazia_laudo(laudo)) {
        int id_paciente = desifilerar_laudo(laudo);
        printf("Laudo para Paciente %d gerado.\n", id_paciente);
    }
    liberar_laudo(laudo);


    return 0;

}
    

