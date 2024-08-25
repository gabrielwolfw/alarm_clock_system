#include "utils.h"
#include "system.h"
#include "altera_avalon_onchip_memory2.h"
#include <stdio.h>

// Direcciones base de la memoria RAM
#define RAM_BASE RAM_0_BASE

// Direcciones para la configuración en la memoria
#define ALARM_CONFIG_OFFSET 0x00
#define TIME_CONFIG_OFFSET  0x20

// Función para guardar la configuración de la alarma
void save_alarm_configuration() {
    AlarmConfig alarm_config;
    alarm_config.alarm_hours = alarm_hours;
    alarm_config.alarm_minutes = alarm_minutes;
    alarm_config.alarm_enabled = alarm_enabled;

    // Guardar en la memoria RAM
    IOWR_ALTERA_AVALON_ONCHIP_MEMORY2_DATA(RAM_BASE, ALARM_CONFIG_OFFSET, *(int*)&alarm_config);

    printf("Configuración de alarma guardada: %02d:%02d\n", alarm_hours, alarm_minutes);
}

// Función para guardar la configuración de la hora actual
void save_current_time_configuration() {
    TimeConfig time_config;
    time_config.hours = hours;
    time_config.minutes = minutes;

    // Guardar en la memoria RAM
    IOWR_ALTERA_AVALON_ONCHIP_MEMORY2_DATA(RAM_BASE, TIME_CONFIG_OFFSET, *(int*)&time_config);

    printf("Hora actual guardada: %02d:%02d\n", hours, minutes);
}

// Función para cargar la configuración de la alarma
void load_alarm_configuration() {
    AlarmConfig alarm_config;

    // Cargar de la memoria RAM
    alarm_config = *(AlarmConfig*)IORD_ALTERA_AVALON_ONCHIP_MEMORY2_DATA(RAM_BASE, ALARM_CONFIG_OFFSET);

    alarm_hours = alarm_config.alarm_hours;
    alarm_minutes = alarm_config.alarm_minutes;
    alarm_enabled = alarm_config.alarm_enabled;

    printf("Configuración de alarma cargada: %02d:%02d\n", alarm_hours, alarm_minutes);
}

// Función para cargar la configuración de la hora actual
void load_current_time_configuration() {
    TimeConfig time_config;

    // Cargar de la memoria RAM
    time_config = *(TimeConfig*)IORD_ALTERA_AVALON_ONCHIP_MEMORY2_DATA(RAM_BASE, TIME_CONFIG_OFFSET);

    hours = time_config.hours;
    minutes = time_config.minutes;

    printf("Hora actual cargada: %02d:%02d\n", hours, minutes);
}




