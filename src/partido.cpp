#include "partido.h"

partido::partido() {
    equipolocal = "";
    equipovisita = "";
    sede = "nombreSede";
    arbitros[0] = "codArbitro1";
    arbitros[1] = "codArbitro2";
    arbitros[2] = "codArbitro3";
    hora = "00:00";
    fecha = "01/01/2026";
    goleslocal = 0;
    golesvisita = 0;
    posesionlocal = 50;
    cantgoleadoreslocal = 0;
    cantgoleadoresvisita = 0;
    for (int i = 0; i < 16; i = i + 1) {
        goleadoreslocal[i] = 0;
        goleadoresvisita[i] = 0;
    }
    jugado = false;
}

partido::partido(string local, string visita) {
    equipolocal = local;
    equipovisita = visita;
    sede = "nombreSede";
    arbitros[0] = "codArbitro1";
    arbitros[1] = "codArbitro2";
    arbitros[2] = "codArbitro3";
    hora = "00:00";
    fecha = "01/01/2026";
    goleslocal = 0;
    golesvisita = 0;
    posesionlocal = 50;
    cantgoleadoreslocal = 0;
    cantgoleadoresvisita = 0;
    for (int i = 0; i < 16; i = i + 1) {
        goleadoreslocal[i] = 0;
        goleadoresvisita[i] = 0;
    }
    jugado = false;
}

void partido::configurarcontexto(string sedefija,
                                string arbitro1,
                                string arbitro2,
                                string arbitro3,
                                string horafija,
                                string fechafija) {
    sede = sedefija;
    arbitros[0] = arbitro1;
    arbitros[1] = arbitro2;
    arbitros[2] = arbitro3;
    hora = horafija;
    fecha = fechafija;
}

void partido::setresultado(int gl, int gv) {
    // al setear marcador lo marco como jugado
    goleslocal = gl;
    golesvisita = gv;
    jugado = true;
}

void partido::setposesionlocal(int porcentaje) {
    int valor = porcentaje;
    if (valor < 0) {
        valor = 0;
    }
    if (valor > 100) {
        valor = 100;
    }
    posesionlocal = valor;
}

int partido::getposesionlocal() const {
    return posesionlocal;
}

int partido::getposesionvisita() const {
    return 100 - posesionlocal;
}

void partido::limpiargoleadores() {
    cantgoleadoreslocal = 0;
    cantgoleadoresvisita = 0;
    for (int i = 0; i < 16; i = i + 1) {
        goleadoreslocal[i] = 0;
        goleadoresvisita[i] = 0;
    }
}

void partido::agregargoleadorlocal(int camiseta) {
    if (cantgoleadoreslocal >= 16) {
        return;
    }
    goleadoreslocal[cantgoleadoreslocal] = camiseta;
    cantgoleadoreslocal = cantgoleadoreslocal + 1;
}

void partido::agregargoleadorvisita(int camiseta) {
    if (cantgoleadoresvisita >= 16) {
        return;
    }
    goleadoresvisita[cantgoleadoresvisita] = camiseta;
    cantgoleadoresvisita = cantgoleadoresvisita + 1;
}

int partido::getcantgoleadoreslocal() const {
    return cantgoleadoreslocal;
}

int partido::getcantgoleadoresvisita() const {
    return cantgoleadoresvisita;
}

int partido::getgoleadorlocal(int pos) const {
    if (pos < 0 || pos >= cantgoleadoreslocal) {
        return 0;
    }
    return goleadoreslocal[pos];
}

int partido::getgoleadorvisita(int pos) const {
    if (pos < 0 || pos >= cantgoleadoresvisita) {
        return 0;
    }
    return goleadoresvisita[pos];
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

string partido::getsede() const {
    return sede;
}

string partido::getarbitro(int indice) const {
    if (indice < 0 || indice >= 3) {
        return "";
    }
    return arbitros[indice];
}

string partido::gethora() const {
    return hora;
}

string partido::getfecha() const {
    return fecha;
}

int partido::getgoleslocal() const {
    return goleslocal;
}

int partido::getgolesvisita() const {
    return golesvisita;
}
