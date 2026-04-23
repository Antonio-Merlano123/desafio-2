#include "listasimple.h"

listasimple::listasimple() {
    cabeza = 0;
    cantidad = 0;
}

listasimple::~listasimple() {
    nodo* actual = cabeza;

    while (actual != 0) {
        nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    cabeza = 0;
    cantidad = 0;
}

void listasimple::agregar(string valor) {
    nodo* nuevo = new nodo(valor);

    if (cabeza == 0) {
        cabeza = nuevo;
        cantidad = cantidad + 1;
        return;
    }

    nodo* cursor = cabeza;
    while (cursor->siguiente != 0) {
        cursor = cursor->siguiente;
    }

    cursor->siguiente = nuevo;
    cantidad = cantidad + 1;
}

string listasimple::obtener(int pos) const {
    if (pos < 0) {
        return "";
    }

    if (pos >= cantidad) {
        return "";
    }

    nodo* cursor = cabeza;
    int i = 0;

    while (i < pos) {
        cursor = cursor->siguiente;
        i = i + 1;
    }

    return cursor->dato;
}

void listasimple::eliminar(int pos) {
    bool posvalida = true;

    if (pos < 0) {
        posvalida = false;
    } else {
        if (pos >= cantidad) {
            posvalida = false;
        }
    }

    if (posvalida == false) {
        return;
    }

    if (pos == 0) {
        nodo* viejo = cabeza;
        cabeza = cabeza->siguiente;
        delete viejo;
        cantidad = cantidad - 1;
        return;
    } else {
        nodo* anterior = cabeza;
        int paso = 0;

        // avanzo hasta el nodo justo antes del que toca borrar
        while (paso < pos - 1) {
            anterior = anterior->siguiente;
            paso = paso + 1;
        }

        nodo* borrar = anterior->siguiente;
        anterior->siguiente = borrar->siguiente;
        delete borrar;
        cantidad = cantidad - 1;
    }
}

bool listasimple::estavacia() const {
    return cantidad == 0;
}

int listasimple::getcantidad() const {
    return cantidad;
}
