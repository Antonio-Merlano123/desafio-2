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
    partidosgrupos = 0;
    diapartidosgrupos = 0;
    cantidadpartidosgrupos = 0;
    capacidadpartidosgrupos = 0;

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

    if (partidosgrupos != 0) {
        delete[] partidosgrupos;
        partidosgrupos = 0;
    }

    if (diapartidosgrupos != 0) {
        delete[] diapartidosgrupos;
        diapartidosgrupos = 0;
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

    if (partidosgrupos != 0) {
        delete[] partidosgrupos;
        partidosgrupos = 0;
    }

    if (diapartidosgrupos != 0) {
        delete[] diapartidosgrupos;
        diapartidosgrupos = 0;
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
    cantidadpartidosgrupos = 0;
    capacidadpartidosgrupos = cantidadgrupos * 6;

    if (capacidadpartidosgrupos > 0) {
        partidosgrupos = new partido[capacidadpartidosgrupos];
        diapartidosgrupos = new int[capacidadpartidosgrupos];

        for (int i = 0; i < capacidadpartidosgrupos; i = i + 1) {
            diapartidosgrupos[i] = -1;
        }
    }
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

int Torneo::buscarindiceequipo(string nombreequipo) const {
    for (int i = 0; i < cantidadequiposbase; i = i + 1) {
        if (equiposbase[i] == nombreequipo) {
            return i;
        }
    }

    return -1;
}

int Torneo::buscarjugadoresdelequipo(string nombreequipo, int indices[], int maxindices) const {
    if (jugadoresbase == 0) {
        return 0;
    }

    int guardados = 0;

    for (int i = 0; i < cantidadjugadores; i = i + 1) {
        if (jugadoresbase[i].getequipo() != nombreequipo) {
            continue;
        }

        if (guardados < maxindices) {
            indices[guardados] = i;
            guardados = guardados + 1;
        }
    }

    return guardados;
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

bool Torneo::generarcalendarioconlimite(int maxpartidospordia, int descansominimo) {
    if (partidosgrupos == 0 || diapartidosgrupos == 0) {
        return false;
    }

    int pordia[17];
    for (int i = 0; i < 17; i = i + 1) {
        pordia[i] = 0;
    }

    int ultimodia[48];
    for (int i = 0; i < 48; i = i + 1) {
        ultimodia[i] = -100;
    }

    cantidadpartidosgrupos = 0;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        if (grupos[g].getcantidad() != 4) {
            return false;
        }

        string e0 = grupos[g].getequipo(0);
        string e1 = grupos[g].getequipo(1);
        string e2 = grupos[g].getequipo(2);
        string e3 = grupos[g].getequipo(3);

        string local[6];
        string visita[6];

        local[0] = e0; visita[0] = e1;
        local[1] = e2; visita[1] = e3;
        local[2] = e0; visita[2] = e2;
        local[3] = e1; visita[3] = e3;
        local[4] = e0; visita[4] = e3;
        local[5] = e1; visita[5] = e2;

        for (int m = 0; m < 6; m = m + 1) {
            int ilocal = buscarindiceequipo(local[m]);
            int ivisita = buscarindiceequipo(visita[m]);

            if (ilocal < 0 || ivisita < 0) {
                return false;
            }

            int diaelegido = -1;

            for (int dia = 0; dia < 17; dia = dia + 1) {
                if (pordia[dia] >= maxpartidospordia) {
                    continue;
                }

                int descansolocal = dia - ultimodia[ilocal];
                int descansovisita = dia - ultimodia[ivisita];

                if (descansolocal < descansominimo) {
                    continue;
                }

                if (descansovisita < descansominimo) {
                    continue;
                }

                diaelegido = dia;
                break;
            }

            if (diaelegido < 0) {
                return false;
            }

            if (cantidadpartidosgrupos >= capacidadpartidosgrupos) {
                return false;
            }

            partidosgrupos[cantidadpartidosgrupos] = partido(local[m], visita[m]);
            diapartidosgrupos[cantidadpartidosgrupos] = diaelegido;
            cantidadpartidosgrupos = cantidadpartidosgrupos + 1;

            pordia[diaelegido] = pordia[diaelegido] + 1;
            ultimodia[ilocal] = diaelegido;
            ultimodia[ivisita] = diaelegido;
        }
    }

    return true;
}

bool Torneo::generarcalendariogrupos() {
    bool okestricto = generarcalendarioconlimite(4, 3);
    if (okestricto) {
        return true;
    }

    bool okintermedio = generarcalendarioconlimite(5, 3);
    if (okintermedio) {
        return true;
    }

    return generarcalendarioconlimite(5, 2);
}

bool Torneo::elegironceinicial(string nombreequipo, jugador once[11]) const {
    int indices[32];
    int cantidad = buscarjugadoresdelequipo(nombreequipo, indices, 32);

    if (cantidad < 11) {
        return false;
    }

    for (int i = 0; i < cantidad; i = i + 1) {
        int j = i + (rand() % (cantidad - i));
        int temporal = indices[i];
        indices[i] = indices[j];
        indices[j] = temporal;
    }

    for (int i = 0; i < 11; i = i + 1) {
        once[i] = jugadoresbase[indices[i]];
    }

    return true;
}

void Torneo::mostrarcalendariogrupos() const {
    if (cantidadpartidosgrupos <= 0) {
        return;
    }

    cout << "calendario fase de grupos" << endl;

    for (int dia = 0; dia < 17; dia = dia + 1) {
        bool tienepartidos = false;

        for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
            if (diapartidosgrupos[i] == dia) {
                tienepartidos = true;
                break;
            }
        }

        if (tienepartidos == false) {
            continue;
        }

        cout << "dia " << (dia + 1) << endl;

        for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
            if (diapartidosgrupos[i] != dia) {
                continue;
            }

            cout << "  - " << partidosgrupos[i].getlocal();
            cout << " vs " << partidosgrupos[i].getvisita() << endl;
        }
    }
}

void Torneo::mostraronceprueba() const {
    if (cantidadpartidosgrupos <= 0) {
        return;
    }

    string local = partidosgrupos[0].getlocal();
    string visita = partidosgrupos[0].getvisita();

    jugador oncelocal[11];
    jugador oncevisita[11];

    bool oklocal = elegironceinicial(local, oncelocal);
    bool okvisita = elegironceinicial(visita, oncevisita);

    if (oklocal == false || okvisita == false) {
        cout << "once inicial prueba: fallo" << endl;
        return;
    }

    cout << "once inicial prueba" << endl;
    cout << "  partido: " << local << " vs " << visita << endl;

    cout << "  titulares " << local << ":" << endl;
    for (int i = 0; i < 11; i = i + 1) {
        cout << "    - " << oncelocal[i].getnombre();
        cout << " (" << oncelocal[i].getposicion() << ")" << endl;
    }

    cout << "  titulares " << visita << ":" << endl;
    for (int i = 0; i < 11; i = i + 1) {
        cout << "    - " << oncevisita[i].getnombre();
        cout << " (" << oncevisita[i].getposicion() << ")" << endl;
    }
}
