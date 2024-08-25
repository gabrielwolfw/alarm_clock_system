#include <stdio.h>
#include "timer.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"

// Direcciones base para los PIO (definidas en system.h)
#define BUTTON_PIO_BASE PIO_BUTTONS_0_BASE
#define DISPLAY_PIO_BASE PIO_7SEGMENTS_0_BASE

// Variables globales para la configuraci�n de la alarma
volatile int alarm_hours = 7;
volatile int alarm_minutes = 0;
volatile int alarm_enabled = 1;

// Funciones para actualizar los displays de 7 segmentos
void update_display(int display_num, int value) {
    IOWR_ALTERA_AVALON_PIO_DATA(DISPLAY_PIO_BASE, value);
}

// Funci�n para manejar la configuraci�n de la alarma con botones
void handle_buttons() {
    int btns = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

    if (btns & 0x01) {  // Asumiendo que el bot�n 1 est� en el bit 0
        alarm_hours = (alarm_hours + 1) % 24;  // Incrementa la hora, reinicia a 0 despu�s de 23
    }
    if (btns & 0x02) {  // Asumiendo que el bot�n 2 est� en el bit 1
        alarm_minutes = (alarm_minutes + 1) % 60;  // Incrementa los minutos, reinicia a 0 despu�s de 59
    }
    if (btns & 0x04) {  // Asumiendo que el bot�n 3 est� en el bit 2
        // Guardar cambios en la configuraci�n de la alarma
        // Aqu� puedes agregar c�digo para manejar la persistencia si es necesario
    }
    if (btns & 0x08) {  // Asumiendo que el bot�n 4 est� en el bit 3
        alarm_enabled = 0;  // Detiene la alarma
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

    while (1) {
        handle_buttons();
        update_time_display();
        // Puedes agregar otras tareas aqu�
    }

    return 0;
}
