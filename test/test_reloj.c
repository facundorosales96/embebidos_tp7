// PRUEBAS
// Al iniciar el reloj esta en 00:00 y con hora invalida
// Al ajustar la hora el reloj queda en hora y es valida
// Fijar la hora de la alarma y consultarla
//...

#include "reloj.h"
#include "unity.h"

// Al iniciar el reloj esta en 00:00 y con hora invalida

void test_reloj_inica_hora_invalida(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0xFF};

    clock_t reloj = ClockCreate(5);

    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Al ajustar la hora el reloj queda en hora y es valida

void test_ajustar_hora(void) {
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(5);
    ClockSetTime(reloj, ESPERADO, 4);

    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}