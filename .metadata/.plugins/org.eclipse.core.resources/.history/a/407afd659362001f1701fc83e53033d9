#include <stdio.h>
#include "timer.h"

void configure_time_and_alarm() {
    int h, m, s;

    // Configuración de la hora actual
    printf("Ingrese la hora actual (hh mm ss): ");
    scanf("%d %d %d", &h, &m, &s);
    set_time(h, m, s);

    // Configuración de la hora de la alarma
    printf("Ingrese la hora de la alarma (hh mm): ");
    scanf("%d %d", &h, &m);
    set_alarm(h, m);

    // Configuración de la alarma (habilitar o deshabilitar)
    int enable;
    printf("Habilitar alarma? (1 = sí, 0 = no): ");
    scanf("%d", &enable);
    enable_alarm(enable);
}

int main() {
    init_timer();

    // Configuración inicial
    configure_time_and_alarm();

    while (1) {
        // Puedes agregar código aquí para manejar otras tareas
        // Actualizar la visualización del reloj, etc.
    }

    return 0;
}
