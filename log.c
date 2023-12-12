#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Log* create_log() {
    Log *log = (Log *)malloc(sizeof(Log));
    log->count = 0;
    return log;
}

void liberar_log(Log *log) {
    free(log);
}

void log_event_exam(Log *log, const char *message, int patient_id) {
    time_t now;
    time(&now);

    strncpy(log->events[log->count].message, message, sizeof(log->events[log->count].message) - 1);
    log->events[log->count].timestamp = now;
    log->count++;
}

void log_event_report(Log *log, const char *message, int patient_id, const char *condition) {
    time_t now;
    time(&now);

    snprintf(log->events[log->count].message, sizeof(log->events[log->count].message),
             "%s - Patient ID: %d, Condition: %s", message, patient_id, condition);
    log->events[log->count].timestamp = now;
    log->count++;
}

void log_event_patient(Log *log, const char *message, int patient_id) {
    time_t now;
    time(&now);

    snprintf(log->events[log->count].message, sizeof(log->events[log->count].message),
             "%s - Patient ID: %d", message, patient_id);
    log->events[log->count].timestamp = now;
    log->count++;
}

void save_log_to_file(const Log *log, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < log->count; i++) {
        fprintf(file, "[%lld] %s\n", (long long int)log->events[i].timestamp, log->events[i].message);
    }

    fclose(file);
}
