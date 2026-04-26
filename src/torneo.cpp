#include "torneo.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "repositorio.h"

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
    cantclasificados1 = 0;
    cantclasificados2 = 0;
    cantclasificados3 = 0;
    partidosdieciseisavos = 0;
    cantdieciseisavos = 0;
    partidosoctavos = 0;
    cantoctavos = 0;
    partidoscuartos = 0;
    cantcuartos = 0;
    partidossemis = 0;
    cantsemis = 0;
    equipocampeon = "";
    equiposubcampeon = "";
    equipotercero = "";
    equipocuarto = "";
    finalessimuladas = false;

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

    if (partidosdieciseisavos != 0) {
        delete[] partidosdieciseisavos;
        partidosdieciseisavos = 0;
    }

    if (partidosoctavos != 0) {
        delete[] partidosoctavos;
        partidosoctavos = 0;
    }

    if (partidoscuartos != 0) {
        delete[] partidoscuartos;
        partidoscuartos = 0;
    }

    if (partidossemis != 0) {
        delete[] partidossemis;
        partidossemis = 0;
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

int Torneo::buscarfilatabla(string nombreequipo) const {
    for (int i = 0; i < cantidadfilastabla; i = i + 1) {
        if (tabla[i].getnombre() == nombreequipo) {
            return i;
        }
    }

    return -1;
}

int Torneo::buscarindiceequiporepo(const Repositorio& repo, string nombreequipo) const {
    int total = repo.getcantidadequipos();

    for (int i = 0; i < total; i = i + 1) {
        if (repo.getequipo(i) == nombreequipo) {
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

double Torneo::calcularlambdapartido(double golesfavora, double golescontrab) const {
    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    double gfa = golesfavora;
    double gcb = golescontrab;

    if (gfa <= 0.0) {
        gfa = mu;
    }

    if (gcb <= 0.0) {
        gcb = mu;
    }

    double factorataque = pow(gfa / mu, alpha);
    double factordefensa = pow(gcb / mu, beta);
    double lambda = mu * factorataque * factordefensa;

    if (lambda < 0.2) {
        lambda = 0.2;
    }

    return lambda;
}

int Torneo::redondeargolespartido(double lambda) const {
    int goles = int(lambda + 0.5);

    if (goles < 0) {
        goles = 0;
    }

    return goles;
}

void Torneo::ordenarfilasgrupo(int filas[4]) const {
    for (int i = 0; i < 4; i = i + 1) {
        for (int j = i + 1; j < 4; j = j + 1) {
            int fi = filas[i];
            int fj = filas[j];

            bool intercambiar = false;

            if (tabla[fj].getpuntos() > tabla[fi].getpuntos()) {
                intercambiar = true;
            } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                if (tabla[fj].getdiferencia() > tabla[fi].getdiferencia()) {
                    intercambiar = true;
                } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                    if (tabla[fj].getgolesfavor() > tabla[fi].getgolesfavor()) {
                        intercambiar = true;
                    } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                        if (tabla[fj].getnombre() < tabla[fi].getnombre()) {
                            intercambiar = true;
                        }
                    }
                }
            }

            if (intercambiar) {
                int temporal = filas[i];
                filas[i] = filas[j];
                filas[j] = temporal;
            }
        }
    }
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

bool Torneo::simularfasegrupos(const Repositorio& repo) {
    if (cantidadpartidosgrupos <= 0) {
        return false;
    }

    for (int i = 0; i < cantidadfilastabla; i = i + 1) {
        string nombre = tabla[i].getnombre();
        if (nombre != "") {
            tabla[i].cargarequipo(nombre);
        }
    }

    for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
        string local = partidosgrupos[i].getlocal();
        string visita = partidosgrupos[i].getvisita();

        int ilocalrepo = buscarindiceequiporepo(repo, local);
        int ivisitarepo = buscarindiceequiporepo(repo, visita);
        int ilocaltabla = buscarfilatabla(local);
        int ivisitatabla = buscarfilatabla(visita);

        if (ilocalrepo < 0 || ivisitarepo < 0) {
            return false;
        }

        if (ilocaltabla < 0 || ivisitatabla < 0) {
            return false;
        }

        double gflocal = repo.getgolesfavorhistorico(ilocalrepo);
        double gclocal = repo.getgolescontrahistorico(ilocalrepo);
        double gfvisita = repo.getgolesfavorhistorico(ivisitarepo);
        double gcvisita = repo.getgolescontrahistorico(ivisitarepo);

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);

        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        partidosgrupos[i].setresultado(goleslocal, golesvisita);

        tabla[ilocaltabla].sumargoles(goleslocal, golesvisita);
        tabla[ivisitatabla].sumargoles(golesvisita, goleslocal);

        if (goleslocal > golesvisita) {
            tabla[ilocaltabla].sumarganado();
            tabla[ivisitatabla].sumarperdido();
        } else if (goleslocal < golesvisita) {
            tabla[ivisitatabla].sumarganado();
            tabla[ilocaltabla].sumarperdido();
        } else {
            tabla[ilocaltabla].sumarempate();
            tabla[ivisitatabla].sumarempate();
        }
    }

    return true;
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

void Torneo::mostrartablagrupos() const {
    cout << "tabla fase de grupos" << endl;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        int filas[4];

        for (int e = 0; e < 4; e = e + 1) {
            filas[e] = buscarfilatabla(grupos[g].getequipo(e));
        }

        bool completo = true;
        for (int e = 0; e < 4; e = e + 1) {
            if (filas[e] < 0) {
                completo = false;
            }
        }

        if (completo == false) {
            continue;
        }

        ordenarfilasgrupo(filas);

        cout << grupos[g].getnombre() << endl;
        for (int i = 0; i < 4; i = i + 1) {
            int f = filas[i];
            cout << "  " << (i + 1) << ". " << tabla[f].getnombre();
            cout << " | pts " << tabla[f].getpuntos();
            cout << " | pj " << tabla[f].getpartidos();
            cout << " | gf " << tabla[f].getgolesfavor();
            cout << " | gc " << tabla[f].getgolescontra();
            cout << " | dif " << tabla[f].getdiferencia() << endl;
        }
    }
}

