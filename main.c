//Include dos tads e bibliotecas
#include "paciente.h"
#include "consulta.h"
#include "fila.h"
#include "laudo.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


//Declaração da função main
int main() {
    //Inicialização das listas e filas
    PacienteLista *lista_pacientes = cria_lista();
    Fila *fila_exame = criar_fila();
    Laudo *fila_laudo = criar_laudo();
    Consulta **maquina = criar_consulta(5);
    Consulta **radiologista=criar_consulta(3);

    //Contador de iterações da simulação
    int contador=0;

    while(contador<43200){

        //Verificação da chance do paciente chegar
        if(gen_randint(0,100)<=20){
            //Criação do paciente
            PacienteNo *pacient = gerar_paciente();
            //Inserção na lista de pacientes
            inserir_lista(lista_pacientes, pacient);
            int id_paciente=pacient->id;
            //Inserção na lsita de exames
            enfilerar(fila_exame, id_paciente);
        }

        //For para simular as máquinas de raio-x atentendo os pacientes
        for(int n=0;n<5;n++){
            //Se a fila de exames não estiver vazia e tiver máquinas disponiveis
            if(!fila_esta_vazia(fila_exame) && consulta_disponivel(maquina[n])){
                //Remoção da fila de exames
                int id = desifilerar(fila_exame);
                //Consulta na máquina
                consultar(maquina[n], id, 0);
                continue;
            }
            //Enfileramento na fila para laudos
            else if(!consulta_disponivel(maquina[n]) && consulta_tempo_passando(maquina[n]) == 0){
                int id_paciente2=pegar_id_paciente(maquina[n]);
                enfilerar_laudo(fila_laudo,id_paciente2, contador);
            }
        }

        //For semelhante ao anterior, agora para simular 
        for(int l=0;l<3;l++){
            if(!esta_vazia_laudo(fila_laudo) && consulta_disponivel(radiologista[l])){
                int id_paciente3 = desifilerar_laudo(fila_laudo);
                consultar(radiologista[l], id_paciente3, 1);
                continue;
            }else if(!consulta_disponivel(radiologista[l])){
                consulta_tempo_passando(radiologista[l]);
            }
        }

        contador++;

        if(contador%10==0){
            Sleep(1000);
            printf("Pausa de 10 segundos \n");

        }
    }

    int exames_restantes = tamanho_fila_exame(fila_exame);
    int laudos_restantes = tamanho_fila_laudo(fila_laudo);

    while(exames_restantes!=0 || laudos_restantes!=0){
        if(exames_restantes!=0){
            for(int n=0;n<5;n++){
                if(!fila_esta_vazia(fila_exame) && consulta_disponivel(maquina[n])){
                    int id = desifilerar(fila_exame);
                    consultar(maquina[n], id, 0);
                    continue;
                }
                else if(!consulta_disponivel(maquina[n]) && consulta_tempo_passando(maquina[n]) == 0){
                    int id_paciente2=pegar_id_paciente(maquina[n]);
                    enfilerar_laudo(fila_laudo,id_paciente2, contador);
                }
                exames_restantes--;
            }
        }
        if(laudos_restantes!=0){
            for(int l=0;l<3;l++){
                if(!esta_vazia_laudo(fila_laudo) && consulta_disponivel(radiologista[l])){
                    int id_paciente3 = desifilerar_laudo(fila_laudo);
                    consultar(radiologista[l], id_paciente3, 1);
                    continue;
                }else if(!consulta_disponivel(radiologista[l])){
                    consulta_tempo_passando(radiologista[l]);
                }
            }
            laudos_restantes--;
        }
        
    }

    


    liberar_fila(fila_exame);
    liberar_laudo(fila_laudo);
    liberar_salas(maquina, 5);
    liberar_salas(radiologista, 3);
    liberar_paciente(lista_pacientes);
    
    return 0;
}
