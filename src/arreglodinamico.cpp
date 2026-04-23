#include "arreglodinamico.h"

arreglodinamico::arreglodinamico() {
    datos = 0;
    cantidad = 0;
    capacidad = 0;
}

arreglodinamico::arreglodinamico(int capacidadinicial) {
    datos = 0;
    cantidad = 0;
    capacidad = 0;

    if (capacidadinicial > 0) {
        datos = new int[capacidadinicial];
        capacidad = capacidadinicial;
    }
}

arreglodinamico::~arreglodinamico() {
    if (datos != 0) {
        delete[] datos;
        datos = 0;
    }

    cantidad = 0;
    capacidad = 0;
}

bool arreglodinamico::reservar(int nuevacapacidad) {
    if (nuevacapacidad <= capacidad) {
        return true;
    }

    if (nuevacapacidad <= 0) {
        return false;
    }

    // hago nuevo bloque y copio lo que ya estaba
    int* temp = new int[nuevacapacidad];

    for (int i = 0; i < cantidad; i = i + 1) {
        temp[i] = datos[i];
    }

    if (datos != 0) {
        delete[] datos;
    }

    datos = temp;
    capacidad = nuevacapacidad;
    return true;
}

bool arreglodinamico::agregar(int valor) {
    if (cantidad >= capacidad) {
        int nc = 0;

        if (capacidad == 0) {
            nc = 4;
        } else {
            nc = capacidad * 2;
        }

        // toca agrandar antes de meter el dato
        if (reservar(nc) == false) {
            return false;
        }
    }

    datos[cantidad] = valor;
    cantidad = cantidad + 1;
    return true;
}

int arreglodinamico::obtener(int indice) const {
    if (indice < 0) {
        return 0;
    }

    if (indice >= cantidad) {
        return 0;
    }

    return datos[indice];
}

bool arreglodinamico::cambiar(int indice, int valor) {
    if (indice < 0) {
        return false;
    } else {
        if (indice >= cantidad) {
            return false;
        } else {
            datos[indice] = valor;
            return true;
        }
    }
}

int arreglodinamico::getcantidad() const {
    return cantidad;
}

int arreglodinamico::getcapacidad() const {
    return capacidad;
}

void arreglodinamico::limpiar() {
    // dejo la memoria pero como si estuviera vacio
    cantidad = 0;
}
