#include "torneo.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

static string convertiramayuscula(string texto) {
    string salida = texto;

    for (int i = 0; i < int(salida.size()); i = i + 1) {
        char c = salida[i];
        if (c >= 'a' && c <= 'z') {
            salida[i] = char(c - ('a' - 'A'));
        }
    }

    return salida;
}

static bool eshostmundial(string nombreequipo) {
    string normal = convertiramayuscula(nombreequipo);

    if (normal.find("ESTADOS UNIDOS") != string::npos) {
        return true;
    }

    if (normal.find("UNITED STATES") != string::npos) {
        return true;
    }

    if (normal == "USA") {
        return true;
    }

    return false;
}

Torneo::Torneo() {
    nombretorneo = "UdeAWorldCup";
    grupos = 0;
    cantidadgrupos = 0;
    tabla = 0;
    cantidadfilastabla = 0;
    equiposcargados = 0;
    jugadoresbase = 0;
    cantidadjugadores = 0;
    capacidadjugadores = 0;
    equiposbase = 0;
    confederacionesbase = 0;
    rankingsbase = 0;
    cantidadequiposbase = 0;

    srand(unsigned(time(0)));
}

Torneo::~Torneo() {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }

    if (jugadoresbase != 0) {
        delete[] jugadoresbase;
        jugadoresbase = 0;
    }

    if (equiposbase != 0) {
        delete[] equiposbase;
        equiposbase = 0;
    }

    if (confederacionesbase != 0) {
        delete[] confederacionesbase;
        confederacionesbase = 0;
    }

    if (rankingsbase != 0) {
        delete[] rankingsbase;
        rankingsbase = 0;
    }
}

void Torneo::preparar() {
    iniciargrupos(12);

    // Esto deja una primera estructura para ir llenando grupos despues.
    for (int i = 0; i < cantidadgrupos; i = i + 1) {
        string nombregrupo = "grupo ";
        char letra = char('a' + i);
        nombregrupo = nombregrupo + letra;
        registrargrupobase(i, nombregrupo);
    }

    cout << "torneo base listo: " << nombretorneo << endl;
}

void Torneo::iniciargrupos(int cantidad) {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }

    if (jugadoresbase != 0) {
        delete[] jugadoresbase;
        jugadoresbase = 0;
    }

    if (equiposbase != 0) {
        delete[] equiposbase;
        equiposbase = 0;
    }

    if (confederacionesbase != 0) {
        delete[] confederacionesbase;
        confederacionesbase = 0;
    }

    if (rankingsbase != 0) {
        delete[] rankingsbase;
        rankingsbase = 0;
    }

    int cantidadfinal = cantidad;
    if (cantidadfinal < 0) {
        cantidadfinal = 0;
    }

    cantidadgrupos = cantidadfinal;
    grupos = new grupo[cantidadgrupos];

    cantidadfilastabla = cantidadgrupos * 4;
    tabla = new tablaposiciones[cantidadfilastabla];
    equiposcargados = 0;
    capacidadjugadores = cantidadfilastabla * 15;
    cantidadjugadores = 0;

    if (capacidadjugadores > 0) {
        jugadoresbase = new jugador[capacidadjugadores];
    }

    if (cantidadfilastabla > 0) {
        equiposbase = new string[cantidadfilastabla];
        confederacionesbase = new string[cantidadfilastabla];
        rankingsbase = new int[cantidadfilastabla];

        for (int i = 0; i < cantidadfilastabla; i = i + 1) {
            equiposbase[i] = "";
            confederacionesbase[i] = "";
            rankingsbase[i] = 0;
        }
    }

    cantidadequiposbase = 0;
}

bool Torneo::registrargrupobase(int indice, string nombregrupo) {
    if (indice < 0) {
        return false;
    } else {
        if (indice >= cantidadgrupos) {
            return false;
        }
    }

    grupos[indice].setnombre(nombregrupo);
    return true;
}

bool Torneo::cargarequipotabla(int fila, string nombreequipo) {
    if (fila < 0) {
        return false;
    }

    if (fila >= cantidadfilastabla) {
        return false;
    }

    tabla[fila].cargarequipo(nombreequipo);
    return true;
}

bool Torneo::cargarequipobase(int indice, string nombreequipo) {
    return cargarequipobase(indice, nombreequipo, "", 0);
}

bool Torneo::cargarequipobase(int indice, string nombreequipo, string confederacion, int ranking) {
    if (indice < 0) {
        return false;
    }

    if (indice >= cantidadfilastabla) {
        return false;
    }

    bool okfila = cargarequipotabla(indice, nombreequipo);
    if (okfila == false) {
        return false;
    }

    if (equiposbase == 0 || confederacionesbase == 0 || rankingsbase == 0) {
        return false;
    }

    equiposbase[indice] = nombreequipo;
    confederacionesbase[indice] = confederacion;
    rankingsbase[indice] = ranking;

    if (equiposcargados < indice + 1) {
        equiposcargados = indice + 1;
    }

    if (cantidadequiposbase < indice + 1) {
        cantidadequiposbase = indice + 1;
    }

    return true;
}

int Torneo::getequiposcargados() const {
    return equiposcargados;
}

bool Torneo::cargarjugadorbase(jugador nuevojugador) {
    if (jugadoresbase == 0) {
        return false;
    }

    if (cantidadjugadores >= capacidadjugadores) {
        return false;
    }

    jugadoresbase[cantidadjugadores] = nuevojugador;
    cantidadjugadores = cantidadjugadores + 1;
    return true;
}

