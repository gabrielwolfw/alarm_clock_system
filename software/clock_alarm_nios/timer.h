#ifndef TIMER_H_
#define TIMER_H_
#include "HAL/inc/alt_types.h"
#include "altera_avalon_pio_regs.h"

#define ALTERA_AVALON_TIMER_STATUS_REG 0  // Asigna el offset correcto del registro de estado
#define ALTERA_AVALON_TIMER_CONTROL_REG 4 // Asigna el offset correcto del registro de control

#define IOWR_ALTERA_AVALON_TIMER_STATUS(base, data)  IOWR((base), ALTERA_AVALON_TIMER_STATUS_REG, (data))
#define IOWR_ALTERA_AVALON_TIMER_CONTROL(base, data) IOWR((base), ALTERA_AVALON_TIMER_CONTROL_REG, (data))


// Variables globales para el tiempo
extern volatile int seconds;
extern volatile int minutes;
extern volatile int hours;

// Variables para la alarma
extern volatile int alarm_hours;
extern volatile int alarm_minutes;
extern volatile int alarm_enabled;

// Prototipos de funciones
void timer_isr(void* context);
void init_timer(void);


#endif /* TIMER_H_ */
