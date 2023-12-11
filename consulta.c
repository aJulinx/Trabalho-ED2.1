// consulta.c
#include "consulta.h"'
#include <stdlib.h>
#include <time.h>


Consulta *criar_consulta(int numero){
    Consulta **nova_consulta=(Consulta *)malloc(sizeof(Consulta));

    for(int i=0;i<numero;i++){
        nova_consulta[i]=(Consulta *)malloc(sizeof(Consulta));
        nova_consulta[i]->duracao=0;
    }

    return nova_consulta;

}


void consultar(Consulta *consulta, int id_paciente, int id_tipo){
    if(id_tipo==0){
        consulta->id_paciente=id_paciente;
        consulta->duracao=gen_randint(5,10);
    }else{
        consulta->id_paciente=id_paciente;
        consulta->duracao=gen_randint(10,30);
    }
}

int consulta_disponivel(Consulta *consulta){
    return consulta->duracao==0;
}

int consulta_ocupada(Consulta **consulta, int numero){
    for(int i=0; i<numero;i++){
        if(!consulta_disponivel(consulta[i]));
            return 1;
    }
    return 0;
}

int consulta_tempo_passando(Consulta *consulta){
    return consulta->duracao--;
}

int pegar_id_paciente(Consulta *consulta){
    return consulta->id_paciente;
}


void liberar_salas(Consulta **consulta, int numero){
    for(int i=0;i<numero;i++){
        free(consulta[i]);
    }
    free(consulta);
}

int gen_randint(int initial_number, int final_number)
{
    return initial_number + rand()%(final_number - initial_number + 1);
};