void Torneo::clasificargrupos() {
    cantclasificados1 = 0;
    cantclasificados2 = 0;
    cantclasificados3 = 0;

    int filasterceros[12];
    int grupoterceros[12];
    int cantfilasterceros = 0;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        int filas[4];
        bool completo = true;

        for (int e = 0; e < 4; e = e + 1) {
            filas[e] = buscarfilatabla(grupos[g].getequipo(e));
            if (filas[e] < 0) {
                completo = false;
            }
        }

        if (completo == false) {
            continue;
        }

        ordenarfilasgrupo(filas);

        if (cantclasificados1 < 12) {
            clasificados1[cantclasificados1] = tabla[filas[0]].getnombre();
            cantclasificados1 = cantclasificados1 + 1;
        }

        if (cantclasificados2 < 12) {
            clasificados2[cantclasificados2] = tabla[filas[1]].getnombre();
            cantclasificados2 = cantclasificados2 + 1;
        }

        if (cantfilasterceros < 12) {
            filasterceros[cantfilasterceros] = filas[2];
            grupoterceros[cantfilasterceros] = g;
            cantfilasterceros = cantfilasterceros + 1;
        }
    }

    // ordenar terceros por puntos, diferencia, goles favor, nombre
    for (int i = 0; i < cantfilasterceros; i = i + 1) {
        for (int j = i + 1; j < cantfilasterceros; j = j + 1) {
            int fi = filasterceros[i];
            int fj = filasterceros[j];
            bool intercambiar = false;

            if (tabla[fj].getpuntos() > tabla[fi].getpuntos()) {
                intercambiar = true;
            } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                if (tabla[fj].getdiferencia() > tabla[fi].getdiferencia()) {
                    intercambiar = true;
                } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                    if (tabla[fj].getgolesfavor() > tabla[fi].getgolesfavor()) {
                        intercambiar = true;
                    } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                        if (tabla[fj].getnombre() < tabla[fi].getnombre()) {
                            intercambiar = true;
                        }
                    }
                }
            }

            if (intercambiar) {
                int temporal = filasterceros[i];
                filasterceros[i] = filasterceros[j];
                filasterceros[j] = temporal;

                int tempg = grupoterceros[i];
                grupoterceros[i] = grupoterceros[j];
                grupoterceros[j] = tempg;
            }
        }
    }

    int limite = cantfilasterceros < 8 ? cantfilasterceros : 8;
    for (int i = 0; i < limite; i = i + 1) {
        clasificados3[i] = tabla[filasterceros[i]].getnombre();
        grupoindterceros[i] = grupoterceros[i];
    }
    cantclasificados3 = limite;
}

