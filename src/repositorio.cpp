#include "repositorio.h"

#include <fstream>
#include <iostream>

using namespace std;

static string quitarsaltos(string texto) {
    // limpio \r y \n pa evitar basura al parsear
    string limpio = "";

    for (int i = 0; i < int(texto.size()); i = i + 1) {
        char c = texto[i];

        if (c == '\r') {
            continue;
        }

        if (c == '\n') {
            continue;
        }

        limpio = limpio + c;
    }

    return limpio;
}

static string quitarlados(string texto) {
    // trim basico con while, sin librerias extras
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

    string limpio = "";
    for (int i = inicio; i < fin; i = i + 1) {
        limpio = limpio + texto[i];
    }

    return limpio;
}

static string normalizarconfederacion(string texto) {
    // estandarizo nombres que a veces vienen distinto
    string limpio = quitarlados(quitarsaltos(texto));

    if (limpio == "UEFA") {
        return "UEFA";
    }

    if (limpio == "CONMEBOL") {
        return "CONMEBOL";
    }

    if (limpio == "AFC") {
        return "AFC";
    }

    if (limpio == "CAF") {
        return "CAF";
    }

    if (limpio == "Concacaf") {
        return "CONCACAF";
    }

    if (limpio == "CONCACAF") {
        return "CONCACAF";
    }

    return limpio;
}

