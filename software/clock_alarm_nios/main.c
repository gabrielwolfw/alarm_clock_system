#include <stddef.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "HAL/inc/sys/alt_irq.h"


#define ALTERA_AVALON_TIMER_CONTROL_CONTINUOUS_MSK 0x2
#define ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK 0x4

// Variables globales para la hora y los minutos
volatile int hours = 0;
volatile int minutes = 0;

// Funci�n de interrupci�n del temporizador
void timer_isr(void* context) {
    // Incrementar los minutos
    minutes++;
    if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
            hours = 0;
        }
    }

    // Actualizar el display (aqu� s�lo se imprime en la consola como ejemplo)
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, (hours << 8) | minutes);

    // Limpiar la interrupci�n del temporizador
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}

int main() {
    // Configuraci�n inicial del temporizador
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0); // Detener el temporizador
    IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, TIMER_0_LOAD_VALUE & 0xFFFF); // Configurar el per�odo
    IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, (TIMER_0_LOAD_VALUE >> 16) & 0xFFFF);
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_CONTINUOUS_MSK | ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK); // Iniciar el temporizador y habilitar la interrupci�n

    // Configurar el ISR
    alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, timer_isr, NULL, NULL);

    // Configurar los displays de 7 segmentos
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, 0); // Inicializar los displays

    while (1) {
        // El procesador entra en un bucle infinito
        // Las actualizaciones del reloj se hacen en el ISR
    }

    return 0;
}