void Torneo::mostrarclasificados() const {
    cout << "clasificados fase de grupos" << endl;

    cout << "primeros de grupo (12):" << endl;
    for (int i = 0; i < cantclasificados1; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados1[i] << endl;
    }

    cout << "segundos de grupo (12):" << endl;
    for (int i = 0; i < cantclasificados2; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados2[i] << endl;
    }

    cout << "mejores terceros (8):" << endl;
    for (int i = 0; i < cantclasificados3; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados3[i] << endl;
    }
}

void Torneo::armardieciseisavos() {
    // regla del enunciado:
    // 1) cabezas de grupo vs terceros
    // 2) resto cabezas vs 4 peores segundos
    // 3) resto de segundos entre si
    int total = cantclasificados1 + cantclasificados2 + cantclasificados3;
    if (cantclasificados1 != 12 || cantclasificados2 != 12 || cantclasificados3 != 8 || total != 32) {
        cout << "armado dieciseisavos: clasificacion incompleta" << endl;
        return;
    }

    int peoressegundos[12];
    for (int i = 0; i < 12; i = i + 1) {
        peoressegundos[i] = i;
    }

    // ordenar segundos de peor a mejor para escoger los 4 peores
    for (int i = 0; i < 12; i = i + 1) {
        for (int j = i + 1; j < 12; j = j + 1) {
            int fi = buscarfilatabla(clasificados2[peoressegundos[i]]);
            int fj = buscarfilatabla(clasificados2[peoressegundos[j]]);

            bool intercambiar = false;
            if (fi >= 0 && fj >= 0) {
                if (tabla[fj].getpuntos() < tabla[fi].getpuntos()) {
                    intercambiar = true;
                } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                    if (tabla[fj].getdiferencia() < tabla[fi].getdiferencia()) {
                        intercambiar = true;
                    } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                        if (tabla[fj].getgolesfavor() < tabla[fi].getgolesfavor()) {
                            intercambiar = true;
                        } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                            if (tabla[fj].getnombre() < tabla[fi].getnombre()) {
                                intercambiar = true;
                            }
                        }
                    }
                }
            }

            if (intercambiar) {
                int t = peoressegundos[i];
                peoressegundos[i] = peoressegundos[j];
                peoressegundos[j] = t;
            }
        }
    }

    int terceros[8];
    int peores4[4];
    int usadossegundo[12];
    int usadostercero[8];

    for (int i = 0; i < 12; i = i + 1) {
        usadossegundo[i] = 0;
    }
    for (int i = 0; i < 8; i = i + 1) {
        terceros[i] = i;
        usadostercero[i] = 0;
    }
    for (int i = 0; i < 4; i = i + 1) {
        peores4[i] = peoressegundos[i];
        usadossegundo[peores4[i]] = 2; // marca especial: peor segundo
    }

    // una mezcla simple para no dejar cruces tan previsibles
    for (int i = 7; i > 0; i = i - 1) {
        int j = rand() % (i + 1);
        int t = terceros[i];
        terceros[i] = terceros[j];
        terceros[j] = t;
    }
    for (int i = 3; i > 0; i = i - 1) {
        int j = rand() % (i + 1);
        int t = peores4[i];
        peores4[i] = peores4[j];
        peores4[j] = t;
    }

    string locales[16];
    string visitas[16];
    int gruposlocal[16];
    int gruposvisita[16];
    int partidosarmados = 0;

    // (1) 8 cabezas vs 8 terceros
    for (int i = 0; i < 8; i = i + 1) {
        int grupohead = i;
        int elegido = -1;

        for (int t = 0; t < 8; t = t + 1) {
            int idtercero = terceros[t];
            if (usadostercero[idtercero] == 1) {
                continue;
            }
            if (grupoindterceros[idtercero] != grupohead) {
                elegido = idtercero;
                break;
            }
        }

        if (elegido < 0) {
            for (int t = 0; t < 8; t = t + 1) {
                int idtercero = terceros[t];
                if (usadostercero[idtercero] == 0) {
                    elegido = idtercero;
                    break;
                }
            }
        }

        locales[partidosarmados] = clasificados1[i];
        visitas[partidosarmados] = clasificados3[elegido];
        gruposlocal[partidosarmados] = grupohead;
        gruposvisita[partidosarmados] = grupoindterceros[elegido];
        usadostercero[elegido] = 1;
        partidosarmados = partidosarmados + 1;
    }

    // (2) 4 cabezas restantes vs 4 peores segundos
    for (int i = 8; i < 12; i = i + 1) {
        int grupohead = i;
        int elegido = -1;

        for (int s = 0; s < 4; s = s + 1) {
            int idseg = peores4[s];
            if (usadossegundo[idseg] == 1) {
                continue;
            }
            if (idseg != grupohead) {
                elegido = idseg;
                break;
            }
        }

        if (elegido < 0) {
            for (int s = 0; s < 4; s = s + 1) {
                int idseg = peores4[s];
                if (usadossegundo[idseg] != 1) {
                    elegido = idseg;
                    break;
                }
            }
        }

        locales[partidosarmados] = clasificados1[i];
        visitas[partidosarmados] = clasificados2[elegido];
        gruposlocal[partidosarmados] = grupohead;
        gruposvisita[partidosarmados] = elegido;
        usadossegundo[elegido] = 1;
        partidosarmados = partidosarmados + 1;
    }

    // (3) el resto de segundos se enfrentan entre si
    int segundosrestantes[8];
    int cantrestantes = 0;
    for (int i = 0; i < 12; i = i + 1) {
        if (usadossegundo[i] == 0) {
            segundosrestantes[cantrestantes] = i;
            cantrestantes = cantrestantes + 1;
        }
    }

    int usadorestante[8];
    for (int i = 0; i < 8; i = i + 1) {
        usadorestante[i] = 0;
    }

    for (int i = 0; i < cantrestantes; i = i + 1) {
        if (usadorestante[i] == 1) {
            continue;
        }

        int jpareja = -1;
        for (int j = i + 1; j < cantrestantes; j = j + 1) {
            if (usadorestante[j] == 1) {
                continue;
            }
            if (segundosrestantes[i] != segundosrestantes[j]) {
                jpareja = j;
                break;
            }
        }

        if (jpareja < 0) {
            for (int j = i + 1; j < cantrestantes; j = j + 1) {
                if (usadorestante[j] == 0) {
                    jpareja = j;
                    break;
                }
            }
        }

        if (jpareja >= 0) {
            locales[partidosarmados] = clasificados2[segundosrestantes[i]];
            visitas[partidosarmados] = clasificados2[segundosrestantes[jpareja]];
            gruposlocal[partidosarmados] = segundosrestantes[i];
            gruposvisita[partidosarmados] = segundosrestantes[jpareja];
            usadorestante[i] = 1;
            usadorestante[jpareja] = 1;
            partidosarmados = partidosarmados + 1;
        }
    }

    // ajuste final por si quedo algun cruce del mismo grupo
    for (int i = 0; i < partidosarmados; i = i + 1) {
        if (gruposlocal[i] != gruposvisita[i]) {
            continue;
        }
        for (int j = i + 1; j < partidosarmados; j = j + 1) {
            if (gruposlocal[i] != gruposvisita[j] && gruposlocal[j] != gruposvisita[i]) {
                string tv = visitas[i];
                visitas[i] = visitas[j];
                visitas[j] = tv;
                int tg = gruposvisita[i];
                gruposvisita[i] = gruposvisita[j];
                gruposvisita[j] = tg;
                break;
            }
        }
    }

    if (partidosdieciseisavos != 0) {
        delete[] partidosdieciseisavos;
    }
    cantdieciseisavos = partidosarmados;
    partidosdieciseisavos = new partido[cantdieciseisavos];

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        partidosdieciseisavos[i] = partido(locales[i], visitas[i]);
    }
}

