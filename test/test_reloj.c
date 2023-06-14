#include "reloj.h"
#include "unity.h"

static bool alarm_enable = false;

void EnableAlarm(bool status) {
    alarm_enable = status;
}

// Al iniciar el reloj esta en 00:00 y con hora invalida

void test_reloj_inica_hora_invalida(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0xFF};

    clock_t reloj = ClockCreate(5, EnableAlarm);

    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Al ajustar la hora el reloj queda en hora y es valida

void test_ajustar_hora(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(5, EnableAlarm);
    ClockSetTime(reloj, ESPERADO, 4);

    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza un seg

void test_hora_avanza_un_segundo(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 1};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 5;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza 10 seg

void test_hora_avanza_diez_segundos(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 1, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 50;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza un minuto

void test_hora_avanza_un_minuto(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 1, 0, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 300;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza 10 minutos

void test_hora_avanza_diez_minutos(void) {
    static const uint8_t ESPERADO[] = {0, 0, 1, 0, 0, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 3000;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza una hora

void test_hora_avanza_una_hora(void) {
    static const uint8_t ESPERADO[] = {0, 1, 0, 0, 0, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 18000;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza 10 horas

void test_hora_avanza_diez_horas(void) {
    static const uint8_t ESPERADO[] = {1, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 180000;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza un dia

void test_hora_avanza_un_dia(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);

    int n = 432000;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Fijar la hora de la alarma y consultarla

void test_fijar_hora_alarma(void) {
    uint8_t hora_alarma[6] = {0};
    clock_t reloj = ClockCreate(5, EnableAlarm);
    uint8_t hora_alarma_fijada[] = {0, 8, 3, 0, 0, 0};

    AlarmSetTime(reloj, hora_alarma_fijada, 6);
    AlarmGetTime(reloj, hora_alarma, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(hora_alarma_fijada, hora_alarma, 6);
}

// Fijar la alarma y avanzar el reloj para que suene

void test_fijar_alarma_y_suena(void) {
    static const uint8_t HORA_INICIAL[] = {0, 0, 0, 0, 0, 0};
    static const uint8_t HORA_ALARMA[] = {0, 0, 0, 0, 1, 0};
    uint8_t hora[6] = {0};

    clock_t reloj = ClockCreate(5, EnableAlarm);

    ClockSetTime(reloj, HORA_INICIAL, 6);
    AlarmSetTime(reloj, HORA_ALARMA, 6);
    ActivateAlarm(reloj, true);

    int n = 50;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA, hora, 6);
    TEST_ASSERT_TRUE(alarm_enable);
}

// Fijar la alarma y avanzar el reloj para que no suene

void test_fijar_alarma_y_no_suena(void) {
    static const uint8_t HORA_INICIAL[] = {0, 0, 0, 0, 0, 0};
    static const uint8_t HORA_ALARMA[] = {0, 0, 0, 0, 1, 0};
    static bool alarm_enable = false;

    uint8_t hora[6] = {0};

    clock_t reloj = ClockCreate(5, EnableAlarm);

    ClockSetTime(reloj, HORA_INICIAL, 6);
    AlarmSetTime(reloj, HORA_ALARMA, 6);
    ActivateAlarm(reloj, false);

    int n = 50;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA, hora, 6);
    TEST_ASSERT_FALSE(alarm_enable);
}

// Hacer sonar la alarma y posponerla

void test_fijar_alarma_y_posponer(void) {
    static const uint8_t HORA_INICIAL[] = {0, 0, 0, 0, 0, 0};
    static const uint8_t HORA_ALARMA[] = {0, 0, 0, 1, 0, 0};
    static const uint8_t HORA_ALARMA_POSPUESTA[] = {0, 0, 0, 2, 0, 0};

    uint8_t hora[6] = {0};

    clock_t reloj = ClockCreate(5, EnableAlarm);

    ClockSetTime(reloj, HORA_INICIAL, 6);
    AlarmSetTime(reloj, HORA_ALARMA, 6);
    ActivateAlarm(reloj, true);

    int n = 300;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA, hora, 6);
    TEST_ASSERT_TRUE(alarm_enable);

    ExtendAlarm(reloj, 1);
    TEST_ASSERT_FALSE(alarm_enable);

    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA_POSPUESTA, hora, 6);
    TEST_ASSERT_TRUE(alarm_enable);
}

// Hacer sonar la alarma y cancelarla hasta el otro dia

void test_fijar_alarma_y_posponer_un_dia(void) {
    static const uint8_t HORA_INICIAL[] = {0, 0, 0, 0, 0, 0};
    static const uint8_t HORA_ALARMA[] = {0, 0, 0, 1, 0, 0};
    static const uint8_t HORA_ALARMA_2[] = {0, 0, 0, 1, 0, 0};

    uint8_t hora[6] = {0};

    clock_t reloj = ClockCreate(5, EnableAlarm);

    ClockSetTime(reloj, HORA_INICIAL, 6);
    AlarmSetTime(reloj, HORA_ALARMA, 6);
    ActivateAlarm(reloj, true);

    int n = 300;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA, hora, 6);
    TEST_ASSERT_TRUE(alarm_enable);

    DisableAlarm(reloj);
    TEST_ASSERT_FALSE(alarm_enable);

    n = 432000;
    for (int i = 0; i < n; i++) {

        ClockUpdate(reloj);
    }
    ClockGetTime(reloj, hora, 6);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(HORA_ALARMA_2, hora, 6);
    TEST_ASSERT_TRUE(alarm_enable);
}