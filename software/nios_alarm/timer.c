#include "timer.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "HAL/inc/sys/alt_irq.h"

// Definiciones de variables globales
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

    // Actualizar el display
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_7SEGMENTS_0_BASE, (hours << 8) | minutes);

    // Limpiar la interrupci�n del temporizador
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}

// Funci�n para inicializar el temporizador
void timer_init(void) {
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0); // Detener el temporizador
    IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, TIMER_0_LOAD_VALUE & 0xFFFF); // Configurar el per�odo bajo
    IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, (TIMER_0_LOAD_VALUE >> 16) & 0xFFFF); // Configurar el per�odo alto

    // Iniciar el temporizador y habilitar la interrupci�n
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
        ALTERA_AVALON_TIMER_CONTROL_START_MSK |
        ALTERA_AVALON_TIMER_CONTROL_CONTINUOUS_MSK |
        ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK);

    // Configurar el ISR
    alt_ic_isr_register(
        TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
        TIMER_0_IRQ,
        timer_isr,
        NULL,
        NULL
    );
}
