#include "equipo.h"

equipo::equipo() {
    // valores por defecto por si crean vacio
    nombre = "sin nombre";
    grupo = "A";
    puntos = 0;
    golesfavor = 0;
    golescontra = 0;
    partidosjugados = 0;
}

equipo::equipo(string nombreinicial, string grupoinicial) {
    nombre = nombreinicial;
    grupo = grupoinicial;
    puntos = 0;
    golesfavor = 0;
    golescontra = 0;
    partidosjugados = 0;
}

void equipo::sumarpuntos(int valor) {
    puntos = puntos + valor;
}

void equipo::registrargoles(int afavor, int encontra) {
    // cada registro suma goles y tambien PJ
    golesfavor = golesfavor + afavor;
    golescontra = golescontra + encontra;
    partidosjugados = partidosjugados + 1;
}

string equipo::getnombre() const {
    return nombre;
}

string equipo::getgrupo() const {
    return grupo;
}

int equipo::getpuntos() const {
    return puntos;
}

int equipo::getgolesfavor() const {
    return golesfavor;
}

int equipo::getgolescontra() const {
    return golescontra;
}

int equipo::getpartidosjugados() const {
    return partidosjugados;
}

void equipo::setnombre(string nuevonombre) {
    nombre = nuevonombre;
}

void equipo::setgrupo(string nuevogrupo) {
    grupo = nuevogrupo;
}
