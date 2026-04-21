#include "grupo.h"

grupo::grupo() {
    nombre = "grupo x";
    cantidad = 0;
}

grupo::grupo(string nombregrupo) {
    nombre = nombregrupo;
    cantidad = 0;
}

void grupo::setnombre(string nuevonombre) {
    nombre = nuevonombre;
}

string grupo::getnombre() const {
    return nombre;
}

bool grupo::agregarequipo(string nombreequipo) {
    bool hayespacio = true;

    if (cantidad >= 4) {
        hayespacio = false;
    }

    if (hayespacio == false) {
        return false;
    }

    int posactual = cantidad;
    equipos[posactual] = nombreequipo;
    cantidad = posactual + 1;

    return true;
}

string grupo::getequipo(int pos) const {
    bool posicionvalida = true;

    if (pos < 0) {
        posicionvalida = false;
    }

    if (pos >= cantidad) {
        posicionvalida = false;
    }

    if (posicionvalida == false) {
        return "";
    }

    string nombreequipo = equipos[pos];
    return nombreequipo;
}

int grupo::getcantidad() const {
    return cantidad;
}

bool grupo::estalleno() const {
    bool lleno = false;

    if (cantidad == 4) {
        lleno = true;
    }

    return lleno;
}
