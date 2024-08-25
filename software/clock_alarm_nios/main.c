#include <stdio.h>
#include <stdint.h>
#include "system.h"
#include "timer.h"
#include "utils.h"



// Direcciones base para los PIO
#define BUTTON_PIO_BASE PIO_BUTTONS_0_BASE
#define SWITCH_PIO_BASE PIO_SWITCHES_0_BASE


void handle_buttons(){
	//Controlar los botones y switches
}



int main() {
    // Inicialización
    init_timer();                // Inicializar temporizador
    load_alarm_configuration();  // Cargar configuración de la alarma
    load_current_time_configuration();  // Cargar configuración de la hora actual

    while (1) {
        handle_buttons();        // Manejar los botones
    }

    return 0;
}

