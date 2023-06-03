// Despues de n ciclos de reloj la hora avanza un segundo, 10 segundos, un minuto...
// Fijar la hora de la alarma y consultarla.
// Fijar la alarma y avanzar la hora para que suene.
// Fijar la alarma, deshabilitarla y avanzar el reloj para que no suene.
// Hacer sonar la alarma y posponerla.
// Hacer sonar la alarma y cancelarla hasta el otro dia.

#include "unity.h"
#include "reloj.h"

// Al inicializar el reloj esta en 00:00 y con hora invalida.
void test_reloj_arranca_con_hora_invalida(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0xff};

    clock_t reloj = ClockCreate(5);
    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Al ajustar la hora el reloj queda en hora y es valido.
void test_ajustar_hora(void) {

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(5);
    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}