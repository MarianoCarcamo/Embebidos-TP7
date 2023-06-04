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

/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include <string.h>

/* === Macros definitions ====================================================================== */
#define DEC_HORA 0
#define UNI_HORA 1
#define DEC_MIN  2
#define UNI_MIN  3
#define DEC_SEC  4
#define UNI_SEC  5
/* === Private data type declarations ========================================================== */

struct clock_s {
    uint8_t hora_actual[6];
    uint32_t tics_per_sec;
    uint32_t tics;
    bool valida;
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

clock_t ClockCreate(int tics_por_segundo) {
    static struct clock_s self[1];
    memset(self, 0, sizeof(self));
    self->tics_per_sec = tics_por_segundo;
    return self;
}

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size) {
    memcpy(hora, reloj->hora_actual, size);
    return reloj->valida;
}

bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size) {
    memcpy(reloj->hora_actual, hora, size);
    reloj->valida = true;
    return true;
}

void ClockTic(clock_t reloj) {
    reloj->tics++;
    if (reloj->tics == 5) { // Incremento en la unidad de segundos
        reloj->hora_actual[UNI_SEC]++;
        reloj->tics = 0;
    }
    if (reloj->hora_actual[UNI_SEC] == 10) { // Incremento en la decena de segundos
        reloj->hora_actual[UNI_SEC] = 0;
        reloj->hora_actual[DEC_SEC]++;
    }
    if (reloj->hora_actual[DEC_SEC] == 6) { // Incremento en la unidad de minutos
        reloj->hora_actual[DEC_SEC] = 0;
        reloj->hora_actual[UNI_MIN]++;
    }
    if (reloj->hora_actual[UNI_MIN] == 10) { // Incremento en la decena de minutos
        reloj->hora_actual[UNI_MIN] = 0;
        reloj->hora_actual[DEC_MIN]++;
    }
    if (reloj->hora_actual[DEC_MIN] == 6) { // Incremento en la unidad de horas
        reloj->hora_actual[DEC_MIN] = 0;
        reloj->hora_actual[UNI_HORA]++;
    }
    if (reloj->hora_actual[UNI_HORA] == 10) { // Incremento en la decena de horas
        reloj->hora_actual[UNI_HORA] = 0;
        reloj->hora_actual[DEC_HORA]++;
    }
    if ((reloj->hora_actual[DEC_HORA] == 2) && (reloj->hora_actual[UNI_HORA] == 4)) { // Paso de dia
        reloj->hora_actual[UNI_HORA] = 0;
        reloj->hora_actual[DEC_HORA] = 0;
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */