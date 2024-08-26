#include <stddef.h>
#include "system.h"
#include "timer.h"
#include "altera_avalon_pio_regs.h"
#include "utils.h"

// Variables globales para mantener el estado de la hora y la alarma
volatile int config_mode = 0; // 0 = Configurar la alarma, 1 = Configurar el reloj

void handle_btns() {
    alt_u8 btns = IORD_ALTERA_AVALON_PIO_DATA(PIO_BUTTONS_0_BASE);
    alt_u8 swtchs = IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCHES_0_BASE);

    config_mode = swtchs & 0x01; // Actualizar el modo de configuración

    TimeConfig current_config;

    // Cargar la configuración actual
    current_config = load_config(config_mode);

    // Configuración del reloj
    if (config_mode == 1) { // Configurar el reloj
        // Incrementar horas
        if (btns & 0x01) {
            current_config.hours = (current_config.hours + 1) % 24;
        }

        // Incrementar minutos
        if (btns & 0x02) {
            current_config.minutes = (current_config.minutes + 1) % 60;
        }

        // Guardar la configuración
        if (btns & 0x04) {
            save_config(config_mode, current_config);
        }
    }
    // Configuración de la alarma
    else if (config_mode == 0) { // Configurar la alarma
        // Incrementar horas de alarma
        if (btns & 0x01) {
            alarm_hours = (alarm_hours + 1) % 24;
        }

        // Incrementar minutos de alarma
        if (btns & 0x02) {
            alarm_minutes = (alarm_minutes + 1) % 60;
        }

        // Guardar la configuración de la alarma
        if (btns & 0x04) {
            save_config(config_mode, (TimeConfig){alarm_hours, alarm_minutes});
        }

        // Activar o desactivar la alarma
        if (btns & 0x08) {
            alarm_active = !alarm_active; // Cambiar el estado de la alarma
        }
    }
}

int main() {
    // Inicializar el temporizador
    timer_init();

    // Configurar los displays de 7 segmentos
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, 0); // Inicializar los displays

    while (1) {
        handle_btns();
    }

    return 0;
}
