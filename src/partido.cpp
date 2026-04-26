#include "partido.h"

partido::partido() {
    equipolocal = "";
    equipovisita = "";
    goleslocal = 0;
    golesvisita = 0;
    jugado = false;
}

partido::partido(string local, string visita) {
    equipolocal = local;
    equipovisita = visita;
    goleslocal = 0;
    golesvisita = 0;
    jugado = false;
}

void partido::setresultado(int gl, int gv) {
    // al setear marcador lo marco como jugado
    goleslocal = gl;
    golesvisita = gv;
    jugado = true;
}

bool partido::sejugo() const {
    return jugado;
}

string partido::getlocal() const {
    return equipolocal;
}

string partido::getvisita() const {
    return equipovisita;
}

int partido::getgoleslocal() const {
    return goleslocal;
}

int partido::getgolesvisita() const {
    return golesvisita;
}
