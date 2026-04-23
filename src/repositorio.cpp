#include "repositorio.h"

#include <fstream>
#include <iostream>

using namespace std;

static int textoaentero(string texto) {
    int inicio = 0;
    int fin = int(texto.size());

    while (inicio < fin) {
        char c = texto[inicio];
        if (c == ' ') {
            inicio = inicio + 1;
        } else {
            break;
        }
    }

    while (fin > inicio) {
        char c = texto[fin - 1];
        if (c == ' ') {
            fin = fin - 1;
        } else {
            break;
        }
    }

    int valor = 0;
    for (int i = inicio; i < fin; i = i + 1) {
        char c = texto[i];
        if (c < '0') {
            break;
        }

        if (c > '9') {
            break;
        }

        valor = (valor * 10) + int(c - '0');
    }

    return valor;
}

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
    cantidadequipos = 0;
    rutacsv = "";

    for (int i = 0; i < maxequipos; i = i + 1) {
        equiposcsv[i] = "";
        confederacionescsv[i] = "";
        rankingscsv[i] = 0;
    }
}

void Repositorio::cargarBase() {
    bool ok = leercsvequipos("../../../selecciones_clasificadas_mundial.csv");

    if (ok) {
        cout << "csv ok -> filas: " << filascsv << ", columnas: " << columnascsv;
        cout << ", equipos: " << cantidadequipos << endl;
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
    cantidadequipos = 0;
    rutacsv = ruta;

    for (int i = 0; i < maxequipos; i = i + 1) {
        equiposcsv[i] = "";
        confederacionescsv[i] = "";
        rankingscsv[i] = 0;
    }

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

        string campos[40];
        int totalcampos = partirlinea(linea, campos, 40);

        bool filavalida = true;
        if (totalcampos < 5) {
            filavalida = false;
        }

        if (cantidadequipos >= maxequipos) {
            filavalida = false;
        }

        if (filavalida) {
            int pos = cantidadequipos;
            rankingscsv[pos] = textoaentero(campos[0]);
            equiposcsv[pos] = campos[1];
            confederacionescsv[pos] = campos[4];
            cantidadequipos = pos + 1;
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

int Repositorio::getcantidadequipos() const {
    return cantidadequipos;
}

string Repositorio::getequipo(int indice) const {
    if (indice < 0) {
        return "";
    }

    if (indice >= cantidadequipos) {
        return "";
    }

    return equiposcsv[indice];
}

string Repositorio::getconfederacion(int indice) const {
    if (indice < 0) {
        return "";
    }

    if (indice >= cantidadequipos) {
        return "";
    }

    return confederacionescsv[indice];
}

int Repositorio::getranking(int indice) const {
    if (indice < 0) {
        return 0;
    }

    if (indice >= cantidadequipos) {
        return 0;
    }

    return rankingscsv[indice];
}
