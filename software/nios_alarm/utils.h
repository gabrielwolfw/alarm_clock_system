#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>

// Definici�n de la estructura para almacenar la configuraci�n
typedef struct {
    int hours;
    int minutes;
} TimeConfig;

void save_config(int is_alarm, TimeConfig config);
TimeConfig load_config(int is_alarm);

#endif /* UTILS_H_ */
