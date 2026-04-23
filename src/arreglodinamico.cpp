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

    // Se crea bloque nuevo y luego se copia lo que ya teniamos cargado.
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
        int nc = capacidad == 0 ? 4 : capacidad * 2;

        // Cuando se llena, crece por salto para no reservar cada insercion.
        if (reservar(nc) == false) {
            return false;
        }
    }

    datos[cantidad] = valor;
    cantidad = cantidad + 1;
    return true;
}

int arreglodinamico::obtener(int indice) const {
    if (indice < 0 || indice >= cantidad) {
        return 0;
    }

    return datos[indice];
}

bool arreglodinamico::cambiar(int indice, int valor) {
    if (indice < 0) {
        return false;
    }

    if (indice >= cantidad) {
        return false;
    }

    datos[indice] = valor;
    return true;
}

int arreglodinamico::getcantidad() const {
    return cantidad;
}

int arreglodinamico::getcapacidad() const {
    return capacidad;
}

void arreglodinamico::limpiar() {
    // Solo reinicia el uso; no libera memoria para poder reusar el bloque.
    cantidad = 0;
}
