#ifndef LOG_H
#define LOG_H

#include <time.h>

typedef struct {
    char message[256];
    time_t timestamp;
} LogEvent;

typedef struct {
    LogEvent events[1000];
    int count;
} Log;

Log* create_log();
void liberar_log(Log *log);
void log_event_exam(Log *log, const char *message, int patient_id);
void log_event_report(Log *log, const char *message, int patient_id, const char *condition);
void log_event_patient(Log *log, const char *message, int patient_id);
void save_log_to_file(const Log *log, const char *filename);

#endif  // LOG_H
