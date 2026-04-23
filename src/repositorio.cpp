#include "repositorio.h"

#include <fstream>
#include <iostream>

using namespace std;

static int partirlinea(string linea, string campos[], int maxcampos) {
    int usados = 0;
    string actual = "";

    for (int i = 0; i < int(linea.size()); i = i + 1) {
        char c = linea[i];

        if (c == ';') {
            if (usados < maxcampos) {
                campos[usados] = actual;
                usados = usados + 1;
            }

            actual = "";
        } else {
            actual = actual + c;
        }
    }

    if (usados < maxcampos) {
        campos[usados] = actual;
        usados = usados + 1;
    }

    return usados;
}

Repositorio::Repositorio() {
    filascsv = 0;
    columnascsv = 0;
    rutacsv = "";
}

void Repositorio::cargarBase() {
    bool ok = leercsvequipos("../../../selecciones_clasificadas_mundial.csv");

    if (ok) {
        cout << "csv ok -> filas: " << filascsv << ", columnas: " << columnascsv << endl;
    } else {
        cout << "no encontre el csv" << endl;
    }
}

bool Repositorio::leercsvequipos(string ruta) {
    ifstream archivo(ruta.c_str());
    if (archivo.is_open() == false) {
        return false;
    }

    filascsv = 0;
    columnascsv = 0;
    rutacsv = ruta;

    string linea = "";

    // linea 1: titulo
    if (getline(archivo, linea) == false) {
        archivo.close();
        return true;
    }

    // linea 2: encabezado real
    if (getline(archivo, linea)) {
        string campos[40];
        columnascsv = partirlinea(linea, campos, 40);
    } else {
        archivo.close();
        return true;
    }

    // desde linea 3: datos de equipos
    while (getline(archivo, linea)) {
        if (linea.size() == 0) {
            continue;
        }

        filascsv = filascsv + 1;
    }

    archivo.close();
    return true;
}

int Repositorio::getfilascsv() const {
    return filascsv;
}

int Repositorio::getcolumnascsv() const {
    return columnascsv;
}
