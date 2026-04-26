#include "grupo.h"

grupo::grupo() {
    nombre = "grupo x";
    cantidad = 0;

    for (int i = 0; i < 4; i = i + 1) {
        equipos[i] = "";
        confederaciones[i] = "";
    }
}

grupo::grupo(string nombregrupo) {
    nombre = nombregrupo;
    cantidad = 0;

    for (int i = 0; i < 4; i = i + 1) {
        equipos[i] = "";
        confederaciones[i] = "";
    }
}

void grupo::setnombre(string nuevonombre) {
    nombre = nuevonombre;
}

string grupo::getnombre() const {
    return nombre;
}

bool grupo::agregarequipo(string nombreequipo) {
    return agregarequipo(nombreequipo, "");
}

bool grupo::agregarequipo(string nombreequipo, string confederacion) {
    // maximo 4 por grupo
    if (cantidad >= 4) {
        return false;
    }

    if (puedeagregarconfederacion(confederacion) == false) {
        return false;
    }

    int posactual = cantidad;
    equipos[posactual] = nombreequipo;
    confederaciones[posactual] = confederacion;
    cantidad = posactual + 1;
    return true;
}

bool grupo::puedeagregarconfederacion(string confederacion) const {
    if (confederacion == "") {
        return true;
    }

    int conteo = 0;
    for (int i = 0; i < cantidad; i = i + 1) {
        if (confederaciones[i] == confederacion) {
            conteo = conteo + 1;
        }
    }

    // regla fifa: uefa hasta 2, resto solo 1
    if (confederacion == "UEFA") {
        return conteo < 2;
    }

    return conteo == 0;
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

string grupo::getconfederacion(int pos) const {
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

    return confederaciones[pos];
}

int grupo::getcantidad() const {
    return cantidad;
}

bool grupo::estalleno() const {
    if (cantidad == 4) {
        return true;
    } else {
        return false;
    }
}

void grupo::limpiar() {
    cantidad = 0;

    for (int i = 0; i < 4; i = i + 1) {
        equipos[i] = "";
        confederaciones[i] = "";
    }
}
