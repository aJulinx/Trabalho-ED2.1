// log.c

#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Adicione esta linha para incluir a biblioteca de tempo

#define MAX_EVENTS 1000

struct Event {
    char message[100];
    long long int timestamp;
};

struct Log {
    struct Event events[MAX_EVENTS];
    int count;
};

Log *create_log() {
    Log *log = (Log *)malloc(sizeof(Log));
    log->count = 0;
    return log;
}

void liberar_log(Log *log) {
    free(log);
}

void log_event(Log *log, const char *message) {
    if (log == NULL || log->count >= MAX_EVENTS || message == NULL) {
        fprintf(stderr, "Error in log_event: Invalid arguments\n");
        return;
    }

    if (log->count < MAX_EVENTS) {
        time_t now;
        time(&now);

        strncpy(log->events[log->count].message, message, sizeof(log->events[log->count].message) - 1);
        log->events[log->count].timestamp = now;
        log->count++;
    } else {
        fprintf(stderr, "Error in log_event: Log is full\n");
    }
}

void log_event_exam(Log *log, const char *message, int patient_id) {
    if (log == NULL || log->count >= MAX_EVENTS || message == NULL) {
        fprintf(stderr, "Error in log_event_exam: Invalid arguments\n");
        return;
    }

    if (log->count < MAX_EVENTS) {
        time_t now;
        time(&now);

        snprintf(log->events[log->count].message, sizeof(log->events[log->count].message),
                 "%s - Patient ID: %d", message, patient_id);
        log->events[log->count].timestamp = now;
        log->count++;
    } else {
        fprintf(stderr, "Error in log_event_exam: Log is full\n");
    }
}

void log_event_report(Log *log, const char *message, int patient_id, const char *condition) {
    if (log == NULL || log->count >= MAX_EVENTS || message == NULL || condition == NULL) {
        fprintf(stderr, "Error in log_event_report: Invalid arguments\n");
        return;
    }

    if (log->count < MAX_EVENTS) {
        time_t now;
        time(&now);

        snprintf(log->events[log->count].message, sizeof(log->events[log->count].message),
                 "%s - Patient ID: %d, Condition: %s", message, patient_id, condition);
        log->events[log->count].timestamp = now;
        log->count++;
    } else {
        fprintf(stderr, "Error in log_event_report: Log is full\n");
    }
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
