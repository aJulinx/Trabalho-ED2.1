#include "paciente.h"
#include "consulta.h"
#include "fila.h"
#include "laudo.h"
#include "log.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicialização do log
    Log *log = create_log();

    // Execução da simulação
    // Inicialização das listas e filas
    PacienteLista *lista_pacientes = cria_lista();
    Fila *fila_exame = criar_fila();
    Laudo *fila_laudo = criar_laudo();
    Consulta **maquina = criar_consulta(5);
    Consulta **radiologista = criar_consulta(3);

    // Contador de iterações da simulação
    int contador = 0;

    // Iterações
    while (contador < 1000) {

        // Verificação da chance do paciente chegar
        if (gen_randint(0, 100) <= 20) {
            // Criação do paciente
            PacienteNo *paciente = gerar_paciente();
            // Inserção na lista de pacientes
            inserir_lista(lista_pacientes, paciente);
            int id_paciente = paciente->id;
            // Inserção na lista de exames
            enfilerar(fila_exame, id_paciente);

            // Registro de evento: Chegada de paciente
            char message[100];  // Ajuste o tamanho conforme necessário
            snprintf(message, sizeof(message), "Chegada de paciente - Patient ID: %d", id_paciente);
            log_event(log, message);

            snprintf(message, sizeof(message), "Idade - Patient ID: %d", paciente->idade);
            log_event(log, message);
        }

        // For para simular as máquinas de raio-x atendendo os pacientes
        for (int n = 0; n < 5; n++) {
            // Se a fila de exames não estiver vazia e tiver máquinas disponíveis
            if (!fila_esta_vazia(fila_exame) && consulta_disponivel(maquina[n])) {
                // Remoção da fila de exames
                int id = desifilerar(fila_exame);
                log_event_exam(log, "Início do exame para o paciente", id);
                // Consulta na máquina
                consultar(maquina[n], id, 0);

                // Registro de evento: Fim do exame para o paciente
                log_event_exam(log, "Fim do exame para o paciente", id);
                continue;
            }
            // Enfileramento na fila para laudos
            else if (!consulta_disponivel(maquina[n]) && consulta_tempo_passando(maquina[n]) == 0) {
                int id_paciente2 = pegar_id_paciente(maquina[n]);
                enfilerar_laudo(fila_laudo, id_paciente2, contador);

                // Registro de evento: Enviado paciente para fila de laudo
                log_event_report(log, "Enviado paciente para fila de laudo", id_paciente2, "Em andamento");
            }
        }

        // For semelhante ao anterior, agora para simular
        for (int l = 0; l < 3; l++) {
            if (!esta_vazia_laudo(fila_laudo) && consulta_disponivel(radiologista[l])) {
                int id_paciente3 = desifilerar_laudo(fila_laudo);
                log_event_report(log, "Início do laudo para o paciente", id_paciente3, "Concluído");
                consultar(radiologista[l], id_paciente3, 1);

                // Registro de evento: Fim do laudo para o paciente
                log_event_report(log, "Fim do laudo para o paciente", id_paciente3, "Concluído");
                continue;
            } else if (!consulta_disponivel(radiologista[l])) {
                consulta_tempo_passando(radiologista[l]);
            }
        }

        contador++;

        /*if (contador % 10 == 0) {
            Sleep(1000);
            printf("Pausa de 10 segundos \n");
        }*/
    }

    // Processamento final para exames e laudos restantes
    int exames_restantes = tamanho_fila_exame(fila_exame);
    int laudos_restantes = tamanho_fila_laudo(fila_laudo);

    while (exames_restantes != 0 || laudos_restantes != 0) {
        if (exames_restantes != 0) {
            for (int n = 0; n < 5; n++) {
                if (!fila_esta_vazia(fila_exame) && consulta_disponivel(maquina[n])) {
                    int id = desifilerar(fila_exame);
                    consultar(maquina[n], id, 0);

                    // Registro de evento: Início do exame para o paciente
                    log_event_exam(log, "Início do exame após o tempo para o paciente", id);
                    exames_restantes--;
                    continue;
                } else if (!consulta_disponivel(maquina[n]) && consulta_tempo_passando(maquina[n]) == 0) {
                    int id_paciente2 = pegar_id_paciente(maquina[n]);
                    enfilerar_laudo(fila_laudo, id_paciente2, contador);

                    // Registro de evento: Enviado paciente para fila de laudo
                    log_event_report(log, "Enviado paciente após o tempo para fila de laudo", id_paciente2, "Em andamento");
                    exames_restantes--;
                }
            }
        }
        if (laudos_restantes != 0) {
            for (int l = 0; l < 3; l++) {
                if (!esta_vazia_laudo(fila_laudo) && consulta_disponivel(radiologista[l])) {
                    int id_paciente3 = desifilerar_laudo(fila_laudo);
                    consultar(radiologista[l], id_paciente3, 1);

                    // Registro de evento: Início do laudo para o paciente
                    log_event_report(log, "Início do laudo aoós o tempo para o paciente", id_paciente3, "Concluído");
                    laudos_restantes--;
                    continue;
                } else if (!consulta_disponivel(radiologista[l])) {
                    consulta_tempo_passando(radiologista[l]);
                }
            }
        }
    }

    // Liberando memória
    liberar_fila(fila_exame);
    liberar_laudo(fila_laudo);
    liberar_salas(maquina, 5);
    liberar_salas(radiologista, 3);
    liberar_paciente(lista_pacientes);

    // Salvando o log no arquivo
    save_log_to_file(log, "log.txt");

    // Liberando memória do log
    liberar_log(log);

    return 0;
}
