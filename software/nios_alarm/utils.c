#include "utils.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"

// Definici�n de variables globales para almacenar la configuraci�n
static TimeConfig alarm_config = {0, 0};
static TimeConfig clock_config = {0, 0};

// Funci�n para guardar la configuraci�n
void save_config(int is_alarm, TimeConfig config) {
    if (is_alarm) {
        alarm_config = config;
    } else {
        clock_config = config;
    }
}

// Funci�n para cargar la configuraci�n
TimeConfig load_config(int is_alarm) {
    if (is_alarm) {
        return alarm_config;
    } else {
        return clock_config;
    }
}
