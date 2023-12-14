// log.h

#ifndef LOG_H
#define LOG_H

typedef struct Log Log;

Log *create_log();
void liberar_log(Log *log);
void log_event(Log *log, const char *message);
void log_event_exam(Log *log, const char *message, int patient_id);
void log_event_report(Log *log, const char *message, int patient_id, const char *condition);
void save_log_to_file(const Log *log, const char *filename);

#endif  // LOG_H
