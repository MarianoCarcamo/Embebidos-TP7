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
    if (reloj->tics == 5) {
        reloj->hora_actual[5]++;
        reloj->tics = 0;
    }
    if (reloj->hora_actual[5] == 10) {
        reloj->hora_actual[5] = 0;
        reloj->hora_actual[4]++;
    }
    if (reloj->hora_actual[4] == 6) {
        reloj->hora_actual[4] = 0;
        reloj->hora_actual[3]++;
    }
    if (reloj->hora_actual[3] == 10) {
        reloj->hora_actual[3] = 0;
        reloj->hora_actual[2]++;
    }
    if (reloj->hora_actual[2] == 6) {
        reloj->hora_actual[2] = 0;
        reloj->hora_actual[1]++;
    }
    if (reloj->hora_actual[1] == 10) {
        reloj->hora_actual[1] = 0;
        reloj->hora_actual[0]++;
    }
    if ((reloj->hora_actual[0] == 2) & (reloj->hora_actual[1] == 4)) {
        reloj->hora_actual[1] = 0;
        reloj->hora_actual[0] = 0;
    }
    // reloj->hora_actual[5] = 1;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */