#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "timer.h"
#include "utils.h"

// Direcciones base para los PIO (definidas en system.h)
#define BUTTON_PIO_BASE PIO_BUTTONS_0_BASE
#define DISPLAY_PIO_BASE PIO_7SEGMENTS_0_BASE

// Variables globales para la configuraci�n de la alarma
volatile int alarm_hours = 7;
volatile int alarm_minutes = 0;
volatile int alarm_enabled = 1;

// Funciones para actualizar los displays de 7 segmentos
void update_display(int display_num, int value) {
    // Enviar valor al display especificado
    IOWR_ALTERA_AVALON_PIO_DATA(DISPLAY_PIO_BASE + display_num, value);
}

// Funci�n para manejar la configuraci�n de la alarma con botones y switches
void handle_buttons() {
    int btns = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);
    int switches = IORD_ALTERA_AVALON_PIO_DATA(PIO_SWITCHES_0_BASE);

    if (btns & 0x01) {  // Bot�n 1
        alarm_hours = (alarm_hours + 1) % 24;
    }
    if (btns & 0x02) {  // Bot�n 2
        alarm_minutes = (alarm_minutes + 1) % 60;
    }
    if (btns & 0x04) {  // Bot�n 3
        if (switches & 0x01) {  // Si el switch est� en 1
            save_alarm_configuration();
        } else {  // Si el switch est� en 0
            save_current_time_configuration();
        }
    }
    if (btns & 0x08) {  // Bot�n 4
        alarm_enabled = 0;
    }
}

// Funci�n para actualizar la visualizaci�n del reloj y la alarma
void update_time_display() {
    int hours_display = (alarm_hours / 10) << 4 | (alarm_hours % 10);
    int minutes_display = (alarm_minutes / 10) << 4 | (alarm_minutes % 10);
    int alarm_hours_display = (alarm_hours / 10) << 4 | (alarm_hours % 10);
    int alarm_minutes_display = (alarm_minutes / 10) << 4 | (alarm_minutes % 10);

    // Actualizar los displays
    update_display(0, hours_display);
    update_display(1, minutes_display);
    update_display(2, alarm_hours_display);
    update_display(3, alarm_minutes_display);
}

int main() {
    init_timer();
    load_alarm_configuration();  // Cargar configuraci�n al inicio
    load_current_time_configuration();  // Cargar configuraci�n de tiempo actual

    while (1) {
        handle_buttons();
        update_time_display();
        // Puedes agregar otras tareas aqu�
    }

    return 0;
}
