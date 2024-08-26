#ifndef TIMER_H_
#define TIMER_H_


#define ALTERA_AVALON_TIMER_CONTROL_CONTINUOUS_MSK 0x2
#define ALTERA_AVALON_TIMER_CONTROL_INTERRUPT_MSK 0x4

#include "alt_types.h"

// Declaración de variables globales
extern volatile int hours;
extern volatile int minutes;
extern volatile int alarm_hours;
extern volatile int alarm_minutes;
extern volatile int alarm_active;

// Declaración de funciones
void timer_init(void);
void timer_isr(void* context);


#endif /* TIMER_H_ */
