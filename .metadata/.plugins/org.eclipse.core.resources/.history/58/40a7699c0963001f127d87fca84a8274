#include "timer.h"
#include "HAL/inc/sys/alt_irq.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"

#define ALTERA_AVALON_TIMER_CONTROL_START_MSK (0x4)
#define ALTERA_AVALON_TIMER_CONTROL_CONT_MSK (0x2)
#define ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK  (0x1)

// Inicialización de las variables globales
volatile int seconds = 0;
volatile int minutes = 0;
volatile int hours = 0;

volatile int alarm_hours = 7;
volatile int alarm_minutes = 0;
volatile int alarm_enabled = 1;

// Función para establecer la hora actual
void set_time(int h, int m, int s) {
    if (h >= 0 && h < 24) hours = h;
    if (m >= 0 && m < 60) minutes = m;
    if (s >= 0 && s < 60) seconds = s;
}

// Función para establecer la hora de la alarma
void set_alarm(int h, int m) {
    if (h >= 0 && h < 24) alarm_hours = h;
    if (m >= 0 && m < 60) alarm_minutes = m;
}

// Función para habilitar o deshabilitar la alarma
void enable_alarm(int enable) {
    alarm_enabled = enable;
}

void timer_isr(void* context) {
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

    if (alarm_enabled && hours == alarm_hours && minutes == alarm_minutes) {
        // Activar la alarma
    }

    // Reiniciar el temporizador
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}

// Función para inicializar el temporizador
void init_timer() {
    // Registrar la ISR
    alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID,
                        TIMER_0_IRQ,
                        timer_isr,NULL,NULL);

    // Iniciar el temporizador con interrupciones habilitadas
    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
                                     ALTERA_AVALON_TIMER_CONTROL_START_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_CONT_MSK|
                                     ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK);
}
