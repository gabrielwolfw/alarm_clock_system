#ifndef TIMER_H
#define TIMER_H

#include "HAL/inc/alt_types.h"

// Variables globales para el tiempo
extern volatile int seconds;
extern volatile int minutes;
extern volatile int hours;

// Variables para la alarma
extern volatile int alarm_hours;
extern volatile int alarm_minutes;
extern volatile int alarm_enabled;

// Prototipos de funciones
void timer_isr(void* context, alt_u32 id);
void init_timer(void);

#endif // TIMER_H
