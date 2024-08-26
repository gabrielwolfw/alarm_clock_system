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

    int config_mode = swtchs & 0x01;

    TimeConfig current_config;

    // Cargar la configuración actual
    current_config = load_config(config_mode);

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

    // Apagar la alarma (no afecta la configuración)
    if (btns & 0x08) {
        // Desactivar la alarma
    }
}
// Mapeo de dígitos a sus correspondientes valores en un display de 7 segmentos
const alt_u8 SEGMENT_MAP[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void update_display(int hours, int minutes) {
    alt_u32 display_value = 0;

    // Separar las horas y minutos en dígitos individuales
    int hour_tens = hours / 10;
    int hour_units = hours % 10;
    int minute_tens = minutes / 10;
    int minute_units = minutes % 10;

    // Mapear los dígitos a sus correspondientes valores en 7 segmentos
    display_value |= SEGMENT_MAP[hour_tens] << 21;  // Dígito más significativo
    display_value |= SEGMENT_MAP[hour_units] << 14; // Segundo dígito
    display_value |= SEGMENT_MAP[minute_tens] << 7; // Tercer dígito
    display_value |= SEGMENT_MAP[minute_units];     // Dígito menos significativo

    // Escribir el valor al PIO para actualizar los displays
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, display_value);
}

int main() {
    // Inicializar el temporizador
	timer_init();

    // Configurar los displays de 7 segmentos
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, 0); // Inicializar los displays

    while (1) {
        // Manejar los botones si es necesario
        handle_btns();

        // Actualizar el display con la hora y los minutos actuales
        update_display(hours, minutes);
    }

    return 0;
}