static int textoaentero(string texto) {
    // conversion simple, corta al primer char no numerico
    string limpio = quitarlados(texto);
    int inicio = 0;
    int fin = int(limpio.size());

    int valor = 0;
    for (int i = inicio; i < fin; i = i + 1) {
        char c = limpio[i];
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
    // separador del csv: punto y coma
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
    cantidadjugadores = 0;
    rutacsv = "";

    for (int i = 0; i < maxequipos; i = i + 1) {
        equiposcsv[i] = "";
        confederacionescsv[i] = "";
        rankingscsv[i] = 0;
        golesfavorhistorico[i] = 0.0;
        golescontrahistorico[i] = 0.0;
        inicioplantillas[i] = -1;
        cantidadplantillas[i] = 0;
    }
}

void Repositorio::cargarBase() {
    //  rutas tipicas de qt
    bool ok = leercsvequipos("../../selecciones_clasificadas_mundial.csv");

    if (ok == false) {
        ok = leercsvequipos("../../../selecciones_clasificadas_mundial.csv");
    }

    if (ok == false) {
        ok = leercsvequipos("selecciones_clasificadas_mundial.csv");
    }

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
    cantidadjugadores = 0;
    rutacsv = ruta;

    for (int i = 0; i < maxequipos; i = i + 1) {
        equiposcsv[i] = "";
        confederacionescsv[i] = "";
        rankingscsv[i] = 0;
        golesfavorhistorico[i] = 0.0;
        golescontrahistorico[i] = 0.0;
        inicioplantillas[i] = -1;
        cantidadplantillas[i] = 0;
    }

    string linea = "";

    // linea 1: titulo
    if (!getline(archivo, linea)) {
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
        if (totalcampos < 10) {
            filavalida = false;
        }

        if (cantidadequipos >= maxequipos) {
            filavalida = false;
        }

        if (filavalida) {
            int pos = cantidadequipos;
            rankingscsv[pos] = textoaentero(campos[0]);
            equiposcsv[pos] = quitarlados(campos[1]);
            confederacionescsv[pos] = normalizarconfederacion(campos[4]);

            int golesfavor = textoaentero(campos[5]);
            int golescontra = textoaentero(campos[6]);
            int ganados = textoaentero(campos[7]);
            int empatados = textoaentero(campos[8]);
            int perdidos = textoaentero(campos[9]);
            // saco promedios historicos de gol por partido
            int partidos = ganados + empatados + perdidos;

            if (partidos <= 0) {
                partidos = 1;
            }

            golesfavorhistorico[pos] = double(golesfavor) / double(partidos);
            golescontrahistorico[pos] = double(golescontra) / double(partidos);
            cantidadequipos = pos + 1;
        }

        filascsv = filascsv + 1;
    }

    archivo.close();
    armarplantillasbase();
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

int Repositorio::getcantidadjugadores() const {
    return cantidadjugadores;
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

double Repositorio::getgolesfavorhistorico(int indice) const {
    if (indice < 0) {
        return 0.0;
    }

    if (indice >= cantidadequipos) {
        return 0.0;
    }

    return golesfavorhistorico[indice];
}

double Repositorio::getgolescontrahistorico(int indice) const {
    if (indice < 0) {
        return 0.0;
    }

    if (indice >= cantidadequipos) {
        return 0.0;
    }

    return golescontrahistorico[indice];
}

jugador Repositorio::getjugador(int indice) const {
    if (indice < 0) {
        return jugador();
    }

    if (indice >= cantidadjugadores) {
        return jugador();
    }

    return jugadorescsv[indice];
}

void Repositorio::armarplantillasbase() {
    // genero 15 jugadores por equipo
    cantidadjugadores = 0;

    for (int i = 0; i < cantidadequipos; i = i + 1) {
        inicioplantillas[i] = cantidadjugadores;
        cantidadplantillas[i] = 0;
        int q = 0;
        while (q < 2) {
            int camiseta = q + 1;
            string nombre = "nombre" + to_string(camiseta) + " apellido" + to_string(camiseta);
            agregarjugadorbase(i, nombre, "arquero");
            q = q + 1;
        }

        int d = 0;
        while (d < 5) {
            int camiseta = d + 3;
            string nombre = "nombre" + to_string(camiseta) + " apellido" + to_string(camiseta);
            agregarjugadorbase(i, nombre, "defensa");
            d = d + 1;
        }

        int v = 0;
        while (v < 5) {
            int camiseta = v + 8;
            string nombre = "nombre" + to_string(camiseta) + " apellido" + to_string(camiseta);
            agregarjugadorbase(i, nombre, "volante");
            v = v + 1;
        }

        int f = 0;
        while (f < 3) {
            int camiseta = f + 13;
            string nombre = "nombre" + to_string(camiseta) + " apellido" + to_string(camiseta);
            agregarjugadorbase(i, nombre, "delantero");
            f = f + 1;
        }
        int golesbase = calculargolesbase(rankingscsv[i]);
        repartirgolesbase(i, golesbase);
    }
}

bool Repositorio::agregarjugadorbase(int indiceequipo, string nombrejugador, string posicion) {
    if (indiceequipo < 0) {
        return false;
    }

    if (indiceequipo >= cantidadequipos) {
        return false;
    }

    if (cantidadjugadores >= maxjugadores) {
        return false;
    }

    int camiseta = cantidadplantillas[indiceequipo] + 1;
    jugador nuevo(nombrejugador, equiposcsv[indiceequipo], posicion, camiseta);
    jugadorescsv[cantidadjugadores] = nuevo;
    cantidadjugadores = cantidadjugadores + 1;
    cantidadplantillas[indiceequipo] = cantidadplantillas[indiceequipo] + 1;
    return true;
}

void Repositorio::repartirgolesbase(int indiceequipo, int golesbase) {
    if (indiceequipo < 0) {
        return;
    }

    if (indiceequipo >= cantidadequipos) {
        return;
    }

    int inicio = inicioplantillas[indiceequipo];
    int cantidad = cantidadplantillas[indiceequipo];
    if (inicio < 0 || cantidad <= 0) {
        return;
    }

    if (golesbase <= 0) {
        return;
    }

    // reparto parejo y lo que sobra se va desde el inicio
    int base = golesbase / cantidad;
    int sobrantes = golesbase % cantidad;

    for (int i = 0; i < cantidad; i = i + 1) {
        int actual = inicio + i;

        for (int j = 0; j < base; j = j + 1) {
            jugadorescsv[actual].agregargol();
        }

        if (i < sobrantes) {
            jugadorescsv[actual].agregargol();
        }
    }

    // asistencias base para que no arranquen todos en 0
    for (int i = 0; i < golesbase; i = i + 1) {
        int apoyo = inicio + ((i + 1) % cantidad);
        jugadorescsv[apoyo].agregarasistencia();
    }
}

int Repositorio::calculargolesbase(int ranking) const {
    if (ranking <= 0) {
        return 4;
    }

    if (ranking <= 8) {
        return 6;
    }

    if (ranking <= 20) {
        return 5;
    }

    return 4;
}