void Torneo::mostrardieciseisavos() const {
    cout << "llave dieciseisavos de final" << endl;
    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        cout << "  partido " << (i + 1) << ": "
             << partidosdieciseisavos[i].getlocal()
             << " vs "
             << partidosdieciseisavos[i].getvisita() << endl;
    }
}

string Torneo::resolverganadoreliminacion(const Repositorio& repo, string local, string visita, int& goleslocal, int& golesvisita) const {
    if (goleslocal > golesvisita) {
        return local;
    }
    if (golesvisita > goleslocal) {
        return visita;
    }

    int ilocal = buscarindiceequiporepo(repo, local);
    int ivisita = buscarindiceequiporepo(repo, visita);

    double problocal = 0.5;

    if (ilocal >= 0 && ivisita >= 0) {
        int rankinglocal = repo.getranking(ilocal);
        int rankingvisita = repo.getranking(ivisita);
        int diferencia = rankingvisita - rankinglocal;

        double sesgo = double(diferencia) / 220.0;
        if (sesgo > 0.35) {
            sesgo = 0.35;
        }
        if (sesgo < -0.35) {
            sesgo = -0.35;
        }

        problocal = 0.5 + sesgo;
        if (problocal < 0.1) {
            problocal = 0.1;
        }
        if (problocal > 0.9) {
            problocal = 0.9;
        }
    }

    double r = double(rand() % 10000) / 10000.0;
    if (r < problocal) {
        goleslocal = goleslocal + 1;
        return local;
    }

    golesvisita = golesvisita + 1;
    return visita;
}