int Torneo::getcantidadjugadores() const {
    return cantidadjugadores;
}

int Torneo::getcantidadgrupos() const {
    return cantidadgrupos;
}

void Torneo::ordenarporelranking(int indices[], int total) const {
    for (int i = 0; i < total; i = i + 1) {
        for (int j = i + 1; j < total; j = j + 1) {
            int ai = indices[i];
            int aj = indices[j];

            bool intercambiar = false;
            if (rankingsbase[aj] < rankingsbase[ai]) {
                intercambiar = true;
            }

            if (rankingsbase[aj] == rankingsbase[ai]) {
                if (equiposbase[aj] < equiposbase[ai]) {
                    intercambiar = true;
                }
            }

            if (intercambiar) {
                int temporal = indices[i];
                indices[i] = indices[j];
                indices[j] = temporal;
            }
        }
    }
}

int Torneo::buscarhost(int indices[], int total) const {
    for (int i = 0; i < total; i = i + 1) {
        int indice = indices[i];
        if (eshostmundial(equiposbase[indice])) {
            return indice;
        }
    }

    return -1;
}

void Torneo::barajarbombo(int bombo[], int inicio) const {
    for (int i = inicio; i < 12; i = i + 1) {
        int j = inicio + (rand() % (12 - inicio));
        int temporal = bombo[i];
        bombo[i] = bombo[j];
        bombo[j] = temporal;
    }
}

bool Torneo::intentarsorteo(int bombos[4][12]) {
    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        grupos[g].limpiar();
    }

    for (int b = 0; b < 4; b = b + 1) {
        for (int g = 0; g < cantidadgrupos; g = g + 1) {
            int elegido = -1;

            for (int p = 0; p < 12; p = p + 1) {
                int indiceequipo = bombos[b][p];
                if (indiceequipo < 0) {
                    continue;
                }

                string conf = confederacionesbase[indiceequipo];
                if (grupos[g].puedeagregarconfederacion(conf)) {
                    elegido = p;
                    break;
                }
            }

            if (elegido < 0) {
                return false;
            }

            int indicefinal = bombos[b][elegido];
            grupos[g].agregarequipo(equiposbase[indicefinal], confederacionesbase[indicefinal]);

            for (int mover = elegido; mover < 11; mover = mover + 1) {
                bombos[b][mover] = bombos[b][mover + 1];
            }

            bombos[b][11] = -1;
        }
    }

    return true;
}

bool Torneo::armargruposporranking() {
    if (cantidadgrupos != 12) {
        return false;
    }

    if (cantidadequiposbase < 48) {
        return false;
    }

    int ordenados[48];
    for (int i = 0; i < 48; i = i + 1) {
        ordenados[i] = i;
    }

    ordenarporelranking(ordenados, 48);

    int bombosbase[4][12];
    for (int b = 0; b < 4; b = b + 1) {
        for (int p = 0; p < 12; p = p + 1) {
            bombosbase[b][p] = -1;
        }
    }

    bool usado[48];
    for (int i = 0; i < 48; i = i + 1) {
        usado[i] = false;
    }

    int host = buscarhost(ordenados, 48);
    int cursorb1 = 0;

    if (host >= 0) {
        bombosbase[0][cursorb1] = host;
        usado[host] = true;
        cursorb1 = cursorb1 + 1;
    }

    for (int i = 0; i < 48 && cursorb1 < 12; i = i + 1) {
        int indice = ordenados[i];
        if (usado[indice]) {
            continue;
        }

        bombosbase[0][cursorb1] = indice;
        usado[indice] = true;
        cursorb1 = cursorb1 + 1;
    }

    int bomboactual = 1;
    int posicionactual = 0;

    for (int i = 0; i < 48; i = i + 1) {
        int indice = ordenados[i];
        if (usado[indice]) {
            continue;
        }

        bombosbase[bomboactual][posicionactual] = indice;
        posicionactual = posicionactual + 1;

        if (posicionactual == 12) {
            posicionactual = 0;
            bomboactual = bomboactual + 1;
        }
    }

    bool listo = false;

    for (int intento = 0; intento < 600; intento = intento + 1) {
        int bombosprueba[4][12];

        for (int b = 0; b < 4; b = b + 1) {
            for (int p = 0; p < 12; p = p + 1) {
                bombosprueba[b][p] = bombosbase[b][p];
            }
        }

        barajarbombo(bombosprueba[0], 1);
        barajarbombo(bombosprueba[1], 0);
        barajarbombo(bombosprueba[2], 0);
        barajarbombo(bombosprueba[3], 0);

        if (intentarsorteo(bombosprueba)) {
            listo = true;
            break;
        }
    }

    if (listo == false) {
        return false;
    }

    int fila = 0;
    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        for (int e = 0; e < grupos[g].getcantidad(); e = e + 1) {
            cargarequipotabla(fila, grupos[g].getequipo(e));
            fila = fila + 1;
        }
    }

    return true;
}

void Torneo::mostrargrupos() const {
    cout << "grupos del torneo" << endl;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        cout << grupos[g].getnombre() << endl;

        for (int e = 0; e < grupos[g].getcantidad(); e = e + 1) {
            cout << "  - " << grupos[g].getequipo(e);
            cout << " (" << grupos[g].getconfederacion(e) << ")" << endl;
        }
    }
}
