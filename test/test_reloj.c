/* TESTS PENDIENTES
Despues de n ciclos de reloj la hora avanza un segundo, 10 segundos, un minuto...
Fijar la hora de la alarma y consultarla.
Fijar la alarma y avanzar la hora para que suene.
Fijar la alarma, deshabilitarla y avanzar el reloj para que no suene.
Hacer sonar la alarma y posponerla.
Hacer sonar la alarma y cancelarla hasta el otro dia.
*/

/************************************************************************************************
Copyright (c) 2023, Mariano Carcamo marianocarcamo98@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
SPDX-License-Identifier: MIT
*************************************************************************************************/

/** \brief Archivo de prueba para la libreria reloj
 **
 ** Archivo de soporte para un desarrollo basado en pruebas sobre la libreria de reloj
 **
 ** \addtogroup tdd TDD
 ** \brief TDD
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "unity.h"
#include "reloj.h"

/* === Macros definitions ====================================================================== */

#define TICS_POR_SEGUNDO 5

#define SIMULAR_SEGUNDOS(VALOR, FUNCION)                                                           \
    for (int count = 0; count < VALOR; count++) {                                                  \
        for (int indice = 0; indice < TICS_POR_SEGUNDO; indice++) {                                \
            FUNCION;                                                                               \
        }                                                                                          \
    }
/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */
void setUp(void) {
}

// Al inicializar el reloj esta en 00:00 y con hora invalida.
void test_reloj_arranca_con_hora_invalida(void) {
    static const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
    uint8_t hora[6] = {0xff};

    clock_t reloj = ClockCreate(TICS_POR_SEGUNDO);
    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Al ajustar la hora el reloj queda en hora y es valido.
void test_ajustar_hora(void) {

    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 0};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(TICS_POR_SEGUNDO);
    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

// Despues de n ciclos de reloj la hora avanza un segundo.
void test_avanza_unidad_segundos(void) {
    static const uint8_t HORA[] = {1, 2, 3, 4, 0, 0};
    static const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};
    uint8_t hora[6];

    clock_t reloj = ClockCreate(TICS_POR_SEGUNDO);
    ClockSetTime(reloj, HORA, 4);
    SIMULAR_SEGUNDOS(1, ClockTic(reloj));
    ClockGetTime(reloj, hora, 6);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