bool Torneo::simularfasesfinales(const Repositorio& repo) {
    if (partidosdieciseisavos == 0 || cantdieciseisavos <= 0) {
        return false;
    }

    finalessimuladas = false;

    if (partidosoctavos != 0) {
        delete[] partidosoctavos;
        partidosoctavos = 0;
    }
    if (partidoscuartos != 0) {
        delete[] partidoscuartos;
        partidoscuartos = 0;
    }
    if (partidossemis != 0) {
        delete[] partidossemis;
        partidossemis = 0;
    }

    string* ganadores16 = new string[cantdieciseisavos];

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        string local = partidosdieciseisavos[i].getlocal();
        string visita = partidosdieciseisavos[i].getvisita();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        partidosdieciseisavos[i].setresultado(goleslocal, golesvisita);
        ganadores16[i] = ganador;
    }

    cantoctavos = cantdieciseisavos / 2;
    partidosoctavos = new partido[cantoctavos];

    for (int i = 0; i < cantoctavos; i = i + 1) {
        partidosoctavos[i] = partido(ganadores16[i * 2], ganadores16[i * 2 + 1]);
    }

    delete[] ganadores16;

    string* ganadores8 = new string[cantoctavos];

    for (int i = 0; i < cantoctavos; i = i + 1) {
        string local = partidosoctavos[i].getlocal();
        string visita = partidosoctavos[i].getvisita();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        partidosoctavos[i].setresultado(goleslocal, golesvisita);
        ganadores8[i] = ganador;
    }

    cantcuartos = cantoctavos / 2;
    partidoscuartos = new partido[cantcuartos];

    for (int i = 0; i < cantcuartos; i = i + 1) {
        partidoscuartos[i] = partido(ganadores8[i * 2], ganadores8[i * 2 + 1]);
    }

    delete[] ganadores8;

    string* ganadores4 = new string[cantcuartos];

    for (int i = 0; i < cantcuartos; i = i + 1) {
        string local = partidoscuartos[i].getlocal();
        string visita = partidoscuartos[i].getvisita();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        partidoscuartos[i].setresultado(goleslocal, golesvisita);
        ganadores4[i] = ganador;
    }

    cantsemis = cantcuartos / 2;
    partidossemis = new partido[cantsemis];

    for (int i = 0; i < cantsemis; i = i + 1) {
        partidossemis[i] = partido(ganadores4[i * 2], ganadores4[i * 2 + 1]);
    }

    delete[] ganadores4;

    string ganadores2[2];
    string perdedores2[2];

    for (int i = 0; i < cantsemis; i = i + 1) {
        string local = partidossemis[i].getlocal();
        string visita = partidossemis[i].getvisita();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        partidossemis[i].setresultado(goleslocal, golesvisita);

        ganadores2[i] = ganador;
        if (ganador == local) {
            perdedores2[i] = visita;
        } else {
            perdedores2[i] = local;
        }
    }

    partidofinal = partido(ganadores2[0], ganadores2[1]);
    partidotercero = partido(perdedores2[0], perdedores2[1]);

    {
        string local = partidofinal.getlocal();
        string visita = partidofinal.getvisita();
        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        int goleslocal = redondeargolespartido(calcularlambdapartido(gflocal, gcvisita));
        int golesvisita = redondeargolespartido(calcularlambdapartido(gfvisita, gclocal));
        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);
        partidofinal.setresultado(goleslocal, golesvisita);

        if (ganador == local) {
            equipocampeon = local;
            equiposubcampeon = visita;
        } else {
            equipocampeon = visita;
            equiposubcampeon = local;
        }
    }

    {
        string local = partidotercero.getlocal();
        string visita = partidotercero.getvisita();
        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        int goleslocal = redondeargolespartido(calcularlambdapartido(gflocal, gcvisita));
        int golesvisita = redondeargolespartido(calcularlambdapartido(gfvisita, gclocal));
        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);
        partidotercero.setresultado(goleslocal, golesvisita);

        if (ganador == local) {
            equipotercero = local;
            equipocuarto = visita;
        } else {
            equipotercero = visita;
            equipocuarto = local;
        }
    }

    finalessimuladas = true;
    return true;
}

