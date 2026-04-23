#include "matrizdinamica.h"

matrizdinamica::matrizdinamica() {
    datos = 0;
    filas = 0;
    columnas = 0;
}

matrizdinamica::matrizdinamica(int filasbase, int columnasbase) {
    datos = 0;
    filas = 0;
    columnas = 0;

    bool tamanosirve = true;

    if (filasbase <= 0) {
        tamanosirve = false;
    }

    if (columnasbase <= 0) {
        tamanosirve = false;
    }

    if (tamanosirve) {
        redimensionar(filasbase, columnasbase);
    }
}

matrizdinamica::~matrizdinamica() {
    if (datos != 0) {
        delete[] datos;
        datos = 0;
    }

    filas = 0;
    columnas = 0;
}

bool matrizdinamica::redimensionar(int nuevasfilas, int nuevascolumnas) {
    bool medidasok = true;

    if (nuevasfilas <= 0) {
        medidasok = false;
    } else {
        if (nuevascolumnas <= 0) {
            medidasok = false;
        }
    }

    if (medidasok == false) {
        return false;
    }

    int total = nuevasfilas * nuevascolumnas;
    int* bloque = new int[total];

    for (int i = 0; i < total; i = i + 1) {
        bloque[i] = 0;
    }

    if (datos != 0) {
        delete[] datos;
    }

    datos = bloque;
    filas = nuevasfilas;
    columnas = nuevascolumnas;
    return true;
}

void matrizdinamica::limpiar() {
    if (datos == 0) {
        return;
    } else {
        int total = filas * columnas;
        for (int i = 0; i < total; i = i + 1) {
            datos[i] = 0;
        }
    }
}

int matrizdinamica::getfilas() const {
    return filas;
}

int matrizdinamica::getcolumnas() const {
    return columnas;
}

bool matrizdinamica::setvalor(int fila, int columna, int valor) {
    int indice = -1;

    if (posicionvalida(fila, columna)) {
        indice = calcularindice(fila, columna);
    } else {
        indice = -1;
    }

    if (indice < 0) {
        return false;
    } else {
        datos[indice] = valor;
        return true;
    }
}

int matrizdinamica::getvalor(int fila, int columna) const {
    int valor = 0;

    if (posicionvalida(fila, columna)) {
        int indice = calcularindice(fila, columna);
        valor = datos[indice];
    } else {
        valor = 0;
    }

    return valor;
}

int matrizdinamica::calcularindice(int fila, int columna) const {
    int basefila = fila * columnas;
    return basefila + columna;
}

bool matrizdinamica::posicionvalida(int fila, int columna) const {
    bool sirve = true;

    if (fila < 0) {
        sirve = false;
    }

    if (columna < 0) {
        sirve = false;
    }

    if (sirve) {
        if (fila >= filas) {
            sirve = false;
        }

        if (columna >= columnas) {
            sirve = false;
        }
    }

    return sirve;
}