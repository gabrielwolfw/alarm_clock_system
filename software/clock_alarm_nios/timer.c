#include "timer.h"
#include "HAL/inc/sys/alt_irq.h"
#include "drivers/inc/altera_avalon_timer_regs.h"
#include "system.h"

// Inicialización de las variables globales
volatile int seconds = 0;
volatile int minutes = 0;
volatile int hours = 0;

volatile int alarm_hours = 7;
volatile int alarm_minutes = 0;
volatile int alarm_enabled = 1;

// Implementación de la ISR del timer
void timer_isr(void* context, alt_u32 id) {
    // Actualizar el reloj
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            if (hours >= 24) {
                hours = 0;
            }
        }
    }

    // Verificar si la alarma debe sonar
    if (alarm_enabled && hours == alarm_hours && minutes == alarm_minutes) {
        // Código para activar la alarma (por ejemplo, encender un LED o hacer sonar un buzzer)
    }

    // Reiniciar el timer para permitir que la ISR vuelva a ejecutarse
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_BASE, 0);
}

// Implementación de la función para inicializar el timer
void init_timer() {
    // Configurar el timer con interrupciones
    alt_ic_isr_register(TIMER_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_IRQ, timer_isr, NULL, NULL);
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_BASE, ALTERA_AVALON_TIMER_CONTROL_START_MSK |
                                        ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
                                        ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK);  // Iniciar el timer con interrupciones habilitadas
}