void Torneo::mostrarfasesfinales() const {
    if (finalessimuladas == false) {
        cout << "fases finales: no simuladas" << endl;
        return;
    }

    cout << "resultados dieciseisavos" << endl;
    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        cout << "  " << partidosdieciseisavos[i].getlocal() << " "
             << partidosdieciseisavos[i].getgoleslocal() << " - "
             << partidosdieciseisavos[i].getgolesvisita() << " "
             << partidosdieciseisavos[i].getvisita() << endl;
    }

    cout << "resultados octavos" << endl;
    for (int i = 0; i < cantoctavos; i = i + 1) {
        cout << "  " << partidosoctavos[i].getlocal() << " "
             << partidosoctavos[i].getgoleslocal() << " - "
             << partidosoctavos[i].getgolesvisita() << " "
             << partidosoctavos[i].getvisita() << endl;
    }

    cout << "resultados cuartos" << endl;
    for (int i = 0; i < cantcuartos; i = i + 1) {
        cout << "  " << partidoscuartos[i].getlocal() << " "
             << partidoscuartos[i].getgoleslocal() << " - "
             << partidoscuartos[i].getgolesvisita() << " "
             << partidoscuartos[i].getvisita() << endl;
    }

    cout << "resultados semifinales" << endl;
    for (int i = 0; i < cantsemis; i = i + 1) {
        cout << "  " << partidossemis[i].getlocal() << " "
             << partidossemis[i].getgoleslocal() << " - "
             << partidossemis[i].getgolesvisita() << " "
             << partidossemis[i].getvisita() << endl;
    }

    cout << "tercer puesto" << endl;
    cout << "  " << partidotercero.getlocal() << " "
         << partidotercero.getgoleslocal() << " - "
         << partidotercero.getgolesvisita() << " "
         << partidotercero.getvisita() << endl;

    cout << "final" << endl;
    cout << "  " << partidofinal.getlocal() << " "
         << partidofinal.getgoleslocal() << " - "
         << partidofinal.getgolesvisita() << " "
         << partidofinal.getvisita() << endl;

    cout << "podio" << endl;
    cout << "  campeon: " << equipocampeon << endl;
    cout << "  subcampeon: " << equiposubcampeon << endl;
    cout << "  tercero: " << equipotercero << endl;
    cout << "  cuarto: " << equipocuarto << endl;
}
