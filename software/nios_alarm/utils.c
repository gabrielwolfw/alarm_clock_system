#include "utils.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"

// Definición de variables globales para almacenar la configuración
static TimeConfig alarm_config = {0, 0};
static TimeConfig clock_config = {0, 0};

// Función para guardar la configuración
void save_config(int is_alarm, TimeConfig config) {
    if (is_alarm) {
        alarm_config = config;
    } else {
        clock_config = config;
    }
}

// Función para cargar la configuración
TimeConfig load_config(int is_alarm) {
    if (is_alarm) {
        return alarm_config;
    } else {
        return clock_config;
    }
}
